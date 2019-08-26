/*  --------------------------------------------------------------------------
    cfit --- "curvefit", interface to L-M fitting
    x,y,w arrays[Nx] with data and weight
    g,sg  arrays[Ng] with guess and error of guess
    chi2  chi squared
    model function
    constraint function
    ireport 0 --- no report, only warnings are printed
            1 --- status information
            2 --- show developement of chi
            3 --- show housekeeping information (internal vars, mostly)
    $Id: cfit.c,v 1.1.1.1 2000/06/02 13:37:22 jraines Exp $
 ------------------------------------------------------------------------*/

#include <stdio.h>
#include <math.h>
#include "libhef.h"

void cfit(double x[], double y[], double w[], int Nx,
	  double g[], double sg[], int Ng, double *chi2, int ireport,
	  void (*funcs)(double *x, double *y, int Nx, double *a, int Na, 
			 double *dyda),
	  void cnstr(double *x, double *y, double *w, double *f, int Nx, 
		  double *g, int Ng))
{
  double *adalf;
  double *adc;                          /* matrix "c" in curevfit.pro */
  double *adal2;                        /* matrix "array" ... */
  double *adbet;                        /* beta */

  double *gtry;                         /* new parameters */
  double *gbck;                         /* in case of matrix inv. fail. */

  double *adfmod;                       /* f(x) (model function at x[i]) */
  double *dyda;                         /* dy/da (derivatives) */

  double dchi2;                         /* float */
  double dochi;                         /* previous chi squared */
  double dlamda;                        /* adjustment of gradient */

  int    i;

  int    iter;

  double dtmp;
  double dfree;                         /* degrees of freedom */

  int    ic;                            /* cols */
  int    ir;                            /* rows */

  int    istat;                         /* flag of minv */

  /* -------------------------------------------------------------------------
  ** some degree of freedom left
  ** -----------------------------------------------------------------------*/

  dfree = (float)(Nx - Ng );
  if( dfree <= 0.0 ) {
    printf("cfit --- no degree of freedom left: %.2f\n",dfree);
    return;
  }

  /* -------------------------------------------------------------------------
  ** make sure there are data
  ** -----------------------------------------------------------------------*/

  dtmp = asum(y,0,Nx);
  if( dtmp == 0.0 ) {
    printf("cfit --- No data seen (sum = %10.3e).\n",dtmp);
    return;
  }

  /* -------------------------------------------------------------------------
  ** get memory
  ** -----------------------------------------------------------------------*/

  adalf  = dvec_get(Ng * Ng);
  adc    = dvec_get(Ng * Ng);
  adal2  = dvec_get(Ng * Ng);
  adbet  = dvec_get(Ng);
  gtry   = dvec_get(Ng);
  gbck   = dvec_get(Ng);
	   
  adfmod = dvec_get(Nx);
  dyda   = dvec_get(Nx * Ng);

  /* -------------------------------------------------------------------------
  ** debug
  ** -----------------------------------------------------------------------*/

  if( ireport >= 1 ) {

    funcs(x,adfmod,Nx,g,Ng,dyda);
    dchi2 = achi2(y,adfmod,w,0,Nx) / dfree;

    printf("cfit --- Nx: %2d Ng: %2d\n",Nx,Ng);
    aprint(g,0,Ng,"cfit --- Guess:");
    printf("cfit --- Spectrum:\n");
    for(i = 0; i < Nx; i++) {
      printf("%2d ",i);
      printf("%10.3e %10.3e %10.3e ",
	     x[i],y[i],w[i]);
      printf("%10.3e ",adfmod[i]);
      printf("%10.3e\n",adfmod[i]-y[i]);
    }
    printf("cfit --- chi2 = %10.3e\n",dchi2);
  }

  /* -------------------------------------------------------------------------
  ** iteration
  ** -----------------------------------------------------------------------*/

  dlamda = 0.001;

  for(iter = 0; iter < 100; iter++) {

    /* -----------------------------------------------------------------------
    ** evaluate model function and derivatives
    ** ---------------------------------------------------------------------*/

    /* printf("cfit --- calling model function\n"); */
    funcs(x,adfmod,Nx,g,Ng,dyda);

    /* -----------------------------------------------------------------------
    ** valid model ?
    ** ---------------------------------------------------------------------*/

    /* fill code in later */

    /* -----------------------------------------------------------------------
    ** calculate chi2
    ** ---------------------------------------------------------------------*/

    dchi2 = achi2(y,adfmod,w,0,Nx) / dfree;

    /* -----------------------------------------------------------------------
    ** all done
    ** ---------------------------------------------------------------------*/

    dtmp = asum(adfmod,0,Nx) / 1.0e7 / dfree;
    

    if( dchi2 < dtmp) {

      printf("cfit --- Guess is good enough (chi2 = %.3f)\n",dchi2);
      goto finalize;
    }

    /* -----------------------------------------------------------------------
    ** alpha according to Numerical Recipies
    ** ---------------------------------------------------------------------*/

    if( ireport >= 4) printf("alpha:\n");
    for(ir = 0; ir < Ng; ir++) {
      for(ic = 0; ic < Ng; ic++) {
	adalf[I(ir,Ng,ic)] = 0.0;
	for(i = 0; i < Nx; i++) {
	  adalf[I(ir,Ng,ic)] += dyda[I(i,Ng,ir)] * dyda[I(i,Ng,ic)] * w[i];
	}
	if( ireport >= 4) printf("%10.3f ",adalf[I(ir,Ng,ic)]);
      }
      if( ireport >= 4) printf("\n");
    }

    /* -----------------------------------------------------------------------
    ** beta according to curvefit.pro
    ** ---------------------------------------------------------------------*/

    if( ireport >= 4) printf("beta:\n");
    for(ic = 0; ic < Ng; ic++) {
      adbet[ic] = 0.0;
      for(i = 0; i < Nx; i++) {
	adbet[ic] += (y[i] - adfmod[i]) * w[i] * dyda[I(i,Ng,ic)];
      }
      if( ireport >= 4) printf("%10.3f ",adbet[ic]);
    }
    if( ireport >= 4) printf("\n");

    /* -----------------------------------------------------------------------
    ** find new parameters
    ** ---------------------------------------------------------------------*/
    dochi = dchi2;
    for(i = 0; i < Ng; i++) gbck[i] = g[i];

    do {

      /* ---------------------------------------------------------------------
      ** matrix "c"
      ** -------------------------------------------------------------------*/
      if( ireport >= 4) printf("c:\n");
      for( ir = 0; ir < Ng; ir++ ) /* rows */ {
	for( ic = 0; ic < Ng; ic++ ) /* cols */ {
	  adc[I(ir,Ng,ic)] = sqrt( adalf[I(ir,Ng,ir)] * adalf[I(ic,Ng,ic)]);
	  if( ireport >= 4) printf("%10.3f ",adc[I(ir,Ng,ic)]);
	}
	if( ireport >= 4) printf("\n");
      }

      /* ---------------------------------------------------------------------
      ** matrix "array"
      ** -------------------------------------------------------------------*/
      for( ir = 0; ir < Ng; ir++ ) /* rows */ {
	for( ic = 0; ic < Ng; ic++ ) /* cols */ {
	  adal2[I(ir,Ng,ic)] = adalf[I(ir,Ng,ic)] / adc[I(ir,Ng,ic)];
	}
      }

      /* ---------------------------------------------------------------------
      ** modify "array"
      ** -------------------------------------------------------------------*/
      for( ir = 0; ir < Ng; ir++ ) /* rows */ {
	adal2[I(ir,Ng,ir)] *= (1.0 + dlamda);
      }
      if( ireport >= 4) {
	printf("array:\n");
	for( ir = 0; ir < Ng; ir++ ) /* rows */ {
	  for( ic = 0; ic < Ng; ic++ ) /* cols */ {
	    printf("%10.3f ",adal2[I(ir,Ng,ic)]);
	  }
	  printf("\n");
	}
      }

      /* ---------------------------------------------------------------------
      ** invert
      ** -------------------------------------------------------------------*/

      /* printf("cfit --- calling minv\n"); */
      istat = minv(adal2,Ng);
      if( istat != 0 ) {
	printf("cfit --- problem with matrix inversion detected\n");
	for(i = 0; i < Ng; i++) gtry[i] = gbck[i];
      } else {

	if( ireport >= 4) {
	  printf("inverted array:\n");
	  for( ir = 0; ir < Ng; ir++ ) /* rows */ {
	    for( ic = 0; ic < Ng; ic++ ) /* cols */ {
	      printf("%10.3f ",adal2[I(ir,Ng,ic)]);
	    }
	    printf("\n");
	  }
	}

	/* -------------------------------------------------------------------
	** new parameters
	** -----------------------------------------------------------------*/
	for(ic = 0; ic < Ng; ic++) {
	  dtmp = 0.0;
	  for( ir = 0; ir < Ng; ir++ ) /* cols */
	    dtmp += adal2[I(ir,Ng,ic)] / adc[I(ir,Ng,ic)] * adbet[ir];

	  gtry[ic] = g[ic] + dtmp;
	}

	if( ireport >= 3) aprint(gtry,0,Ng,"cfit --- New parameters:");
      }

      /* ---------------------------------------------------------------------
      ** check constraints
      ** ------------------------------------------------------------------ */

      cnstr(x,y,w,adfmod,Nx,gtry,Ng);

      if( ireport >= 3) aprint(gtry,0,Ng,"cfit --- New parameters:");

      /* ---------------------------------------------------------------------
      ** model function AND chi2
      ** -------------------------------------------------------------------*/

      funcs(x,adfmod,Nx,gtry,Ng,dyda);
      dchi2 = achi2(y,adfmod,w,0,Nx) / dfree;
      if( ireport >= 4) aprint(y,0,Nx,"y");
      if( ireport >= 4) aprint(adfmod,0,Nx,"fmod");
      if( ireport >= 4) printf("%10.3e, old: %10.3e\n",dchi2,dochi);
      
      dlamda *= 10.0;	

      if( ireport >= 3) printf("lamda: %10.3e\n",dlamda);
      if( dlamda > 1.0e25 ) {
	printf("cfit --- lamda too big: %.3e\n",dlamda);
	aeset(g,0,Ng,0.0);
	goto finalize;
      }
    } while( dchi2 >= dochi );

    if( ireport >= 2) printf("%10.3e, old: %10.3e\n",dchi2,dochi);

    /* -----------------------------------------------------------------------
    ** decrease lamda
    ** -------------------------------------------------------------------- */

    dlamda *= 0.01;

    /* -----------------------------------------------------------------------
    ** store new guess
    ** -------------------------------------------------------------------- */

    for(i = 0; i < Ng; i++) g[i] = gtry[i];

    dtmp = (dochi - dchi2) / dochi;
    if( ireport >= 3) printf("cfit --- rel change in chi2: %10.3e\n",dtmp);    

    if( dtmp <= 1.0e-4 ) goto finalize;
  }

  /* -------------------------------------------------------------------------
  ** this code only reached on error
  ** ---------------------------------------------------------------------- */

  printf("cfit --- maximal iterations reached (%d). Return.\n",iter);
  aeset(g,0,Ng,0.0);

 finalize:

  funcs(x,adfmod,Nx,g,Ng,dyda);
  dchi2 = achi2(y,adfmod,w,0,Nx) / dfree;

  *chi2  = (double)dchi2;

  if( ireport >= 1 ) {

    printf("cfit --- Spectrum:\n");
    for(i = 0; i < Nx; i++) {
      printf("%2d ",i);
      printf("%10.3e %10.3e %10.3e ",
	     x[i],y[i],w[i]);
      printf("%10.3e ",adfmod[i]);
      printf("%10.3e (%10.3e)\n",adfmod[i]-y[i],(adfmod[i]-y[i])/adfmod[i]);
    }
    printf("cfit --- chi2 = %10.3e\n",dchi2);
    aprint(gtry,0,Ng,"cfit --- New parameters:");
  }

  /* -------------------------------------------------------------------------
  ** covariance matrix
  ** -----------------------------------------------------------------------*/

  /* .........................................................................
  ** alpha according to Numerical Recipies
  ** ...................................................................... */

  for(ir = 0; ir < Ng; ir++) {
    for(ic = 0; ic < Ng; ic++) {
      adalf[I(ir,Ng,ic)] = 0.0;
      for(i = 0; i < Nx; i++) {
	adalf[I(ir,Ng,ic)] += dyda[I(i,Ng,ir)] * dyda[I(i,Ng,ic)] * w[i];
      }
    }
  }

  /* .........................................................................
  ** invert
  ** ...................................................................... */
  istat = minv(adalf,Ng);

  /* .........................................................................
  ** sigmas
  ** ...................................................................... */
  for(ir = 0; ir < Ng; ir++) sg[ir] = sqrt(adalf[I(ir,Ng,ir)]);

  /* -------------------------------------------------------------------------
  ** free mem
  ** -----------------------------------------------------------------------*/

  dvec_free(adalf);
  dvec_free(adc);
  dvec_free(adal2);
  dvec_free(adbet);
  dvec_free(gtry);
  dvec_free(gbck);
	   	    
  dvec_free(adfmod);
  dvec_free(dyda  );

  return;
}

/*  --------------------------------------------------------------------[<]---
    noconstraint --- no constrain for fitting
    --------------------------------------------------------------------[>]-*/
void noconstraint(double *x, double *y, double *w, double *f, int Nx, 
		  double *g, int Ng)
{
  return;
}

