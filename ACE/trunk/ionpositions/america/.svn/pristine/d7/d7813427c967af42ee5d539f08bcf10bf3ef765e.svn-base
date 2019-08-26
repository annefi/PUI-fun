/* $Id: magframe_out_br.h,v 1.7 1998/04/16 18:32:30 ad Exp $ */
#include "hdfi.h"

struct MagFrm_out_br
{
  float64 bin_start;  /* beginning of bin. # of sec since Jan 1 1996 UTC */
  float64 bin_end;    /* end of bin. # of sec since Jan 1 1996 UTC */

  float64 b_out[3];
  float64 b_mag_av;
  float64 b_sigma;
  uint32 iflag_out;
  uint8  weight;
};

/*The identity of the variables is as follows: */
/*b_out[3]	are the 3 (R,T,N) components of the output 16-second */
/*		average of the IMF. */
/*b_mag_av      the value of <|B|> computed over 16 seconds */
/*b_sigma       dBrms over 16 seconds */
/* weight       number of individual measurements in the average */
/*iflag_out	obsolete. Now set to be same as weight */
