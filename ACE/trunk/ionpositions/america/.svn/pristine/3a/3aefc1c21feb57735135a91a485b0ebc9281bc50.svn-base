/* $Id: swepam_dnswe.h,v 1.1 1997/06/20 18:01:44 jeff Exp $ */
#include "hdfi.h"

#define SWEPAM_DNSWE_specseg  5 /*spectral seg index, approx = spins */
#define SWEPAM_DNSWE_phi     30 /*"Spin" sector index */
#define SWEPAM_DNSWE_energy   4 /*Energy sample index within a spin sector*/
#define SWEPAM_DNSWE_otheta   7 /*Polar angle index.odd phi.0=CEM1, .. 6=CEM7*/
#define SWEPAM_DNSWE_etheta   5 /*Polar angle index.evenphi.0=CEM1, .. 6=CEM7*/
                                /* CEM1, CEM6 are zero filled in even mode */

struct DNSWE
{
  uint32 output_sctime;   /* time for beginning of data output cycle */
  uint32 collect_sctime;  /* time for beginning of data collection */
  uint8  QAC;              /* number of bad frames in this cycle */

  /* Data set header - PhiLim & Lmx not used in DNSWE (or DPHE) mode*/
  uint8 PhiLim;   /* Decompressed Philimit (55-61)*/
  uint8 DQAlarm;  /* Data Quality alarm. 0/1 = OK/Suspect data */
  uint8 CEMLev;   /* CEM bias level. 0-15 */
  uint8 Lmx;      /* ESA lvl with max count rate.0-199.255=invalid*/

  /* Count array - Compressed count "pixels" */
  /* use otheta for theta index, zero fill missing even values */
  uint8 COUNT[SWEPAM_DNSWE_specseg][SWEPAM_DNSWE_phi][SWEPAM_DNSWE_energy][SWEPAM_DNSWE_otheta]; 
};
