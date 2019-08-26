/* $Id: mag_hskp.h,v 1.9 1997/09/04 23:27:42 jeff Exp $ */
#include "hdfi.h"

struct MagHskpSet
{
  uint32 sctime_readout;           /* 32 bit spacecraft readout time  */
  uint32 sctime_collection;        /* 32 bit spacecraft collection time  */

  uint32 QAC;              /* number of missing frames in this cycle */
  uint8 QACarr[16]; /* each entry corresponds to a single minor frame */
		    /* if value =0 frame is OK.  =1 frame contains fill data*/

  uint8 st1a;            /* status byte 1, minor frame 1         */
  uint8 st2a;            /* status byte 2, minor frame 2         */
  uint8 st3;             /* status byte 3                        */
  uint8 st4;             /* status byte 4                        */
  uint8 st5;             /* status byte 5                        */
  uint8 st6;             /* status byte 6                        */
  uint8 pctemp;          /* power converter temperature status   */
  uint8 cmon;            /* current monitor reading status       */
  uint8 st1b;            /* status byte 1, minor frame 9         */
  uint8 st2b;            /* status byte 2, minor frame 10        */
  uint8 hk1;             /* housekeeping byte 1                  */
  uint8 hk2;             /* housekeeping byte 2                  */
  uint8 hk3;             /* housekeeping byte 3                  */
  uint8 hk4;             /* housekeeping byte 4                  */
  uint8 hk5;             /* housekeeping byte 5                  */
  uint8 sync;            /* sync byte, TBD                       */
  uint16 st;             /* st byte(s), TBD                      */ 
  uint8 in_temp;         /* inboard temperature                  */
  uint8 out_temp;        /* outboard temperature                 */
  uint8 in_pwrlvl;       /* inboard heater power level           */
  uint8 out_pwrlvl;      /* outboard heater power level          */
  uint8 current;         /* MAG current                          */
  uint8 SenIntTempPosY;  /* MAG +Y Sensor Interface Temp         */
  uint8 SenIntTempNegY;  /* MAG -Y Sensor Interface Temp         */
  uint8 MagPowBits;      /* MAG Power/Ordinance Bits */
				/* 7 - Main Sys Power A -       Bit pos  15 */
				/* 6 - Main Sys Power B -       Bit pos  16 */
				/* 5 - Main Int Heaters -       Bit pos  19 */
				/* 4 - Main Interface Heater -  Bit pos  56 */
				/* 3 - Main Boom Y Axis Arm  -  Bit pos  67 */
				/* 2 - Backup Boom Y Axis Arm-  Bit pos  72 */
				/* 1 - Unused -                             */
				/* 0 - Unused -                             */
};
