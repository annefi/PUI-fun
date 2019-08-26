/* $Id: swepam_dsti.h,v 1.1 1997/06/20 18:06:21 jeff Exp $ */
#include "hdfi.h"

#define SWEPAM_DSTI_specseg 5 /* spectral segment index. approx = spins */
#define SWEPAM_DSTI_phi     6 /* "spin" sector index */
#define SWEPAM_DSTI_energy  4 /* Energy sample index within a spin sector */
#define SWEPAM_DSTI_theta   4 /* polar angle indx.0=CEM13,1=CEM14,..,3=CEM16*/

struct DSTI  /* swepam ion Supra thermal data sets from "track" SW Ion Mode*/
{
  uint32 output_sctime;   /* time for beginning of data output cycle */
  uint32 collect_sctime;  /* time for beginning of data collection */
  uint8  QAC;             /* number of bad frames in this cycle */
  
  /* data set header */
  uint8 PhiLim;   /* Decompressed phi limit.  55-61 */
  uint8 DQAlarm;  /* Data Quality alarm. 0/1= OK/data suspect */
  uint8 CEMLev;   /* CEM bias level. 0-15 */
  uint8 Lmx;      /* ESA lvl with max count rate in previous SWI or SSTI mode*/
		    /*0-199.255=invalid*/

  /* spectral segment header */
  uint8 RLmxs[5];     /* Rel ESA lvl with max rate in Spec seg s */
  uint8 DCLmxs[5];    /* Data Channel of Lmxs */
  uint8 PhiLmxs[5];   /* Phi of Lmxs */

  /* count array - compressed count "pixels" */
  uint8 COUNT[SWEPAM_DSTI_specseg][SWEPAM_DSTI_phi][SWEPAM_DSTI_energy][SWEPAM_DSTI_theta];
};
