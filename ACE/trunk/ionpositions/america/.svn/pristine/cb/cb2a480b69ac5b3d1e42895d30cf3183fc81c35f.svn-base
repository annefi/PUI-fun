/* $Id: s3_edb.h,v 1.1 1997/08/15 20:15:22 jeff Exp $ */
#include "hdfi.h"

struct s3_edb
{
  uint32 sctime_readout;         /* 32 bit spacecraft readout time    */
  float64 ACEepoch_collection;  /* Spin start time.  # of sec since 1/1/96 */

  uint8 QAC;              /* number of missing frame in this cycle */
  uint8 QACarr[12];       /* =1 frame missing (bad), =0 frame OK */ 

  uint8 data[12][203];    /* 12 frames of S3DPU data in a complete EDB */

};
