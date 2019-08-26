/* $Id: swepam_drawe.h,v 1.1 1997/06/20 18:02:10 jeff Exp $ */
#include "hdfi.h"

struct DRAWE
{
  uint32 output_sctime;   /* time for beginning of data output cycle */
  uint32 collect_sctime;  /* time for beginning of data collection */
  uint8  QAC;             /* number of bad frames in this cycle */

  uint8 rawdat[16*57];  /* One SWEPAM-E minor frame */
};
