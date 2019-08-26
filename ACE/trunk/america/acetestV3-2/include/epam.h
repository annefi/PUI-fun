/* $Id: epam.h,v 1.8 1997/08/06 19:51:21 jeff Exp $ */

#include "hdfi.h"

#define NUMFRM 128  /* number of minor frames in a cycle */
#define BYTMIN 21   /* number of bytes of epam data per minor frame */

/* reported every 8 major frames (128 minor frames)*/
/* some items are subcommed, hence there are only 2 of them in 8 frames */

struct EpamData
{
  uint32 sctime_readout;      /* 32 bit spacecraft time at readout */
  uint32 sctime_collection;   /* 32 bit spacecraft time at collection*/

  uint32 QAC;	  /* indicates the number of missing frame in this cycle */
  uint8 QACarr[NUMFRM]; /* each entry corresponds to a single minor frame */
		    /* if value =0 frame is OK.  =1 frame contains fill data*/

  uint8 data[NUMFRM][BYTMIN]; /* 21 bytes data per minor frame */
				/* 128 minor frames per cycle */

  /* sunpulse data */
  uint16 PhaseAng[NUMFRM];   /* Phase angle for each frame in this cycle*/
  uint16 SunPulLat[2][8];     /* sun pulse latched at mn frm 0&8 [2] */
			     /* over the 8 [8] major frame cycle */
  uint32 SunPulDat[2][8];    /* Sun sensor data */
		/* bits 31-24 : unused */
		/* bits 23-20 : Mnr frame */
		/* bits 19-10 : sub secont count (684.75 cnts=1 sec)*/
		/* bits  9- 8 : ID bits, 00=err,01=top,10=side,11=neither */
		/* bits  7- 0 : Y angle measurment (Grey code) */
		/* */
		/*   From C&DH Specification (mf0:index1=0, mf8:index1=1) */
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


  /* Housekeeping data is here */
  uint8 Cal[8];                    /* int/ext cal readout                  */
  uint8 Ref10[2];                  /* +10V Ref Monitor                     */
  uint8 Mon10[2];                  /* +10V Monitor                         */
  uint8 Mon6[2];                   /* +6V Monitor                          */
  uint8 Bias[2];                   /* Detector Bias Voltage Monitor        */
  uint8 AmpTemp[2];                /* Log Amp D Temperature                */
  uint8 MFSATemp[2];               /* MFSA Log Amp D Temperature           */
  uint8 DetTemp[2];                /* Detector D Temperature               */
  uint8 YTemp[2];                  /* EPAM 2B Yoke Temperature             */
  uint8 InCur[8];                  /* input current monitor                */
  uint8 E1Temp[8];                 /* epam 1 electronics temp.             */
  uint8 Sen2ATemp[8];              /* epam 2a sensor temp.                 */
  uint8 Sen2BTemp[8];              /* epam 2b sensor temp.                 */
  uint8 DeckTemp[8];               /* Instrument Deck Temp near EPAM       */
  uint8 Cur[8];                    /* epam current                         */
  uint8 HtrCur[8];                 /* epam heater current                  */
  uint8 PowBits[8];                /* power switching and ordinance bits   */
  /*--- EPAM power switching and ordinance bits ---*/
  /*--- bit position 7: Interface Heater   at position 10 of 112 bits ---*/
  /*--- bit position 6: Internal Heaters   at position 11 of 112 bits ---*/
  /*--- bit position 5: Main System Power  at position 28 of 112 bits ---*/
  /*--- bit position 4: PyroArm (LEMS 30)  at position 56 of 112 bits ---*/
  /*--- bit position 3: PyroArm (LEMS 120) at position 57 of 112 bits ---*/
  /*--- bit position 2: PyroArm (CD)       at position 58 of 112 bits ---*/
  /*--- bit position 1: 0                                             ---*/
  /*--- bit position 0: 0                                             ---*/
};
