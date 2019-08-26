/* $Id: s3_mbasic.h,v 1.3 1997/05/07 23:15:42 jeff Exp $ */
#include  "hdfi.h"

/* #define swims_basic_cyclen   32             32*1.0          */
/* #define swims_basic_cycpersr 60                             */
#define  MBAS_CYC  60                 /* number of cycles per SR= 60/1   */
#define  MBAS_TSZ  1920               /* total size in bytes             */
#define  MBAS_CSZ  MBAS_TSZ/MBAS_CYC 

struct mbasic  {
           uint32  sctime_readout;      /*  32 bit  spacecraft  time  */
           uint32  sctime_collection;      /*  32 bit  spacecraft  time  */
           uint32  QAC;         /*  number of missing frames in this SR */

           uint8  BASIC[MBAS_CYC][MBAS_CSZ]; 
};
