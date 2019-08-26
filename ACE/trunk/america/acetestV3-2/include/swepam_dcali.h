/* $Id: swepam_dcali.h,v 1.1 1997/06/20 17:56:55 jeff Exp $ */
#include "hdfi.h"

#define SWEPAM_DCALI_specseg 5 /* spectral segment index. approx=spins */
#define SWEPAM_DCALI_phi    27 /* "Spin" sector index */
#define SWEPAM_DCALI_discrim 2 /* Discrim thrshld index in spin sector */
#define SWEPAM_DCALI_theta  16 /* Polar angle index.  0=CEM1,..,15=CEM16 */

struct DCALI               /* CALI Data Mode */
{
  uint32 output_sctime;   /* time for beginning of data output cycle */
  uint32 collect_sctime;  /* time for beginning of data collection */
  uint8  QAC;             /* number of bad frames in this cycle */
  
  /* Data set header */
  uint8 PhiLim;       /* Decompressed phi limit (55-61) */
  uint8 DQAlarm;      /* Data Quality alarm.  0/1=OK/data suspect */
  uint8 CEMLev;       /* CEM bias level */
  uint8 Lmx;          /* ESA lvl with max count rate in previous */
		        /* SWI or SSTI mode.0-199.255=invalid*/

  /* spectral segment headers, NOT USED BY DCALI, all should be 0 */
  uint8 RLmxs[5];      /* Rel ESA lvl with max rate in Spec seg s */
  uint8 DCLmxs[5];     /* Data Channel of Lmxs */
  uint8 PhiLmxs[5];    /* Phi of Lmxs */

  /* Count array.  Compressed count "pixels" */
  uint8 COUNT[SWEPAM_DCALI_specseg][SWEPAM_DCALI_phi][SWEPAM_DCALI_discrim][SWEPAM_DCALI_theta]; 
};
