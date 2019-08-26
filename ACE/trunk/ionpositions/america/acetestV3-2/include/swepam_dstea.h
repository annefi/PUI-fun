/* $Id: swepam_dstea.h,v 1.1 1997/06/20 18:05:42 jeff Exp $ */
#include "hdfi.h"

#define SWEPAM_DSTEA_specseg  5  /* spectral segment index, approx = spins */
#define SWEPAM_DSTEA_phi     60  /* "Spin" sector index */
#define SWEPAM_DSTEA_energy   2  /* Energy sample index withn a spin sector */
#define SWEPAM_DSTEA_otheta   7  /* Polar angle indx.oddphi.0=CEM1,..,6=CEM7*/
#define SWEPAM_DSTEA_etheta   5  /* Polar angle indx.evenphi.0=CEM1,..,6=CEM7*/

struct DSTEA   /* swepam-e data set from Supra thermal angle scan mode */
{
  uint32 output_sctime;   /* time for beginning of data output cycle */
  uint32 collect_sctime;  /* time for beginning of data collection */
  uint8  QAC;             /* number of bad frames in this cycle */

  /* Data set header- Philim and Lmx not used in DSTEA mode */
  uint8 PhiLim;   /* Decompressed phil limit. (55-61) */
  uint8 DQAlarm;  /* Data Quality alarm. 0/1 = OK/suspect data */
  uint8 CEMLev;   /* CEM bias level. 0-15 */
  uint8 Lmx;      /* set to 255=invalid*/

  /* count array - compressed count "pixels" */
  /* even phi values have 0 fill in elements 0&6 (CEM1&CEM7) */
  uint8 COUNT[SWEPAM_DSTEA_specseg][SWEPAM_DSTEA_phi][SWEPAM_DSTEA_energy][SWEPAM_DSTEA_otheta];
};
