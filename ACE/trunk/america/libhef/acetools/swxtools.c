/* ---------------------------------------------------------------------------
   swxtools.c --- tools for ACE/SWICS data analysis
   (c) 1998 Simon Hefti (hefti@umich.edu)
   $Id: swxtools.c,v 1.5 2004/10/19 13:45:40 jraines Exp $
   ------------------------------------------------------------------------ */

static char* rcsid =\
"$Id: swxtools.c,v 1.5 2004/10/19 13:45:40 jraines Exp $";

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "acetools.h"

#define NLUTABLE 60

/* ===========================================================================
** ACE/SWICS peak positions and sigmas
** ======================================================================== */


/* -------------------------------------------------------------------- --- --
   Function: lax_tofcent_ch
   Synopsis: For given Etot [keV] and mass [amu] return TOF channel using:
     TOF = c / sqrt(Etot * (1 - a) - b)
   ------------------------------------------------------------------- --- -*/
long lax_tofcent_ch(double detot_keV, long lm_amu)
{

  static double dlutab[NLUTABLE][3];
  static int    ifirsttime = 1;

  int           i    = 0;
  double        dc   = 0.0;
  long          lres = 0L;
  double        dnom = 0.0;

  /* --- the first time: set up look-up table --- */

  if( ifirsttime ) {
    ifirsttime = 0;
    for(i = 0;i < NLUTABLE; i++) {
      dlutab[i][0] = -1.0;
      dlutab[i][1] = -1.0;
    }

    /* 980722141.log */
    /* 981102234.log */
    /* 981132218.log */
    /* 981141417.log */
    /* 981171508.log */

    dlutab[ 4][0] = 0.010;   dlutab[ 4][1] =  1.0;   dlutab[ 4][2] = 2350.0;
    dlutab[12][0] = 0.010;   dlutab[12][1] =  1.0;   dlutab[12][2] = 4070.0;
    dlutab[16][0] = 0.010;   dlutab[16][1] =  1.0;   dlutab[16][2] = 4700.0;
    dlutab[20][0] = 0.010;   dlutab[20][1] =  1.0;   dlutab[20][2] = 5210.0;
    dlutab[28][0] = 0.010;   dlutab[28][1] =  3.0;   dlutab[28][2] = 6160.0;
    dlutab[56][0] = 0.010;   dlutab[56][1] =  5.0;   dlutab[56][2] = 8600.0;
  }

  /* --- is requested mass in table ? --- */

  lres = -1L;
  if( (lm_amu < 0L) || (lm_amu >= NLUTABLE) ) {
    fprintf(stderr,
	    "E:lax_tofcent_ch:mass %ld out of range.\n",lm_amu);
  }
  else /* mass is in range */ {
    if(dlutab[lm_amu][0] == -1.0) {
      fprintf(stderr,
	      "E:lax_tofcent_ch:mass %ld not in table.\n",lm_amu);
    }
    else /* mass is in table */ {

      /* dc   = 1100.0 * sqrt((double)lm_amu); */
      dc   = dlutab[lm_amu][2];

      dnom = detot_keV * (1.0 - dlutab[lm_amu][0]) - dlutab[lm_amu][1];
      if( dnom <= 0.0 ) {
	fprintf(stderr,
		"E:lax_tofcent_ch:cannot get squareroot of %.2f.\n",dnom);
      }
      else /* square root ok */ {
	dnom = sqrt(dnom);
	if( dnom <= 0.0 ) {
	  fprintf(stderr,
		  "E:lax_tofcent_ch:bad denominator %.2f.\n",dnom);
	}
	else /* denominator ok */ {

	  lres = (long)(dc / dnom);
	}
      }
    }
  }
  return(lres);

}

/* -------------------------------------------------------------------- --- --
   Function: dax_tofsig1_ch
   Synopsis: return sig1 of TOF signal in [channels]
   ------------------------------------------------------------------- --- -*/
double dax_tofsig1_ch(long ltof_ch, long lm_amu)
{
  static double adlutab[NLUTABLE];
  static int    ifirsttime = 1;

  int           i    = 0;
  double        dres = 0.0;

  dres = -1.0;

  /* --- the first time: set up look-up table --- */

  if( ifirsttime ) {

    ifirsttime = 0;

    for(i = 0;i < NLUTABLE; i++) adlutab[i] = -1.0;

    /* 981102234.log */
    /* 981132218.log */
    /* 981141417.log */
    /* 981171508.log */

    adlutab[ 4] = 0.012;
    adlutab[12] = 0.012;
    adlutab[16] = 0.012;
    adlutab[20] = 0.0125; /* inaccurate ! */
    adlutab[28] = 0.0145; /* " */
    adlutab[56] = 0.0120; /* " */

  }

  /* --- is requested mass in table ? --- */

  if( (lm_amu < 0L) || (lm_amu >= NLUTABLE) ) {
    fprintf(stderr,
	    "dax_tofsig1 --- mass %ld out of range.\n",lm_amu);
  }
  else /* mass is in range */ {
    if(adlutab[lm_amu] == -1.0) {

      fprintf(stderr,
	      "dax_tofsig1 --- mass %ld not in table.\n",lm_amu);

    }
    else /* mass is in table */ {

      dres = adlutab[lm_amu];
    }
  }

  return(dres * (double)ltof_ch);
}

/* -------------------------------------------------------------------- --- --
   Function: dax_tofsig2_ch
   Synopsis: return sig2 of TOF signal in [channels]
   ------------------------------------------------------------------- --- -*/
double dax_tofsig2_ch(long ltof_ch, long lm_amu)
{
  return(0.0125 * (double)ltof_ch);
}

/* -------------------------------------------------------------------- --- --
   Function: lax_esdcent_ch
   Synopsis: For given Etot [keV] and mass [amu] return ESSD channel.
   ------------------------------------------------------------------- --- -*/
long lax_esdcent_ch(double detot_keV, long lm_amu)
{
  static double dlutab[NLUTABLE][2];
  static int    ifirsttime = 1;

  int           i    = 0;
  long          lres = 0L;

  /* --- the first time: set up look-up table --- */

  if( ifirsttime ) {
    ifirsttime = 0;
    for(i = 0;i < NLUTABLE; i++) {
      dlutab[i][0] = -1.0;
      dlutab[i][1] = -1.0;
    }

    /* 981102234.log */
    /* 981132218.log */
    /* 981141417.log */
    /* 981171508.log */

    dlutab[ 4][0] = 0.286;   dlutab[ 4][1] =   3.2;
    dlutab[12][0] = 0.329;   dlutab[12][1] =  -4.1;
    dlutab[16][0] = 0.317;   dlutab[16][1] =  -8.2;
    dlutab[20][0] = 0.300;   dlutab[20][1] =  -9.5;
    dlutab[28][0] = 0.220;   dlutab[28][1] =  -0.1;
    dlutab[56][0] = 0.200;   dlutab[56][1] = -13.0;

  }

  /* --- is requested mass in table ? --- */

  lres = -1L;
  if( (lm_amu < 0L) || (lm_amu >= NLUTABLE) ) {
    fprintf(stderr,
	    "E:lax_esdcent_ch:mass %ld out of range.\n",lm_amu);
  }
  else /* mass is in range */ {
    if(dlutab[lm_amu][0] == -1.0) {
      fprintf(stderr,
	      "E:lax_esdcent_ch:mass %ld not in table.\n",lm_amu);
    }
    else /* mass is in table */ {

      lres = (long)(detot_keV * dlutab[lm_amu][0] + dlutab[lm_amu][1]);
    }
  }
  return(lres);
}

long lax_esdcen_ch(long ltof_ch, long lm_amu) /* OLD VERSION */
{
  static double dlutab[NLUTABLE];
  static int    ifirsttime = 1;

  int           i = 0;
  long          lres = 0L;
  double        dtmp = 0.0;

  /* --- the first time: set up look-up table --- */

  if( ifirsttime ) {
    ifirsttime = 0;
    for(i = 0;i < NLUTABLE; i++) dlutab[i] = -1.0;

    /* 980722141.log */

    dlutab[ 4] = 2.0e6;
    dlutab[12] = 4.9e6;
    dlutab[16] = 5.9e6;
    dlutab[20] = 7.0e6;
    dlutab[28] = 8.3e6;
  }

  /* --- valid TOF  ? --- */
  lres = -1L;

  if( ltof_ch > 0L ) {

    /* --- is requested mass in table ? --- */

    if( (lm_amu < 0L) || (lm_amu >= NLUTABLE) ) {

      fprintf(stderr,
	      "E:lax_esdcent_ch:mass %ld out of range.\n",lm_amu);

    }
    else /* --- is mass in table ? --- */ {

      if(dlutab[lm_amu] == -1.0) {

	fprintf(stderr,
		"E:lax_esdcent_ch:mass %ld not in table.\n",lm_amu);

      }
      else /* mass is in table */ {

	dtmp = (double)ltof_ch;
	dtmp = dtmp * dtmp;

	lres = (long)( dlutab[lm_amu] / dtmp );

      }
    }
  }

  return(lres);

}

/* -------------------------------------------------------------------- --- --
   Function: dax_esdsig_ch
   Synopsis: return sig of ESSD signal in [channels]
   ------------------------------------------------------------------- --- -*/
double dax_esdsig_ch(long lesd_ch, long lm_amu)
{
  static double adlutab[NLUTABLE];
  static int    ifirsttime = 1;

  int           i    = 0;
  double        dres = 0.0;

  dres = -1.0;

  /* --- the first time: set up look-up table --- */

  if( ifirsttime ) {

    ifirsttime = 0;

    for(i = 0;i < NLUTABLE; i++) adlutab[i] = -1.0;

    /* 981102234.log */
    /* 981132218.log */
    /* 981141417.log */
    /* 981171508.log */

    adlutab[ 4] = 0.090;
    adlutab[12] = 0.120;
    adlutab[16] = 0.134;
    adlutab[20] = 0.140; /* large errors */
    adlutab[28] = 0.160; /* " */           
    adlutab[56] = 0.140; /* " */           

  }

  /* --- is requested mass in table ? --- */

  if( (lm_amu < 0L) || (lm_amu >= NLUTABLE) ) {
    fprintf(stderr,
	    "dax_esdsig --- mass %ld out of range.\n",lm_amu);
  }
  else /* mass is in range */ {
    if(adlutab[lm_amu] == -1.0) {

      fprintf(stderr,
	      "dax_esdsig --- mass %ld not in table.\n",lm_amu);

    }
    else /* mass is in table */ {

      dres = adlutab[lm_amu];
    }
  }

  return(dres * (double)lesd_ch);
}

/* -------------------------------------------------------------------- --- --
   Function: vax_peakpos
   Synopsis:
     Calculates peak positions for ACE/SWICS (T0, sig_T, E0 and sig_E)
     using the routines defined above:
       lax_tofcent_ch
       dax_tofsig1_ch
       lax_esdcent_ch
       dax_esdsig_ch
     The advantage of this routine is that just one call is needed to
     get all the information.
   ------------------------------------------------------------------- --- -*/
void vpax_peakpos(double *pdetot_keV, long *plm_amu, 
		 long *plt0, double *pdst,long *ple0, double *pdse)
{
  *plt0 = lax_tofcent_ch(*pdetot_keV,*plm_amu);
  *pdst = dax_tofsig1_ch(*plt0,*plm_amu);

  *ple0 = lax_esdcent_ch(*pdetot_keV,*plm_amu);
  *pdse = dax_esdsig_ch(*ple0,*plm_amu);

  printf("DBG: %5.1f %2ld --> %4ld %5.1f %3ld %5.1f\n",
	 *pdetot_keV,*plm_amu,*plt0,*pdst,*ple0,*pdse);

  return;
}

void vax_peakpos(double detot_keV, long lm_amu, 
		 long lt0, double dst,long le0, double dse)
{
  vpax_peakpos(&detot_keV,&lm_amu, 
	       &lt0,&dst,&le0,&dse);
}

void vax_peakpos_if(double *pdetot_keV, long *plm_amu, 
		    long *plt0, double *pdst,long *ple0, double *pdse)
{
  static double detot_keV;
  static long   lm_amu;
  static long   lt0;
  static double dst;
  static long   le0;
  static double dse;

  detot_keV = *pdetot_keV;
  lm_amu    = *plm_amu;
  lt0       = *plt0;
  dst       = *pdst;
  le0       = *ple0;
  dse       = *pdse;

  vax_peakpos(detot_keV,lm_amu,lt0,dst,le0,dse);

  pdetot_keV = &detot_keV;
  plm_amu    = &lm_amu;
  plt0       = &lt0;
  pdst       = &dst;
  ple0       = &le0;
  pdse       = &dse;

  return;
}

void vax_peakpos_arg(int argc, void *argv[])
{
  double *pdetot_keV;
  long   *plm_amu;
  long   *plt0;
  double *pdst;
  long   *ple0;
  double *pdse;

  /* arguments */

  if( argc != 6 ) {
    printf("vax_peakpos_if --- %2d arguments are not enough (6 expected)\n",
	   argc);

    return;
  }

  /* put arguments to variables */

  pdetot_keV = (double *)(argv[0]);
  plm_amu    = (long *)(argv[1]);
  plt0       = (long *)(argv[2]);
  pdst       = (double *)(argv[3]);
  ple0       = (long *)(argv[4]);
  pdse       = (double *)(argv[5]);

  /* call routine */

  vpax_peakpos(pdetot_keV,plm_amu,plt0,pdst,ple0,pdse);

  /* argv[2]    = plt0; */

  return;
}

/* ===========================================================================
** Ellipse handling
** ======================================================================== */


/* -------------------------------------------------------------------- --- --
   Function: bax_ellipse_isin
   Synopsis: returns 1 if (x,y) is within ellipse est, 0 else.
   ------------------------------------------------------------------- --- -*/
BYTE bax_ellipse_isin(double dx, double dy, EST *pest)
{
  double dx1  = 0.0, dx2 = 0.0;
  double dy1  = 0.0, dy2 = 0.0;
  double dang = 0.0;
  double dtmp = 0.0;
  double da;                            /* temps for semi-axis */
  double da1;
  double da2;
  double db;
  double db1;
  double db2;


  /* -------------------------------------------------------------------------
  ** move to ellipse center
  ** ---------------------------------------------------------------------- */

  dx1 = dx - pest->stp0.dx;
  dy1 = dy - pest->stp0.dy;

  /* -------------------------------------------------------------------------
  ** invert rotation
  ** ---------------------------------------------------------------------- */
  
  dang = -pest->dphi;
  dx2  = dx1 * cos(dang) - dy1 * sin(dang);
  dy2  = dx1 * sin(dang) + dy1 * cos(dang);

  /* -------------------------------------------------------------------------
  ** two-sided ellipses ?
  ** ---------------------------------------------------------------------- */

  if( (pest->sts2.dx == 0.0) || (pest->sts2.dx == 0.0) ) {
    /* both sides the same: stsa */
    da1 = pest->stsa.dx;
    da2 = pest->stsa.dx;
    db1 = pest->stsa.dy;
    db2 = pest->stsa.dy;
  } else {
    /* asymmetric */
    da1 = pest->stsa.dx;  /*    /-\   b2*/
    da2 = pest->sts2.dx;  /*   / | \    */
    db1 = pest->stsa.dy;  /*a1 |_|__\ a2*/
    db2 = pest->sts2.dy;  /*   \ |  /   */
                  	  /*    \|-/  b1*/
  }


  /* -------------------------------------------------------------------------
  ** test ellipse
  ** ---------------------------------------------------------------------- */

  if( dx1 < 0.0 ) da = da1;
  else            da = da2;

  if( dy1 < 0.0 ) db = db1;
  else            db = db2;

  dtmp = dratio(dsqr(dx2),dsqr(da)) +
         dratio(dsqr(dy2),dsqr(db));

  /* if( dtmp <= 1.0 ) printf("bax --- %5.3f %5.3f: %5.3f\n",dx,dy,dtmp); */

  if( dtmp < 0.0 ) {
    printf("bax_ellipse_isin --- problem with semi-axis: %.3f %.3f\n",
	   da,db);
    return(0);
  }

  /*
  printf("DBG (ellipse): input:   %7.3f %7.3f\n",dx,dy);
  printf("               Ellipse: %7.3f %7.3f (%7.3f %7.3f) (%7.3f %7.3f)\n",
	 pest->stp0.dx,pest->stp0.dy,
	 da1,da2,db1,db2);
  printf("               used:    %7.3f %7.3f, Result: %1d\n",
	 da,db,(dtmp <= 1.0));
  */

  return((long)(dtmp <= 1.0));
}

/* ===========================================================================
** data reduction
** ======================================================================== */

/* -------------------------------------------------------------------- --- --
   Function: dduty
   Synopsis: 
     ACE/SWICS duty cycle (fraction of spin period where SWICS is exposed to
       solar wind)
     daspect: aspect angle
     dmach:   mach number of solar wind
   ------------------------------------------------------------------- --- -*/
double dduty(double daspect, double dmach)
{
  return(1.0);
}

/* -------------------------------------------------------------------- --- --
   Function: dgeometryfactor
   Synopsis: 
     ACE/SWICS geometry factor
     Depends on aspect angle due to the three detectors
     daspect: aspect angle
   ------------------------------------------------------------------- --- -*/
double dgeometryfactor(double daspect)
{
  return(0.0185); /* cm^2 */
}

/* -------------------------------------------------------------------- --- --
   Function: deff
   Synopsis: 
     ACE/SWICS TCR efficiencies
     detot: total energy before carbon foil
   ------------------------------------------------------------------- --- -*/
double deff(double detot)
{
  return(1.0);
}

/* -------------------------------------------------------------------- --- --
   Function: vdiffflux
   Synopsis: 
     Differential Flux [#/cm^2 s keV/e]
     adcts:   measured counts(E/q)
     adeoq:   E/q for spectrum above (in same order)
     daspect: aspect angle
     dmach:   SW mach number
     dpav:    post-acceleration
     dcrg:    charge
     addj:    result: differentl flux
   ------------------------------------------------------------------- --- -*/
void vdiffflux(double adcts[60], double adeoq[60], double daspect,
	       double dmach, double dpav, double dcrg, double addj[60])
{
  double ddeltaeoq;
  double dspintime;
  double ddutycycle;
  double dgeom;
  double detot;
  double defficiency;
  int    i;

  dspintime  = 12.0; /* s */

  ddutycycle = dduty(daspect,dmach);

  dgeom      = dgeometryfactor(daspect);

  for(i = 0; i < 60; i++) {

    addj[i] = 0.0;

    if( adcts[i] > 0.0 ) {

      ddeltaeoq = 0.064 * adeoq[i];

      detot    = dcrg * (adeoq[i] + dpav);

      defficiency = deff(detot);

      if( (defficiency > 0.0 ) &&
          (dspintime   > 0.0 ) &&
          (ddutycycle  > 0.0 ) &&
          (dgeom       > 0.0 ) &&
          (ddeltaeoq   > 0.0 ) ) {

	addj[i] = adcts[i] / dspintime / ddutycycle / dgeom / 
	  ddeltaeoq / defficiency;
      }
    }
  }
  return;
}


/* -------------------------------------------------------------------- --- --
   Function: dflux
   Synopsis: 
     Flux [#/cm^2 s]
     addj:    differentl flux
     adeoq:   E/q for spectrum above (in same order)
   ------------------------------------------------------------------- --- -*/
double dflux(double addj[60],double adeoq[60])
{
  double dres;
  double ddeltastar;
  int    i;

  dres = 0.0;

  for(i = 0; i < 60; i++) {

    if( addj[i] > 0.0 ) {

      ddeltastar = 1.0365 * adeoq[i];

      dres += addj[i] * ddeltastar;
    }
  }

  return(dres);
}

/* -------------------------------------------------------------------- --- --
   dspeed --- calculate speed from 60-entries vector

   adcts: contains counts.
   adeoq: E/q values in the same order as adcts.

   /Note/: adcts[0],adcts[1] are neglected (jump from 0-->100 kV)

   see also: mrxxspd.
   ------------------------------------------------------------------- --- -*/
double dspeed(double adcts[60],double adeoq[60], double dmas, double dcrg,
	      double *pdvth)
{
  double dnorm;
  double dres;
  double dvth;
  double adeoqspeed[NEDB];
  int    i = 0;

  dres = 0.0;

  /* --- sum(counts) > dmin --- */

  dnorm = 0.0;
  for(i = 2;i < NEDB; i++) {

    /* don't include first step */

    if( adcts[i] > 0.0 ) dnorm += adcts[i];

  }
  
  if( dnorm < 0.0) {
    printf("dspeed --- not enough data (sum = %.1f)\n",dnorm);
    return(-1.0);
  }

  /* --- E/q and speed  --- */

  for(i = 2;i < NEDB; i++) {

    adeoqspeed[i] = sqrt(2.0e3 * adeoq[i] / dmas / 1.6606e-27 *
			 dcrg * 1.6022e-19) / 1.0e3;
  }

  /* --- normalization --- */

  dnorm = 0.0;
  for(i = 2;i < NEDB; i++) dnorm += adcts[i] / adeoq[i];

  /* --- moment --- */

  dres  = 0.0;
  for(i = 2;i < NEDB; i++) dres += adcts[i] / adeoq[i] * adeoqspeed[i];

  dres  = dres / dnorm;

  /* --- second moment --- */

  dvth = 0.0;
  for(i = 2;i < NEDB; i++) dvth += adcts[i] / adeoq[i] *
			     dsqr(adeoqspeed[i]);

  dvth /= dnorm;

  /* --- thermal speed --- */

  if( dvth <= dres ) dvth = -1.0;
  else               dvth = sqrt(dvth - dsqr(dres));

  /*
  printf("DBG swxtools::dspeed --- dnorm = %10.1f\n",dnorm);
  printf("DBG swxtools::dspeed --- dres  = %10.1f\n",dres);
  printf("DBG swxtools::dspeed --- dvth  = %10.1f\n",dvth);
  */

  /* --- test for NaN --- */

  if( dres != dres ) dres = -1.0;
  if( dvth != dvth ) dvth = -1.0;

  *pdvth = dvth;

  return(dres);
}

/* -------------------------------------------------------------------- --- --
   Function: dax_aprxspeed
   Synopsis: calculate first and second moment of a distribution.
     Given an array of 60 numbers, representing counts as a
     function of E/q, the function calculates the first moment, using 
     the E/q table from the "decoded" structure.
     The second moment is used to estimate the thermal speed.
     The sum of counts, weigthed by E/q, is calculated as well.
   ------------------------------------------------------------------- --- -*/
double dax_aprxspeed(double adc[NEDB],SBCYC *pc, double dm, double dq,
		     double dmin, double *pdtherm, double *pdsum)
{
  double adeoq[NEDB];
  double adeoqspeed[NEDB];
  double dnorm;
  double dspd;
  int    i = 0;
  double dtmp = 0.0;

  dspd   = -999.9;
  *pdtherm = -999.9;
  *pdsum   = -999.9;

  /* --- sum(counts) > dmin --- */

  dnorm = 0.0;
  for(i = 0;i < NEDB; i++) dnorm += adc[i];
  
  if( dnorm < dmin ) {
    fprintf(stderr,
	    "E:dax_aprxspeed: not enough data (sum = %.1f,min = %.1f)\n",
	    dnorm,dmin);
    return(0.0);
  }

  *pdsum = dnorm;

  /* --- E/q and speed  --- */

  for(i = 0;i < NEDB; i++) {

    /* E/q of step */

    adeoq[i] = dswxeoq(i,pc->abxeqtab,pc->adcnq);
    adeoqspeed[i] = sqrt(2.0e3 * adeoq[i] / dm / 1.6606e-27 *
			 dq * 1.6022e-19) / 1.0e3;
  }

  /* --- normalization --- */

  dnorm = 0.0;
  for(i = 0;i < NEDB; i++) dnorm += adc[i] / adeoq[i];

  /* --- moment --- */

  dspd = 0.0;
  for(i = 0;i < NEDB; i++) dspd += adc[i] / adeoq[i] *
			     adeoqspeed[i];

  dspd = dspd / dnorm;

  /* --- second moment --- */

  *pdtherm = 0.0;
  for(i = 0;i < NEDB; i++) *pdtherm += adc[i] / adeoq[i] *
			     dsqr(adeoqspeed[i]);

  *pdtherm = *pdtherm / dnorm;

  /* --- thermal speed --- */

  dtmp = dsqr(dspd);

  if( *pdtherm <= dspd ) *pdtherm = -1.0;
  else                     *pdtherm = sqrt(*pdtherm - dsqr(dspd));

  /* --- test for NaN --- */

  if( *pdtherm != *pdtherm ) *pdtherm = -1.0;
  if( *pdsum   != *pdsum   ) *pdsum   = -1.0;
  if( dspd   != dspd   ) dspd   = -1.0;

  return(dspd);
}

/*  --------------------------------------------------------------------------
    Function: mrxxspd --- get xx speed form matrix rates (xx = H+,He++,...)

    /Note/: EDB 0 and 1 are neglected.
    /Note/: For dspeed, the entries of adxmr1 to be neglected must be
            the /first/ two ones.
    see also: dspeed, asxl2.
    ------------------------------------------------------------------------*/
void mrxxspd(SBCYC *pcyc, double *dspd, double *dvth, double *deoq,
	     double dmas, double dcrg, int ixx)
{
  double adxmr1[NEDB];
  double adxeoq[NEDB];

  double dtmp;

  int    i;

  dtmp = 0.0;

  /* --- re-arrange data --- */

  for(i = 2; i < NEDB; i++) {

    adxmr1[59-(i-1)]  = (double)pcyc->alxmr[i][ixx][NSEC];
    adxeoq[i] = dswxeoq(i,pcyc->abxeqtab, pcyc->adcnq);

  }

  /*
  for(i = 0; i < NEDB; i++) {
    printf("%2d %6.1f %6.1f\n",i,adxmr1[i],adxeoq[i]);
  }
  */

  /* --- re-arrange data --- */

  *dvth = -3.0;
  *dspd = dspeed(adxmr1,adxeoq,dmas,dcrg,dvth);

  if( *dspd < 200.0 ) dtmp = 400.0;
  else                dtmp = *dspd;

  *deoq = 0.5 * dmas * 1.6066e-27 / dcrg / 1.6022e-19 *
    dsqr(dtmp) * 1.0e3;

  return;
}

/*  --------------------------------------------------------------------------
    Function: mrxxtot --- get sum of counts of MR xx

    /Note/: EDB 0 and 1 are neglected.

    see also: mrxxdra, asxl2.
    ------------------------------------------------------------------------*/
double mrxxtot(SBCYC *pcyc, int ixx)
{
  double dtot;

  int    i;

  dtot = 0;
  for(i = 2; i < NEDB; i++) {
    dtot += (double)pcyc->alxmr[i][ixx][NSEC];
  }

  return(dtot);
}

/*  --------------------------------------------------------------------------
    Function: mrxxdra --- "density ratio" from matrix rates

    see also: mrxxtot, asxl2.
    ------------------------------------------------------------------------*/
double mrxxdra(SBCYC *pcyc, int ixx, int iyy)
{
  double dxx;
  double dyy;

  double dres = 0.0;

  dxx  = mrxxtot(pcyc,ixx);
  dyy  = mrxxtot(pcyc,iyy);

  dres = dratio(dxx,dyy);

  return(dres);
}

/* ---------------------------------------------------------------------------
** xphafilt --- returns 0 ("discard") if v(E/q,m/q) < 0.5 vH, 1 (use) else
** ------------------------------------------------------------------------ */
int xphafilt(double vH, double vth, double eoq, double pav, 
	     int itof, int iesd)
{
  double eoqhe;
  int    ires = 0;
  double *adfm;
  double dmoq;
  double dtof;
  double dveoq;

  ires  = 1;                            /* default: use PHA word */

  /* -------------------------------------------------------------------------
  ** first: "Geiss method"
  ** ---------------------------------------------------------------------- */

  dtof = (double)(itof);
  dmoq = adpumoq(eoq,(pav + 1.5),dtof);

  /*
    printf("DBG xphafilt --- v %5.1f eoq %7.3f pav %7.3f T %4d moq %7.3f\n",
    vH,eoq,pav,itof,dmoq);
  */
	 
  /* .........................................................................
  ** speed from E/q for calculated m/q
  ** ...................................................................... */

  dveoq = sqrt(2.0e3 * eoq / dmoq / MELEM * QELEM) / 1.0e3;

  if( dveoq < 0.5 * vH ) ires = 0;

  /*
    printf("DBG xphafilt --- veoq %5.1f ires %d\n",
    dveoq,ires);
  */

  /* -------------------------------------------------------------------------
  ** then: Tech Rep 2
  ** ---------------------------------------------------------------------- */

  if( ires ) {                          /* not decided yet */

    /* E/q according to vH */
    eoqhe = MELEM / QELEM * dsqr(vH * 1.05) * 1.0e3;
    if( eoq < eoqhe) {
      /* forward model */
      adfm = xfm(eoq,pav,4.0,2.0);
      /* compare TOF with forward model */
      if( itof > (int)(adfm[0] + 5.0 * adfm[1]) ) {
	if( iesd <= 20 ) {
	  ires = 0;
	}
      }
    }
  }

  /*
  printf("DBG xphafilt --- v %5.1f E/q (v) %6.3f (stp) %6.3f res: %1d\n",
     vH,eoqhe,eoq,ires);
  */

  return(ires);

  /* Note:
  ** vth not yet used */
}


/* ===========================================================================
** Efficiency
** ======================================================================== */

/*  --------------------------------------------------------------------------
    auxcheff --- eff of SSD in AUX ch
    ------------------------------------------------------------------------*/
double auxeff(double de0, double ddelta, double dthre)
{
  double dz;

  if( ddelta <= 0.0 ) {
    printf("auxeff --- cannot handle sigma: %.2f\n",ddelta);
    return(-1.0);
  }

  dz = (dthre - de0) / sqrt(2.0) / ddelta;

  return(0.5 * ferfcc(dz));
}


/*  --------------------------------------------------------------------------
    xeffv1 --- first version of routine handling SWICS effiviency
    ------------------------------------------------------------------------*/
double xeffv1(double de, double dmas)
{
  static double XE2A[57];               /* see LabBook p 321 (green) */
  static double XE2B[57];               /* parameters for eta_2 (DCR/FSR) */
  static double XE20[57];

  static double XE3A[57];               /* see LabBook p 321 (green) */
  static double XE3B[57];               /* parameters for eta_3 (TCR/DCR) */
  static double XE30[57];

  double eta_1 = 0.0;
  double eta_2 = 0.0;
  double eta_3 = 0.0;
  double eta   = 0.0;

  static int ifirsttime = 1;

  int    im;

  if( ifirsttime == 1 ) {

    ifirsttime = 0;

    aeset(XE2A,0,57,-1.0);
    aeset(XE2B,0,57,-1.0);
    aeset(XE20,0,57,-1.0);

    aeset(XE3A,0,57,-1.0);
    aeset(XE3B,0,57,-1.0);
    aeset(XE30,0,57,-1.0);

    /* eta_2 */

    /* alpha */
    XE2A[16] = 0.65;
    XE2A[56] = 0.63;

    /* beta */
    XE2B[16] = 0.016;
    XE2B[56] = 0.006;

    /* threshold */
    XE20[16] =  90.0;
    XE20[56] = 220.0;

    /* eta_3 */

    XE3A[16] = 0.92;
    XE3A[56] = 0.93;

    XE3B[16] = 0.2;
    XE3B[56] = 0.04;

    XE30[16] =  71.0;
    XE30[56] = 150.0;
  }

  if( (dmas <= 0.0) || (dmas > 56.0) ) {
    printf("xeffv1 --- cannot deal with mass = %.0f.\n",dmas);
    return(eta);
  }

  im = (int)dmas;
  if( XE2A[im] <= 0.0 ) {
    printf("xeff1 --- mass %.0f not in model.\n",dmas);
    return(eta);
  }

  /* -------------------------------------------------------------------------
  ** eta_1
  ** ---------------------------------------------------------------------- */

  eta_1 = 1.0;                          /* not yet determined */

  /* -------------------------------------------------------------------------
  ** eta_2
  ** ---------------------------------------------------------------------- */

  eta_2 = xeffv1_helper(XE2A[im],XE2B[im],XE20[im],de);

  /* -------------------------------------------------------------------------
  ** eta_3
  ** ---------------------------------------------------------------------- */

  eta_3 = xeffv1_helper(XE3A[im],XE3B[im],XE30[im],de);

  /* -------------------------------------------------------------------------
  ** eta
  ** ---------------------------------------------------------------------- */

  eta = eta_1 * eta_2 * eta_3;

  /* printf("xeffv1 --- %5.3f %5.3f %5.3f %5.3f\n",eta_1,eta_2,eta_3,eta); */

  return(eta);
}

/*  --------------------------------------------------------------------------
    xeffv1_helper --- arctag-term for xeffv1
    ------------------------------------------------------------------------*/
double xeffv1_helper(double da, double db, double de0, double de)
{
  double dres;

  /* DBG */
  /*
  printf("DBG xeffv1_helper --- (DPIO2 -   acos(0)) = %.5f\n",
	DPIO2 - acos(0.0));
  printf("DBG xeffv1_helper --- (DPI   - 2 acos(0)) = %.5f\n",
	DPI - 2.0 * acos(0.0));
  */

  dres  = atan( db * (de - de0) ) + DPIO2;
  dres  = da * dres / DPI;

  return(dres);
}

/* ===========================================================================
** SWICS/ACE kinetic properties from Matrix Rates/AUX
** ======================================================================== */

/*  --------------------------------------------------------------------------
    auxspd --- kinetic prop from AUX channel
    ------------------------------------------------------------------------*/
void auxspd(SBCYC  *pcyc, double adgue[4], double adsgu[4])
{
  int    imx;

  double adauxeq[NEDB];                 /* E/q */
  double adauxch[NEDB];                 /* counts in AUX channel */
  double adauxchrev[NEDB];              /* reversed direction */
  double adtmp[7];                      /* weight for fitting */
  int    i;
  double deps;                          /* efficienccy */
  double dchi;

  double glow[4];
  double ghig[4];

  /* -------------------------------------------------------------------------
  ** E/q
  ** ---------------------------------------------------------------------- */

  for(i = 0; i < NEDB; i++)
    adauxeq[i] = (0.1029 * pow(1.036545,pcyc->abxeqtab[59-i]));
    
  /* -------------------------------------------------------------------------
  ** counts in AUX channel
  ** ---------------------------------------------------------------------- */

  for(i = 0; i < NEDB; i++) adauxch[i]  = 0.0;

    /* .......................................................................
    ** do not forget slip between data accumulation and transmission
    ** .................................................................... */

  for(i = 1; i < 59; i++) {

    adauxch[i-1]  = (double)pcyc->alxsr[i][LXPR][NSEC];
    adauxch[i-1] += (double)pcyc->alxsr[i][LXAR][NSEC];
  }

  /* reverse dir for finding H+ maximum */
  for(i = 0; i < NEDB; i++) adauxchrev[i] = adauxch[59 - i];

  /* -------------------------------------------------------------------------
  ** apply efficiency for H
  ** ---------------------------------------------------------------------- */

  /*
  for(i = 1; i < 59; i++) {
    deps       = auxeff(adauxeq[i] + pcyc->dxpav,2.475,23.25);
    if( deps < 0.01 ) deps = 0.0;
    adauxch[i] = dratio(adauxch[i],deps);
  }
  */

  /* -------------------------------------------------------------------------
  ** make sure we have data
  ** ---------------------------------------------------------------------- */

  deps = asum(adauxch,1,58);
  if (deps < 11600.0 ) {
    printf("auxspd --- no data in AUX channel (sum = %10.3e)\n",deps);
    aeset(adgue,0,4,-1.0);
    return;
  }

  /* -------------------------------------------------------------------------
  ** E/q --> v
  ** ---------------------------------------------------------------------- */
  for(i = 0; i < NEDB; i++)
    adauxeq[i] = sqrt(adauxeq[i] * 2.0e3 / 1.6606e-27 * 1.6022e-19) /
      1.0e3;

  /* -------------------------------------------------------------------------
  ** identify max
  ** ---------------------------------------------------------------------- */

  /* aprint(adauxch,0,NEDB,"aswxl2 --- Spectrum"); */
  imx = firstmax(adauxchrev,0,NEDB,300.0);
  imx = 59 - imx;
  /* printf("aswxl2 --- max found: %3d (%10.3e)\n",imx,adauxch[imx]); */

  /* -------------------------------------------------------------------------
  ** enough counts ?
  ** ---------------------------------------------------------------------- */

  if (adauxch[imx] < 500.0 ) {
    printf("auxspd --- no data in max(AUX channel):  %10.3e\n",
	   adauxch[imx]);
    aeset(adgue,0,4,-1.0);
    return;
  }

  /* -------------------------------------------------------------------------
  ** check position of max (need 7 points)
  ** ---------------------------------------------------------------------- */

  if( (imx > 3) && (imx < 56) ) {

    for(i = 0; i < 7; i++) adtmp[i] = 1.0 / (adauxch[imx - 3 + i] + 10);

    /* -----------------------------------------------------------------------
    ** estimate parameters
    ** -------------------------------------------------------------------- */

    adgue[0] = adauxch[imx] * 1.0;
    adgue[1] = adauxeq[imx] * 1.0;
    adgue[2] = dmax(adgue[1] * 0.05,1.0);
    adgue[3] = (asum(adauxch,imx-3,2) + asum(adauxch,imx+2,2))/4.0;

    /* -----------------------------------------------------------------------
    ** assume estimated parameters are not too bad AND set limits
    ** -------------------------------------------------------------------- */
    glow[0]  = 100.0;           ghig[0]  = 1.0e6;
    glow[1]  = adgue[1] - 30.0; ghig[1]  = adgue[1] + 30.0;
    glow[2]  = 0.1;             ghig[2]  = 100.0;
    glow[3]  = 1.0;             ghig[3]  = 1000.0;

    /* .......................................................................
    ** Note: if called with Nx < 0, auxconstr will only set glow,ghig and ret
    ** .................................................................... */

    /*        x       y       w     f     Nx,g,   Ng */
    auxconstr(adauxeq,adauxch,&dchi,adsgu,-1,glow,4);
    auxconstr(adauxeq,adauxch,&dchi,adsgu,-2,ghig,4);

    /* aprint(adauxch,imx-3,7,"auxspd --- Spectrum"); */
    cfit(&adauxeq[imx - 3],&adauxch[imx - 3],adtmp,7,
	 adgue,adsgu,4,&dchi,0,bck_gauss,auxconstr);

    /*
    printf("auxspd --- Solution: ");
    
    printf("%7.0f/%5.0f ",adgue[0],adsgu[0]);
    printf("%5.1f/%4.1f ",adgue[1],adsgu[1]);
    printf("%5.1f/%4.1f ",adgue[2],adsgu[2]);
    printf("%5.1f/%5.1f ",adgue[3],adsgu[3]);

    printf("\n");
    */
  }
  return;
}


/*  --------------------------------------------------------------------------
    auxconstr --- constrain for fitting to AUX channel counts
    if called with Nx = -1, the routine uses g to set the lower bounds
    if called with Nx = -2, the routine uses g to set the upper bounds
    ------------------------------------------------------------------------*/
void auxconstr(double *x, double *y, double *w, double *f, int Nx, 
		  double *g, int Ng)
{
  static double glow[4] = {0,250.0,0.0,0.0};
  static double ghig[4] = {1.0e6,1000.0,200.0,1000.0};

  int    i;
  static int    ireport = 1;

  /* -------------------------------------------------------------------------
  ** set bounds
  ** ---------------------------------------------------------------------- */

  if( Nx == -1 ) {
    for(i = 0; i < Ng; i++) glow[i] = g[i];
    ireport = 1;
    return;
  }
  if( Nx == -2 ) {
    for(i = 0; i < Ng; i++) ghig[i] = g[i];
    ireport = 1;
    return;
  }

  ireport = 0;

  if( ireport == 1 ) {
    
    aprint(glow,0,Ng,"auxconstr --- low  limits");
    aprint(ghig,0,Ng,"auxconstr --- high limits");
    aprint(g,0,Ng,"auxconstr --- Guess");
    ireport = 0;
  }

  /* -------------------------------------------------------------------------
  ** sigma >= 0
  ** ---------------------------------------------------------------------- */
  if( g[2] <= 0.0 ) {
    /* printf("auxconstr --- %.3f\n",g[2]); */
    g[2] = fabs(g[2]);
  }

  /* -------------------------------------------------------------------------
  ** check for lower/upper bound
  ** ---------------------------------------------------------------------- */
  for(i = 0; i < Ng; i++) {

    if( g[i] <= glow[i] ) g[i] = glow[i];
    if( g[i] >= ghig[i] ) g[i] = ghig[i];
  }

  /* -------------------------------------------------------------------------
  ** bck < A
  ** ---------------------------------------------------------------------- */
  if( g[3] >= 0.1 * g[0] ) g[3] = 0.05 * g[0];

  return;
}


/*  --------------------------------------------------------------------------
    xmrspd --- kinetic prop for Matrix Rate imr
    ------------------------------------------------------------------------*/
void xmrspd(SBCYC  *pcyc, double adgue[4], double adsgu[4], int imr)
{
  int    imn;
  int    imx;

  double adxmreq[NEDB];                 /* E/q */
  double adxmrch[NEDB];                 /* counts in XMR channel */
  double adtmp[7];                      /* weight for fitting */
  int    i;
  double deps;                          /* efficienccy */
  double dchi;

  double glow[4];
  double ghig[4];

  double dmas;
  double dcrg;
  double dmoq;

  /* -------------------------------------------------------------------------
  ** mass/charge depending on imr
  ** ---------------------------------------------------------------------- */

  switch (imr) {
  case 0: /* H+ */
    dmas =  1.0;
    dcrg =  1.0;
    /* printf("xmrspd --- H+\n"); */
    break;
  case 1: /* He++ */
    dmas =  4.0;
    dcrg =  2.0;
    /* printf("xmrspd --- He++\n"); */
    break;
  case 2: /* He+ */
    dmas =  4.0;
    dcrg =  1.0;
    /* printf("xmrspd --- He+\n"); */
    break;
  case 3: /* O7+ */
    dmas = 16.0;
    dcrg =  7.0;
    /* printf("xmrspd --- O7+\n"); */
    break;
  case 4: /* O6+ */
    dmas = 16.0;
    dcrg =  6.0;
    /* printf("xmrspd --- O6+\n"); */
    break;
  default:
    printf("xmrspd --- cannot deal with MR %1d\n",imr);
    aeset(adgue,0,4,-1.0);
    return;
  }

  dmoq = dmas / dcrg;

  /* -------------------------------------------------------------------------
  ** E/q
  ** ---------------------------------------------------------------------- */

  for(i = 0; i < NEDB; i++)
    adxmreq[i] = pcyc->adcnq[LCNQEOQ0] * 
      pow(pcyc->adcnq[LCNQEOQ1],pcyc->abxeqtab[59-i]);
    /*           0.4271               1.036547 */
    
  /* -------------------------------------------------------------------------
  ** counts in XMR channel
  ** ---------------------------------------------------------------------- */

  for(i = 0; i < NEDB; i++) adxmrch[i]  = 0.0;

    /* .......................................................................
    ** do not forget slip between data accumulation and transmission
    ** .................................................................... */

  for(i = 1; i < 59; i++)
    adxmrch[i-1]  = (double)pcyc->alxmr[i][imr][NSEC];


  /* -------------------------------------------------------------------------
  ** apply efficiency
  ** ---------------------------------------------------------------------- */

  /*
  for(i = 1; i < 59; i++) {
    deps       = xmreff(adxmreq[i] + pcyc->dxpav,2.475,23.25);
    if( deps < 0.01 ) deps = 0.0;
    adxmrch[i] = dratio(adxmrch[i],deps);
  }
  */

  /* -------------------------------------------------------------------------
  ** make sure we have data
  ** ---------------------------------------------------------------------- */

  deps = asum(adxmrch,1,58);
  if (deps < 10.0 ) {
    printf("xmrspd --- no data in XMR channel (sum = %10.3e)\n",deps);
    aeset(adgue,0,4,-1.0);
    return;
  }

  /* -------------------------------------------------------------------------
  ** E/q --> v
  ** ---------------------------------------------------------------------- */
  for(i = 0; i < NEDB; i++)
    adxmreq[i] = sqrt(adxmreq[i] * 2.0e3 / 1.6606e-27 * 1.6022e-19 / dmoq) /
      1.0e3;

  /* -------------------------------------------------------------------------
  ** identify max
  ** ---------------------------------------------------------------------- */

  /*
  printf("xmrspd --- Spectrum\n");
  for(i = 1; i < 59; i++) {
    printf("%2d %6.1f %6.0f\n",i,adxmreq[i],adxmrch[i]);
  }
  */

  /* aprint(adxmrch,0,NEDB,"xmrspd --- Spectrum"); */
  fmax(adxmrch,NEDB,&imx,&imn);
  /* printf("xmrspd --- max found: %3d (%10.3e)\n",imx,adxmrch[imx]); */

  /* -------------------------------------------------------------------------
  ** enough counts ?
  ** ---------------------------------------------------------------------- */

  if (adxmrch[imx] < 10.0 ) {
    printf("xmrspd --- no data in max(XMR channel):  %10.3e\n",
	   adxmrch[imx]);
    aeset(adgue,0,4,-1.0);
    return;
  }

  /* -------------------------------------------------------------------------
  ** check position of max (need 7 points)
  ** ---------------------------------------------------------------------- */

  if( (imx > 3) && (imx < 56) ) {

    for(i = 0; i < 7; i++) adtmp[i] = 1.0 / (adxmrch[imx - 3 + i] + 10);

    /* -----------------------------------------------------------------------
    ** estimate parameters
    ** -------------------------------------------------------------------- */

    adgue[0] = adxmrch[imx] * 1.0;
    adgue[1] = adxmreq[imx] * 1.0;
    adgue[2] = dmax(adgue[1] * 0.05,1.0);
    adgue[3] = 0.0;

    /* -----------------------------------------------------------------------
    ** assume estimated parameters are not too bad AND set limits
    ** -------------------------------------------------------------------- */
    glow[0]  = 0.1;             ghig[0]  = 1.0e6;
    glow[1]  = adgue[1] - 30.0; ghig[1]  = adgue[1] + 30.0;
    glow[2]  = 0.1;             ghig[2]  = 100.0;
    glow[3]  = 0.0;             ghig[3]  = 200.0;

    /* .......................................................................
    ** Note: if called with Nx < 0, xmrconstr will only set glow,ghig and ret
    ** .................................................................... */

    /*        x       y       w     f     Nx,g,   Ng */
    auxconstr(adxmreq,adxmrch,&dchi,adsgu,-1,glow,4);
    auxconstr(adxmreq,adxmrch,&dchi,adsgu,-2,ghig,4);

    /*
    aprint(glow,0,4,"xmrspd --- low  limits");
    aprint(ghig,0,4,"xmrspd --- high limits");
    aprint(adgue,0,4,"xmrspd --- Guess");
    */

    /* aprint(adxmrch,imx-3,7,"xmrspd --- Spectrum"); */
    cfit(&adxmreq[imx - 3],&adxmrch[imx - 3],adtmp,7,
	 adgue,adsgu,4,&dchi,0,bck_gauss,auxconstr);

    /*
    printf("xmrspd --- Solution: ");
    
    printf("%7.0f/%5.0f ",adgue[0],adsgu[0]);
    printf("%5.1f/%4.1f ",adgue[1],adsgu[1]);
    printf("%5.1f/%4.1f ",adgue[2],adsgu[2]);
    printf("%5.1f/%5.1f ",adgue[3],adsgu[3]);

    printf("\n");
    */
  }
  return;
}

/* ---------------------------------------------------------------------------
   xfm --- Forward Model for SWICS
   ------------------------------------------------------------------------ */
double *xfm(double eoq, double pav, double mas, double crg)
{
  /* NOTE ON POST-ACCELERATION VOLTAGES:

     The pav shifts the centers in both tof and esd dimenions.  For some,
     reason the orginal set of coef. (for level 127) were fit assuming a pav
     of 22.8kV, even though a3gxpavdpu(127) returns 21.2998.

     When trying to determine new coef. for the new PAPS level, 171,
     it was determined that pav = 25.8682 caused the centers to align
     perfectly in tof, meaning that only the esd coef. (H3/4) needed to be
     tuned (for existing ions).

     So, a linear fit was made that converts values returned by
     a3gxpavdpu for level 127 and 171 to these two values of 22.8 kV
     and 25.8682.  And, a switch was implemented which switched
     forward model coef. based on the two a3gxpavdpu-returned values.  
   */
  /* Post-accel. voltages (pav) for which forward model coef. were determined
     paps level 127, corresponding to pav = 21.2998
     paps level 171, corresponding to pav = 24.8682
  */
  const double KNOWN_PAV[2] = {21.2998,24.8682};

  static double adfm[4];

  static double A1  =  5.81090;
  static double A2  = -1.50052;
  static double A3  = -3.01352;
  static double A4  =  0.471113;
  static double A5  =  0.0804588;
  static double A6  =  0.0731559;
  static double T2C =  5.115;
  static double E2C =  0.417498936;

  static double H1[57];
  static double H2[57];
  static double H3[57];
  static double H4[57];
  static double H5[57];
  static double H6[57];
  static double UL[57];

  static int ifirsttime = 1;

  double x;
  double y;
  double TOF;
  double TOFDPU;
  double sTOF;
  double ESD;
  double sESD;
  double alf;
  double bet;
  double gam;
  double etoq;
  double moq;

  int    im;

  moq = mas / crg;

  if( ifirsttime == 1 ) {

    if (pav >= .99*KNOWN_PAV[0] && pav <= 1.01*KNOWN_PAV[0]){ // level 127

      printf("xfm -I- using pav = %6.2f coef.\n",KNOWN_PAV[0]);

      // must be inside if so bad first cycle pav does not break all
      ifirsttime = 0; 

      aeset(H1,0,57,-1.0);
      aeset(H2,0,57,-1.0);
      aeset(H3,0,57,-1.0);
      aeset(H4,0,57,-1.0);
      aeset(H5,0,57,-1.0);
      aeset(H6,0,57,-1.0);
      aeset(UL,0,57,-1.0);

      H1[ 1] = 1466554.25;
      H1[ 3] = 1452412.0;
      H1[ 4] = 1423990.2;
      H1[12] = 1410767.2;
      H1[14] = 1395060.1;
      H1[16] = 1379527.9;
      H1[20] = 1401869.9;
      H1[24] = 1392056.0;
      H1[28] = 1383950.2;
      H1[32] = 1382425.5;
      H1[56] = 1358009.1;

      UL[ 1] = 1.34; // copied from 4He, H1 compensates
      UL[ 3] = 1.34; // copied from 4He, H1 compensates
      UL[ 4] = 1.34;
      UL[12] = 1.47;
      UL[14] = 1.66;
      UL[16] = 1.88;
      UL[20] = 1.08;
      UL[24] = 1.60;  // copied from 28, H1 compensates
      UL[28] = 1.60;
      UL[32] = 1.60;  // copied from 28, H1 compensates
      UL[56] = 1.53;

      H2[ 1] = 0.0124;
      H2[ 3] = 0.0124;
      H2[ 4] = 0.0124;
      H2[12] = 0.0124;
      H2[14] = 0.0124;
      H2[16] = 0.0124;
      H2[20] = 0.0124;
      H2[24] = 0.0124;
      H2[28] = 0.0124;
      H2[32] = 0.0124;
      H2[56] = 0.0124;

      H3[ 1] = 28.05;
      H3[ 3] = -34.77;
      H3[ 4] =   3.381;
      H3[12] =   3.940;
      H3[14] =   0.0;
      H3[16] =   6.243;
      H3[20] =   0.0;
      H3[24] =  -2.17;
      H3[28] =  12.068;
      H3[32] =  21.23;
      H3[56] =   1.090;

      H4[ 1] = -1.64;
      H4[ 3] = 3.07;
      H4[ 4] = 0.850;
      H4[12] = 0.934;
      H4[14] = 1.0  ;
      H4[16] = 0.852;
      H4[20] = 1.0;
      H4[24] = 1.0;
      H4[28] = 0.739;
      H4[32] = 0.58;
      H4[56] = 0.920;

      H5[ 1] = 0.78;
      H5[ 3] = 0.78;
      H5[ 4] = 0.78;
      H5[12] = 0.78;
      H5[14] = 0.78;
      H5[16] = 0.78;
      H5[20] = 0.78;
      H5[24] = 0.78;
      H5[28] = 0.78;
      H5[32] = 0.78;
      H5[56] = 0.41;

      H6[ 1] = -0.79;
      H6[ 3] = -0.79;
      H6[ 4] = -0.79;
      H6[12] = -0.79;
      H6[14] = -0.79;
      H6[16] = -0.79;
      H6[20] = -0.79;
      H6[24] = -0.79;
      H6[28] = -0.79;
      H6[32] = -0.79;
      H6[56] = -0.63;
    }
    else if (pav >= .99*KNOWN_PAV[1] && pav <= 1.01*KNOWN_PAV[1]){ // level 171
      printf("xfm -I- using pav = %6.2f coef.\n",KNOWN_PAV[1]);

      // must be inside if so bad first cycle pav does not break all
      ifirsttime = 0; 

      aeset(H1,0,57,-1.0);
      aeset(H2,0,57,-1.0);
      aeset(H3,0,57,-1.0);
      aeset(H4,0,57,-1.0);
      aeset(H5,0,57,-1.0);
      aeset(H6,0,57,-1.0);
      aeset(UL,0,57,-1.0);

      // TOF correction
      // axfmtweak note: set to 1000000.0 to find coef.
      H1[ 1] = 1469383.9;
      H1[ 3] = 1423990.2;  // copied from 4He
      H1[ 4] = 1423990.2;
      H1[12] = 1410767.2;
      H1[14] = 1395060.1;
      H1[16] = 1379527.9;
      H1[20] = 1401869.9;
      H1[24] = 1401869.9;
      H1[28] = 1383950.2;
      H1[32] = 1383950.2;
      H1[56] = 1358009.1;

      // Energy lost in carbon foil (kV)
      UL[ 1] = 0.49;
      UL[ 3] = 1.34;  // copied from 4He
      UL[ 4] = 1.34;
      UL[12] = 1.47;
      UL[14] = 1.66;
      UL[16] = 1.88;
      UL[20] = 1.08;
      UL[24] = 1.08;
      UL[28] = 1.60;
      UL[32] = 1.60;
      UL[56] = 1.53;

      // TOF sigma
      H2[ 1] = 0.0124;  // copied from 4He
      H2[ 3] = 0.0124;  // copied from 4He
      H2[ 4] = 0.0124;
      H2[12] = 0.0124;
      H2[14] = 0.0124;
      H2[16] = 0.0124;
      H2[20] = 0.0124;
      H2[24] = 0.0124;
      H2[28] = 0.0124;
      H2[32] = 0.0124;
      H2[56] = 0.0124;

      // ESD correction offset, H3
      H3[ 1] =   -0.34;
      H3[ 3] =   3.381; // copied from 4He
      H3[ 4] = 0.67;
      H3[12] =  5.05;
      H3[14] =  1.01;
      H3[16] =   -0.17;
      H3[20] =   8.81;
      H3[24] =   25.12;
      H3[28] =  7.93;
      H3[32] =  -3.38;
      H3[56] =   6.15;

      // ESD correction slope, H4
      H4[ 1] = 1.22;
      H4[ 3] = 0.850;  // copied from 4He
      H4[ 4] = 0.84;
      H4[12] = 0.81; 
      H4[14] = 0.92;
      H4[16] = 0.89;  
      H4[20] = 0.81;
      H4[24] = 0.59;
      H4[28] = 0.79;
      H4[32] = 1.01; 
      H4[56] = 0.73;

      // ESD sigma multiplier
      H5[ 1] = 0.78;
      H5[ 3] = 0.78;
      H5[ 4] = 0.78;
      H5[12] = 0.78;
      H5[14] = 0.78;
      H5[16] = 0.78;
      H5[20] = 0.78;
      H5[24] = 0.78;
      H5[28] = 0.78;
      H5[32] = 0.78;
      H5[56] = 0.41;

      // ESD sigma exponent
      H6[ 1] = -0.79;
      H6[ 3] = -0.79; // copied from 4He
      H6[ 4] = -0.79;
      H6[12] = -0.79;
      H6[14] = -0.79;
      H6[16] = -0.79;
      H6[20] = -0.79;
      H6[24] = -0.79;
      H6[28] = -0.79;
      H6[32] = -0.79;
      H6[56] = -0.63;
    }
    else {
      printf("xfm -F- post-accel. voltage (%6.2f) not one of known values (%6.2f or %6.2f)\n",
	     pav, KNOWN_PAV[0], KNOWN_PAV[1]);
      return(adfm);
    }
  }

  if( (mas <= 0.0) || (mas > 56.0) ) {
    printf("xfm -F- cannot deal with mass = %.0f.\n",mas);
    return(adfm);
  }

  im = (int)mas;
  if( H1[im] <= 0.0 ) {
    printf("xfm -F- mass %.0f not in model.\n",mas);
    return(adfm);
  }

  /* -------------------------------------------------------------------------
  ** TOF position
  ** ---------------------------------------------------------------------- */

  // adjust pav to value used to determined forward model coef.
  // (see note at beginning of routine)
  // 21.2998 -> 22.8 
  // 24.8682 -> 25.8682
  pav = (0.8598)*pav + 4.4864;

  etoq = eoq + pav;

  x    = etoq - UL[im];
  if( x <= 0.0 ) {
    printf("xfm -F- problems with (E/q + PAPS - UL) = %.2f\n",x);
    return(adfm);
  }
  y    = H1[im] / x;
  TOF  = sqrt(y * moq);

  /* -------------------------------------------------------------------------
  ** TOF sigma
  ** ---------------------------------------------------------------------- */

  sTOF = H2[im] * TOF;

  /* -------------------------------------------------------------------------
  ** ESSD position
  ** ---------------------------------------------------------------------- */

  TOFDPU = adputof(eoq,pav,moq);

  if( TOFDPU <= 1.0 ) {
    printf("xfm -F- running into troubles with TOF = %.1f\n",TOF);
    return(adfm);
  }
  y      = TOFDPU / T2C;
  y      = log(y);

  alf    = A5;
  bet    = A2 + A4 * y;
  gam    = A1 + y * (A3 + A6 * y * y) - log(mas);

  y      = (-bet + sqrt(bet * bet - 4.0 * alf * gam)) / 2.0 / alf;
  ESD    = exp(y) * E2C;
  ESD    = H3[im] + H4[im] * ESD;

  /* -------------------------------------------------------------------------
  ** ESSD sigma
  ** ---------------------------------------------------------------------- */

  sESD = H5[im] * pow((crg * etoq / mas),H6[im]) * ESD;

  /* -------------------------------------------------------------------------
  ** done
  ** ---------------------------------------------------------------------- */

  adfm[0] = TOF;
  adfm[1] = sTOF;
  adfm[2] = ESD;
  adfm[3] = sESD;

  return(adfm);
}
