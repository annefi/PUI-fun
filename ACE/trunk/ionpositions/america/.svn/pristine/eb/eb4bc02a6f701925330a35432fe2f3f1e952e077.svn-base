/* $Id: swepam_i.h,v 1.5 1998/12/02 01:47:38 asc Exp $ */

/* Structure definition for SWI moments */

#ifndef	SWEPAM_I_H
#define	SWEPAM_I_H 1

#include "swepam_dcali.h"
#include "swepam_dengi.h"
#include "swepam_dhskpi.h"
#include "swepam_dloadi.h"
#include "swepam_drawi.h"
#include "swepam_dssti.h"
#include "swepam_dsti.h"
#include "swepam_dsti2.h"
#include "swepam_dswi.h"
#include "swepam_bri.h"

#define DATA_SIZE_RTSW 1344 /* # of bytes in 1 RTSW mode */
#define DATA_SIZE_SWI  4352 /* # of bytes in 1 SWI mode */
#define I_SPEC 5            /* # of spectral segments */
#define I_ANGLE 33          /* # of pixels in RTSW data set */
#define I_ANGLE_TOT 96      /* # of pixels in SWI data set */
#define I_ESTEP 8           /* # of E steps per angle/seg */
#define I_ETOT 40           /* total # of energy steps */
#define I_COUNT_RTSW 1320   /* # of counts in 1 RTSW mode */
#define I_COUNT_SWI 3840    /* # of counts in 1 SWI mode */
#define I_MFHDR   4         /* Major frame header */
#define I_RTMFHDR 4         /* Real Time Major frame header */
#define I_SSSHDR  5         /* Spectral Segment Header */
#define I_DSHDR  2          /* Data Set Header */
#define I_CEM 12          /* # of CEMs used in SWI mode */
#define I_PHI 61          /* # of phi angles */

#include "hdfi.h"
#include "swepam.h"

struct swepam_i {
  uint16   year;	/* Full four-digit year, eg, 1998	*/
  uint16   yday;	/* Day of year, 1-365 (or -366)		*/
  uint8    mon;		/* Month, 1-12				*/
  uint8    mday;	/* Day of month, 1-31			*/
  uint8    hour;	/* Hour, 0-23				*/
  uint8    min;		/* Minutes past the hour, 0-59		*/
  uint8    sec;		/* Seconds, 0-59			*/
  uint32   sct;		/* Spacecraft time?			*/

  float32  np;		/* Proton density, cm-3			*/
  float32  np_bound;	/* Proton density, bound		*/
  float32  he_ratio;	/* Alpha ratio				*/
  float32  speed;	/* Proton speed, km/s			*/
  float32  Ttt[3][3];	/* Temperature tensor			*/
  float32  Trr_bound;	/* Bounded temperature			*/
  float32  Tpara;	/* parallel component of temperature	*/
  float32  Tperp[2];	/* perp.    component of temperature	*/

  uint32   limit;	/* ??? */
  uint32   lmx;		/* ESA level with max count rate, 0-199	*/
  float32  spin;	/* Spacecraft spin rate			*/
  uint32   flag3d;	/* bitmask flagging "suspect" data	*/
  float32  rtsw_counts;
  float32  rtsw_pc;
  float32  total_counts;
  int32    cem_max;	/* CEM holding max counts		*/
  uint8    imax[I_SPEC];
  uint8    jmax[I_SPEC];
  uint8    kmax[I_SPEC];

  uint8	   peak_p;	/* Proton peak, index into dist_fun_1d	*/
  uint8    break_p_a;	/* Break between protons and alphas	*/
  uint8    peak_a;	/* Alpha peak, index into dist_fun_1d	*/
  float32  vel_p_rtn[3]; /* RTN components of proton speeds	*/
  float32  vel_a_rtn[3]; /* RTN components of alpha speeds	*/

  float32  vel_p_gse[3]; /* GSE components of proton speeds	*/
  float32  vel_a_gse[3]; /* GSE components of alpha speeds	*/

  float32  sc_pos_gse[3]; /* Spacecraft position at this time, GSE coords */

  /* Dist Fun */
  float32  dist_fun_1d[I_ETOT];	/* 1-D Distribution function		*/
  float32  flux_1d[I_ETOT];	/* 1-D corrected flux		*/
  uint32   counts[I_ETOT];	/* uncorrected counts, over phi & theta	*/
/*  uint32   counts_per_cem[12][I_ETOT];		/* ESM ESM ESM */
/*  uint16   counts_xxx[12][72][I_ETOT];		/* ESM ESM ESM */
/*  float32  phase;				/* ESM ESM ESM */
};

#endif	/* SWEPAM_I_H */

