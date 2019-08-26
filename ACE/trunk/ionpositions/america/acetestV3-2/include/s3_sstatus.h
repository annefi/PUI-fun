/* $Id: s3_sstatus.h,v 1.3 1998/12/07 18:12:39 ad Exp $	     */
#include "hdfi.h"

/* sctime_readout: scclock of first minor frame of Science Record */

struct sstatus{
	uint32 sctime_readout;	/* 32 bit spacecraft time  */

	uint32 QAC;	/* number of missing frames in this SR */
	uint8  QACarr[720]; /* array of flags indicating which minor frames */
	                    /* in the SR are missing. 0=OK, 1=missing */

	uint16 STACMD[60];  /* Command bytes */
	uint32 STARET[60];  /* Return bytes */
};
