/* $Id: s3_dspare_cmd.h,v 1.3 1998/01/30 19:50:50 hemple Exp $ */

#include "hdfi.h"

#define SCOMMANDITEMS 55

struct s3s_dspare_cmd {

uint32 sctime; /* 32bit spacecraft time */

/* SEPICA Command parameters, from EDB's 0,20,40 */
int16 SCommand1[SCOMMANDITEMS];
int16 SCommand2[SCOMMANDITEMS];
int16 SCommand3[SCOMMANDITEMS];

/* some unique SEPICA command parameters pulled from the above arrays */
int16 Pressure_set_1[3];    /* pressure */
int16 Pressure_set_2[3];    /* pressure */
int16 Pressure_set_3[3];    /* pressure */
int16 HvEnable[3];	    /* HV enables */
int16 BITChannel_1[3];	    /* BIT channel */
int16 BITChannel_2[3];	    /* BIT channel */
int16 BITChannel_3[3];	    /* BIT channel */
int16 DAC0Channel_1[3];     /* DAC 0 channel */
int16 DAC0Channel_2[3];     /* DAC 0 channel */
int16 DAC0Channel_3[3];     /* DAC 0 channel */
int16 DAC1Channel_1[3];     /* DAC 1 channel */
int16 DAC1Channel_2[3];     /* DAC 1 channel */

};
