/* $Id: s3_mtof.h,v 1.3 1997/05/07 23:15:42 jeff Exp $           */
#include  "hdfi.h"

#define  MTIME_CYC   1    /* number of cycle per SR=  60/60   */
#define  MTIME_TSZ  2100  /* total size in bytes  */
#define  MTIME_CSZ  MTIME_TSZ/MTIME_CYC

struct mtof  {
           uint32  sctime_readout;      /*  32 bit  spacecraft  time  */
           uint32  sctime_collection;      /*  32 bit  spacecraft  time  */
           uint32  QAC;         /*  number of missing frames in this SR */

           uint8  MTOF[MTIME_TSZ];     
};
