/* $Id: s3_cmonitor.h,v 1.4 1999/09/01 21:22:19 ad Exp $           */

/* SWICS monitor rates */

#include  "hdfi.h"

#define  CMON_N     6    /*  number of monitor rates   */
#define  CMON_S     8    /*  number of sectors   */
#define  CMON_CYC  60    /*  number of cycles per SR = 60/1   */
#define  CMON_TSZ  ( CMON_N*CMON_S*CMON_CYC )   /*  total size in bytes */
#define  CMON_CSZ  ( CMON_N*CMON_S )

struct cmonitor  {
           uint32  sctime_readout;      /*  32 bit  spacecraft  time  */
           uint32  sctime_collection;      /*  32 bit  spacecraft  time  */
           uint32  QAC;         /* number of missing frames in this SR */

           uint8  MONITOR[CMON_CYC][CMON_CSZ];   
};
