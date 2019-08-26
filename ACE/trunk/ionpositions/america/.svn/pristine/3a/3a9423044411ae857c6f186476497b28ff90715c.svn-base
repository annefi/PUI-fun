/* $Id: s3_cbasic.h,v 1.4 1999/09/01 21:22:19 ad Exp $           */

/* SWICS basic rates */

#include  "hdfi.h"

#define  CBAS_N    12                 /* number of basic rates, only 8 used? */
#define  CBAS_S    8                  /* number of sectors */
#define  CBAS_CYC  60                 /* number of cycles per SR= 60/1   */
#define  CBAS_TSZ  ( CBAS_N*CBAS_S*CBAS_CYC ) /* total size in bytes 60x8x12     */
#define  CBAS_CSZ  ( CBAS_N*CBAS_S )

struct cbasic  {
           uint32  sctime_readout;      /*  32 bit  spacecraft  time  */
           uint32  sctime_collection;   /*  32 bit  spacecraft  time  */
           uint32  QAC;         /*number of missing frams in this SR  */

           uint8  BASIC[CBAS_CYC][CBAS_CSZ]; 

};
