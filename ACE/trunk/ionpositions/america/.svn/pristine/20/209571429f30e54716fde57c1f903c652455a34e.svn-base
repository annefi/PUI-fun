/* $Id: s3_sbasic.h,v 1.6 1998/12/07 18:12:39 ad Exp $	     */
#include "hdfi.h"

/* SEPICA Basic rates */

#define SBAS_N     16  /* number of basic rates */
#define SBAS_S     8  /* number of sectors */
#define SBAS_CYC   12  /* number of cycles per SR = 60 / 5 */
#define SBAS_NFILL 2  /* amount of fill data per cycle */

 /* total size (in bytes) of SBAS data (including slack) in a full SR */
#define SBAS_TSZ   2340  

 /* size (in bytes) of SMON cycle (including slack) */
#define SBAS_CSZ   SBAS_TSZ/SBAS_CYC 
#define SBAS_ESZ   SBAS_TSZ/60  /* size (in bytes) of SBAS area in EDB */

/* Basic rates are collected over 5 spins and output during the next */
/* 5 spins(or edb's). There are 12 basic rate collection cycles per */
/* Science Record */

/* sctime_readout: spacecraft clock of first minor frame of the */
/* first edb of the basic rate output cycle */

/* sctime_collection:  time of the start of the first spin in the */
/* collection cycle, in spacecraft clock time units */

/* sbasic structure contains basic rates for 1 5-spin collection cycle */
struct sbasic{

   uint32 sctime_readout;	/* 32 bit spacecraft time  */
   float64 sctime_collection; /* spacecraft time, sub-second resolution */
   uint32 QAC;	/* number of frames of missing data in this 5-spin cycle */

   uint16 BASIC[SBAS_N][SBAS_S];/* 16 Basic rates, 8 sectors */
   uint16 FILL[SBAS_NFILL];    /*  Fill data  */
};
