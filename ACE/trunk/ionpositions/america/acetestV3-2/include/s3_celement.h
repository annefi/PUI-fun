/* $Id: s3_celement.h,v 1.3 1997/05/07 22:58:29 jeff Exp $           */
#include  "hdfi.h"

#define  CTIME_CYC   1    /* number of cycle per SR=  60/60   */
#define  CTIME_TSZ  120  /* total size in bytes  */
#define  CTIME_CSZ  CTIME_TSZ/CTIME_CYC

struct celement  {
           uint32  sctime_readout;   /*  readout : 32 bit S/C  time  */
           uint32  sctime_collection;   /*  collection : 32 bit  S/C  time  */
           uint32  QAC;         /* number of missing frams in this SR */

           uint8  ELEMENT[CTIME_TSZ];     
};
