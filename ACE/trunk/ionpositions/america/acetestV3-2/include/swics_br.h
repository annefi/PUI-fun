/* $Id: swics_br.h,v 1.2 1999/09/01 21:22:19 ad Exp $ */
#include "hdfi.h"

struct Swics_br
{
  float64 bin_start;            /* beginning of bin. ACE epoch */
  float64 bin_end;              /* end of bin. ACE epoch */

  int32 dpps[60];               /* DPPS voltage */
  int32 grpaps[60];             /* Post-Accel. Power Supply voltage (unconverted - mult by 0.15) */
  int32 edb[60];                /* = (EDB,-1) if (good/bad) EDB */
  int32 rate[5][60];            /* unsectored, decompressed rates */
				/* 0=H+(AuxH), 1=He++, 2=O6, 3=O7, 4=Fe(8-11) */
};
