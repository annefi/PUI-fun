/* $Id: s3_dummy.h,v 1.3 1998/09/28 05:31:14 asc Exp $ */
#include "hdfi.h"

struct s3_dummy
{
  uint32 sctime_readout;         /* 32 bit spacecraft readout time    */

  uint8 data[203];    /* S3 dummy minor frame data */

};
