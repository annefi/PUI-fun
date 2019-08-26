/* $Id: uleis_br_out.h,v 1.2 1997/09/22 16:35:21 steves Exp $ */
#include "hdfi.h"

struct Uleis_br_out
{
  float64 bin_start;  /* beginning of bin. # of sec since Jan 1 1996 UTC */
  float64 bin_end;    /* end of bin. # of sec since Jan 1 1996 UTC */

  float32 ULEIS_livetime;   /* livetime for this measurement. */

  uint16 rate_assign[9];
  float32 brws_rates[9];
};
