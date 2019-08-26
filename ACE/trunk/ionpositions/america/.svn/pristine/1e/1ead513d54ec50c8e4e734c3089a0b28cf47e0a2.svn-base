/* $Id: s3_ssector.h,v 1.5 1998/12/07 18:12:39 ad Exp $	     */
#include "hdfi.h"

#define SSEC_N     20  /* number of matrix rates */
#define SSEC_S     8  /* number of sectors */
#define SSEC_CYC   6  /* number of cycles per SR = 60 / 10 */

 /* total size (in bytes) of SMON data (including slack) in a full SR */
#define SSEC_TSZ   1440  

 /* size (in bytes) of SSEC cycle (including slack) */
#define SSEC_CSZ   SSEC_TSZ/SSEC_CYC 

#define SSEC_ESZ   SSEC_TSZ/60  /* size (in bytes) of SSEC area in EDB */

/* Sectored rates are collected over 10 spins and output during the next */
/* 10 spins (or edb's). There are 6 sectored rate collection cycles per */
/* Science Record */

/* sctime_readout: spacecraft clock of first minor frame of the */
/* first edb of the sectored rate output cycle */

/* sctime_collection:  time of the start of the first spin in the */
/* collection cycle, in spacecraft clock time units */

/* ssector structure contains basic rates for 1 10-spin collection cycle */

struct ssector{

   uint32 sctime_readout;	/* 32 bit spacecraft time  */
   float64 sctime_collection; /* spacecraft time, sub-second resolution */
   uint32 QAC;	/* Number of missing frames in this 10-spin cycle */

   uint16 SECTOR[SSEC_N][SSEC_S]; /* 20 Sectored rates, 8 sectors */
};
