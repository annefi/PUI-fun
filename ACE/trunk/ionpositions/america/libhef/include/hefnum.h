/* ---------------------------------------------------------------------------
   hefnum.h --- collection of numerical routines
   (c) 1998/1999 Simon Hefti (hefti@umich.edu)
   $Id: hefnum.h,v 1.1.1.1 2000/06/02 13:37:21 jraines Exp $
   ------------------------------------------------------------------------ */

#ifndef HEFNUMH
#define HEFNUMH

int    his_inf   (double x);
int    his_nan   (double x);

double dratio    (double x, double y);
double draterr   (double x, double y, double perr);

double dsqrt     (double x);
double dsqr      (double x);            /* aka SQR */
double dsign     (double a, double b);  /* aka SIGN */
double dmax      (double a, double b);  /* aka FMAX */
int    imin      (int a, int b);        /* aka IMIN */

double dmom1     (double *adx, double *ady, int Nx);
double dmomN     (double *adx,double *ady, int Nx, double dN);
int    fmax      (double *dax, int Nx, int *imx, int *imi);
int    firstmax  (double *dax, int istart, int ilen, double dthresh);

double ferfcc    (double x);
double ferf      (double x);

void   one_gauss (double *x, double *y, int Nx, double *a, int Na, 
		  double *dyda);
void   bck_gauss (double *x, double *y, int Nx, double *a, int Na,
		  double *dyda);
double dgauss    (double x0, double sig, double x);

double lagipol   (double *x, double *y, int istart, int ilen, double xwant);

#include "mfunctions.h"
#include "afunctions.h"

#include "cfit.h"
#include "svd.h"

// ===> kiel
// Was in kpathsea/c-minmax.h but that is not on this system
#ifndef DBL_MAX
#define DBL_MAX 1e+37
#endif

#endif
