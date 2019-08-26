/* ---------------------------------------------------------------------------
   afunctions --- array handling
   by Hefti (hef), University of Michigan (hefti@umich.edu)
   $Id: afunctions.c,v 1.1.1.1 2000/06/02 13:37:22 jraines Exp $
   -------------------------------------------------------------------------*/

#include <stdio.h>

#include "libhef.h"


/*  --------------------------------------------------------------------------
    asum --- sum entries in one array of type double from start..start+len
    ------------------------------------------------------------------------*/
double asum(double *x, int istart, int ilen)
{
  double dsum;
  int    i;

  dsum = 0.0;
  for(i = istart; i < (istart + ilen); i++) dsum += x[i];
  return(dsum);
}


/*  --------------------------------------------------------------------------
    aprint --- print array from start..start+len
    ------------------------------------------------------------------------*/
void aprint(double *x, int istart, int ilen, char *ztit)
{
  int    i;

  printf("%s\n",ztit);
  for(i = istart; i < (istart + ilen); i++) printf("%3d %10.2f\n",
						   i,x[i]);
  return;
}



/*  --------------------------------------------------------------------------
    aind --- set x[i] = i
    ------------------------------------------------------------------------*/
void aind(double *x, int istart, int ilen)
{
  int    i;

  for(i = istart; i < (istart + ilen); i++) x[i] = (double)i;
  return;
}

/*  --------------------------------------------------------------------------
    aadd --- x[i] = x[i] + y[i]
    ------------------------------------------------------------------------*/
void aadd(double *x, double *y, int istart, int ilen)
{
  int    i;

  for(i = istart; i < (istart + ilen); i++) x[i] = x[i] + y[i];
  return;
}

/*  --------------------------------------------------------------------------
    asmul --- scalar multiplication (x[i] = a * x[i])
    ------------------------------------------------------------------------*/
void asmul(double *x, int istart, int ilen, double a)
{
  int    i;

  for(i = istart; i < (istart + ilen); i++) x[i] = a * x[i];
  return;
}

/*  --------------------------------------------------------------------------
    aemul --- elemental multiplication (x[i] = x[i] * y[i])
    ------------------------------------------------------------------------*/
void aemul(double *x, double *y, int istart, int ilen)
{
  int    i;

  for(i = istart; i < (istart + ilen); i++) x[i] = y[i] * x[i];
  return;
}

/*  --------------------------------------------------------------------------
    aget --- get value: return x[idx] (for SWIG/perl)
    ------------------------------------------------------------------------*/
double aget(double *x, int idx)
{
  return(x[idx]);
}

/*  --------------------------------------------------------------------------
    aset --- set value: x[idx] = dval
    ------------------------------------------------------------------------*/
void aset(double *x, int idx, double dval)
{
  x[idx] = dval;
  return;
}

/*  --------------------------------------------------------------------------
    aeset --- set values: x[i] = dval, istart <= i < istart+ilem
    ------------------------------------------------------------------------*/
void aeset(double *x, int istart, int ilen, double dval)
{
  int    i;

  for(i = istart; i < (istart + ilen); i++) x[i] = dval;
  return;
}

/*  --------------------------------------------------------------------------
    achi2 --- calculate sum((x - y)^2 * w)
    ------------------------------------------------------------------------*/
double achi2(double *x, double *y, double *w, int istart, int ilen)
{
  double dchi2;
  double dtmp;
  int    i;

  dchi2 = 0.0;
  for(i = istart; i < (istart + ilen); i++) {
    dtmp = (x[i] - y[i]);
    dchi2 += dtmp * dtmp * w[i];
  }
  return(dchi2);
}
