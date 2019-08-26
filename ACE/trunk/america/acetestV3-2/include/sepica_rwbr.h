/* $Id: sepica_rwbr.h,v 1.3 1998/02/18 21:55:37 asc Exp $ */
#include "hdfi.h"

#define SEP_GEOMFAC .18   /* cm2 - sr */

struct Sepica_rwbr
{
  float64 bin_start;  /* beginning of bin. # of sec since Jan 1 1996 UTC */
  float64 bin_end;  /* end of bin. # of sec since Jan 1 1996 UTC */

    /* rate for indicated channel, negative values indicate */
    /* missing data */
    float32 H_lo;             /* low Energy (0.1-0.8 Mev/n) H channel */
    float32 H_hi;             /* high Energy (0.8-9.0 Mev/n) H channel */
    float32 He_lo;            /* low Energy (0.025-0.75 MeV/n) He channel */
    float32 He_hi;            /* high Energy (0.75-14 MeV/n) He channel */
    float32 C;                /* (1.5-25 MeV/n) C channel */
    float32 O;                /* (1.12-18.8 MeV/n) O channel */
    float32 Mg_Si;            /* (0.7-11.5 MeV/n) Mg,Si channel */
    float32 Fe;               /* (0.35-5.75 MeV/n) Fe channel */

    float32 livetime;       /* livetime for this cycle */
};
