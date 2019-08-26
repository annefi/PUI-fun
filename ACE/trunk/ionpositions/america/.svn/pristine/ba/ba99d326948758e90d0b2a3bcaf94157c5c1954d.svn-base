/* $Id: s3_sdiag.h,v 1.4 1998/12/07 18:12:39 ad Exp $	     */
#include "hdfi.h"

#define SEP_DIAG_CYCLEN    88 

#define SEP_DIAG_CYCPERSR  60  /* number of diag collection cycles per Science Rec */

/* sctime_readout: spacecraft clock of first minor frame of the EDB */

/* sctime_collection: diag data are collected over 1 spin and output */
/* during the next spin. There are 60 diag collection cycles per SR. */
/* sctime_collection contains the time of the start of the  */
/* collection cycle (spin), in spacecraft clock time units */


struct sdiag{
	uint32 sctime_readout;	/* 32 bit spacecraft time  */
	float64 sctime_collection; /* spacecraft time, sub-second resolution */

	uint16 QAC;	/* number of missing frames in this EDB */

	uint16  concat; /* Sequence number for this structure will be */
		        /* greater than 1 for cases where the number of */
		        /* events in the EDB exceeds SEP_PHA_MAX. In these */
                        /* cases, concat will count down from N to 1, where N */
                        /* is the total number of spha structures for the */
                        /* current EDB. */

	uint16 numevts; /* Number of diag events in this structure. */
                        /* Should be SEP_DIAG_MAX when concat > 1. */
                        /* When concat == 1, numevts <= SEP_DIAG_MAX */
			
        uint16 numevtsedb; /* Number of diag events in the whole EDB */
	
	uint16 edb; /* sequence number of EDB in Science Record (0-59) */

	uint16 DIAG[4][SEP_DIAG_CYCLEN]; /* engineering data */
};
