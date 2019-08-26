/* $Id: mag_avgvec.h,v 1.2 1998/09/18 21:16:21 ad Exp $ */
#include "hdfi.h"

#define MAGAVGDIM 3

struct MagAvgVec
{
  uint32 sctime_readout;          /* 32 bit spacecraft readout time.    */
			          /* scclock for first minor frame */
  uint32 sctime_collection;       /* 32 bit spacecraft collection time    */
                                  /* beginning of MAG data collection cycle */
  uint32 QAC;                     /* number of missing minor frames in this 16-sec cycle */

  float64 b_inertial[MAGAVGDIM];  /* 16 second average mag vector in despun s/c */
			          /* inertial coordinates */
  float64 b_sigma;		  /* dBrms over 16 seconds */
};
