/* $Id: swepam_denge.h,v 1.2 1997/07/17 00:07:04 jeff Exp $ */
#include "hdfi.h"

struct DENGE
{
  uint32 output_sctime;   /* time for beginning of data output cycle */
  uint32 collect_sctime;  /* time for beginning of data collection */
  uint8  QAC;             /* number of bad frames in this cycle */

  uint8  MinFrmIndx[16];  /* minor frame count.  element 0 not reported*/
  uint8  EventFlag[16];   /* Event flags. element 0 not reported */
  uint8  StatRec[16][3];  /* 3 status record/frame.  frame 0 no data */
  uint16 ScalarRecDat[16][7]; /* 7 Scalar channels /frame */
  uint8  ScalarRecFil[16][7]; /* 7 bytes of Scalar fill /frame */
  uint16 DumpRecAdd[16];   /* DumpRec Address */
  uint8  DumpRecDat[16][28];   /* DumpRec data */
  uint8  MinFrmChk[16];  /* 2's compliment checksum */
};
