/* $Id: swepam_dloadi.h,v 1.2 1997/07/17 00:07:04 jeff Exp $ */
#include "hdfi.h"

struct DLOADI              /* Swepam Ion Load Mode*/
{
  uint32 output_sctime;   /* time for beginning of data output cycle */
  uint32 collect_sctime;  /* time for beginning of data collection */
  uint8  QAC;             /* number of bad frames in this cycle */

  uint8    MinFrmIndx[16];     /* minor frame index. */
  uint8    EventFlag[16];     /* Event flags. */
  uint8    StatRec[16][3];    /* 3 status record/frame. */
  uint8    LoadErrRec[16][6];    /* 6 byte load error/frame */
  uint8    LoadErrFil[16][26];   /* 26 bytes of load error fill data */
  uint16   DumpRecAdd[16];    /* address of first data byte in dump record */
  uint8    DumpRecDat[16][28]; /* 28 bytes of dump record data/frame */
  uint8    MinFrmChk[16];     /* 2's compliment checksum- 1 per frame */
};
  
