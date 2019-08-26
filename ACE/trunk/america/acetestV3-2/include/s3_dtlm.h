/* $Id: s3_dtlm.h,v 1.1 1997/01/16 17:31:06 jeff Exp $ */

#include "hdfi.h"

struct sshdtlm{
  uint32 sctime;           /* 32 bit spacecraft time             */

  uint32 QAC;              /* =1 if missing data, =0 otherwise */

  uint8 buf[60*34];           /* 34 bytes of hk, including header */
};
