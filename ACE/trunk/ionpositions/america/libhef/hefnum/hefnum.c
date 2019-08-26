/* ---------------------------------------------------------------------------
   hefnum.c --- numerical
   (c) 1998/1999 Simon Hefti (hefti@umich.edu)
   $Id: hefnum.c,v 1.2 2002/02/14 15:49:08 jraines Exp $
   ------------------------------------------------------------------------ */

#include <stdio.h>
#include <math.h>

// ===> kiel
//#include <kpathsea/c-minmax.h>  /* added for RH 7.1 GCC 2.96, JR 19Jul2001 */

#include "libhef.h"


/*  --------------------------------------------------------------------------
    his_inf --- simple-minded test for Inf
    ----------------------------------------------------------------------- */
int his_inf(double x)
{
  if( x >  DBL_MAX ) return(1);
  if( x < -DBL_MAX ) return(1);

  return(0);
}

/*  --------------------------------------------------------------------------
    his_nan --- simple-minded test for NaN
    ----------------------------------------------------------------------- */
int his_nan(double x)
{
  if( x == x ) return(0);

  return(1);
}

/*  --------------------------------------------------------------------------
    Function: dratio
    Synopsis: returns x/y or -1
    ----------------------------------------------------------------------- */
double dratio(double x, double y)
{
  if( y != 0.0 ) return(x/y);
  else           return(-1.0);

  return(-1.0);
}

/*  --------------------------------------------------------------------------
    draterr --- returns x/y; or -1 if y < 0 or if poissonian error > perr
    ----------------------------------------------------------------------- */
double draterr(double x, double y, double perr)
{
  double derr;

  derr = dratio(x + y,x * y);
  if( derr < 0.0 ) return(-1.0);
  if( sqrt(derr) > perr) {
    printf("draterr --- x = %.2f y = %.2f delta = %.3f\n",
	   x,y,derr);
    return(-1.0);
  }
  else {
    return(dratio(x,y));
  }

  return(-1.0);
}

/*  --------------------------------------------------------------------------
    dsqrt --- returns sqrt(x)
    ----------------------------------------------------------------------- */
double dsqrt(double x)
{
  if( x > 0.0 ) return(sqrt(x));
  else {
    printf("dsqrt --- Problem: x = %.2f\n",x);
    return(-1.0);
  }
  return(-1.0);
}

/*  --------------------------------------------------------------------------
    dsqr --- returns x * x
    ----------------------------------------------------------------------- */
double dsqr(double x)
{
  return(x * x);
}

/*  --------------------------------------------------------------------------
    dsign --- 
    ----------------------------------------------------------------------- */
double dsign(double a, double b)
{
  return((b) >= 0.0 ? fabs(a) : -fabs(a));
}

/*  --------------------------------------------------------------------------
    dmax --- return max of two numbers
    ----------------------------------------------------------------------- */
double dmax(double a, double b)
{
  if( a > b ) return(a);
  else        return(b);
}

/*  --------------------------------------------------------------------------
    imin --- return min of two numbers
    ----------------------------------------------------------------------- */
int imin(int a, int b)
{
  if( a < b ) return(a);
  else        return(b);
}

double dmom1(double *adx,double *ady, int Nx)
{
  return(dmomN(adx,ady,Nx,1.0));
}

double dmomN(double *adx,double *ady, int Nx, double dN)
{
  double dnorm;
  double dres;
  int    i = 0;

  dres = 0.0;

  /* -------------------------------------------------------------------------
  **  sum(y) > 0
  ** ---------------------------------------------------------------------- */

  dnorm = 0.0;
  for(i = 0;i < Nx; i++) dnorm += ady[i];

  if( dN == 0.0 ) {
    return(dnorm);
  }
  
  if( dnorm < 0.0) {
    printf("dmomN --- not enough data (sum = %.1f)\n",dnorm);
    return(-1.0);
  }

  /* -------------------------------------------------------------------------
  **  first moment
  ** ---------------------------------------------------------------------- */

  dres  = 0.0;
  if( dN == 1.0 ) {
    for(i = 0;i < Nx; i++) dres += ady[i] * adx[i];
  } else {
    for(i = 0;i < Nx; i++) dres += ady[i] * pow(adx[i],dN);
  }

  dres  = dres / dnorm;


  /* -------------------------------------------------------------------------
  ** test for NaN
  ** ---------------------------------------------------------------------- */

  if( dres != dres ) dres = -1.0;

  return(dres);
}

/*  --------------------------------------------------------------------------
    fmax --- finds min, max in array. Returns position.
    ----------------------------------------------------------------------- */
int fmax(double *dax, int Nx, int *imx, int *imi)
{
  double dtmin;
  double dtmax;
  int    i;

  *imi = -1;
  *imx = -1;

  dtmin = dax[0];
  dtmax = dax[0];

  for(i = 1; i < Nx; i++) {

    /* printf("%2d %6.1f\n",i,dax[i]); */

    if( dax[i] > dtmax ) {
      dtmax = dax[i];
      *imx = i;
    }

    if( dax[i] < dtmin ) {
      dtmin = dax[i];
      *imi = i;
    }
  }


  /*
  printf("DBG: fmax --- max at %2d (%10.3e)\n",*imx,dax[*imx]);
  printf("min at %2d (%6.1f)\n",*imi,dax[*imi]);
  */

  return(*imx);
}

/*  --------------------------------------------------------------------------
    firstmax --- finds first max in array. Returns position.
    ----------------------------------------------------------------------- */
int firstmax(double *dax, int istart, int ilen, double dtresh)
{
  double dtmax;
  int    i;
  int    imx;
  int    idowncnt;

  imx     = -1;
  idowncnt =  1;

  dtmax = dax[istart];

  for(i = (istart+1); i < (istart+ilen); i++) {

    /* printf("firstmax --- %2d %6.1f\n",i,dax[i]); */

    if( dax[i] > dtmax ) {
      dtmax = dax[i];
      imx  = i;
    }

    if( dtmax > dtresh ) {
      if( (dax[i] / dtmax) < 0.5) idowncnt++;
      else                        idowncnt = 0;
    }
    if( idowncnt >= 3 ) break;
  }

  return(imx);
}

/*  --------------------------------------------------------------------------
    ferfcc --- error function (Numerical Recipies).

    Using the following definitions:
    erf(x)   = 2/sqrt(pi) * int( exp(-t^2),t=0..x );
    erf(0)        = 0;
    erf(infinity) = 1;
    erfcc(x) = 1 - erf(x);
    erf2(x)  = 1/sqrt(pi) * int( exp(-t^2),t=-infinity..x );
    erf2(x)  = 1/2 * (1 + erf(x) );
    erf3(x)  = 1/sqrt(2 * pi) * int( exp(-z^2/2),z=-infinity..x);
    erf3(x)  = erf2(x/sqrt(2)) = 1/2 * (1 + erf(x/sqrt(2))) =
               1/2(2 - erfcc(x/sqrt));
    ----------------------------------------------------------------------- */
double ferfcc(double x)
{
  double t = 0.0, z = 0.0, ans = 0.0;
  double res = 0.0;

  z = fabs(x);
  
  t = 1.0 / (1.0 + 0.5*z);
  
  ans = t*exp(-z*z-1.26551223+t*(1.00002368+t*(0.37409196+t*(0.09678418+
        t*(-0.18628806+t*(0.27886807+t*(-1.13520398+t*(1.48851587+
        t*(-0.82215223+t*0.17087277)))))))));
        
  res = (x >= 0.0 ? ans : 2.0-ans);
  
  return(res);
}

/*  --------------------------------------------------------------------------
    ferf --- "normal" error function.
    erf3(x)  = erf2(x/sqrt(2)) = 1/2 * (1 + erf(x/sqrt(2))) =
               1/2(2 - erfcc(x/sqrt));
    ----------------------------------------------------------------------- */
double ferf(double x)
{
  double res = -1.0;

  res = 0.5 * (2.0 - ferfcc( x / sqrt(2.0) ) );
  
  return(res);
}

/*  --------------------------------------------------------------------------
    one_gauss --- gaussian for use as model function with cfit()

    Nx >= 1 is the number of elements in x and y.
            Derivatives are stored in dyda in order dydA(x=x1),dydx0(x1),
	    dyds(x1),dydA(x=x2),dydx0(x2),dyds(x2) etc
    Na = 3  is the number of parameters. a: A, x0, sig
    ----------------------------------------------------------------------- */
void one_gauss(double *x, double *y, int Nx, double *a, int Na, double *dyda)
{
  double dA;
  double dx0;
  double ds;
  
  double dz1;
  double dez1;

  int    ix;

  /* printf("one_gauss --- %6.2f %6.2f %6.2f\n",a[1],a[2],a[3]); */

  if( Na != 3 ) {
    printf("one_gauss --- Na = 3 (instead of %d) expected.\n",Na);
    return;
  }

  dA  = a[0];
  dx0 = a[1];
  ds  = a[2];

  if( ds <= 0.0 ) {
    printf("one_gauss --- cannot deal with sig = %10.3e\n",ds);
    return;
  }

  for(ix = 0; ix < Nx; ix++) {

    dz1 = (x[ix] - dx0) / ds;

    if( fabs(dz1) > 6.0 ) dz1 = 6.0;

    dez1 = exp(-dsqr(dz1)/2.0);

    y[ix] = dA * dez1;

    dyda[I(ix,Na,0)] = dez1;
    dyda[I(ix,Na,1)] = dA * dez1 * dz1 / ds;
    dyda[I(ix,Na,2)] = dyda[I(ix,Na,1)] * dz1;
  }

  return;
}

/*  --------------------------------------------------------------------------
    bck_gauss --- gaussian w/ background for use as model function with cfit()

    Nx >= 1 is the number of elements in x and y.
            Derivatives are stored in dyda in order dydA(x=x1),dydx0(x1),
	    dyds(x1),dydA(x=x2),dydx0(x2),dyds(x2) etc
    Na = 4  is the number of parameters. a: A, x0, sig, bck
    ----------------------------------------------------------------------- */
void bck_gauss(double *x, double *y, int Nx, double *a, int Na, double *dyda)
{
  double dA;
  double dx0;
  double ds;
  double dbck;
  
  double dz1;
  double dez1;

  int    ix;

  /* printf("bck_gauss --- %6.2f %6.2f %6.2f\n",a[1],a[2],a[3]); */

  if( Na != 4 ) {
    printf("bck_gauss --- Na = 4 (instead of %d) expected.\n",Na);
    return;
  }

  dA    = a[0];
  dx0   = a[1];
  ds    = a[2];
  dbck  = a[3];

  if( ds <= 0.0 ) {
    printf("bck_gauss --- cannot deal with sig = %10.3e\n",ds);
    return;
  }

  /* aprint(a,0,Na,"bck_gauss --- g"); */

  for(ix = 0; ix < Nx; ix++) {

    dz1 = (x[ix] - dx0) / ds;

    if( fabs(dz1) > 6.0 ) dz1 = 6.0;

    dez1 = exp(-dsqr(dz1)/2.0);

    y[ix] = dA * dez1 + dbck;

    dyda[I(ix,Na,0)] = dez1;
    dyda[I(ix,Na,1)] = dA * dez1 * dz1 / ds;
    dyda[I(ix,Na,2)] = dyda[I(ix,Na,1)] * dz1;
    dyda[I(ix,Na,3)] = 1.0;
  }

  /* aprint(y,0,Nx,"bck_gauss --- y"); */

  return;
}

/*  --------------------------------------------------------------------------
    dgauss --- 1/sqrt(2 pi)/sig * exp[(x-x0)^2/2/sig^2]
    ----------------------------------------------------------------------- */
double dgauss(double x0, double sig, double x)
{
  double dz   = 0.0;
  double dres = 0.0;

  static double doosqrt2pi = 0.0;

  if( doosqrt2pi == 0.0 ) {
    doosqrt2pi = 1.0 / sqrt(2.0 * DPI);
  }

  if( sig <= 0.0 ) {
    printf("dgauss: unusable sigma: %.2f\n",sig);
    return(-1.0);
  }

  dz = (x - x0) / sig;

  if( fabs(dz) > 10.0 ) return(0.0);

  dres = doosqrt2pi / sig * exp(-0.5 * dz * dz);

  return(dres);
}


/*  --------------------------------------------------------------------------
    lagipol --- Lagrange's linear Interpolation
    we assume that x increases monotonically.
    ----------------------------------------------------------------------- */
double lagipol(double *x, double *y, int istart, int ilen, double xwant)
{
  int    i;
  int    ipos;
  double dA0;
  double dA1;
  double dres;

  /* -------------------------------------------------------------------------
  ** make sure x[istart] <= xwant <= x[istart + ilen - 1]
  ** ---------------------------------------------------------------------- */

  if( (xwant < x[istart]) ||  (xwant > x[istart+ilen-1]) ) {
    printf("lagipol --- wanted value out of range: %5.3f %5.3f %5.3f\n",
	   x[istart],xwant,x[istart+ilen-1]);
    return(-1.0);
  }



  /* -------------------------------------------------------------------------
  ** edges
  ** ---------------------------------------------------------------------- */

  if(xwant == x[istart])        return(y[istart]);
  if(xwant == x[istart+ilen-1]) return(y[istart+ilen-1]);

  /* -------------------------------------------------------------------------
  ** find interval (ipos != end)
  ** ---------------------------------------------------------------------- */

  for(i = istart; i < (istart + ilen - 1); i++) {
    if( x[i] == xwant ) return(y[i]);
    if( x[i] >= xwant ) {
      ipos = i;
      break;
    }
  }

  /* -------------------------------------------------------------------------
  ** coefficients
  ** ---------------------------------------------------------------------- */

  dA0 = x[ipos] - x[ipos + 1];
  if( dA0 != 0.0 ) {
    dA0 = (xwant - x[ipos + 1]) / dA0;
  } else {
    printf("lagipol --- Problem finding coefficient A0.\n");
    return(-1.0);
  }

  dA1 = x[ipos + 1] - x[ipos];
  if( dA1 != 0.0 ) {
    dA1 = (xwant - x[ipos]) / dA1;
  } else {
    printf("lagipol --- Problem finding coefficient A1.\n");
    return(-1.0);
  }

  /* -------------------------------------------------------------------------
  ** result
  ** ---------------------------------------------------------------------- */

  dres = y[ipos] * dA0 + y[ipos + 1] * dA1;

  return(dres);
}

