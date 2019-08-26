/* $Id: swepam_dloade.h,v 1.2 1997/07/17 00:07:04 jeff Exp $ */
#include "hdfi.h"

struct DLOADE         /* Load Mode  */
{
  uint32 output_sctime;   /* time for beginning of data output cycle */
  uint32 collect_sctime;  /* time for beginning of data collection */
  uint8  QAC;              /* number of bad frames in this cycle */

  uint8  MinFrmIndx[16]; /* minor frame index. element 0= 8 bits of mjfrm hdr*/
  uint8  EventFlag[16];   /* Event flags. element 0= 16bits of mjfrm hdr*/
  uint8  StatRec[16][3]; /* 3 status record/frame.element 0 =24 mjfrmhdr bits*/
  uint8  LoadErrRec[16][6]; /* 6 bytes of LoadErrRec /frame */
  uint8  LoadErrFil[16][15]; /* 15 bytes of LoadErrFill /frame */
  uint16 DumpRecAdd[16];   /* Address of DumpRecDat */
  uint8  DumpRecDat[16][28];   /* 28 bytes of DumpRec / frame */
  uint8  MinFrmChk[16];  /* 2's compliment checksum */
};
