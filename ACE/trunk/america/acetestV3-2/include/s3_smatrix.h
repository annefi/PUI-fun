/* $Id: s3_smatrix.h,v 1.6 1998/12/07 18:12:39 ad Exp $	     */
#include "hdfi.h"

#define SMAT_N     60  /* number of matrix rate channels */
#define SMAT_S     1  /* number of sectors */
#define SMAT_CYC   6  /* number of cycles per SR = 60 / 10 */

 /* total size (in bytes) of SMAT data (including slack) in a full SR */
#define SMAT_TSZ   540 

/* size (in bytes) of SMAT cycle (including slack) */
#define SMAT_CSZ   SMAT_TSZ/SMAT_CYC 
#define SMAT_ESZ   SMAT_TSZ/60  /* size (in bytes) of SMAT area in EDB */

/* Matrix rates are collected over 10 spins and output during the next */
/* 10 spins(or edb's). There are 6 matrix rate collection cycles per */
/* Science Record */

/* sctime_readout: spacecraft clock of first minor frame of the */
/* first edb of the matrix rate output cycle */

/* sctime_collection:  time of the start of the first spin in the */
/* collection cycle, in spacecraft clock time units */

/* smatrix structure contains SEPICA matrix rates for 1 10-spin collection cycle */

struct smatrix{
   uint32 sctime_readout;  /* 32 bit spacecraft time  */
   float64 sctime_collection; /* spacecraft time, sub-second resolution */
   uint32 QAC;     /* number of missing frames in this 10-spin cycle */

   uint16 MATRIX[SMAT_N]; /* 49 Matrix rates, 11 fill */
};

