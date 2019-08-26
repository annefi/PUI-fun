/* --------------------------------------------------------------- <Prolog> --
   Name:      swxtools.h
   Title:     Header file: Tools for ACE/SWICS data analysis
   $Id: swxtools.h,v 1.1.1.1 2000/06/02 13:37:21 jraines Exp $
   ------------------------------------------------------------- </Prolog> -*/

#include "datatypes.h"
#include "decoded.h"

#ifndef SWXTOOLSH
#define SWXTOOLSH

/* ===========================================================================
** ACE/SWICS peak positions and sigmas
** ======================================================================== */
long   lax_tofcent_ch   (double detot_keV, long lm_amu);
double dax_tofsig1_ch   (long ltof_ch, long lm_amu);
double dax_tofsig2_ch   (long ltof_ch, long lm_amu);
long   lax_esdcent_ch   (double detot_keV, long lm_amu);
double dax_esdsig_ch    (long lesd_ch, long lm_amu);

void   vax_peakpos      (double detot_keV, long lm_amu, long lt0, double dst,
			 long le0, double dse);
void   vpax_peakpos     (double *pdetot_keV, long *plm_amu, 
			 long *plt0, double *pdst,long *ple0, double *pdse);
void   vax_peakpos_if   (double *detot_keV, long *lm_amu, 
			 long *lt0, double *dst,long *le0, double *dse);
void   vax_peakpos_arg  (int argc, void *argv[]);


/* ===========================================================================
** Ellipse handling
** ======================================================================== */
BYTE   bax_ellipse_isin (double dx, double dy, EST *pest);

/* ===========================================================================
** data reduction
** ======================================================================== */
double dduty            (double daspect, double dmach);
double dgeometryfactor  (double daspect);
double deff             (double detot);
void   vdiffflux        (double adcts[60], double adeoq[60], double daspect,
			 double dmach, double dpav, double dcrg,
			 double addj[60]);
double dflux            (double addj[60],double adeoq[60]);
double dspeed           (double adcts[60],double adeoq[60],
			 double dmas, double dcrg,
			 double *pdvth);

double dax_aprxspeed    (double adc[NEDB],SBCYC *pc, double dm, double dq,
			 double dmin, double *pdtherm, double *pdsum);
void   mrxxspd          (SBCYC *pcyc, double *dspd, double *dvth,
			 double *deoq,double dmas, double dcrg, int ixx);
double mrxxtot          (SBCYC *pcyc, int ixx);
double mrxxdra          (SBCYC *pcyc, int ixx, int iyy);

int xphafilt(double vH, double vth, double eoq, double pav, 
	     int itof, int iesd);
/* ===========================================================================
** Efficiency
** ======================================================================== */
double auxeff           (double de0, double ddelta, double dthre);
double xeffv1(double de, double dmas);
double xeffv1_helper(double da, double db, double de0, double de);

/* ===========================================================================
** SWICS/ACE kinetic properties from Matrix Rates
** ======================================================================== */

void auxspd(SBCYC  *pcyc, double adgue[4], double adsgu[4]);
void auxconstr(double *x, double *y, double *w, double *f, int Nx, 
	       double *g, int Ng);
void xmrspd(SBCYC  *pcyc, double adgue[4], double adsgu[4], int imr);

/* ===========================================================================
** SWICS/ACE Foward Model
** ======================================================================== */
double *xfm(double eoq, double pav, double mas, double crg);

#endif
