/* $Id: s3schk.h,v 1.3 1997/09/05 22:33:24 jeff Exp $ */
#include "hdfi.h"

struct s3schk    /* Spacecraft housekeeping data for S3 instruments */
{

    uint32 sctime_readout;   /* Readout time */
    uint8 CDHId;             /* C&DH A = 01, C&DH B = 10, error otherwise */

  uint32 SunPulDat[2];    /* Sun sensor data */
		/* bits 31-24 : unused */
		/* bits 23-20 : Mnr frame */
		/* bits 19-10 : sub secont count (684.75 cnts=1 sec)*/
		/* bits  9- 8 : ID bits, 00=err,01=top,10=side,11=neither */
		/* bits  7- 0 : Y angle measurment (Grey code) */
		/* */
		/*   From C&DH Specification (mf0:index=0, mf8:index=1) */
		/* For the time tag in Science minor frame 0: for a minor */
		/* frame ID of 0, the sun pulse would have occured in the */
		/* current major frame.  For a minor frame ID of 1 to 15, */
		/* the sun pulse would have occured in the previous major */
		/* frame */
		/* For the time tag in Science minor frame 8: for a minor */
		/* frame ID of 0-8, the sun pulse would have occured in the */
		/* current major frame.  For a minor frame ID of 9 to 15, */
		/* the sun pulse would have occured in the previous major */
		/* frame */

    /* S3DPU SCHK values */
    uint8 S3PwrCvtVol;       /* S3DPU power converter voltage */
    uint8 S3Cur;             /* S3DPU current */
    uint8 S3ConSecCur;       /* S3DPU converter secondary curent */
    uint8 S3PowSupATmp;      /* S3DPU Power Supply A temp */
    uint8 S3PowSupBTmp;      /* S3DPU Power Supply B temp */
    uint8 S3DckTmp;          /* S3DPU Deck Temp */
    uint8 S3Log;             /* S3DPU Logic and telltale bits */
				/* bit 7: Power conv sel telltale */
				/* bit 6: Interface A/B select */
				/* bit 5: Converter A power */
				/* bit 4: Converter B power */
				/* bits 3-0: not used */


    /* Sepica SCHK values */
    uint8 SepDecTmp;        /* Deck temperature near Sepica */
    uint8 SepCur;           /* Sepica current */
    uint8 SepIsoButTmp;     /* Sepica Iso-butane tank temp */
    uint8 SepLog;           /* Sepica logic and telltales */
				/* bit 7: Sepica Gas Valve */
				/* bit 6: Sepica Main Power */
				/* bit 5: Sepica Internal Heater (1&2)*/
				/* bit 4: Sepica Interface Heater */
				/* bits 3-0: Unused */

    /* Swics SCHK values */
    uint8 SwcCur;              /* SWICS current */
    uint8 SwcIntTmp;           /* SWICS internal temp */
    uint8 SwcDckTmp;           /* SWICS Deck temp */
    uint8 SwcLog;              /* SWICS logic and telltales */
				/* bit 7: SWICS Main Power */
				/* bit 6: SWICS Internal heaters */
				/* bit 5: SWICS Interface heaters */
				/* bit 4: SWICS Pyro Main/Backup */
				/* bits 3-0: Unused */

    /* Swims SCHK values */
    uint8 SwmCur;              /* SWIMS current */
    uint8 SwmIntTmp;           /* SWIMS Internal Temp */
    uint8 SwmLog;              /* SWICS logic and telltales */
				/* bit 7: SWIMS Cover Telltale */
				/* bit 6: SWIMS Main Power */
				/* bit 5: SWIMS Internal Heater */
				/* bit 4: SWIMS Interface Heater */
				/* bit 3: SWIMS Pyro Main/Backup */
				/* bits 2-0: Unused */
};
