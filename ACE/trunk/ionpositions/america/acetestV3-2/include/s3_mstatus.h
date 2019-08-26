/* $Id: s3_mstatus.h,v 1.2 1997/05/06 19:11:02 jeff Exp $           */
#include  "hdfi.h"

struct mstatus  {
           uint32  sctime_readout;      /*  32 bit  spacecraft  time  */
           uint32  sctime_collection;      /*  32 bit  spacecraft  time  */
           uint32  QAC;         /*  number of missing frames in this SR */

           uint16  STACMD[60];        /*  Command bytes   */
           uint32  STARET[60];        /*  Return  bytes   */

};
