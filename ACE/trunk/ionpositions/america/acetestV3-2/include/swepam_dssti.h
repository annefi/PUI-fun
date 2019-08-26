/* $Id: swepam_dssti.h,v 1.1 1997/06/20 18:02:39 jeff Exp $ */
#include "hdfi.h"

#define SWEPAM_DSSTI_specseg  5 /* spectral segment index.. approx = spins */
#define SWEPAM_DSSTI_nphitheta 96 /* mask index identifing spin sector phi */
	/* and polar angle theta */
#define SWEPAM_DSSTI_energy  8 /* Energy index */

struct DSSTI               /* SSTI Data Mode */
{
  uint32 output_sctime;   /* time for beginning of data output cycle */
  uint32 collect_sctime;  /* time for beginning of data collection */
  uint8  QAC;             /* number of bad frames in this cycle */
  
  /* Data set header */
  uint8 PhiLim;  /* Decompressed philimit (55-61) */
  uint8 DQAlarm; /* Data Quality alarm. 0/1 = OK/suspect data */
  uint8 CEMLev;  /* CEM bias level. 0-15 */
  uint8 Lmx;     /* ESA lvl with max count rate previous SWI or SSTI mode.*/
		 /* 0-199.255=invalid*/

  /* Spectral segment headers */
  uint8 RLmxs[5];     /* Rel ESA lvl with max rate in Spec seg s */
  uint8 DCLmxs[5];    /* Data Channel or theta of Lmxs */
  uint8 PhiLmxs[5];   /* Phi of Lmxs */

  /* Count array - compressed count "pixels" */
  uint8 COUNT[SWEPAM_DSSTI_specseg][SWEPAM_DSSTI_nphitheta][SWEPAM_DSSTI_energy];
};
