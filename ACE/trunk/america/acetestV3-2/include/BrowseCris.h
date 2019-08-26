/* $Id: BrowseCris.h,v 1.3 1997/09/11 00:07:52 jeff Exp $ */

/* $Source: /home/mussel9/asc/aceprog/include/RCS/BrowseCris.h,v $ */
/* $Author: jeff $ */
/* $Date: 1997/09/11 00:07:52 $ */
/* $Revision: 1.3 $ */

#include "hdfi.h"

struct BrowseCris {
   float64 bin_start;
   float64 bin_end;
   float32 FluxHelium_31;
   float32 FluxHelium_41;
   float32 FluxHelium_70;
   float32 FluxCno_63;
   float32 FluxCno_84;
   float32 FluxCno_144;
   float32 FluxCnoSum;
   float32 FluxHiZ_92;
   float32 FluxHiZ_124;
   float32 FluxHiZ_220;
   float32 FluxHiZSum;
   float32 FluxPen;
   float32 FluxPenSubset;
   float32 WgtFactHelium_31;
   float32 WgtFactHelium_41;
   float32 WgtFactHelium_70;
   float32 WgtFactCno_63;
   float32 WgtFactCno_84;
   float32 WgtFactCno_144;
   float32 WgtFactCnoSum;
   float32 WgtFactHiZ_92;
   float32 WgtFactHiZ_124;
   float32 WgtFactHiZ_220;
   float32 WgtFactHiZSum;
   float32 WgtFactPen;
   float32 WgtFactPenSubset;
};
