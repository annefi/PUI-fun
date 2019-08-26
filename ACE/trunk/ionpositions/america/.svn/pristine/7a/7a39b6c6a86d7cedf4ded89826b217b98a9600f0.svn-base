/* $Id: s3_mmonitor.h,v 1.3 1997/05/07 23:15:42 jeff Exp $           */
#include  "hdfi.h"

/*  #define swims_mon_cyclen   64            64*1.0          */
/*  #define swims_mon_cycpersr 60                            */ 

#define  MMON_CYC   60    /*  number of cycles per SR = 60/1   */
#define  MMON_TSZ  3840   /*  total size in bytes              */
#define  MMON_CSZ  MMON_TSZ/MMON_CYC

struct mmonitor  {
           uint32  sctime_readout;      /*  32 bit  spacecraft  time  */
           uint32  sctime_collection;      /*  32 bit  spacecraft  time  */
           uint32  QAC;         /*  number of missing frames in this SR */

           uint8  MONITOR[MMON_CYC][MMON_CSZ];   
};
