/* ---------------------------------------------------------------------------
   a3dif.h --- interface to ACE/S3 data
   (c) 1998/1999 Simon Hefti (hefti@umich.edu)
   $Id: a3dif.h,v 1.5 2004/05/20 14:58:18 jraines Exp $
   -------------------------------------------------------------------------*/

#include "libhef.h"

#ifndef A3DIFH
#define A3DIFH

/* ---------------------------------------------------------------------------
** flags for a3xelletm
** ------------------------------------------------------------------------ */
#define A3XELLETM_FLT 1                 /* filter out accidental coincid. */
#define A3XELLETM_WGT 2                 /* apply basic-rate weighting */

/* ---------------------------------------------------------------------------
** flags for a3mmq
** ------------------------------------------------------------------------ */
#define A3MMQ_FLT 1                     /* filter out accidental coincid. */
#define A3MMQ_WGT 2                     /* apply basic-rate weighting */

/* ---------------------------------------------------------------------------
** flags for a3eth
** ------------------------------------------------------------------------ */
#define A3ETH_FLT 1                     /* filter out accidental coincid. */
#define A3ETH_WGT 2                     /* apply basic-rate weighting */

/* ---------------------------------------------------------------------------
** flags for a3qth
** ------------------------------------------------------------------------ */
#define A3QTH_FLT 1                     /* filter out accidental coincid. */
#define A3QTH_WGT 2                     /* apply basic-rate weighting */

#define A3XRELL_FLT   1                 /* filter out accidental coincid. */
#define A3XRELL_WGT   2                 /* apply basic-rate weighting */
#define A3XRELL_UPPER 4                 /* use upper half of ellipse only */

/* ---------------------------------------------------------------------------
** SWIMS 
** ------------------------------------------------------------------------ */
#define A3MTOFCH_MAX  4096              /* number of tof channels maximum */

/* number of ns per tof channel.  The value 500.0 is tof range, which
    should be read from TM instead of hardcoded here. */
#define A3MTOF_NSPERCH  500.0/A3MTOFCH_MAX 

  /* =========================================================================
  ** file handling/reading
  ** ====================================================================== */

int    a3opencyclefile  (char *zfn);
int    a3closecyclefile (void);

int    a3readcycle      (void);

int    a3rcyc           (BYTE abedb[NEDB][NBINEDB], 
			 double adtime[NEDB], BYTE abQAC[NEDB]);

char   *a3hdffn(void);
char   *a3ncfver(void);

  /* =========================================================================
  ** expanding (or: decoding)
  ** ====================================================================== */

SBCYC  *a3expandcycle   (void);
int    a3expand         (void);

  /* =========================================================================
  ** Cycle Checking
  ** ====================================================================== */

int    a3ccycg          (void);
int    a3ccycg_recnrinc (void);
int    a3ccycg_timeinc  (void);
int    a3ccycx          (void);
int    a3ccycx_mcplev   (int lev);
int    a3ccycx_pavlev   (int lev);
int    a3ccycx_eqhk     (void);
int    a3ccycx_eqtabnom (int itab);
int    a3ccycx_rates    (void);

int    a3cycx_nominal(int itab);
int    a3xpavlev(void);

int    a3ccycm          (void);
int    a3ccycm_mcalev   (int lev);
int    a3ccycm_mcolev   (int lev);
int    a3ccycm_hyplev   (int lev);
int    a3ccycm_eqhk     (void);
int    a3ccycm_eqtabnom (int itab);

int    a3cycm_nominal(int alev, int olev, int hlev, int itab);


  /* =========================================================================
  ** accessing data
  ** ====================================================================== */

double a3gtime          (void);
char  *a3zrecid(void);

int    a3gxbrtab        (BYTE *abtab);
int    a3pxbrtab        (FILE *fp);

/* int    a3gxeqtab        (BYTE *abtab); */
double *a3gxeqtab(void);
int    a3gxeqtab_i(int ie);

int    a3pxeqtab        (FILE *fp);
float  *a3gxeqdpu       (void);
double a3gxeqdpu_i(int ie);
double a3gxeqaux_i(int ie);

float  *a3gmeqtab       (void);
int    a3gmeqtab_i      (int ie);
float  *a3gmeqdpu       (void);
double a3gmeqdpu_i(int ie);

double a3gxpavdpu(void);

int    a3pxmrtab        (SBCYC *pcyc, FILE *fp);

BYTE   a3gdpuhk(int,int);

BYTE   a3gshk(int,int);

double *a3gcnq          (void);
int    a3xadc(void);
int    a3xtrigcal(void);
int    a3xtrigmode(void);

double *a3gcnm          (void);
int    a3gbrtab(int ibox, int icorn);
int    a3gmrtab(int ibox, int icorn);

float a3gxhk(int ie, int i);

int    a3gxsr           (int isr, double *adfsr);

double *a3gxfsr         (void);
double a3gxfsr_i(int ie, int isec);
double *a3gxdcr         (void);
double a3gxdcr_i(int ie, int isec);
double *a3gxtcr         (void);
double a3gxtcr_i(int ie, int isec);
double *a3gxsdr         (void);
double a3gxsdr_i(int ie, int isec);
double *a3gxar          (void);
double a3gxar_i(int ie, int isec);
double *a3gxpr          (void);
double a3gxpr_i(int ie, int isec);

int    a3gxmr_old       (int isr, double *adfsr);
double *a3gxmrh_1       (void);
double *a3gxmrhe2       (void);
long   a3gxmr_i(int ie, int irate, int isec);
double *a3gxmrhe1       (void);
double *a3gxmro_7       (void);
double *a3gxmro_6       (void);
double *a3gxmrfes       (void);
double *a3gxmrsis       (void);
double *a3gxmrerr       (void);
double a3gxmr           (int imr, int ie, int isec);

int    a3mhyplev(void);

float a3gmhk(int ie, int i);

  /* =========================================================================
  ** SWICS PHA
  ** ====================================================================== */

int    a3xnpha          (int ie);
float  *a3gxmoq         (int ie);
double a3gxmoq_i(int ie, int i);
float  *a3gxmas         (int ie);
double a3gxmas_i(int ie, int i);
int    a3gxtof_i(int ie, int i);
int    a3gxesd_i(int ie, int i);
int    a3gxdid_i(int ie, int i);
int    a3gxsec_i(int ie, int i);
int    a3gxrng_i(int ie, int i);

double a3cxmoq(double dmoq_ch);
double a3cxmas(double dmas_ch);

double a3xbrwgt         (int ie, int ibr);

long   a3gxbr(int ie, int ibr, int isec);
int    a3gxnr(int ie, int ibr, int isec);

int    a3xellmmq        (int ie, double moq0, double smq1, double smq2, 
			         double mas0, double sma1, double sma2);

double a3xelletm(int ie, int ir, double vH, long lflag,
	      double t0, double st1, double st2, 
	      double e0, double se1, double se2);

double a3xrell(int ie, int ir, double vH, long lflag,
	       double moq0, double bmoq,
	       double mas0, double bmas);

int a3mmq(double *adhst, double *adx, double *ady, long lflag, double vH,
  int Nx, double dxl, double dxh,
  int Ny, double dyl, double dyh);

int a3eth(double *adhst, long lflag, int ie, double vH, 
	  int offx, int Nx, int offy, int Ny);

int a3qth(double *adhst, long lflag, double vH, 
	  int offx, int Nx, int offy, int Ny);

/* =========================================================================
** SWIMS Rates
** ====================================================================== */
double a3gmfsr_i(int ie, int isec);
double a3gmfsra_i(int ie, int isec);
double a3gmfsrb_i(int ie, int isec);
double a3gmfsrab_i(int ie, int isec);
double a3gmrsr_i(int ie, int isec);
double a3gmdcr_i(int ie, int isec);
double a3gmmfsr_i(int ie, int isec);
double a3gmmdcr_i(int ie, int isec);

/* =========================================================================
** SWIMS PHA
** ====================================================================== */
int a3mnpha(int ie);
int a3gmdid(int ie, int i);
int a3gmsec(int ie, int i);
int a3gmstamp(int ie, int i);
int a3gmstopk1(int ie, int i);
int a3gmstopk2(int ie, int i);
int a3gmtof(int ie, int i);
double a3cmtof(int dtof_ch);
/* =========================================================================
** Accumulate SWIMS PHA
** ====================================================================== */

int    a3mcntpha        (int ie, int tid, int tlow, int thig);
double *a3mtofhist      (int iel, int ieh, int itl, int ith, int tid);

double *a3xmrspd(int imr);
double *a3auxspd(void);

double a3xeoqsumv1(double v0, double vth, double mas, double crg,
		   int ifrst, int ilast);

long a3mtof2_i(int i);
long a3mtof1_i(int i);


#endif

