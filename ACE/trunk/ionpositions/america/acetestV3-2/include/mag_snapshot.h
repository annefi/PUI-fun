/* $Id: mag_snapshot.h,v 1.6 1997/05/07 18:44:38 jeff Exp $ */
#include "hdfi.h"

#define SNPVAL 21
#define SNAPCYCLELEN 340  /* The snapshot buffer is 340 major frames long */

struct MagSnapSet                   /* setkey=sG                     */
{
  uint32 sctime_readout;            /* 32 bit spacecraft readout time  */
  uint32 sctime_collection;            /* 32 bit spacecraft collection time  */

  uint32 QAC;                       /* number of missing frames in this cycle*/

         /* 21 x, y and z values per major frame  */
  uint16 hxyz[3][SNPVAL*SNAPCYCLELEN];

};
