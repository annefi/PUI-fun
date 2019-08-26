/* - <Prolog> ----------------------------------------------------------------
   libtim.c --- time handling routines
   1998 Simon Hefti (hef), University of Michigan (hefti@umich.edu)
   $Id: libtim.c,v 1.1.1.1 2000/06/02 13:37:22 jraines Exp $
   - </Prolog> ------------------------------------------------------------ */

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "libtim.h"

/* - [<] ---------------------------------------------------------------------
   date_time --- convert dd mm yyyy --> sec70 --> broken time
   - [>] ------------------------------------------------------------------ */
void date_time(long alltime[14], long *mday, long *mon, long *year)
{
  
  long ltmp1 = 0L;
  long ltmp2 = 0L;
  long ltmp3 = 0L;
  
  long sec70;

  long jd70 = 0L;  /* julday of 1-Jan-1970 */
  long djul = 0L;  /* julday of this day */

  ltmp1 = 1L;
  ltmp2 = 1L;
  ltmp3 = 1970L;
  
  ltjulday(&ltmp1,&ltmp2,&ltmp3,&jd70);

  ltmp1 = *mon;
  ltmp2 = *mday;
  ltmp3 = *year;
  
  ltjulday(&ltmp1,&ltmp2,&ltmp3,&djul);
  
  sec70 = (djul - jd70) * SECOFDAY;
  
  sec70_time(alltime,&sec70);
  
  return;
}


/* - [<] ---------------------------------------------------------------------
   doy_time --- yyyy ddd --> sec70 --> broken time
   - [>] ------------------------------------------------------------------ */
void doy_time(long alltime[14], long *doy, long *year)
{
  
  long ltmp1 = 0L;
  long ltmp2 = 0L;
  long ltmp3 = 0L;
  
  long sec70;

  long jd70 = 0L;  /* ltjulday of 1-Jan-1970 */
  long jdyr = 0L;  /* ltjulday of 1-Jan-of_current_year */

  ltmp1 = 1L;
  ltmp2 = 1L;
  ltmp3 = 1970L;
  
  ltjulday(&ltmp1,&ltmp2,&ltmp3,&jd70);

  ltmp1 = 1L;
  ltmp2 = 1L;
  ltmp3 = *year;
  
  ltjulday(&ltmp1,&ltmp2,&ltmp3,&jdyr);
  
  sec70 = (jdyr - jd70 + *doy - 1L) * SECOFDAY;
  
  sec70_time(alltime,&sec70);
  
  return;
}


/* - [<] ---------------------------------------------------------------------
   sec70_time --- sec70 --> broken time
   - [>] ------------------------------------------------------------------ */
void sec70_time(long alltime[14], long *sec70)
{
  long d70 = 0L; /* days since 1-Jan-1970 */
  long secday = 0L; /* sec of day 0..86400-1 */
  long djul = 0L; /* julian day number */
  
  long hr = 0L; /* hour of day */
  long min = 0L; /* min of hour */
  long sec = 0L; /* sec of min */
  
  long year = 0L;
  long month = 0L; /* month of year (1..12) */
  long day = 0L;  /* day of month (1..31) */
  
  long doy = 0L; /* day of year (1..366) */
  long wday = 0L; /* day of week (0..6)->(Sun..Sat) */
  
  long ltmp1 = 0L;
  long ltmp2 = 0L;
  long ltmp3 = 0L;
  long ltmp4 = 0L;
  
  long jd70 = 0L;  /* ltjulday of 1-Jan-1970 */
  long jdyr = 0L;  /* ltjulday of 1-Jan-of_current_year */
  
  d70    = *sec70 / SECOFDAY;
  secday = *sec70 % SECOFDAY;
  
  ltmp1 = 1L;
  ltmp2 = 1L;
  ltmp3 = 1970L;
  
  ltjulday(&ltmp1,&ltmp2,&ltmp3,&jd70);
  
  djul = d70 + jd70;
  
  hr  = secday / 3600L;
  min = (secday % 3600L) / 60L;
  sec = secday - hr * 3600L - min * 60L;
  
  ltcaldat(&djul,&ltmp1,&ltmp2,&ltmp3);
  
  year  = ltmp3;
  month = ltmp1;
  day   = ltmp2;
  
  ltmp1 = month;
  ltmp2 = day;
  ltmp3 = year;
  
  ltjulday(&ltmp1,&ltmp2,&ltmp3,&ltmp4);
  
  ltmp1 = 1L;
  ltmp2 = 1L;
  ltmp3 = year;
  
  ltjulday(&ltmp1,&ltmp2,&ltmp3,&jdyr);

  doy = ltmp4 - jdyr + 1L;
  
  wday = (djul + 1L) % 7;
  
  alltime[SEC70POS] = *sec70;
  alltime[JULDYPOS] = djul;
  alltime[SECDYPOS] = secday;
  alltime[DOY__POS] = doy;
  alltime[DAY__POS] = day;
  alltime[MONTHPOS] = month;
  alltime[YEAR_POS] = year;
  alltime[HOUR_POS] = hr;
  alltime[MIN__POS] = min;
  alltime[SEC__POS] = sec;
  alltime[WDAY_POS] = wday;
  alltime[DUM1_POS] = 0L;
  alltime[DUM2_POS] = 0L;
  alltime[DUM3_POS] = 0L;
  
  return;
}


/* - [<] ---------------------------------------------------------------------
   ltjulday --- dd mm yyyy --> julian day
   - [>] ------------------------------------------------------------------ */
void ltjulday(long *mm, long *id, long *iyyy, long *jday)
{
  long jul = 0L;
  long ja = 0L;
  long jy = *iyyy;
  long jm = 0L;

  if (jy == 0L)
  {
    printf("War: year %ld encountered. Returning 0\n",jy);
    *jday = 0;
    return;
  }
  

  if (jy < 0L) ++jy;

  if (*mm > 2L)
  {
    jm = *mm + 1L;
  }
  else
  {
    --jy;
    jm = *mm + 13L;
  }
  
  jul = (long) (floor(365.25*jy) + floor(30.6001*jm) + *id + 1720995L);
  if( *id + 31L * (*mm + 12L*(*iyyy) ) >= LTIGREG1)
  {
    ja   = (long)(0.01*jy);
    jul += 2L - ja + (long)(0.25 * ja);
  }
  
  *jday = jul;

  return;
}



/* - [<] ---------------------------------------------------------------------
   ltcaldat --- julian day --> dd mm yyyy
   - [>] ------------------------------------------------------------------ */
void ltcaldat(long *julian, long *mm, long *id, long *iyyy)
{
  long ja = 0L;
  long jalpha = 0L;
  long jb = 0L;
  long jc = 0L;
  long jd = 0L;
  long je = 0L;

  if (*julian >= LTIGREG2) {
    
    jalpha = (long)(((float) (*julian - 1867216L) - 0.25)/36524.25);
    ja     = *julian + 1 + jalpha - (long)(0.25*jalpha);
  }
  else {
    ja     = *julian;
  }

  jb = ja + 1524L;
  jc = (long)(6680.0 + ((float) (jb - 2439870L) - 122.1)/365.25);
  jd = (long)(365*jc + (0.25 * jc));
  je = (long)((jb - jd)/30.6001);
  *id = jb - jd -(long)(30.6001 * je);
  *mm = je - 1L;

  if (*mm > 12L) *mm -= 12L;

  *iyyy = jc - 4715L;

  if (*mm > 2L) --(*iyyy);
  if (*iyyy <= 0L) --(*iyyy);

  return;
}

/*  --------------------------------------------------------------------[<]---
    is_leap --- returns 1 if year is leap year, 0 else.
    --------------------------------------------------------------------[>]-*/
int is_leap(int iyear)
{
  if( (iyear % 4 == 0) && ( (iyear % 100 != 0) || (iyear % 400 == 0) ) ) {
    return(1);
  }
  else {
    return(0);
  }
  return(-1);
}

/*  --------------------------------------------------------------------[<]---
    timstr --- format time as: Mon 13-Jul-1998 (194) 14:44:04
    --------------------------------------------------------------------[>]-*/
char *timstr(long sec70)
{
  /* transform "wday" to string */
  static char   azwday[7][8] = 
  {"Sun","Mon","Tue","Wed","Thu","Fri","Sat"};
  /* transform "month" to string */
  static char   azmonth[13][8] = 
  {"ill","Jan","Feb","Mar","Apr","May","Jun",
   "Jul","Aug","Sep","Oct","Nov","Dec"};

  static char zstr[256];

  long   alltime[14];

  sec70_time(alltime,&sec70);

  sprintf(zstr,"%s %2.2ld-%s-%4.4ld (%3.3ld) %2.2ld:%2.2ld:%2.2ld",
	  azwday[alltime[WDAY_POS]],
	  alltime[DAY__POS],
	  azmonth[alltime[MONTHPOS]],
	  alltime[YEAR_POS],
	  alltime[DOY__POS],
	  alltime[HOUR_POS],
	  alltime[MIN__POS],
	  alltime[SEC__POS]);

  return(zstr);
}
