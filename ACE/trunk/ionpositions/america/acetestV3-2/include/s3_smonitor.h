/* $Id: s3_smonitor.h,v 1.6 1998/12/07 18:12:39 ad Exp $	     */
#include "hdfi.h"

#define SMON_N     12  /* number of monitor rates */
#define SMON_S     8  /* number of sectors */
#define SMON_CYC   12  /* number of cycles per SR = 60 / 5 */
#define SMON_NFILL 4  /* amount of fill data elements */

 /* total size (in bytes) of SMON data (including slack) in a full SR */
#define SMON_TSZ   1800 

 /* size (in bytes) of SMON cycle (including slack) */
#define SMON_CSZ   SMON_TSZ/SMON_CYC 
#define SMON_ESZ   SMON_TSZ/60  /* size (in bytes) of SMON in EDB */

/* monitor rates are collected over 5 spins and output during the next */
/* 5 spins(or edb's). There are 12 matrix rate collection cycles per */
/* Science Record */

/* sctime_readout: spacecraft clock of first minor frame of the */
/* first edb of the monitor rate output cycle */

/* sctime_collection:  time of the start of the first spin in the */
/* collection cycle, in spacecraft clock time units */

struct smonitor{

   uint32 sctime_readout;     /* 32 bit spacecraft time  */
   float64 sctime_collection; /* spacecraft time, sub-second resolution */
   uint32 QAC;	/* number of missing frames in this 5-spin cycle */

   uint16 MONITOR[SMON_N][SMON_S];/* 12 Monitor rates, 8 sectors */
   uint16 FILL[SMON_NFILL];    /* Fill  data   */
};
