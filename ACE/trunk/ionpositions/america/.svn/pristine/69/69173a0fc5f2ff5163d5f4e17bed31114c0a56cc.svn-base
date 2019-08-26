/* $Id: mag_fft.h,v 1.7 1997/05/07 18:44:38 jeff Exp $ */

#include "hdfi.h"

#define FFTBIN 32                /* 32 FFT frequency bins            */
#define MJ_FFT_CYC 5             /* Major frames per FFT cycle       */

struct MagFFTSet                 /* setkey=fG                           */
{
  uint32 sctime_readout;       /* 32 bit spacecraft readout time  */
  uint32 sctime_collection;       /* 32 bit spacecraft collection time  */

  uint32 QAC;			/* number of missing frames in this cycle */

  uint16 fft_statbits[MJ_FFT_CYC];   /* bits 15-9 - unused (=0) */
				     /* bit  8    = Rg (ST5 bit 2) */
				     /* lsByte    = ST6         */

  uint8 fft_val[10][FFTBIN];
  /* first index = 0 -> X-axis FFT transform real output    */
  /* first index = 1 -> Y-axis FFT transform real output    */
  /* first index = 2 -> Z-axis FFT transform real output    */
  /* first index = 3 -> X-Y cross-spectra real output       */
  /* first index = 4 -> X-Y cross-spectra imaginary output  */
  /* first index = 5 -> X-Z cross-spectra real output       */
  /* first index = 6 -> X-Z cross-spectra imaginary output  */
  /* first index = 7 -> Y-Z cross-spectra real output       */
  /* first index = 8 -> Y-Z cross-spectra imaginary output  */
  /* first index = 9 -> magnitude FFT transform real output */
};
