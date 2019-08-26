/* $Id: uleis_hskp.h,v 1.8 1997/11/14 23:57:55 steves Exp $ */

#include "hdfi.h"

#define NUMFRM 128		/* number of minor frames in a cycle */

struct UHskpSet
{
  uint32 output_sctime;		/* time for beginning of data output cycle */
  uint32 collect_sctime;	/* time for beginning of data collection */

  uint32 QAC;			/* number of missing frames in this cycle */
  uint8 chk_sum_chk;	      /* 0 means chk_sum test passed; 1 means failed */
                              /*   also in uleis_statblk_trl.h               */

   /* position flag (1 = yes, 0 = no) of dump data in each mnr frm */
   /* puts the total for this minor frame in last array element */
  uint8 dump_flg[129];

   /* position flag (1 = yes, 0 = no) of Status TLM data in each mnr frm */
   /* puts the total for this minor frame in last array element */
  uint8 stat_tlm_flg[129];

  uint8 DeckTemp[8];		/* mf 0  - Instrument Deck Temp: near ULEIS */
  uint8 lvps_voltage[8];	/* mf 9  - lvps voltage */
  uint8 total_cur[8];		/* mf 10 - total current */
  uint8 lvps_cur_analg[8];	/* mf 10 - analog elect. lvps current */
  uint8 heater_cur[8];		/* mf 10 - Internal & I/F Heater Current */
  uint8 telescp_temp[8];	/* mf 12 - telescope temperature */
  uint8 analg_elect_temp[8];	/* mf 12 - analog electr. temp. (internal) */
  uint8 dpu_temp[8];		/* mf 12 - dpu temperature (internal) */

  uint8 UPowBits[8];		/* power switching and ordinance array */
/*- ULEIS power switching and ordinance (start bit count at 1, not 0) -*/
/*  element postn 7: Internal Heaters         bit pos 20 of 112 (ON/OFF) */
/*  element postn 6: Interface Heater         bit pos 21 of 112 (ON/OFF) */
/*  element postn 5: Main System Power        bit pos 24 of 112 (ON/OFF) */
/*  element postn 4: Pyro A Arm (ICI-1SE192F) bit pos 60 of 112 (ON/OFF) */
/*  element postn 3: Pyro B Arm (ICI-1SE192F) bit pos 63 of 112 (ON/OFF) */
/*  element postn 2: 0                                                   */
/*  element postn 1: 0                                                   */
/*  element postn 0: 0                                                   */

  /* sunpulse data */
  uint8  PhaseAng[NUMFRM];   /* Phase angle for each frame in this cycle*/
  uint8  SunSenID[NUMFRM];   /* bits 7-2=0, bit1=sunsentop,bit0=sunsenside*/
  uint16 SunPulLat[2][8];     /* sun pulse latched at mn frm 0&8 [2] */
			     /* over the 8 [8] major frame cycle */
			     /* SC spin clock value at the time of the sun */
			     /* pulse */
  uint32 SunPulDat[2][8];    /* Time of sun pulse */
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


};
