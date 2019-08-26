/* $Id: s3_spha.h,v 1.6 1998/12/07 18:12:39 ad Exp $	     */
#include "hdfi.h"

#define SEP_PHA_MAX 30     /* the maximum number of pha events that fit */
                           /* into this data structure - an arbitrary number */

#define SEP_PHA_CYCPERSR 60 /* number of pha collection cycles per Science Rec */

/* sctime_readout: spacecraft clock of first minor frame of the EDB */

/* sctime_collection: pha data are collected over 1 spin and output */
/* during the next spin. There are 60 pha collection cycles per SR. */
/* sctime_collection contains the time of the start of the */
/* collection cycle (spin), in spacecraft clock time units */

struct spha{
	uint32 sctime_readout;	   /* 32 bit spacecraft time  */
	float64 sctime_collection; /* spacecraft time, sub-second resolution */

	uint16 QAC;	/* number of frames missing in this EDB */

	uint16  concat; /* Sequence number for this structure will be */
		        /* greater than 1 for cases where the number of */
		        /* events in the EDB exceeds SEP_PHA_MAX. In these */
		        /* cases, concat will count down from N to 1, where N */
			/* is the total number of spha structures for the */
			/* current EDB. */

	uint16 numevts; /* Number of pha events in this data structure. */
                        /* Should be SEP_PHA_MAX when concat > 1. */
			/* When concat == 1, numevts <= SEP_PHA_MAX */

	uint16 numevtsedb; /* Number of pha events in the whole EDB */

	uint16 edb; /* sequence number of EDB in Science Record (0-59) */
	
	uint8  range[SEP_PHA_MAX]; /* range*/
	uint8  sector[SEP_PHA_MAX];/* sector*/
	uint8  fan[SEP_PHA_MAX];   /* fan */
	uint8  sys[SEP_PHA_MAX];   /* sys*/
	uint8  dZ[SEP_PHA_MAX];    /*  delta Z */
	uint16 E[SEP_PHA_MAX];     /* Energy*/
	uint8  Eg[SEP_PHA_MAX];    /* Energy gain bit */
	uint16 dE[SEP_PHA_MAX];    /* delta Energy */
	uint8  dEg[SEP_PHA_MAX];   /* delta Energy gain bit*/
	uint16 Y[SEP_PHA_MAX];     /* Y value */
};
