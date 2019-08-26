/* $Id: swepam_dcale.h,v 1.2 1998/03/24 19:08:17 asc Exp $ */
#include "hdfi.h"

#define SWEPAM_DCALE_specseg 5  /* Spectral segment index..approx = spins */
#define SWEPAM_DCALE_phi 51     /* "Spin" sector index */
#define SWEPAM_DCALE_discrim 2  /* Discrim thrshld within a spin sect,0/1=A/B*/ 
#define SWEPAM_DCALE_theta 7    /* Polar angle index. 0=CEM1, 1=CEM2 .. CEM7 */

struct DCALE
{
  uint32 output_sctime;   /* time for beginning of data output cycle */
  uint32 collect_sctime;  /* time for beginning of data collection */
  uint8  QAC;             /* number of bad frames in this collection cycle */

  /* Data set header - PhiLim and Lmx not use by DCALE*/
  uint8 PhiLim;       /* Decompressed phi limit (55-61) */
  uint8 DQAlarm;      /* Data Quality alarm, 0/1 = OK/data suspect */
  uint8 CEMLev;       /* CEM level bias level, 0-15 */
  uint8 Lmx;          /* Set to 255=invalid */

  /* spectral segment headers - NOT USED BY DCALE, they should all be 0 */
  uint8 RLmxs[5];          /* Rel ESA lvl with max rate in Spec seg s */
  uint8 DCLmxs[5];          /* Data Channel of Lmxs */
  uint8 PhiLmxs[5];          /* Phi of Lmxs */

  /* Compressed count "pixels" */
  uint8 COUNT[SWEPAM_DCALE_specseg][SWEPAM_DCALE_phi][SWEPAM_DCALE_discrim][SWEPAM_DCALE_theta];
};

