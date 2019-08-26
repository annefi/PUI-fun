/* $Id: BrowseSis.h,v 1.3 1997/09/11 00:07:52 jeff Exp $ */

/* $Source: /home/mussel9/asc/aceprog/include/RCS/BrowseSis.h,v $ */
/* $Author: jeff $ */
/* $Date: 1997/09/11 00:07:52 $ */
/* $Revision: 1.3 $ */

#include "hdfi.h"

struct BrowseSis {
   float64 bin_start;
   float64 bin_end;
   float32 FluxProton_6_5;
   float32 FluxProton_7_5;
   float32 FluxHelium_3_7;
   float32 FluxHelium_4_8;
   float32 FluxHelium_7_4;
   float32 FluxHelium_14;
   float32 FluxCno_7;
   float32 FluxCno_9_7;
   float32 FluxCno_15;
   float32 FluxCno_28;
   float32 FluxHiZ_9_4;
   float32 FluxHiZ_13_6;
   float32 FluxHiZ_21_4;
   float32 FluxHiZ_41;
   float32 FluxPen;
   float32 FluxHeliumSubset;
   float32 FluxCnoSubset;
   float32 WgtFactProton_6_5;
   float32 WgtFactProton_7_5;
   float32 WgtFactHelium_3_7;
   float32 WgtFactHelium_4_8;
   float32 WgtFactHelium_7_4;
   float32 WgtFactHelium_14;
   float32 WgtFactCno_7;
   float32 WgtFactCno_9_7;
   float32 WgtFactCno_15;
   float32 WgtFactCno_28;
   float32 WgtFactHiZ_9_4;
   float32 WgtFactHiZ_13_6;
   float32 WgtFactHiZ_21_4;
   float32 WgtFactHiZ_41;
   float32 WgtFactPen;
   float32 WgtFactHeliumSubset;
   float32 WgtFactCnoSubset;
};
