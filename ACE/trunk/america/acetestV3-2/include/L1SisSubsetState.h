/* $Id: L1SisSubsetState.h,v 1.1 1997/08/11 03:12:16 rgr Exp $ */

/* $Source: /home/mussel9/asc/aceprog/include/RCS/L1SisSubsetState.h,v $ */
/* $Author: rgr $ */
/* $Date: 1997/08/11 03:12:16 $ */
/* $Revision: 1.1 $ */

#define NSUBSET  SIZE_SIS_SUBSET_FILTER

struct L1SisSubsetState {
   uint32              NumberSubsets;
   uint32              NumberSubsetsUnfiltered;
   struct L1SisSubset  subset[NSUBSET];
};

#undef NSUBSET
