/* $Id: swepam_dswi.h,v 1.1 1997/06/20 18:06:56 jeff Exp $ */
#include "hdfi.h"

#define SWEPAM_DSWI_specseg 5 /* spectral segment index. approx = spins */
#define SWEPAM_DSWI_nphitheta 96 /*mask indes identifing spin sector phi and */
		/* polar angle theta */
#define SWEPAM_DSWI_energy 8 /* Energy index */

struct DSWI   /* SWI Mode */
{
  uint32 output_sctime;   /* time for beginning of data output cycle */
  uint32 collect_sctime;  /* time for beginning of data collection */
  uint8  QAC;             /* number of bad frames in this cycle */
  
  /* data set header */
  uint8 PhiLim;    /* Current sensor limit */
  uint8 DQAlarm;   /* Data Quality alarm */
  uint8 CEMLev;    /* CEM level */
  uint8 Lmx;       /* ESA lvl with max count rate.0-199.255=invalid*/

  /* spectral segment header */
  uint8 RLmxs[5];   /* Rel ESA lvl with max rate in Spec seg s */
  uint8 DCLmxs[5];  /* Data Channel of Lmxs */
  uint8 PhiLmxs[5]; /* Phi of Lmxs */

  /* count array - compressed count "pixels" */
  uint8 COUNT[SWEPAM_DSWI_specseg][SWEPAM_DSWI_nphitheta][SWEPAM_DSWI_energy];
};
