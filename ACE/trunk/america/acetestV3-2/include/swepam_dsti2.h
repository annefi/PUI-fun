/* $Id: swepam_dsti2.h,v 1.1 1997/06/20 18:04:04 jeff Exp $ */
#include "hdfi.h"

#define SWEPAM_DSTI2_specseg 5 /* spectral segment index. approx = spins */
#define SWEPAM_DSTI2_phi     6 /* "Spin" sector index */
#define SWEPAM_DSTI2_energy  4 /* Energy sample index withing a spin sector */
#define SWEPAM_DSTI2_theta   4 /* Polar angle index.  0=CEM13, .. ,3=CEM16 */

struct DSTI2  /* SWEPAM-I Supra thermal data sets from Search STI Mode */
{
  uint32 output_sctime;   /* time for beginning of data output cycle */
  uint32 collect_sctime;  /* time for beginning of data collection */
  uint8  QAC;             /* number of bad frames in this cycle */
  
  /* Data set header */
  uint8 PhiLim;   /* Decompressed phi limit. 55-61 */
  uint8 DQAlarm;  /* Data Quality alarm. 0/1=OK/data suspect */
  uint8 CEMLev;   /* CEM bias level. 0-15 */
  uint8 Lmx;      /* ESA lvl with max count rate in previous SWI or SSTI mode*/
		    /*0-199.255=invalid*/

  /* Spectral segment headers */
  uint8 RLmxs[5];     /* Rel ESA lvl with max rate in Spec seg s */
  uint8 DCLmxs[5];    /* Data Channel of Lmxs */
  uint8 PhiLmxs[5];   /* Phi of Lmxs */

  /* count array - compressed count "pixels" */
  uint8 COUNT[SWEPAM_DSTI2_specseg][SWEPAM_DSTI2_phi][SWEPAM_DSTI2_energy][SWEPAM_DSTI2_theta];
};
