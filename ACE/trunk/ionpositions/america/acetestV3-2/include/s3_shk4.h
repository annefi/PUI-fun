/* $Id: s3_shk4.h,v 1.2 1998/12/07 18:12:39 ad Exp $ */
#include "hdfi.h"

struct sshshk4{
	uint32 sctime_readout;	/* first minor frame of readout cycle, */
	                        /* 32 bit spacecraft clock time */
	float64 sctime_collection; /* time of the start of the first spin in the */
	                           /* 5-spin cycle. sub-second resolution */

	uint32 QAC; /* number of missing minor frames in the 5-spin cycle  */

	uint8 HKSECTOR;	/* Housekeeping Sector    */
	uint8 PC1YTH;	/* PC 1 Y Threshold  */
	uint8 PC1ZTH;	/* PC 1 Z Threshold  */
	uint8 PC2YTH;	/* PC 2 Y Threshold  */
	uint8 PC2ZTH;	/* PC 2 Z Threshold  */
	uint8 PC3YTH;	/* PC 3 Y Threshold  */
	uint8 PC3ZTH;	/* PC 3 Z Threshold  */
	uint8 SSD1TH;	/* SSD 1 Threshold   */
	uint8 BIT1PERIOD;	/* BIT 1 Period   */
	uint8 SSD2TH;	/* SSD 2 Threshold   */
	uint8 BIT2PERIOD;	/* BIT 2 Period   */
	uint8 SSD3TH;	/* SSD 3 Threshold   */
	uint8 BIT3PERIOD;	/* BIT 3 Period   */
	uint8 DEDX1TH;	/* dEdX 1 Threshold   */
	uint8 DEDX2TH;	/* dEdX 2 Threshold   */
	uint8 DEDX3TH;	/* dEdX 3 Threshold   */
	uint8 DET1TRIG;	/* CAMEX 1 Trigger   */
	uint8 DET1EVENT;	/* Valid Event 1 Condition  */
	uint8 DET1GAIN;	/* SSD 1 CAMEX Gain  */
	uint16 DET1CHANNELS;	/* BIT 1 Channels   */
	uint8 DET2TRIG;	/* CAMEX 2 Trigger   */
	uint8 DET2EVENT;	/* Valid Event 2 Condition  */
	uint8 DET2GAIN;	/* SSD 2 CAMEX Gain  */
	uint16 DET2CHANNELS;	/* BIT 2 Channels   */
	uint8 DET3TRIG;	/* CAMEX 3 Trigger   */
	uint8 DET3EVENT;	/* Valid Event 3 Condition  */
	uint8 DET3GAIN;	/* SSD 3 CAMEX Gain  */
	uint16 DET3CHANNELS;	/* BIT 3 Channels   */
	uint16 ACTRCTRL;	/* ACTR Control Register   */
	uint8 FANPRIOR; /* Fan Priority    */
	uint16 ACTRSAMPLE;      /* ACTR Sample Register   */
};
