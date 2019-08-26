/* $Id: uleis_statblk_trl.h,v 1.8 1997/11/15 00:00:24 steves Exp $ */

#include "hdfi.h"

#define U_MAJFRM              8		/* 8 major frames (0-7) */
#define U_STATBLK_SIZE       14		/* Status block of 14 bytes */
#define U_TRL_SIZE           128	/* Status trailer of 128 bytes */

struct UStatBlkTrlSet
{
  uint32 output_sctime;		/* time for beginning of data output cycle */
  uint32 collect_sctime;	/* time for beginning of data collection */
  uint32 QAC;			/* number of bad frames in this cycle */
  uint8 chk_sum_chk;	      /* 0 means chk_sum test passed; 1 means failed */
                              /*   also in uleis_hskp.h                      */

     /* Status Block: 8 major frames, 14 bytes */
/*  uint8 statblock[U_MAJFRM][U_STATBLK_SIZE];*/

     /* Status Trailer: 128 bytes */
/*  uint8 trailer[U_TRL_SIZE];*/


/* variable set */

     /* Status Block: 112 bytes */
  uint16 Sync;               /*Status Block 0   Byte  1- 2 */ /* = FAFE */ 
  uint16 SoftwareID;                         /* Byte  3- 4 */
  uint16 MinFrCnt;                           /* Byte  5- 6 */
  uint16 CmdAccCnt;                          /* Byte  7- 8 */
  uint16 CmdRejCnt;                          /* Byte  9-10 */
  uint32 CmdEcho;                            /* Byte 11-14 */
  uint32 RejCmdEcho;         /*Status Block 1   Byte  1- 4 */
  uint16 CmdSide1IntrCnt;                    /* Byte  5- 6 */
  uint16 CmdSide2IntrCnt;                    /* Byte  7- 8 */
  uint16 CodePagNum;                         /* Byte  9-10 */
  uint16 SunSectrID;                         /* Byte 11-12 */
  uint16 SpinCntReg;                         /* Byte 13-14 */
  uint16 WatchdogCnt;        /*Status Block 2   Byte  1- 2 */
  uint16 RamPag1TestRslts;                   /* Byte  3- 4 */
  uint16 RamPag2TestRslts;                   /* Byte  5- 6 */
  uint16 EEPROMCksum;                        /* Byte  7- 8 */
  uint16 TimerIntrCnt;                       /* Byte  9-10 */
  uint16 CurTLMSide;                         /* Byte 11-12 */
  uint16 DefTLMSide;                         /* Byte 13-14 */
  uint16 MemPekVal;          /*Status Block 3   Byte  1- 2 */
  uint16 MemPekPagNum;                       /* Byte  3- 4 */
  uint16 MemPekAddr;                         /* Byte  5- 6 */
  uint16 MemPokVal;                          /* Byte  7- 8 */
  uint16 MemPokPagNum;                       /* Byte  9-10 */
  uint16 MemPokAddr;                         /* Byte 11-12 */
  uint16 MemDmpPagNum;                       /* Byte 13-14 */
  uint16 MemDmpAddrPntr;     /*Status Block 4   Byte  1- 2 */
  uint16 OutputPort0PokVal;                  /* Byte  3- 4 */
  uint16 OutputPort1PokVal;                  /* Byte  5- 6 */
  uint16 OutputPort2PokVal;                  /* Byte  7- 8 */
  uint16 OutputPort6PokVal;                  /* Byte  9-10 */
  uint16 InputPort0Val;                      /* Byte 11-12 */
  uint16 InputPort1Val;                      /* Byte 13-14 */
  uint16 InputPort2Val;      /*Status Block 5   Byte  1- 2 */
  uint16 InputPort6Val;                      /* Byte  3- 4 */
  uint16 EEPROMPag3Stat;                     /* Byte  5- 6 */
  uint16 EEPROMPag67Stat;                    /* Byte  7- 8 */
  uint16 CtrlWord2CmdStat;                   /* Byte  9-10 */
  uint16 MemLdSiz;                           /* Byte 11-12 */
  uint16 MemLdPag;                           /* Byte 13-14 */
  uint16 MemLdAddr;          /*Status Block 6   Byte  1- 2 */
  uint16 MemLdCksum;                         /* Byte  3- 4 */
  uint16 MemLdComCksum;                      /* Byte  5- 6 */
  uint16 MemLdCksumErrCnt;                   /* Byte  7- 8 */
  uint16 AECmdErrCnt;                        /* Byte  9-10 */
  uint16 AECmdIntrCnt;                       /* Byte 11-12 */
  uint16 MajFrCntx8;                         /* Byte 13-14 */
  uint16 Spn1SpnCnt;         /*Status Block 7   Byte  1- 2 */
  uint16 Spn2SpnCnt;                         /* Byte  3- 4 */
  uint16 Spn3SpnCnt;                         /* Byte  5- 6 */
  uint16 Spn4SpnCnt;                         /* Byte  7- 8 */
  uint16 Spn5SpnCnt;                         /* Byte  9-10 */
  uint16 Spn6SpnCnt;                         /* Byte 11-12 */
  uint16 Spn7SpnCnt;                         /* Byte 13-14 */

     /* Status Trailer: 128 bytes 	(as of 4/7/97) */
  uint16 Spn8SpnCnt;        /*Status Trailer   Byte   1-  2 */
  uint16 Spn9SpnCnt;                        /* Byte   3-  4 */
  uint16 Spn10SpnCnt;                       /* Byte   5-  6 */
  uint16 CumSpnCnt;                         /* Byte   7-  8 */
  uint16 EvntCnt;                           /* Byte   9- 10 */
  uint16 Spn1MinFrCnt;                      /* Byte  11- 12 */
  uint8  HVAutFlg;                          /* Byte  13     */
  uint8  HVActFlg;                          /* Byte  14     */

  uint8  HK_ADC[16][3];                     /* Byte  15- 62 */

  uint8  PHAFrzFlg;			    /* Byte  63     0=dsabl,1=enbl*/
  uint8  SSDEnaFlg;                         /* Byte  64     */
  uint8  AEAutoResetEnaFlg;                 /* Byte  65     */
  uint8  CalModFlg;                         /* Byte  66     */
  uint8  TOFFlg;                            /* Byte  67     22=TOF1,24=TOF2*/
  uint8  AETlltlBits;                       /* Byte  68     */
  uint16 MotrAutFlg;                        /* Byte  69- 70 */
  uint8  MotrPwrFlg;                        /* Byte  71     0=off,nonzero=on*/
  uint8  MotrFid;                           /* Byte  72     */
  uint16 MotrPostn;                         /* Byte  73- 74 */


  uint16 Rt1MinSectr;                       /* Byte  75- 76 */
  uint16 Rt1MinSpn;                         /* Byte  77- 78 */
  uint16 Rt1HiSecErrLim;                    /* Byte  79- 80 */
  uint16 Rt1LoSecErrLim;                    /* Byte  81- 82 */
  uint16 Rt1HiSpnErrLim;                    /* Byte  83- 84 */
  uint16 Rt1LoSpnErrLim;                    /* Byte  85- 86 */
  uint16 Rt1Indx;                           /* Byte  87- 88 */


  uint16 Rt2MinSectr;                       /* Byte 89-90   */
  uint16 Rt2MinSpn;                         /* Byte 91-92   */
  uint16 Rt2HiSecErrLim;                    /* Byte 93-94   */
  uint16 Rt2LoSecErrLim;                    /* Byte 95-96   */
  uint16 Rt2HiSpnErrLim;                    /* Byte 97-98   */
  uint16 Rt2LoSpnErrLim;                    /* Byte 99-100  */
  uint16 Rt2Indx;                           /* Byte 101-102 */
  uint16 MtrErrFlg;                         /* Byte 103-104 */
  uint8  MtrMotnFlg;                        /* Byte 105     0=No Motion*/
  uint8  EvntRdoutFmt;                      /* Byte 106     */
  uint8  MUXSelMd;                          /* Byte 107     */
  uint8  VS1Enab;                           /* Byte 108     */
  uint8  VS2Enab;                           /* Byte 109     */
  uint8  VS1VS2Enab;                        /* Byte 110     */
  uint16 PHARnkSpn1Sec1;                    /* Byte 111-112 */
  uint16 PHARnkSpn1Sec2;                    /* Byte 113-114 */
  uint16 PHARnkSpn1Sec3;                    /* Byte 115-116 */
  uint16 PHARnkSpn1Sec4;                    /* Byte 117-118 */
  uint16 PHARnkSpn1Sec5;                    /* Byte 119-120 */
  uint16 PHARnkSpn1Sec6;                    /* Byte 121-122 */
  uint16 PHARnkSpn1Sec7;                    /* Byte 123-124 */
  uint16 PHARnkSpn1Sec8;                    /* Byte 125-126 */
  /* 16-bit sum of first 7999 words */
  uint16 SciRecCksum;                       /* Byte 127-128 */

}; 
