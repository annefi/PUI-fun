/* $Id: s3_cstatus.h,v 1.2 1997/05/06 19:10:16 jeff Exp $           */
#include  "hdfi.h"

struct cstatus  {
           uint32  sctime_readout;      /*  32 bit  spacecraft  time  */
           uint32  sctime_collection;   /*  32 bit  spacecraft  time  */
           uint32  QAC;         /* number of missing frames in this ST */

           uint16  STACMD[60];        /*  Command bytes   */
           uint32  STARET[60];        /*  Return  bytes   */
};
