/* $Id: swepam_drawi.h,v 1.1 1997/06/20 18:02:25 jeff Exp $ */
#include "hdfi.h"

struct DRAWI
{
  uint32 output_sctime;   /* time for beginning of data output cycle */
  uint32 collect_sctime;  /* time for beginning of data collection */
  uint8  QAC;              /* number of bad frames in this cycle */

  uint8 rawdat[16*68];  /* One swepam-i minor frame */
};
