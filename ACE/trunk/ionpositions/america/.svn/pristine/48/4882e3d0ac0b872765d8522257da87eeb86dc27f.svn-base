/* $Id: mag_vector.h,v 1.5 1997/05/07 18:44:38 jeff Exp $ */
#include "hdfi.h"

#define MAGNUMVCT 96
#define MAGVECDIM 3

struct MagVectorSet
{
  uint32 sctime_readout;         /* 32 bit spacecraft readout time    */
  uint32 sctime_collection;         /* 32 bit spacecraft collection time    */

  uint32 QAC;              /* number of missing frame in this cycle */

  int16 vector[MAGVECDIM][MAGNUMVCT];  /* component of magnetic vector  */
};
