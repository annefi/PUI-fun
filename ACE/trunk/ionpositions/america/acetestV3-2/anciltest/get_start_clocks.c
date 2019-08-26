/* Compute ACEepoch and SCclock for first second of each day since ACE launch
 *
 * Output: For each day - YEAR Day-of-year ACEepoch SCclock
 *
 * Andrew Davis, Jan 2002
 *
 */

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "hdfi.h"

/* offset in seconds between ACEepoch and UNIXepoch */
#define TMOFFSET_70_96 820454400

/* offset in seconds between scclock and ACEepoch (at ACE launch) */
#define TMOFFSET_96_ACEPOCH 52069705.604

/* ACE EPOCH at beginning of 1997-237 (ACE Launch day) */
/* including leap second */
#define STARTACEEPOCH 52012801

/* max size of array holding leapsecond info */
#define MAXLEAPSECS 20

/* index of num of days in year. Expect ACE mission will end before 2030 */
/* note: leap-years not set before 1996...don't care */
int16 daysinyear[2030];

/* the ACEepoch time of all leap seconds inserted since ACEepoch */
/* It is assumed that there will never be any deleted leap seconds */
float64 ACEepoch_leapsecs[MAXLEAPSECS];


int main(argc, argv)
int argc;
char *argv[];
{
  int ii;
  struct tm tstruct;
  time_t tval_tmp;
  float64 scclock, oldscclock;
  float64 ACEepoch, ACEepochEnd;

  int32 init_ACEancillary();
  float64 SCclock_to_ACEepoch();
  float64 ACEepoch_to_SCclock();
  float64 GetACEepochEnd();
  void init_daysinyear();
  int init_leapseconds();
      

  if (argc!=2) {
      fprintf(stderr,"Usage: %s hdf_file\n",argv[0]);
            exit(1);
  }

  init_daysinyear();
  if (init_leapseconds() != 0)
     exit(-1);

  /* load the ACE ancillary data from the HDF file */
  /* init_ACEancillary() exits if there is an error */
  init_ACEancillary(argv[1]);

  /* compute ACEepoch for beginning of today */
  ACEepochEnd = GetACEepochEnd();
  /* Add 10 days */
  ACEepochEnd += 10.0 * 86400.0;

  ACEepoch = STARTACEEPOCH;
  oldscclock = -100000.0;
  ii = 1;  /* already included first leap-sec in  STARTACEEPOCH */

  fprintf(stdout,"Year  doy  ACEepochBegin  SCclockBegin\n");

  while(ACEepoch <= ACEepochEnd) {
     tval_tmp = (time_t)ACEepoch + TMOFFSET_70_96;
     gmtime_r(&tval_tmp, &tstruct);
     scclock = ACEepoch_to_SCclock(ACEepoch);
     if (scclock < 0.0) scclock = oldscclock + 86400.0;
     if (scclock > 0.0)
        fprintf(stdout,"%4d  %3d  %11d  %10d\n",
	     1900+tstruct.tm_year, 1 + tstruct.tm_yday, (int)ACEepoch, (int)(floor(scclock+0.5)));
     ACEepoch += 86400;
     /* adjust for added leap seconds */
     if((ACEepoch >= ACEepoch_leapsecs[ii])&&(ACEepoch_leapsecs[ii] > 0.0)) {
        ACEepoch += 1.0;
	ii++;
     }
     oldscclock = scclock;
  }
/*  fprintf(stdout,"%.1f\n",ACEepochEnd); */

  exit(0);
}


void init_daysinyear()
{
   int ii;

   for(ii=0;ii<2030;ii++)
      daysinyear[ii]=365;
   /* now assign leapyears where we care, worry about leap-seconds */
   /* some other time... */
   daysinyear[1996]=366;
   daysinyear[2000]=366;
   daysinyear[2004]=366;
   daysinyear[2008]=366;
   daysinyear[2012]=366;
   daysinyear[2016]=366;
   daysinyear[2020]=366;
   daysinyear[2024]=366;
   daysinyear[2028]=366;
}

int init_leapseconds()
{
   int ii;
   FILE *flist;
   char filenm[100];

   sprintf(filenm,"%s","/users/asc/aceprog/leap_secs.db");
   if((flist=fopen(filenm,"r"))==NULL) {
      fprintf(stderr,"\ninit_leapseconds: Could not open leap_secs db file %s\n\n",filenm);
      return(-1);
   }
   for(ii=0;ii<MAXLEAPSECS;ii++)
      ACEepoch_leapsecs[ii] = -1.0;

   for(ii=0;ii<MAXLEAPSECS;ii++) {
      fscanf(flist,"%lf %*d %*d %*d %*s\n",&(ACEepoch_leapsecs[ii]));
      if (ACEepoch_leapsecs[ii] < 0.0) {
         break;
      }
   }

   fclose(flist);
   return(0);
}

/* compute ACEepoch for the beginning of the current day */
float64 GetACEepochEnd()
{
   int ii;
   float64 End;

   time_t SecsSince1970,temp1,temp2,diff;
   struct tm tstructUTC,tstructLocal;

   /* seconds since Jan 1 1970 */
   SecsSince1970 = time(NULL);

   /* populate time structures with values for the current time */
   gmtime_r(&SecsSince1970, &tstructUTC);
   localtime_r(&SecsSince1970, &tstructLocal);

   /* find difference in seconds between localtime and UTC */
   temp1 = mktime(&tstructUTC);
   temp2 = mktime(&tstructLocal);
   diff = temp1 - temp2;

   /* set local time structure values to beginning of the day */
   tstructLocal.tm_hour = 0;
   tstructLocal.tm_min = 0;
   tstructLocal.tm_sec = 0;

   /* seconds since Jan 1 1970 to beginning of current day */
   SecsSince1970 = mktime(&tstructLocal);

   End = (float64)(SecsSince1970 - TMOFFSET_70_96) - diff;

   for(ii=0;ii<MAXLEAPSECS;ii++) {
      if(ACEepoch_leapsecs[ii] <= 0.0 ) break;
      if(End >= ACEepoch_leapsecs[ii])
         End += 1.0;
   }

   return(End);
}
