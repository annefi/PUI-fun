/* $Id: BrowseSis_1.h,v 1.1 2001/11/14 00:35:01 rgr Exp $ */

/* $Source: /users/asc/aceprog/include/RCS/BrowseSis_1.h,v $ */
/* $Author: rgr $ */
/* $Date: 2001/11/14 00:35:01 $ */
/* $Revision: 1.1 $ */

#include "hdfi.h"
#include "SisConstants.h"

struct BrowseSis_1 {
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

   float32 CounterRtsw0[NUM_SIS_HIGH_PRIORITY_SAMPLES];
   float32 CounterRtsw1[NUM_SIS_HIGH_PRIORITY_SAMPLES];

   float32 RateT4;
   float32 RateCoin1;
   float32 WgtFactT4;
   float32 WgtFactCoin1;
};
