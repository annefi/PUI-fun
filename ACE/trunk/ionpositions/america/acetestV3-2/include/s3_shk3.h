/* $Id: s3_shk3.h,v 1.2 1998/12/07 18:12:39 ad Exp $ */
#include "hdfi.h"

struct sshshk3{
	uint32 sctime_readout;	/* first minor frame of readout cycle, */
	                        /* 32 bit spacecraft clock time */
	float64 sctime_collection; /* time of the start of the first spin in the */
	                           /* 5-spin cycle. sub-second resolution */

	uint32 QAC; /* number of missing minor frames in the 5-spin cycle  */

	uint8 HKSECTOR;	/* Housekeeping Sector    */
	uint8 FAN1MODE;	/* Fan 1 Mode   */
	uint8 FAN1BASE;	/* Fan 1 Baseline Subtr.  */
	uint8 FAN1LOGIC;	/* Fan 1 SSD Logic  */
	uint8 FAN1PCY;	/* Fan 1 Valid PC  */
	uint8 FAN1PCZ;	/* Fan 1 Valid PC  */
	uint8 FAN1SSD;	/* Fan 1 Valid SSD  */
	uint8 FAN1BANK;	/* Fan 1 Memory Bank  */
	uint8 FAN1BLOCK;	/* Fan 1 Memory Block  */
	uint8 FAN1DATA;	/* Fan 1 Data Selected  */
	uint8 FAN2MODE;	/* Fan 2 Mode   */
	uint8 FAN2BASE;	/* Fan 2 Baseline Subtr.  */
	uint8 FAN2LOGIC;	/* Fan 2 SSD Logic  */
	uint8 FAN2PCY;	/* Fan 2 Valid PC  */
	uint8 FAN2PCZ;	/* Fan 2 Valid PC  */
	uint8 FAN2SSD;	/* Fan 2 Valid SSD  */
	uint8 FAN2BANK;	/* Fan 2 Memory Bank  */
	uint8 FAN2BLOCK;	/* Fan 2 Memory Block  */
	uint8 FAN2DATA;	/* Fan 2 Data Selected  */
	uint8 FAN3MODE;	/* Fan 3 Mode   */
	uint8 FAN3BASE;	/* Fan 3 Baseline Subtr.  */
	uint8 FAN3LOGIC;	/* Fan 3 SSD Logic  */
	uint8 FAN3PCY;	/* Fan 3 Valid PC  */
	uint8 FAN3PCZ;	/* Fan 3 Valid PC  */
	uint8 FAN3SSD;	/* Fan 3 Valid SSD  */
	uint8 FAN3BANK;	/* Fan 3 Memory Bank  */
	uint8 FAN3BLOCK;	/* Fan 3 Memory Block  */
	uint8 FAN3DATA;	/* Fan 3 Data Selected  */
};
