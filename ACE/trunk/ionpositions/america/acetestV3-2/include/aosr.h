/* $Id: aosr.h,v 1.8 1998/10/20 22:26:40 asc Exp $ */

#include "hdfi.h"

struct attorb_entry {
    uint32   sctime;      /* time of measurement in Spacecraft clock ticks */

    int32    istp_time[2]; /* time of measurement in ISTP format. */
                           /* First entry is YEARDAYOFYEAR, eg: 1998201 for */
			   /* day 201 of 1998. Second entry is the millisecond of */
			   /* the day */

    char8    UT_time[13];  /* A character string containing UT time of */
                           /* the measurement */

    float64  pri2bdy[3][3];    /* Primary to body rotation matrix */
                               /* NOT IMPLEMENTED */

    uint8    state;    /* state status.  {Beg/end}_{pass/manuever} */
                       /* The data is collected under one of the following */
		       /* four conditions: */
                       /* state = 1 - Beginning of DSN telemetry pass */
                       /* state = 2 - End of DSN telemetry pass */
                       /* state = 3 - Beginning of spacecraft maneuver */
                       /* state = 4 - End of spacecraft maneuver */

    /* attitude data. Attitude vectors are normalized to unity */
    /* See ASC web page for definitions of coordinate systems */
    float64  att_J2GCI[3]; /* attitude direction cosines in J2000 */
    float64  att_RTN[3]; /* attitude direction cosines in RTN */
    float64  att_GSE[3]; /* attitude direction cosines in GSE */
    float64  att_GSM[3]; /* attitude direction cosines in GSM */
    float64  att_HSEb[3]; /* attitude direction cosines in HSEb */
    float64  att_HSEa[3]; /* attitude direction cosines in HSEa */
    float64  att_HS[3]; /* attitude direction cosines in HS */

    /* spin-rate data */
    float64  spin_J2GCI[3]; /* spin rate vector in J2000, rad/sec */
    float64  spin_RTN[3]; /* spin rate vector in RTN, rad/sec */
    float64  spin_GSE[3]; /* spin rate vector in GSE, rad/sec */
    float64  spin_GSM[3]; /* spin rate vector in GSM, rad/sec */
    float64  spin_HSEb[3]; /* spin rate vector in HSEb, rad/sec */
    float64  spin_HSEa[3]; /* spin rate vector in HSEa, rad/sec */
    float64  spin_HS[3]; /* spin rate vector in HS, rad/sec */

    /* spacecraft position data */
    float64  pos_J2GCI[3]; /* S/C position in J2000, km */
    float64  pos_GSE[3]; /* S/C position in GSE, km */
    float64  pos_GSM[3]; /* S/C position in GSM, km */
    float64  pos_HSEb[3]; /* S/C position in HSEb, km */
    float64  pos_HSEa[3]; /* S/C position in HSEa, km NOT IMPLEMENTED */
    float64  pos_HS[3]; /* S/C position in HS, km */

    /* spacecraft velocity data */
    float64  vel_J2GCI[3]; /* S/C velocity in J2000, km/s */
    float64  vel_GSE[3]; /* S/C velocity in GSE, km/s */
    float64  vel_GSM[3]; /* S/C velocity in GSM, km/s */
    float64  vel_HSEb[3]; /* S/C velocity in HSEb, km/s NOT IMPLEMENTED */
    float64  vel_HSEa[3]; /* S/C velocity in HSEa, km/s NOT IMPLEMENTED */
    float64  vel_HS[3]; /* S/C velocity in HS, km/s NOT IMPLEMENTED */
};

