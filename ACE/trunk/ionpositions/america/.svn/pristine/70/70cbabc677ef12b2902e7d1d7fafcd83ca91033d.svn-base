/* $Id: ancil_subs.c,v 1.41 2002/09/09 22:49:35 asc Exp $ */

#include <math.h>
#include <memory.h>
#include <string.h>
#include <time.h>
#include "hdfi.h"           /* using HDF variable definitions */
#include "aosr.h"
#include "ccr.h"
#include "df.h"
#include "mfhdf.h"

#define AA_ERR -1         /* used with bad data */
#define AA_GOOD 0         /* used with normal data */
#define AA_POOR 1         /* used for segments when there has been a */
                          /* spacecraft maneuver */ 

#define SC_ACE_epoch_offset 52069705.604 /*UTC time start of scclock from */ 
					   /* Jan 1 1996, including leap second */
					   /* which occurred mid-year 1997 */

/* offset in seconds between ACEepoch and UNIXepoch (1970), */
/* not including leap seconds */
#define TMOFFSET_70_96 820454400

/* These are the functional routines for ACE ancillary data */
/* They include */
/*    SCclock_to_ACEepoch() : Spacecraft clock to ACE epoch (Jan 1 1996 UTC) */
/*    ACEepoch_to_SCclock() : ACE epoch to SC clock */
/*    ACE_attitude_RTN()    : attitide in RTN coordinates from SC clock */
/*    ACE_position_J2GCI()  : position in J2000 GCI coordinates from SC clock */
/*    ACE_position_GSE()    : position in GSE coordinates from SC clock */
/*    ACE_velocity_GSE()    : velocity in GSE coordinates from SC clock */

/*    ACE_position_GSM()    : position in GSM coordinates from SC clock */
/*    ACE_velocity_GSM()    : velocity in GSM coordinates from SC clock */
/*       Note: the GSM routines above use linear interpolation
               for times between AOSR reports - not appropriate for
	       a coordinate system that wiggles on a 24-hour period!
*/	       
/*    ACE_aosr()            : complete aosr data structure for given scclock */
/*    dump_ascii_aosr()     : print all attitude/orbit records in ascii */
/*    dump_ascii_ccr()      : print all clock cal records in ascii */
/*    dump_ascii_ccr_oneliner()      : print all clock cal records in ascii,*/
                                        /* all data for each record one one line */

/* The SCclock is being used as a float64 even though it originally exists */
/* as a uint32.  This is because some of the functions (ACEepoch, spin phase)*/
/* will require subsecond resolution.  The other functions are using the */
/* floating point values for consistency. */

/* return values of -1 indicate an error */

/* These functions will require access to lookup tables.  As a result */
/* there are initialization functions which will load the tables into memory.*/
/* They are designed to be called once before the results functions are used.*/

/* pointer to table of attitude-orbit structures */
static struct attorb_entry *ao; 

/* pointer to table of clock-calibration structures */
static struct ccr_entry *cc;

/* number of records in the above tables */
static int32 num_rec_aosr,num_rec_ccr;

int32 init_acc_aosr(int32 hdf_fp, int32 sd_id, char *access_mode);
int32 init_acc_ccr(int32 hdf_fp, int32 sd_id, char *access_mode);
int32 read_aosr(struct attorb_entry *attorb_entry_struc, int32 recnum_rd);
int32 read_ccr(struct ccr_entry *ccr_entry_struc, int32 recnum_rd);
int32 ACE_aosr(float64 scclock, struct attorb_entry *aosr_struct);
void close_rd_aosr();
void close_rd_ccr();

int32 init_ACEancillary(char *filenm)
{
   int32 hdf_fp, sd_id;
   int ii,retval;
   static int done=0;

   /* do nothing if called more than once */
   if(done==1) {
      fprintf(stderr,"init_ACEancillary: please call me just once...continuing\n");
      return(AA_GOOD);
   }

   if (filenm == NULL) {
     fprintf(stderr, "init_ACEancillary: pass me a filename parameter!\n");
     exit(AA_ERR);
   }

   if ((hdf_fp=Hopen(filenm, DFACC_RDONLY, 0)) == FAIL) {
   //if ((hdf_fp=Hopen("ace_att_gse_23May2003.txt", 1, 0)) == -1) {
     fprintf(stderr, "Hopen: could not open ancil hdf file %s\n",filenm);
     exit(AA_ERR);
   }
   Vstart(hdf_fp);

   if ((sd_id=SDstart(filenm, DFACC_RDONLY)) == FAIL) {
     fprintf(stderr, "SDstart: could not open ancil hdf file %s\n",filenm);
     exit(AA_ERR);
   }

   num_rec_aosr = init_acc_aosr(hdf_fp, sd_id,"r");
   if(num_rec_aosr<=0) {
     fprintf(stderr,"init_ACEancillary: no aosr data!\n");
     exit(AA_ERR);
   }
   num_rec_ccr = init_acc_ccr(hdf_fp, sd_id,"r");
   if(num_rec_ccr<=0) {
     fprintf(stderr,"init_ACEancillary: no ccr data!\n");
     exit(AA_ERR);
   }

   if((ao =
   (struct attorb_entry *)malloc(num_rec_aosr * sizeof(struct attorb_entry)))
   == NULL) {
      fprintf(stderr, "init_ACEancillary: mem alloc for aosr table failed!\n");
      exit(AA_ERR);
   }

   if((cc =
   (struct ccr_entry *)malloc(num_rec_ccr * sizeof(struct ccr_entry)))
   == NULL) {
      fprintf(stderr, "init_ACEancillary: mem alloc for ccr table failed!\n");
      exit(AA_ERR);
   }

   /* fprintf(stdout,"%d   %d\n",num_rec_aosr, num_rec_ccr);  */

   for(ii=0;ii<num_rec_aosr;ii++) {
      if((retval= read_aosr(ao + ii,ii))==FAIL) {
         fprintf(stderr, "init_ACEancillary: aosr table read failed!\n");
         exit(AA_ERR);
      }
      /* printf("time = %u\n",ao[ii].sctime); */
   }

   for(ii=0;ii<num_rec_ccr;ii++) {
      if((retval= read_ccr(cc + ii,ii))==FAIL) {
         fprintf(stderr, "init_ACEancillary: ccr table read failed!\n");
         exit(AA_ERR);
      }
      /* printf("start = %u\n",cc[ii].start); */  
   }

   /* all done, close HDF file */

   close_rd_aosr();
   close_rd_ccr();
   Vend(hdf_fp);
   if (SDend(sd_id)==FAIL) {
      fprintf(stderr, "SDend: could not close hdf file\n");
      exit(AA_ERR);
   }      
   if (Hclose(hdf_fp)==FAIL) {
      fprintf(stderr, "Hclose: could not close hdf file\n");
      exit(AA_ERR);
   }

   done = 1;
   return(AA_GOOD); 
}

/* returns seconds since Jan 1, 1996 UTC (ACE epoch), */
/* at the specified scclock using a modified binary search. */

float64 SCclock_to_ACEepoch( float64 scclock ) 
{
   int32   low, high, mid;
   float64 alpha, slope, offset;
   static  int32 last_case_value=-1,first;

   if(cc==NULL) {
      fprintf(stderr, "SCclock_to_ACEepoch: Error! Call init_ACEancillary() to load ancil database\n");
      exit(AA_ERR);
   }

   /* scclock has a bad value */
   if ( scclock < 0.0 ) {
      return ((float64)-1.0) ;
   }

   /* scclock value is before the range of values */
   if ( scclock < cc[0].start ) {
      return (scclock + (float64)SC_ACE_epoch_offset );
   }

   /* scclock value is after the range of values then
         extrapolate, using the most last CCR data available */
   if ( scclock > cc[num_rec_ccr-1].end ) {
   return((scclock * cc[num_rec_ccr-1].slope) + cc[num_rec_ccr-1].offset
	  + (float64)SC_ACE_epoch_offset );
   }

   /* scclock is in the range of values between cc[0].start and 
                                cc[num_rec_ccr-1].end */
   first = 1;
   low = 0; high = num_rec_ccr-1;
   while(low<=high) {

     if (first == 0) mid = (low+high)/2;
     else {
       first = 0;
       if (last_case_value == -1) mid = (low+high)/2;
       else mid = last_case_value;
     }

     if(scclock < cc[mid-1].end) high = mid-1; 
     else if (scclock > cc[mid].end) low = mid+1;
     else {
       last_case_value = mid;
       /* for a twentyfour range */ 
       if (scclock >= cc[mid].start && scclock <= cc[mid].end) {
/*	 fprintf(stderr,"%.8f   %.3f\n",cc[mid].slope,cc[mid].offset); */
	 return((scclock * cc[mid].slope) + cc[mid].offset
		+ (float64)SC_ACE_epoch_offset );
       }
       /* there are one or more missing CCRs so we must linear interpolate */
       else {
	 alpha = (scclock-cc[mid-1].end)/(cc[mid].start-cc[mid-1].end);
         slope  = alpha*cc[mid].slope +(1.-alpha)*cc[mid-1].slope;
         offset = alpha*cc[mid].offset+(1.-alpha)*cc[mid-1].offset;
/*	 fprintf(stderr,"interp: %.8f   %.3f\n",slope,offset);  */
	 return((scclock*slope)+offset+(float64)SC_ACE_epoch_offset);
       }
     }
   }
   return(-1.);
}

/* returns scclock at the specified ACE epoch (secs since Jan 1, 1996 UTC) */
float64 ACEepoch_to_SCclock( float64 ACEepoch ) 
{
  float64 scclock, ACEepoch2, diff, diff2;
  int i;
  static int imax=20;
  float64 SCclock_to_ACEepoch();

  /* time must be after ACE epoch */
  if(ACEepoch<(float64)SC_ACE_epoch_offset) return (-1.);

  scclock = ACEepoch-(float64)SC_ACE_epoch_offset;

  i=0;
  for(;;){
    i++;
    if(i>imax) break;
    ACEepoch2 = SCclock_to_ACEepoch(scclock); 
    diff =  ACEepoch2 - ACEepoch;
    scclock = scclock - 0.5*diff;
    diff2=sqrt(diff*diff);
    if(diff2 < 1.e-3) return (scclock);
  }
  if (diff2 < 0.2)
     return(scclock);
  else
     return(-1.);
}

/* returns the attitude in RTN coordinates at the specified scclock */
/* solution for attitude lies on the unit sphere */

/* Note: this version is very simple-minded. It assumes the aosr records */
/* are time-ordered, and it does not implement any intelligent search */
/* algorithm */

/* Note: Returns -1 if scclock is out of bounds */
/* Note: Returns +1 (AA_POOR) if the state flag indicates */
/* a maneuver was in progress */

/* linear interpolation routines */

int32 ACE_attitude_RTN( float64 scclock, float64 *att_rtn )
{
   int32 ii;
   float64 range01,crange01,a1,a2,a3,sum;

   if(ao==NULL) {
      fprintf(stderr, "ACE_attitude_RTN: Error! Call init_ACEancillary() to load ancil database\n");
      exit(AA_ERR);
   }

   if ( scclock < ao[0].sctime) {
      att_rtn[0]=ao[0].att_RTN[0];
      att_rtn[1]=ao[0].att_RTN[1];
      att_rtn[2]=ao[0].att_RTN[2];
      return(AA_ERR);
   }
   
   for(ii=0;ii<num_rec_aosr;ii++) {
      if (scclock<=ao[ii].sctime) {
         
        /* test for bad RTN data */
	if(ao[ii].att_RTN[0]==0.){
          att_rtn[0]=ao[ii].att_RTN[0];
          att_rtn[1]=ao[ii].att_RTN[1];
          att_rtn[2]=ao[ii].att_RTN[2];
          return(AA_ERR);
        }

	if (scclock == ao[ii].sctime) {
          att_rtn[0]=ao[ii].att_RTN[0];
          att_rtn[1]=ao[ii].att_RTN[1];
          att_rtn[2]=ao[ii].att_RTN[2];
	}
	else {
          range01 =(ao[ii].sctime-scclock)/(ao[ii].sctime-ao[ii-1].sctime);
	  crange01 = 1.-range01;
          a1=range01*ao[ii-1].att_RTN[0]+crange01*ao[ii].att_RTN[0];
          a2=range01*ao[ii-1].att_RTN[1]+crange01*ao[ii].att_RTN[1];
          a3=range01*ao[ii-1].att_RTN[2]+crange01*ao[ii].att_RTN[2];
	  sum=sqrt(pow(a1,2)+pow(a2,2)+pow(a3,2));
          att_rtn[0]=a1/sum;
          att_rtn[1]=a2/sum;
          att_rtn[2]=a3/sum;
	}
	if (ao[ii-1].state == 3 && ao[ii].state == 4) 
	  return(AA_POOR);
	else
	  return(AA_GOOD);
      }
   }
   att_rtn[0]=ao[num_rec_aosr-1].att_RTN[0];
   att_rtn[1]=ao[num_rec_aosr-1].att_RTN[1];
   att_rtn[2]=ao[num_rec_aosr-1].att_RTN[2];
   return(AA_ERR);
}

/* returns the position (km) in J2000 GCI coordinates at the specified scclock */

/* Note: this version is very simple-minded. It assumes the aosr records */
/* are time-ordered, and it does not implement any intelligent search */
/* algorithm */
/* Note: Returns -1 if scclock is out of bounds */

/* linear interpolation routines */

int32 ACE_position_J2GCI( float64 scclock, float64 *posgci ) 
{
  int32 ii;
  float64 range01,crange01;

   if(ao==NULL) {
      fprintf(stderr, "ACE_position_J2GCI: Error! Call init_ACEancillary() to load ancil database\n");
      exit(AA_ERR);
   }

  if (scclock < ao[0].sctime) {
      posgci[0]=ao[0].pos_J2GCI[0];
      posgci[1]=ao[0].pos_J2GCI[1];
      posgci[2]=ao[0].pos_J2GCI[2];
      return(AA_ERR);
   }
  for(ii=0;ii<num_rec_aosr;ii++) {
      if (scclock<=ao[ii].sctime) {
	if (scclock == ao[ii].sctime) {
          posgci[0]=ao[ii].pos_J2GCI[0];
          posgci[1]=ao[ii].pos_J2GCI[1];
          posgci[2]=ao[ii].pos_J2GCI[2];
	}
	else {
          range01 =(ao[ii].sctime-scclock)/(ao[ii].sctime-ao[ii-1].sctime);
	  crange01 = 1.-range01;
          posgci[0]=range01*ao[ii-1].pos_J2GCI[0]+crange01*ao[ii].pos_J2GCI[0];
          posgci[1]=range01*ao[ii-1].pos_J2GCI[1]+crange01*ao[ii].pos_J2GCI[1];
          posgci[2]=range01*ao[ii-1].pos_J2GCI[2]+crange01*ao[ii].pos_J2GCI[2];
	}
          return(AA_GOOD);
      }
   }
   posgci[0]=ao[num_rec_aosr-1].pos_J2GCI[0];
   posgci[1]=ao[num_rec_aosr-1].pos_J2GCI[1];
   posgci[2]=ao[num_rec_aosr-1].pos_J2GCI[2];
   return(AA_ERR);
}


/* returns the position (km) in GSE coordinates at the specified scclock */

/* Note: this version is very simple-minded. It assumes the aosr records */
/* are time-ordered, and it does not implement any intelligent search */
/* algorithm */
/* Note: Returns -1 if scclock is out of bounds */

/* linear interpolation routines */

int32 ACE_position_GSE( float64 scclock, float64 *pos_gse ) 
{
  int32 ii;
  float64 range01,crange01;

   if(ao==NULL) {
      fprintf(stderr, "ACE_position_GSE: Error! Call init_ACEancillary() to load ancil database\n");
      exit(AA_ERR);
   }

  if (scclock < ao[0].sctime) {
      pos_gse[0]=ao[0].pos_GSE[0];
      pos_gse[1]=ao[0].pos_GSE[1];
      pos_gse[2]=ao[0].pos_GSE[2];
      return(AA_ERR);
   }
  for(ii=0;ii<num_rec_aosr;ii++) {
      if (scclock<=ao[ii].sctime) {
	if (scclock == ao[ii].sctime) {
          pos_gse[0]=ao[ii].pos_GSE[0];
          pos_gse[1]=ao[ii].pos_GSE[1];
          pos_gse[2]=ao[ii].pos_GSE[2];
	}
	else {
          range01 =(ao[ii].sctime-scclock)/(ao[ii].sctime-ao[ii-1].sctime);
	  crange01 = 1.-range01;
          pos_gse[0]=range01*ao[ii-1].pos_GSE[0]+crange01*ao[ii].pos_GSE[0];
          pos_gse[1]=range01*ao[ii-1].pos_GSE[1]+crange01*ao[ii].pos_GSE[1];
          pos_gse[2]=range01*ao[ii-1].pos_GSE[2]+crange01*ao[ii].pos_GSE[2];
	}
          return(AA_GOOD);
      }
   }
   pos_gse[0]=ao[num_rec_aosr-1].pos_GSE[0];
   pos_gse[1]=ao[num_rec_aosr-1].pos_GSE[1];
   pos_gse[2]=ao[num_rec_aosr-1].pos_GSE[2];
   return(AA_ERR);
}

/* returns the velocity (km/s) in GSE coordinates at the specified scclock */
/* linear interpolation routines */

int32 ACE_velocity_GSE( float64 scclock, float64 *vel_gse ) 
{
   int32 ii;
   float64 range01,crange01;

   if(ao==NULL) {
      fprintf(stderr, "ACE_velocity_GSE: Error! Call init_ACEancillary() to load ancil database\n");
      exit(AA_ERR);
   }

   if (scclock < ao[0].sctime) {
      vel_gse[0]=ao[0].vel_GSE[0];
      vel_gse[1]=ao[0].vel_GSE[1];
      vel_gse[2]=ao[0].vel_GSE[2];
      return(AA_ERR);
   }
   for(ii=0;ii<num_rec_aosr;ii++) {
     if (scclock<=ao[ii].sctime) {
       if (scclock == ao[ii].sctime) {
         vel_gse[0]=ao[ii].vel_GSE[0];
         vel_gse[1]=ao[ii].vel_GSE[1];
         vel_gse[2]=ao[ii].vel_GSE[2];
       }
       else {
         range01 =(ao[ii].sctime-scclock)/(ao[ii].sctime-ao[ii-1].sctime);
	 crange01 = 1.-range01;
         vel_gse[0]=range01*ao[ii-1].vel_GSE[0]+crange01*ao[ii].vel_GSE[0];
         vel_gse[1]=range01*ao[ii-1].vel_GSE[1]+crange01*ao[ii].vel_GSE[1];
         vel_gse[2]=range01*ao[ii-1].vel_GSE[2]+crange01*ao[ii].vel_GSE[2];
       }
       return(AA_GOOD);
     }
   }   
    vel_gse[0]=ao[num_rec_aosr-1].vel_GSE[0];
    vel_gse[1]=ao[num_rec_aosr-1].vel_GSE[1];
    vel_gse[2]=ao[num_rec_aosr-1].vel_GSE[2];
    return(AA_ERR);
}

/* New routines for gsm coordinates */
/* SJF 12/14/99 */
/* Uses linear interpolation - not appropriate!? */

int32 ACE_position_GSM( float64 scclock, float64 *pos_gsm ) 
{
  int32 ii;
  float64 range01,crange01;

   if(ao==NULL) {
      fprintf(stderr, "ACE_position_GSM: Error! Call init_ACEancillary() to load ancil database\n");
      exit(AA_ERR);
   }

  if (scclock < ao[0].sctime) {
      pos_gsm[0]=ao[0].pos_GSM[0];
      pos_gsm[1]=ao[0].pos_GSM[1];
      pos_gsm[2]=ao[0].pos_GSM[2];
      return(AA_ERR);
   }
  for(ii=0;ii<num_rec_aosr;ii++) {
      if (scclock<=ao[ii].sctime) {
	if (scclock == ao[ii].sctime) {
          pos_gsm[0]=ao[ii].pos_GSM[0];
          pos_gsm[1]=ao[ii].pos_GSM[1];
          pos_gsm[2]=ao[ii].pos_GSM[2];
	}
	else {
          range01 =(ao[ii].sctime-scclock)/(ao[ii].sctime-ao[ii-1].sctime);
	  crange01 = 1.-range01;
          pos_gsm[0]=range01*ao[ii-1].pos_GSM[0]+crange01*ao[ii].pos_GSM[0];
          pos_gsm[1]=range01*ao[ii-1].pos_GSM[1]+crange01*ao[ii].pos_GSM[1];
          pos_gsm[2]=range01*ao[ii-1].pos_GSM[2]+crange01*ao[ii].pos_GSM[2];
	}
          return(AA_GOOD);
      }
   }
   pos_gsm[0]=ao[num_rec_aosr-1].pos_GSM[0];
   pos_gsm[1]=ao[num_rec_aosr-1].pos_GSM[1];
   pos_gsm[2]=ao[num_rec_aosr-1].pos_GSM[2];
   return(AA_ERR);
}

/* returns the velocity (km/s) in GSM coordinates at the specified scclock */
/* Uses linear interpolation routines - not appropriate !? */

int32 ACE_velocity_GSM( float64 scclock, float64 *vel_gsm ) 
{
   int32 ii;
   float64 range01,crange01;

   if(ao==NULL) {
      fprintf(stderr, "ACE_velocity_GSM: Error! Call init_ACEancillary() to load ancil database\n");
      exit(AA_ERR);
   }

   if (scclock < ao[0].sctime) {
      vel_gsm[0]=ao[0].vel_GSM[0];
      vel_gsm[1]=ao[0].vel_GSM[1];
      vel_gsm[2]=ao[0].vel_GSM[2];
      return(AA_ERR);
   }
   for(ii=0;ii<num_rec_aosr;ii++) {
     if (scclock<=ao[ii].sctime) {
       if (scclock == ao[ii].sctime) {
         vel_gsm[0]=ao[ii].vel_GSM[0];
         vel_gsm[1]=ao[ii].vel_GSM[1];
         vel_gsm[2]=ao[ii].vel_GSM[2];
       }
       else {
         range01 =(ao[ii].sctime-scclock)/(ao[ii].sctime-ao[ii-1].sctime);
	 crange01 = 1.-range01;
         vel_gsm[0]=range01*ao[ii-1].vel_GSM[0]+crange01*ao[ii].vel_GSM[0];
         vel_gsm[1]=range01*ao[ii-1].vel_GSM[1]+crange01*ao[ii].vel_GSM[1];
         vel_gsm[2]=range01*ao[ii-1].vel_GSM[2]+crange01*ao[ii].vel_GSM[2];
       }
       return(AA_GOOD);
     }
   }   
    vel_gsm[0]=ao[num_rec_aosr-1].vel_GSM[0];
    vel_gsm[1]=ao[num_rec_aosr-1].vel_GSM[1];
    vel_gsm[2]=ao[num_rec_aosr-1].vel_GSM[2];
    return(AA_ERR);
}

/* New routine to pass entire AOSR structure, for a given SC clock. */
/* SBK 02/09/98 */
/* modified by Andrew Davis, 02/10/98 */

/* Note: Returns -1 if scclock is out of bounds, but still fills the */
/* structure with the first(last) data available */

/* Note: Returns +1 (AA_POOR) if the state flag indicates */
/* a maneuver was in progress */

/* Note: HSEa attitude, spin, position, velocity not yet implemented */
/* Note: HSEb spin and HS spin not implemented */

int32 ACE_aosr(float64 scclock, struct attorb_entry *aosr_out)
{
   int32 ii;
   struct attorb_entry aosr_tmp;
   float64 range01,crange01,a1,a2,a3,sum;

   if(ao==NULL) {
      fprintf(stderr, "ACE_aosr: Error! Call init_ACEancillary() to load ancil database\n");
      exit(AA_ERR);
   }

   /* make sure aosr_tmp is zeroed out to start with */
   memset(&aosr_tmp,0,sizeof(struct attorb_entry));
   
   /* pass first aosr record if scclock too small */
   if ( scclock < ao[0].sctime) {
      memcpy(aosr_out,&ao[0],sizeof(struct attorb_entry));
      return(AA_ERR);
   }

   for(ii=0;ii<num_rec_aosr;ii++) {
     if (scclock<=ao[ii].sctime) {
        if (scclock == ao[ii].sctime) {
	   /* interpolation not necessary, exact time tag match */
           memcpy(aosr_out,&ao[ii],sizeof(struct attorb_entry));
	}
	else { /* START BLOCK to interpolate AOSR structure members */

	    aosr_tmp.sctime=(uint32)rint(scclock);

	    /* istp_time is left zeroed for now */

            /* set UT_time to "Not set" for now */
	    sprintf(aosr_tmp.UT_time,"Not set");

	    /* Primary to body rotation matrix is left zeroed for now */

	    /* set state to the state quoted in the previous aosr */
	    /* 1 = begin pass, 2 = end pass, 3 = begin maneuver, */
	    /* 4 = end maneuver */
	    /* if state = 3, the user should be aware the attitude data */
	    /* is suspect */
	    aosr_tmp.state = ao[ii-1].state;

	    range01=(ao[ii].sctime-scclock)/(ao[ii].sctime-ao[ii-1].sctime);
            crange01 = 1.-range01;

	    /* attitude - J2GCI */
	    a1=range01*ao[ii-1].att_J2GCI[0]+crange01*ao[ii].att_J2GCI[0];
	    a2=range01*ao[ii-1].att_J2GCI[1]+crange01*ao[ii].att_J2GCI[1];
	    a3=range01*ao[ii-1].att_J2GCI[2]+crange01*ao[ii].att_J2GCI[2];
	    sum=sqrt(pow(a1,2)+pow(a2,2)+pow(a3,2));
	    aosr_tmp.att_J2GCI[0] = a1/sum;
	    aosr_tmp.att_J2GCI[1] = a2/sum;
	    aosr_tmp.att_J2GCI[2] = a3/sum;

	    /* attitude - RTN */
	    a1=range01*ao[ii-1].att_RTN[0]+crange01*ao[ii].att_RTN[0];
	    a2=range01*ao[ii-1].att_RTN[1]+crange01*ao[ii].att_RTN[1];
	    a3=range01*ao[ii-1].att_RTN[2]+crange01*ao[ii].att_RTN[2];
	    sum=sqrt(pow(a1,2)+pow(a2,2)+pow(a3,2));
	    aosr_tmp.att_RTN[0] = a1/sum;
	    aosr_tmp.att_RTN[1] = a2/sum;
	    aosr_tmp.att_RTN[2] = a3/sum;

   	    /* attitude - GSE */
	    a1=range01*ao[ii-1].att_GSE[0]+crange01*ao[ii].att_GSE[0];
	    a2=range01*ao[ii-1].att_GSE[1]+crange01*ao[ii].att_GSE[1];
	    a3=range01*ao[ii-1].att_GSE[2]+crange01*ao[ii].att_GSE[2];
	    sum=sqrt(pow(a1,2)+pow(a2,2)+pow(a3,2));
	    aosr_tmp.att_GSE[0] = a1/sum;
	    aosr_tmp.att_GSE[1] = a2/sum;
	    aosr_tmp.att_GSE[2] = a3/sum;

   	    /* attitude - GSM */
	    a1=range01*ao[ii-1].att_GSM[0]+crange01*ao[ii].att_GSM[0];
	    a2=range01*ao[ii-1].att_GSM[1]+crange01*ao[ii].att_GSM[1];
	    a3=range01*ao[ii-1].att_GSM[2]+crange01*ao[ii].att_GSM[2];
	    sum=sqrt(pow(a1,2)+pow(a2,2)+pow(a3,2));
	    aosr_tmp.att_GSM[0] = a1/sum;
	    aosr_tmp.att_GSM[1] = a2/sum;
	    aosr_tmp.att_GSM[2] = a3/sum;

   	    /* attitude - HSEb */
	    a1=range01*ao[ii-1].att_HSEb[0]+crange01*ao[ii].att_HSEb[0];
	    a2=range01*ao[ii-1].att_HSEb[1]+crange01*ao[ii].att_HSEb[1];
	    a3=range01*ao[ii-1].att_HSEb[2]+crange01*ao[ii].att_HSEb[2];
	    sum=sqrt(pow(a1,2)+pow(a2,2)+pow(a3,2));
	    aosr_tmp.att_HSEb[0] = a1/sum;
	    aosr_tmp.att_HSEb[1] = a2/sum;
	    aosr_tmp.att_HSEb[2] = a3/sum;

	    /* attitude - HSEa */
	    /* not implemented */

	    /* attitude - HS */
	    a1=range01*ao[ii-1].att_HS[0]+crange01*ao[ii].att_HS[0];
	    a2=range01*ao[ii-1].att_HS[1]+crange01*ao[ii].att_HS[1];
	    a3=range01*ao[ii-1].att_HS[2]+crange01*ao[ii].att_HS[2];
	    sum=sqrt(pow(a1,2)+pow(a2,2)+pow(a3,2));
	    aosr_tmp.att_HS[0] = a1/sum;
	    aosr_tmp.att_HS[1] = a2/sum;
	    aosr_tmp.att_HS[2] = a3/sum;

	    /* for spin-rate vectors, it may be better to interpolate */
            /* the spin-rate magnitude, then multiply by the */
            /* interpolated attitude vector? */

	    /* spin - J2GCI */
            aosr_tmp.spin_J2GCI[0]=
	      range01*ao[ii-1].spin_J2GCI[0]+crange01*ao[ii].spin_J2GCI[0];
            aosr_tmp.spin_J2GCI[1]=
	      range01*ao[ii-1].spin_J2GCI[1]+crange01*ao[ii].spin_J2GCI[1];
            aosr_tmp.spin_J2GCI[2]=
	      range01*ao[ii-1].spin_J2GCI[2]+crange01*ao[ii].spin_J2GCI[2];

	    /* spin - RTN */
            aosr_tmp.spin_RTN[0]=
	      range01*ao[ii-1].spin_RTN[0]+crange01*ao[ii].spin_RTN[0];
            aosr_tmp.spin_RTN[1]=
	      range01*ao[ii-1].spin_RTN[1]+crange01*ao[ii].spin_RTN[1];
            aosr_tmp.spin_RTN[2]=
	      range01*ao[ii-1].spin_RTN[2]+crange01*ao[ii].spin_RTN[2];

	    /* spin - GSE */
            aosr_tmp.spin_GSE[0]=
	      range01*ao[ii-1].spin_GSE[0]+crange01*ao[ii].spin_GSE[0];
            aosr_tmp.spin_GSE[1]=
	      range01*ao[ii-1].spin_GSE[1]+crange01*ao[ii].spin_GSE[1];
            aosr_tmp.spin_GSE[2]=
	      range01*ao[ii-1].spin_GSE[2]+crange01*ao[ii].spin_GSE[2];

	    /* spin - GSM */
            aosr_tmp.spin_GSM[0]=
	      range01*ao[ii-1].spin_GSM[0]+crange01*ao[ii].spin_GSM[0];
            aosr_tmp.spin_GSM[1]=
	      range01*ao[ii-1].spin_GSM[1]+crange01*ao[ii].spin_GSM[1];
            aosr_tmp.spin_GSM[2]=
	      range01*ao[ii-1].spin_GSM[2]+crange01*ao[ii].spin_GSM[2];

	    /* spin - HSEa, HSEb, HS not implemented */

	    /* position - J2GCI */
	    aosr_tmp.pos_J2GCI[0]=range01*ao[ii-1].pos_J2GCI[0]+ 
	      crange01*ao[ii].pos_J2GCI[0];
	    aosr_tmp.pos_J2GCI[1]=range01*ao[ii-1].pos_J2GCI[1]+ 
	      crange01*ao[ii].pos_J2GCI[1];
	    aosr_tmp.pos_J2GCI[2]=range01*ao[ii-1].pos_J2GCI[2]+ 
	      crange01*ao[ii].pos_J2GCI[2];

	    /* position - GSE */
            aosr_tmp.pos_GSE[0]=range01*ao[ii-1].pos_GSE[0]+ 
            crange01*ao[ii].pos_GSE[0];
            aosr_tmp.pos_GSE[1]=range01*ao[ii-1].pos_GSE[1]+ 
            crange01*ao[ii].pos_GSE[1];
            aosr_tmp.pos_GSE[2]=range01*ao[ii-1].pos_GSE[2]+ 
            crange01*ao[ii].pos_GSE[2];

	    /* position - GSM */
            aosr_tmp.pos_GSM[0]=range01*ao[ii-1].pos_GSM[0]+ 
            crange01*ao[ii].pos_GSM[0];
            aosr_tmp.pos_GSM[1]=range01*ao[ii-1].pos_GSM[1]+ 
            crange01*ao[ii].pos_GSM[1];
            aosr_tmp.pos_GSM[2]=range01*ao[ii-1].pos_GSM[2]+ 
            crange01*ao[ii].pos_GSM[2];

	    /* position - HSEa */
	    /* not implemented */

	    /* position - HSEb */
            aosr_tmp.pos_HSEb[0]=range01*ao[ii-1].pos_HSEb[0]+ 
            crange01*ao[ii].pos_HSEb[0];
            aosr_tmp.pos_HSEb[1]=range01*ao[ii-1].pos_HSEb[1]+ 
            crange01*ao[ii].pos_HSEb[1];
            aosr_tmp.pos_HSEb[2]=range01*ao[ii-1].pos_HSEb[2]+ 
            crange01*ao[ii].pos_HSEb[2];

	    /* position - HS */
            aosr_tmp.pos_HS[0]=range01*ao[ii-1].pos_HS[0]+ 
            crange01*ao[ii].pos_HS[0];
            aosr_tmp.pos_HS[1]=range01*ao[ii-1].pos_HS[1]+ 
            crange01*ao[ii].pos_HS[1];
            aosr_tmp.pos_HS[2]=range01*ao[ii-1].pos_HS[2]+ 
            crange01*ao[ii].pos_HS[2];

	    /* velocity - J2GCI */
            aosr_tmp.vel_J2GCI[0]=range01*ao[ii-1].vel_J2GCI[0]+ 
            crange01*ao[ii].vel_J2GCI[0];
            aosr_tmp.vel_J2GCI[1]=range01*ao[ii-1].vel_J2GCI[1]+ 
            crange01*ao[ii].vel_J2GCI[1];
            aosr_tmp.vel_J2GCI[2]=range01*ao[ii-1].vel_J2GCI[2]+ 
            crange01*ao[ii].vel_J2GCI[2];

	    /* velocity - GSE */
            aosr_tmp.vel_GSE[0]=range01*ao[ii-1].vel_GSE[0]+ 
            crange01*ao[ii].vel_GSE[0];
            aosr_tmp.vel_GSE[1]=range01*ao[ii-1].vel_GSE[1]+ 
            crange01*ao[ii].vel_GSE[1];
            aosr_tmp.vel_GSE[2]=range01*ao[ii-1].vel_GSE[2]+ 
            crange01*ao[ii].vel_GSE[2];

	    /* velocity - GSM */
            aosr_tmp.vel_GSM[0]=range01*ao[ii-1].vel_GSM[0]+ 
            crange01*ao[ii].vel_GSM[0];
            aosr_tmp.vel_GSM[1]=range01*ao[ii-1].vel_GSM[1]+ 
            crange01*ao[ii].vel_GSM[1];
            aosr_tmp.vel_GSM[2]=range01*ao[ii-1].vel_GSM[2]+ 
            crange01*ao[ii].vel_GSM[2];

	    /* velocity - HSEb */
            aosr_tmp.vel_HSEb[0]=range01*ao[ii-1].vel_HSEb[0]+ 
            crange01*ao[ii].vel_HSEb[0];
            aosr_tmp.vel_HSEb[1]=range01*ao[ii-1].vel_HSEb[1]+ 
            crange01*ao[ii].vel_HSEb[1];
            aosr_tmp.vel_HSEb[2]=range01*ao[ii-1].vel_HSEb[2]+ 
            crange01*ao[ii].vel_HSEb[2];

	    /* velocity - HSEa */
	    /* not implemented */

	    /* velocity - HS */
            aosr_tmp.vel_HS[0]=range01*ao[ii-1].vel_HS[0]+ 
            crange01*ao[ii].vel_HS[0];
            aosr_tmp.vel_HS[1]=range01*ao[ii-1].vel_HS[1]+ 
            crange01*ao[ii].vel_HS[1];
            aosr_tmp.vel_HS[2]=range01*ao[ii-1].vel_HS[2]+ 
            crange01*ao[ii].vel_HS[2];

	    memcpy(aosr_out,&aosr_tmp,sizeof(struct attorb_entry));

	} /* END BLOCK to interpolate AOSR structure members */

	/* check to see if maneuver in progress */
        if (ao[ii-1].state == 3 && ao[ii].state == 4)
            return(AA_POOR);
        else
            return(AA_GOOD);
     }
   }

   /* pass last aosr record if scclock too large */
   memcpy(aosr_out,&ao[num_rec_aosr-1],sizeof(struct attorb_entry));
   return(AA_ERR);
}


void dump_ascii_ccr()
{
   int32 ii;
   for(ii=0;ii<num_rec_ccr;ii++) {		    
      fprintf(stdout,"\n");
      fprintf(stdout,"start = %lu\n",cc[ii].start);
      fprintf(stdout,"end = %lu\n",cc[ii].end);
      fprintf(stdout,"slope = %.9e\n",cc[ii].slope);
      fprintf(stdout,"offset = %.3f\n",cc[ii].offset);
      fprintf(stdout,"cdh = %u\n",cc[ii].cdh);
      fprintf(stdout,"year = %u\n",cc[ii].year);
      fprintf(stdout,"doy = %u\n",cc[ii].doy);
      fprintf(stdout,"\n");
   }
}

void dump_ascii_ccr_oneliner()
{
   int32 ii;
   for(ii=0;ii<num_rec_ccr;ii++) {		    
      fprintf(stdout,"year = %u ",cc[ii].year);
      fprintf(stdout,"doy = %u ",cc[ii].doy);
      fprintf(stdout,"start = %lu ",cc[ii].start);
      fprintf(stdout,"end = %lu ",cc[ii].end);
      fprintf(stdout,"slope = %.9e ",cc[ii].slope);
      fprintf(stdout,"offset = %.3f ",cc[ii].offset);
      fprintf(stdout,"cdh = %u\n",cc[ii].cdh);
   }
}

void dump_ascii_aosr()
{
   int32 ii;
   for(ii=0;ii<num_rec_aosr;ii++) {		    
    fprintf(stdout,"\n");
    fprintf(stdout,"time = %lu\n",ao[ii].sctime);
    fprintf(stdout,"ISTP time = %ld  %ld\n",ao[ii].istp_time[0],ao[ii].istp_time[1]);
    /* new code */
    fprintf(stdout,"UT_time = %s\n",ao[ii].UT_time);
    fprintf(stdout,"status = %d\n",ao[ii].state);
    fprintf(stdout,"attJ   = %22.10e %22.10e %22.10e\n",
        ao[ii].att_J2GCI[0],ao[ii].att_J2GCI[1],ao[ii].att_J2GCI[2]);
    fprintf(stdout,"attRTN = %22.10e %22.10e %22.10e\n",
        ao[ii].att_RTN[0],ao[ii].att_RTN[1],ao[ii].att_RTN[2]);
    fprintf(stdout,"attGSE = %22.10e %22.10e %22.10e\n",
        ao[ii].att_GSE[0],ao[ii].att_GSE[1],ao[ii].att_GSE[2]);
    fprintf(stdout,"attGSM = %22.10e %22.10e %22.10e\n",
        ao[ii].att_GSM[0],ao[ii].att_GSM[1],ao[ii].att_GSM[2]);
    fprintf(stdout,"attHSEb = %22.10e %22.10e %22.10e\n",
        ao[ii].att_HSEb[0],ao[ii].att_HSEb[1],ao[ii].att_HSEb[2]);
    fprintf(stdout,"attHS = %22.10e %22.10e %22.10e\n",
        ao[ii].att_HS[0],ao[ii].att_HS[1],ao[ii].att_HS[2]);

    fprintf(stdout,"spinJ  = %22.10e %22.10e %22.10e\n",
        ao[ii].spin_J2GCI[0],ao[ii].spin_J2GCI[1],ao[ii].spin_J2GCI[2]);
    fprintf(stdout,"spinRTN= %22.10e %22.10e %22.10e\n",
        ao[ii].spin_RTN[0],ao[ii].spin_RTN[1],ao[ii].spin_RTN[2]);
    fprintf(stdout,"spinGSE= %22.10e %22.10e %22.10e\n",
        ao[ii].spin_GSE[0],ao[ii].spin_GSE[1],ao[ii].spin_GSE[2]);

    fprintf(stdout,"posJ   = %22.10e %22.10e %22.10e\n",
        ao[ii].pos_J2GCI[0],ao[ii].pos_J2GCI[1],ao[ii].pos_J2GCI[2]);
    fprintf(stdout,"posGSE = %22.10e %22.10e %22.10e\n",
        ao[ii].pos_GSE[0],ao[ii].pos_GSE[1],ao[ii].pos_GSE[2]);
    fprintf(stdout,"posGSM = %22.10e %22.10e %22.10e\n",
        ao[ii].pos_GSM[0],ao[ii].pos_GSM[1],ao[ii].pos_GSM[2]);
    fprintf(stdout,"posHSEb = %22.10e %22.10e %22.10e\n",
        ao[ii].pos_HSEb[0],ao[ii].pos_HSEb[1],ao[ii].pos_HSEb[2]);
    fprintf(stdout,"posHS = %22.10e %22.10e %22.10e\n",
        ao[ii].pos_HS[0],ao[ii].pos_HS[1],ao[ii].pos_HS[2]);
    fprintf(stdout,"velJ   = %22.10e %22.10e %22.10e\n",
        ao[ii].vel_J2GCI[0],ao[ii].vel_J2GCI[1],ao[ii].vel_J2GCI[2]);
    fprintf(stdout,"velGSE = %22.10e %22.10e %22.10e\n",
        ao[ii].vel_GSE[0],ao[ii].vel_GSE[1],ao[ii].vel_GSE[2]);
    fprintf(stdout,"velGSM = %22.10e %22.10e %22.10e\n",
        ao[ii].vel_GSM[0],ao[ii].vel_GSM[1],ao[ii].vel_GSM[2]);
    fprintf(stdout,"velHSEb = %22.10e %22.10e %22.10e\n",
        ao[ii].vel_HSEb[0],ao[ii].vel_HSEb[1],ao[ii].vel_HSEb[2]);
    fprintf(stdout,"velHS = %22.10e %22.10e %22.10e\n",
        ao[ii].vel_HS[0],ao[ii].vel_HS[1],ao[ii].vel_HS[2]);
    fprintf(stdout,"\n");
   }
}


/* functions below are probably not useful to the general user */

void dump_GSE_aosr()
{
  FILE *fp;
  int32 ii,jj;
  float gg;

  if((fp=fopen("gse_new.dat","w")) == NULL) {
    printf("Cannot open gse.dat file \n");
    exit(1);
  }

  /*  fprintf(fp,"%d \n",num_rec_aosr); */
  
  for(ii=0;ii<num_rec_aosr;ii++) {
    jj=(int)(((float)ao[ii].istp_time[0])-1997000.)/1000.;
    if (jj == 0) gg=   ((float)ao[ii].istp_time[0])-1997000.+
		   ((float)ao[ii].istp_time[1]) / 86400000.;
    if (jj == 1) gg=365.+(float)ao[ii].istp_time[0]-1998000.+
		   ((float)ao[ii].istp_time[1]) / 86400000.;
    fprintf(fp,"%8ld %8ld %18.10e %18.10e %18.10e %10.5f \n",
	    ao[ii].istp_time[0],ao[ii].istp_time[1],
            ao[ii].pos_GSE[0],ao[ii].pos_GSE[1],ao[ii].pos_GSE[2],gg);
  }
}

void dump_timing_ccr()
{
  FILE *fp;
  int32 ii;
  float64 gg,hh;
  
  if((fp=fopen("so_new.dat","w")) == NULL) {
    printf("Cannot open gse.dat file \n");
    exit(1);
  }
  
  /*  fprintf(stdout,"num_rec_ccr = %d \n",num_rec_ccr); */
  
  for(ii=0;ii<num_rec_ccr;ii++) {
    gg=(float64)cc[ii].year+( (float64)cc[ii].doy)/365.;
    hh=(float64)cc[ii].start*(float64)cc[ii].slope+(float64)cc[ii].offset+ 
      (float64)SC_ACE_epoch_offset;
    fprintf(fp,"%2u %5u %4u %16.7e %8.3f %10.4f %17.9e %9lu %9lu %14.9f \n",
	    cc[ii].cdh, cc[ii].year,cc[ii].doy,
	    cc[ii].slope,cc[ii].offset,
	    gg,cc[ii].slope-1,cc[ii].start,cc[ii].end,hh);
  }
}

void dump_SCClock()
{
  FILE *fp;
  float64 ACEepoch1,ACEepoch2;
  float64 SCclock_to_ACEepoch();
  int ii;
  float64 g1,g2;

  if((fp=fopen("Clock_new.dat","w")) == NULL) {
    printf("\nCannot open Clock.dat file");
    exit(1);
  }

  printf("\n SCclock        ACEepoch    "); 
  for(ii=0;ii<num_rec_ccr;ii++) {
      g1=(float64)(cc[ii].end);
      ACEepoch1=SCclock_to_ACEepoch(g1);
      g2=(float64)(cc[ii].end+1);
      ACEepoch2=SCclock_to_ACEepoch(g2);
      fprintf(fp,"\n %12.2f %16.5f %13.7f",g1,ACEepoch1,
	      ACEepoch2-ACEepoch1);
  }
}







