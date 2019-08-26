/* ---------------------------------------------------------------------------
   a3dif --- interface to ACE/S3 data
   (c) 1998/1999 Simon Hefti (hefti@umich.edu)
   $Id: a3dif.c,v 1.8 2004/05/20 14:58:18 jraines Exp $
   -------------------------------------------------------------------------*/

#include <stdio.h>
#include <netcdf.h>
#include <math.h>
#include "libhef.h"

#define A3DIFBUF 40

static int    edbid;  /* netCDF id */
static int    vid;
static size_t vlen;
static int    ic;
static int    ic_max;

static BYTE   abbedb[A3DIFBUF][NEDB][NBINEDB];
static double adbtime[A3DIFBUF][NEDB];
static BYTE   abbQAC[A3DIFBUF][NEDB];

static int    a3difcur;  /* current cyc from Buffer */
static int    a3difread; /* number of cycs read */
static int    a3difallread;
static int    a3diffilecnt = 0; /* count calls to opencyclefile */
                                /* used for a3rcyc, if more than one 
				** .nc file is used in sequence */

static SBCYC  cyc;

/* ===========================================================================
** file handling/reading
** ======================================================================== */

/* ---------------------------------------------------------------------------
   a3opencyclefile --- open file with given name for reading
   -------------------------------------------------------------------------*/
int a3opencyclefile(char *zfn)
{
  int itmp;
  
  // ===> JMR
  printf("a3opencyclefile --- Opening file %s\n",zfn);

  itmp = nc_open(zfn, NC_NOWRITE, &edbid);
  if (itmp != NC_NOERR) {
    hperr(stderr,PNOVICE,"a3opencyclefile --- %s.\n",nc_strerror(itmp));
    return(1); 
  }

  a3diffilecnt++;

  a3difallread = 0;
  a3difcur     = 0;
  a3difread    = 0;

  return(0);
}

/* ---------------------------------------------------------------------------
   a3closecyclefile --- close file
   -------------------------------------------------------------------------*/
int a3closecyclefile(void)
{
  int itmp;
  
  itmp = nc_close(edbid);       /* close netCDF dataset */
  if (itmp != NC_NOERR) {
    hperr(stderr,PNOVICE,"a3closecyclefile --- %s.\n",nc_strerror(itmp));
    return(1);
  }
  a3difallread = 0;
  return(0);
}
  

/* ---------------------------------------------------------------------------
   a3readcycle --- read one record of data (60 EDBs) (includes buffering)
   -------------------------------------------------------------------------*/
int a3readcycle(void)
{
  int    i;
  int    ircres;

  /* -------------------------------------------------------------------------
  ** fill buffer
  ** -----------------------------------------------------------------------*/

  if( (a3difcur == 0) && (a3difallread == 0) ) {

    hperr(stderr,PNOVICE,"a3readcycle --- filling buffer.\n");

    for(i = 0; i < A3DIFBUF; i++) {

      ircres = 0;

      ircres = a3rcyc(&(abbedb[i][0][0]),
		     &adbtime[i][0],
		     &abbQAC[i][0]);

      if( ircres != 0 ) break;
    }
    a3difread = i;
    a3difcur  = a3difread;
    /*
      hperr(stderr,PNOVICE,"DBG - a3readcycle --- after filling buffer: %d\n",
	   a3difcur);
    */
  }

  a3difcur--;

  if( a3difcur >= 0 ) return(0);
  else                return(1);

  return(0);
}

/* ---------------------------------------------------------------------------
   a3rcyc --- read one record of data (60 EDBs) (low-level)
   -------------------------------------------------------------------------*/
int a3rcyc(BYTE abedb[NEDB][NBINEDB], double adtime[NEDB], BYTE abQAC[NEDB])
{
  static int ifirsttime = 1;
  static int inewfilecnt = -1;

  int    itmp;
  int    i;

  size_t aidx3[3];
  size_t aidx2[2];
  size_t acnt3[3];
  size_t acnt2[2];

  /* -------------------------------------------------------------------------
  ** the first time: set ic = 0, read number of cycles.
  ** -----------------------------------------------------------------------*/

  if( a3diffilecnt > inewfilecnt ) {

    ifirsttime = 1;
    inewfilecnt = a3diffilecnt;

    hperr(stderr,PNOVICE,
	  "a3rcyc --- New file detected. Resetting a3rcyc parameters.\n");

  }

  if( ifirsttime == 1 ) {

    /* find umlimited dimension (right now netCDF allows only one) */
    itmp = nc_inq_unlimdim(edbid,&vid);
    if (itmp != NC_NOERR) {
      hperr(stderr,PEXPERT,
	    "a3rcyc --- %s.\n",nc_strerror(itmp));
      return(1);
    }

    itmp = nc_inq_dimlen(edbid,vid,&vlen);
    if (itmp != NC_NOERR) {
      hperr(stderr,PEXPERT,
	    "a3rcyc --- %s.\n",nc_strerror(itmp));
      return(1);
    }

    ic_max = vlen;

    ifirsttime = 0;
    ic = 0;
  }

  /* -------------------------------------------------------------------------
  ** read next cycle (as long as there are some)
  ** -----------------------------------------------------------------------*/

  if( ic < ic_max ) {

    /* --- get EDBs --- */

    itmp = nc_inq_varid (edbid, "cyc", &vid);
    if (itmp != NC_NOERR) {
      hperr(stderr,PNOVICE,"a3rcyc --- %s.\n",nc_strerror(itmp));
      return(1);
    }

    aidx3[0] = ic; acnt3[0] =       1; /* cyc */
    aidx3[1] =  0; acnt3[1] =    NEDB; /* EDB */
    aidx3[2] =  0; acnt3[2] = NBINEDB; /* EDBbytes */

    itmp = nc_get_vara_uchar(edbid, vid, aidx3, acnt3,&abedb[0][0]);
    if (itmp != NC_NOERR) {
      hperr(stderr,PNOVICE,"a3rcyc --- %s.\n",nc_strerror(itmp));
      return(1);
    }


    /* get time */

    itmp = nc_inq_varid (edbid, "time", &vid);
    if (itmp != NC_NOERR) {
      hperr(stderr,PNOVICE,"a3rcyc --- %s.\n",nc_strerror(itmp));
      return(1);
    }

    aidx2[0] = ic; acnt2[0] =       1; /* cyc */
    aidx2[1] =  0; acnt2[1] =    NEDB; /* EDB */

    itmp = nc_get_vara_double(edbid,vid,aidx2,acnt2,adtime);
    if (itmp != NC_NOERR) {
      hperr(stderr,PNOVICE,"a3rcyc --- %s.\n",nc_strerror(itmp));
      return(1);
    }

    /* get QAC */

    itmp = nc_inq_varid (edbid, "QAC", &vid);
    if (itmp != NC_NOERR) {
      hperr(stderr,PNOVICE,"a3rcyc --- %s.\n",nc_strerror(itmp));
      return(1);
    }

    aidx2[0] = ic; acnt2[0] =       1; /* cyc */
    aidx2[1] =  0; acnt2[1] =    NEDB; /* EDB */

    itmp = nc_get_vara_uchar(edbid,vid, aidx2, acnt2,&abQAC[0]);
    if (itmp != NC_NOERR) {
      hperr(stderr,PNOVICE,"a3rcyc --- %s.\n",nc_strerror(itmp));
      return(1);
    }

    /* -----------------------------------------------------------------------
    ** Watch out for fill values
    ** ---------------------------------------------------------------------*/

    for(i = 0; i < NEDB; i++) {
      if(adtime[i] == NC_FILL_DOUBLE) adtime[i] = -1.0;
    }

    ic++;

  } else /* ic >= ic_max */ {

    hperr(stderr,PNOVICE,"a3rcyc --- no more cycles found in file.\n");
    a3difallread = 1;
    return(1);
  }
  return(0);
}

/* ---------------------------------------------------------------------------
   a3ncfver --- report version of my netCDF file format
   -------------------------------------------------------------------------*/
char *a3ncfver(void)
{
  static char znam[256];

  int    itmp;

  static size_t start_txt[1];
  static size_t count_txt[1];

  sprintf(znam,"format version for my netCDF files not available");

  itmp = nc_inq_varid (edbid, "version", &vid);
  if (itmp != NC_NOERR) {
    return(znam);
  }

  start_txt[0] =   0;
  count_txt[0] = 256;

  itmp = nc_get_vara_text(edbid,vid,start_txt,count_txt,znam);
  if (itmp != NC_NOERR) {
    sprintf(znam,"format version for my netCDF files not available");
  }

  return(znam);
}

/* ---------------------------------------------------------------------------
   a3hdffn --- report name of original HDF file (if available)
   -------------------------------------------------------------------------*/
char *a3hdffn(void)
{
  static char znam[256];

  int    itmp;

  static size_t start_txt[1];
  static size_t count_txt[1];

  sprintf(znam,"HDF filename not available");

  itmp = nc_inq_varid (edbid, "HDFname", &vid);
  if (itmp != NC_NOERR) {
    hperr(stderr,PNOVICE,"DBG a3hdffn --- variable HDFname not found.\n");
    hperr(stderr,PNOVICE,"+ netCDF error: %s\n",nc_strerror(itmp));
    return(znam);
  }

  start_txt[0] =   0;
  count_txt[0] = 256;

  itmp = nc_get_vara_text(edbid,vid,start_txt,count_txt,znam);
  if (itmp != NC_NOERR) {
    hperr(stderr,PNOVICE,"DBG a3hdffn --- cannot read variable HDFname.\n");
    hperr(stderr,PNOVICE,"+ netCDF error: %s\n",nc_strerror(itmp));
    sprintf(znam,"HDF filename not available");
  }

  return(znam);
}


/* ===========================================================================
** expanding (or: decoding)
** ======================================================================== */

/* ---------------------------------------------------------------------------
   a3expandcycle --- expand previously read data
   -------------------------------------------------------------------------*/
SBCYC *a3expandcycle(void)
{
  int    ipos;
  long   ltmp;

  /* printf("DBG - a3expandcycle --- a3difcur: %d\n",a3difcur); */

  if( a3difcur >= 0 ) {
    
    ipos       = a3difread - 1 - a3difcur;

    ltmp       =  0;
    ltmp       = (abbedb[ipos][0][34+11] << 16) |
      (abbedb[ipos][0][34+12] <<  8) | 
      (abbedb[ipos][0][34+13]);

    /*
    hperr(stderr,PNOVICE,"a3readcycle --- %2d %2d %5ld\n",
	   a3difcur,
	   abbedb[ipos][0][5],
	   ltmp);
    */

    expand(&abbedb[ipos][0][0],
	   &adbtime[ipos][0],
	   &abbQAC[ipos][0],&cyc);


    return(&cyc);

  } else {
    hperr(stderr,PNOVICE,"a3expandcycle --- no more cycles available.\n");
    return((SBCYC *)NULL);
  }
}

/* ---------------------------------------------------------------------------
   a3expand --- expand internally (without giving back the pointer)
   -------------------------------------------------------------------------*/
int a3expand(void)
{
  static SBCYC *pcyc;

  pcyc = a3expandcycle();

  return(0);
}

/* ===========================================================================
** Cycle Checking
** ======================================================================== */

/* general quality check */
int a3ccycg(void)
{
  return(ccycg(&cyc));
}

/* increasing record number */
int a3ccycg_recnrinc(void)
{
  return(ccycg_recnrinc(&cyc));
}

/* increasing time */
int a3ccycg_timeinc(void)
{
  return(ccycg_timeinc(&cyc));
}

/* Check for decompression problems */
int a3ccycg_decomp_problem(void)
{
  if( cyc.sdecomp_problem )
    hperr(stderr,PNOVICE,"a3ccycg_decomp_problem --- decoding problems seen.\n");
  return(cyc.sdecomp_problem);
}

/* all data needed for SWICS are available */
int a3ccycx(void)
{
  return(ccycx(&cyc));
}

/* MCP is at level lev */
int a3ccycx_mcplev(int lev)
{
  return(ccycx_mcplev(&cyc,lev));
}

/* a3xpavlev --- PAPS Level for SWICS */
int a3xpavlev(void)
{
  return(cyc.abxcmd[LXPAPS]);
}

/* PAPS is at level lev */
int a3ccycx_pavlev(int lev)
{
  return(ccycx_pavlev(&cyc,lev));
}

/* E/q stepping (from HK) is ok.
** Routine checks for monotonically decreasing HK values. */
int a3ccycx_eqhk(void)
{
  return(ccycx_eqhk(&cyc));
}

/* E/q stepping (from table) is nominal.
** E/q stepping table from EDBs is compared with known tables. */
int a3ccycx_eqtabnom(int itab)
{
  return(ccycx_eqtabnom(&cyc,itab));
}

/* SWICS rates consistent
** all rates >= 0.0 and DCR >= TCR */
int a3ccycx_rates(void)
{
  return(ccycx_rates(&cyc));
}

/* ensure settings of SWICS/ACE */
int a3cycx_nominal(int itab)
{
  int ires;

  ires = a3ccycg();
  if( ires == 0 ) ires += a3ccycg_recnrinc();
  if( ires == 0 ) ires += a3ccycg_timeinc();
  if( ires == 0 ) ires += a3ccycg_decomp_problem();
  if( ires == 0 ) ires += a3ccycx();
  if( ires == 0 ) ires += a3ccycx_mcplev(2);
  /* After PAPS ramp up (May/June 2000) two levels are considered nominal.
     Jim Raines, 19Sep2002. */
  if( ires == 0 ) {
    if (a3ccycx_pavlev(127) && a3ccycx_pavlev(171)){ // true if neither level
      ires += 1;
    }
  }
  if( ires == 0 ) ires += a3ccycx_eqhk();
  if( ires == 0 ) ires += a3ccycx_eqtabnom(itab);
  if( ires == 0 ) ires += a3ccycx_rates();

  return(ires);
}

/* all data needed for SWIMS are available */
int a3ccycm(void)
{
  return(ccycm(&cyc));
}

/* SWIMS Start MCP is at level lev */
int a3ccycm_mcalev(int lev)
{
  return(ccycm_mcalev(&cyc,lev));
}

/* SWIMS Stop MCP is at level lev */
int a3ccycm_mcolev(int lev)
{
  return(ccycm_mcolev(&cyc,lev));
}

/* SWIMS Hyperbola is at level lev */
int a3ccycm_hyplev(int lev)
{
  return(ccycm_hyplev(&cyc,lev));
}

/* a3mhyplev --- Hyperbola Level for SWIMS (from CMD block) */
int a3mhyplev(void)
{
  return(cyc.asmcmd[LMAHYP]);
}

/* ---------------------------------------------------------------------------
   SWIMS Housekeeping block
   -------------------------------------------------------------------------*/
float a3gmhk(int ie, int i)
{
  if ( ie >= NEDB || i < 0 || i >= NMHK){
    return(-1);
  }
  return(cyc.afmhk[ie][i]);
}
  

/* SWIMS E/q stepping (from HK) is ok */
int a3ccycm_eqhk(void)
{
  return(ccycm_eqhk(&cyc));
}

/* SWIMS E/q stepping (from table) is nominal */
int a3ccycm_eqtabnom(int itab)
{
  return(ccycm_eqtabnom(&cyc,itab));
}

/* ------------------------------------------------------------------------ */
/* ensure settings of SWIMS/ACE */
/* ------------------------------------------------------------------------ */
int a3cycm_nominal(int alev, int olev, int hlev, int itab)
{
  int ires;

  /* alev --- Start MCP Level
  ** olev --- Stop
  ** hlev --- Hyperbola Level
  ** itab --- not yet used: E/q Table Selection
   */

  ires = a3ccycg();
  if( ires == 0 ) ires += a3ccycg_recnrinc();
  if( ires == 0 ) ires += a3ccycg_timeinc();
  if( ires == 0 ) ires += a3ccycm();
  if( ires == 0 ) ires += a3ccycm_mcalev(alev);
  if( ires == 0 ) ires += a3ccycm_mcolev(olev);
  if( ires == 0 ) ires += a3ccycm_hyplev(hlev);
  if( ires == 0 ) ires += a3ccycm_eqhk();
  if( ires == 0 ) ires += a3ccycm_eqtabnom(itab);

  return(ires);
}

/* ===========================================================================
** accessing data
** ======================================================================== */

/* ---------------------------------------------------------------------------
   a3gtime --- get time of beginning of cycle
   -------------------------------------------------------------------------*/
double a3gtime(void)
{
  int i;
  for(i = 0; i < NEDB; i++) {
    if( cyc.adtime[i] > 1.0 ) {
      return(cyc.adtime[i] - 12.0 * (double)i);
    }
  }
  hperr(stderr,PNOVICE,"a3gtime --- No valid time found in cycle. Returning -2.0\n");
  hperr(stderr,PNOVICE,"+ %s.\n",zrecid(&cyc));  
  return(-2.0);
}

/* ---------------------------------------------------------------------------
   a3zrecid --- record time and number as string
   -------------------------------------------------------------------------*/
char *a3zrecid(void)
{
  /*printf("DBG a3zrecid: %ld %ld %.0f\n",
	 cyc.lrecNr,
	 cyc.alNr[0],
	 cyc.adtime[0]);
  */
  return(zrecid(&cyc));
}


/* ---------------------------------------------------------------------------
   a3gxbrtab --- get SWICS BR table
   -------------------------------------------------------------------------*/
int a3gxbrtab(BYTE *abtab)
{
  int i;
  int j;

  for(i = 0; i < NXBRBOX; i++)
    for(j = 0; j < NCORN; j++)
      abtab[I(i,NCORN,j)] = cyc.abxbrtab[i][j];
  return(0);
}


/* ---------------------------------------------------------------------------
   a3pxbrtab --- print SWICS BR table to fp
   -------------------------------------------------------------------------*/
int a3pxbrtab(FILE *fp)
{
  int i;
  int j;

  BYTE abtab[NXBRBOX * NCORN];

  a3gxbrtab(abtab);

  fprintf(fp,"a3pxbrtab --- rec %5ld (%s).\n",
	 cyc.lrecNr,timstr(cyc.adtime[0]));

  for(i = 0; i < NXBRBOX; i++) {
    fprintf(fp,"%2d ",i);
    for(j = 0; j < NCORN; j++) {
      fprintf(fp,"%3d ",abtab[I(i,NCORN,j)]);
    }
    fprintf(fp,".\n");
  }
  return(0);
}

/* ---------------------------------------------------------------------------
   a3gxeqtab --- get SWICS E/q table from DPU Spare
   -------------------------------------------------------------------------*/
double *a3gxeqtab(void)
{
  static double adtab[NXEQ];
  int i;

  hperr(stderr,PNOVICE,"a3gxeqtab --- usage depreciated. No longer supported.\n");

  for(i = 0; i < NXEQ; i++) adtab[i] = (double)cyc.abxeqtab[i];

  return(adtab);
}

/* ---------------------------------------------------------------------------
   a3gxeqtab_i --- get SWICS digital value of E/q
   -------------------------------------------------------------------------*/
int a3gxeqtab_i(int ie)
{
  if( crng(ie,0,NEDB-1,"a3gxeqtab_i") ) return(-1.0);
  return(cyc.abxeqtab[ie]);
}

/* ---------------------------------------------------------------------------
   a3gxeqdpu --- get SWICS E/q values (calculated from eqtab; not HK)
   -------------------------------------------------------------------------*/
float *a3gxeqdpu(void)
{
  hperr(stderr,PNOVICE,"a3gxeoqdpu --- usage depreciated. No longer supported.\n");
  return(cyc.afxeoqdpu);
}

/* ---------------------------------------------------------------------------
   a3gxeqdpu_i --- get SWICS E/q of step i (calculated from eqtab; not HK)
   -------------------------------------------------------------------------*/
double a3gxeqdpu_i(int ie)
{
  return(cyc.afxeoqdpu[ie]);
}

/* ---------------------------------------------------------------------------
   a3gxeqaux_i --- get SWICS E/q of step i for AUX channel.
   -------------------------------------------------------------------------*/
double a3gxeqaux_i(int ie)
{
  return(cyc.afxeoqaux[ie]);
}

/* ---------------------------------------------------------------------------
   a3gxpavdpu --- SWICS PAPS according to DPU (not HK)
   -------------------------------------------------------------------------*/
double a3gxpavdpu(void)
{
  return(cyc.fxpav);
}

/* ---------------------------------------------------------------------------
   a3gmeqtab --- get SWIMS E/q table
   -------------------------------------------------------------------------*/
float *a3gmeqtab(void)
{
  static float aftab[NMEQ];
  int i;

  for(i = 0; i < NMEQ; i++) aftab[i] = (float)cyc.asmeqtab[i];

  return(aftab);
}

/* ---------------------------------------------------------------------------
   a3gmeqtab_i --- SWIMS entrance system voltage CMD for spin i
   -------------------------------------------------------------------------*/
int a3gmeqtab_i(int ie)
{
  if( crng(ie,0,NEDB-1,"a3gmeqtab_i") ) return(-1);

  return(cyc.asmeqtab[ie]);
}

/* ---------------------------------------------------------------------------
   a3mtof1_i --- SWIMS element i of TOF histogram 1 accum. by DPU
   -------------------------------------------------------------------------*/
long a3mtof1_i(int i)
{
  if( crng(i,0,NMTOFHIST-1,"a3mtof1_i") ) return(-1);

  return(cyc.almtof1[i]);
}

/* ---------------------------------------------------------------------------
   a3mtof2_i --- SWIMS element i of TOF histogram 2 accum. by DPU
   -------------------------------------------------------------------------*/
long a3mtof2_i(int i)
{
  if( crng(i,0,NMTOFHIST-1,"a3mtof2_i") ) return(-1);

  return(cyc.almtof2[i]);
}

/* ---------------------------------------------------------------------------
   a3gmeqdpu --- get SWIMS E/q values (calculated from eqtab; not HK)
   -------------------------------------------------------------------------*/
float *a3gmeqdpu(void)
{
  return(cyc.afmeoqdpu);
}

/* ---------------------------------------------------------------------------
   a3gmeqdpu_i --- get SWIMS E/q values (calculated from eqtab; not HK)
   ------------------------------------------------------------------------ */
double a3gmeqdpu_i(int ie)
{
  if( crng(ie,0,NEDB-1,"a3gmeqdpu_i") ) return(-1.0);
  return(cyc.afmeoqdpu[ie]);
}

/* ---------------------------------------------------------------------------
   a3pxbrtab --- print SWICS E/q table to fp
   -------------------------------------------------------------------------*/
int a3pxeqtab(FILE *fp)
{
  int i;

  double *adtab;

  adtab = a3gxeqtab();

  fprintf(fp,"a3pxeqtab --- rec %5ld (%s).",
	 cyc.lrecNr,timstr(cyc.adtime[0]));

  for(i = 0; i < NXEQ; i++) {
    if( i % 20 == 0 ) fprintf(stdout,"\n");
    fprintf(fp,"%3.0f ",adtab[i]);
  }
  fprintf(fp,".\n");
  return(0);
}

/* ---------------------------------------------------------------------------
   a3pxmrtab --- print SWICS MR table to fp
   -------------------------------------------------------------------------*/
int a3pxmrtab(SBCYC *pcyc, FILE *fp)
{
  int i;
  int j;

  fprintf(fp,"a3pxmrtab --- rec %5ld (%s).\n",
	 pcyc->lrecNr,timstr(pcyc->adtime[0]));

  for(i = 0; i < NXMRBOX; i++) {
    fprintf(fp,"%2d ",i);
    for(j = 0; j < NCORN; j++) {
      fprintf(fp,"%3d ",pcyc->abxmrtab[i][j]);
    }
    fprintf(fp,".\n");
  }
  return(0);
}

/* ---------------------------------------------------------------------------
   a3gcnq --- get SWICS m/q Classification constants
   -------------------------------------------------------------------------*/
double *a3gcnq(void)
{
  return(cyc.adcnq);
}

/* ---------------------------------------------------------------------------
   a3xadc --- SWICS ADC on (1) or off (0)
   -------------------------------------------------------------------------*/
int a3xadc(void)
{
  long ltmp;

  /* hperr(stderr,PNOVICE,"DBG a3xadc --- %d\n",cyc.abxcmd[LXTRIG]); */
  ltmp = (long)(cyc.abxcmd[LXTRIG]);
  return(getbits(ltmp,31,1));
}

/* ---------------------------------------------------------------------------
   a3xtrigcal --- SWICS "Cal Trigger" state on (1) or off (0)
   -------------------------------------------------------------------------*/
int a3xtrigcal(void)
{
  long ltmp;

  ltmp = (long)(cyc.abxcmd[LXTRIG]);
  return(getbits(ltmp,30,1));
}

/* ---------------------------------------------------------------------------
   a3xtrigmode --- SWICS Trigger Mode (T AND E, T OR E, E only, T only)
   -------------------------------------------------------------------------*/
int a3xtrigmode(void)
{
  long ltmp;

  ltmp = (long)(cyc.abxcmd[LXTRIG]);
  return(getbits(ltmp,28,2));
}

/* ---------------------------------------------------------------------------
   a3gcnm --- get SWICS mass Classification constants
   -------------------------------------------------------------------------*/
double *a3gcnm(void)
{
  return(cyc.adcnm);
}

/* ---------------------------------------------------------------------------
   Table of Basic-Rate Definitions
   -------------------------------------------------------------------------*/
int a3gbrtab(int ibox, int icorn)
{
  if( (ibox < 0 )  || (ibox >= NXBRBOX) ||
      (icorn < 0)  || (icorn >= NCORN) ) {
    hperr(stderr,PNOVICE,"a3gbrtab --- Cannot access box %d or Corner %d\n",
	   ibox,icorn);
    return(-1);
  }
  return((int)cyc.abxbrtab[ibox][icorn]);
}

/* ---------------------------------------------------------------------------
   Table of Matrix-Rate Definitions
   -------------------------------------------------------------------------*/
int a3gmrtab(int ibox, int icorn)
{
  if( (ibox < 0 )  || (ibox >= NXMRBOX) ||
      (icorn < 0)  || (icorn >= NCORN) ) {
    hperr(stderr,PNOVICE,"a3gmrtab --- Cannot access box %d or Corner %d\n",
	   ibox,icorn);
    return(-1);
  }
  return((int)cyc.abxmrtab[ibox][icorn]);
}

/* ---------------------------------------------------------------------------
   SWICS Housekeeping block
   -------------------------------------------------------------------------*/
float a3gxhk(int ie, int i)
{
  if ( ie >= NEDB || i < 0 || i >= NXHK){
    return(-1);
  }
  return(cyc.afxhk[ie][i]);
}
  
/* ---------------------------------------------------------------------------
   S3DPU Housekeeping Block Item
   -------------------------------------------------------------------------*/
BYTE a3gdpuhk(int ie, int i)
{
  if ( ie >= NEDB || i < 0 || i >= NDHK){
    return(-1);
  }
  return(cyc.abs3dpuhk[ie][i]);
}

/* ---------------------------------------------------------------------------
   SEPICA Housekeeping Block Item
   -------------------------------------------------------------------------*/
BYTE a3gshk(int ie, int i)
{
  if ( ie >= NEDB || i < 0 || i >= NSHK){
    return(-1);
  }
  return(cyc.abshk[ie][i]);
}
/* = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
** Sensor Rates
** = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =*/

/* -------------------------------------------------------------------------*/
/* a3gxsr --- get SWICS sensor rate (summed over sectors) */
/* -------------------------------------------------------------------------*/
int a3gxsr(int isr, double *adfsr)
{
  int i;

  for(i = 0; i < NXEQ; i++) {

    adfsr[i] = (double)cyc.alxsr[i][isr][NSEC];
  }

  return(0);
}

/* -------------------------------------------------------------------------*/
/* a3gxfsr --- get SWICS FSR (summed over sectors) */
/* -------------------------------------------------------------------------*/
double *a3gxfsr(void)
{

  static double adfsr[NXEQ];
  hperr(stderr,PNOVICE,"a3gxfsr --- usage depreciated. Routine is no longer supported.\n");
  a3gxsr(LXFSR,adfsr);
  return(adfsr);
}

/* ---------------------------------------------------------------------------
   a3gxfsr_i --- get SWICS FSR[ie] of EDB ie and sector isec
   -------------------------------------------------------------------------*/
double a3gxfsr_i(int ie, int isec)
{
  if( crng(ie,0,NEDB-1,"a3gxfsr_i") ) return(0.0);
  if( crng(isec,0,NSEC,"a3gxfsr_i") ) return(0.0);

  return((double)cyc.alxsr[ie][LXFSR][isec]);
}

/* -------------------------------------------------------------------------*/
/* a3gxdcr --- get SWICS DCR (summed over sectors) */
/* -------------------------------------------------------------------------*/
double *a3gxdcr(void)
{
  static double adfsr[NXEQ];
  hperr(stderr,PNOVICE,"a3gxdcr --- usage depreciated. Routine is no longer supported.\n");
  a3gxsr(LXDCR,adfsr);
  return(adfsr);
}

/* ---------------------------------------------------------------------------
   a3gxdcr_i --- get SWICS DCR[ie] of EDB ie and sector isec
   -------------------------------------------------------------------------*/
double a3gxdcr_i(int ie, int isec)
{
  if( crng(ie,0,NEDB-1,"a3gxdcr_i") ) return(0.0);
  if( crng(isec,0,NSEC,"a3gxdcr_i") ) return(0.0);

  return((double)cyc.alxsr[ie][LXDCR][isec]);
}

/* -------------------------------------------------------------------------*/
/* a3gxtcr --- get SWICS TCR (summed over sectors) */
/* -------------------------------------------------------------------------*/
double *a3gxtcr(void)
{
  static double adfsr[NXEQ];
  hperr(stderr,PNOVICE,"a3gxtcr --- usage depreciated. Routine is no longer supported.\n");
  a3gxsr(LXTCR,adfsr);
  return(adfsr);
}

/* ---------------------------------------------------------------------------
   a3gxtcr_i --- get SWICS TCR[ie] of EDB ie and sector isec
   -------------------------------------------------------------------------*/
double a3gxtcr_i(int ie, int isec)
{
  if( crng(ie,0,NEDB-1,"a3gxtcr_i") ) return(0.0);
  if( crng(isec,0,NSEC,"a3gxtcr_i") ) return(0.0);

  return((double)cyc.alxsr[ie][LXTCR][isec]);
}

/* -------------------------------------------------------------------------*/
/* a3gxsdr --- get SWICS SSD rate (summed over sectors) */
/* -------------------------------------------------------------------------*/
double *a3gxsdr(void)
{
  static double adfsr[NXEQ];
  hperr(stderr,PNOVICE,"a3gxsdr --- usage depreciated. Routine is no longer supported.\n");
  a3gxsr(LXSSR,adfsr);
  return(adfsr);
}

/* ---------------------------------------------------------------------------
   a3gxsdr_i --- get SWICS SSD Rate of EDB ie and sector isec
   -------------------------------------------------------------------------*/
double a3gxsdr_i(int ie, int isec)
{
  if( crng(ie,0,NEDB-1,"a3gxsdr_i") ) return(0.0);
  if( crng(isec,0,NSEC,"a3gxsdr_i") ) return(0.0);

  return((double)cyc.alxsr[ie][LXSSR][isec]);
}

/* -------------------------------------------------------------------------*/
/* a3gxpr --- get SWICS AUX proton rate (summed over sectors) */
/* -------------------------------------------------------------------------*/
double *a3gxpr(void)
{
  static double adfsr[NXEQ];
  hperr(stderr,PNOVICE,"a3gxpr --- usage depreciated. Routine is no longer supported.\n");
  a3gxsr(LXPR,adfsr);
  return(adfsr);
}

/* ---------------------------------------------------------------------------
   a3gxpr_i --- get SWICS "proton rate" (AUX)  of EDB ie and sector isec
   -------------------------------------------------------------------------*/
double a3gxpr_i(int ie, int isec)
{
  if( crng(ie,0,NEDB-1,"a3gxpr_i") ) return(0.0); /* check range */
  if( crng(isec,0,NSEC,"a3gxpr_i") ) return(0.0);

  return((double)cyc.alxsr[ie][LXPR][isec]);
}

/* -------------------------------------------------------------------------*/
/* a3gxar --- get SWICS AUX alpha rate (summed over sectors) */
/* -------------------------------------------------------------------------*/
double *a3gxar(void)
{
  static double adfsr[NXEQ];
  hperr(stderr,PNOVICE,"a3gxar --- usage depreciated. Routine is no longer supported.\n");
  a3gxsr(LXAR,adfsr);
  return(adfsr);
}

/* ---------------------------------------------------------------------------
   a3gxar_i --- get SWICS "alpha rate" (AUX)  of EDB ie and sector isec
   -------------------------------------------------------------------------*/
double a3gxar_i(int ie, int isec)
{
  if( crng(ie,0,NEDB-1,"a3gxar_i") ) return(0.0); /* check range */
  if( crng(isec,0,NSEC,"a3gxar_i") ) return(0.0);

  return((double)cyc.alxsr[ie][LXAR][isec]);
}

/* = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
** Matrix Rates
** = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =*/

/* -------------------------------------------------------------------------*/
/* a3gxmr --- get SWICS Matrix rate (summed over sectors) */
/* -------------------------------------------------------------------------*/
int a3gxmr_old(int isr, double *adfsr)
{
  int i;

  hperr(stderr,PNOVICE,"a3gxmr_old --- Depreciated. Try a3gxmr(imr,ie,isec) instead.\n");

  for(i = 0; i < NXEQ; i++) {

    adfsr[i] = (double)cyc.alxmr[i][isr][NSEC];
  }

  return(0);
}

/* -------------------------------------------------------------------------*/
/* a3gxmrh_1 --- get SWICS matrix rate for H+ (summed over sectors) */
/* -------------------------------------------------------------------------*/
double *a3gxmrh_1(void)
{
  static double adfsr[NXEQ];
  a3gxmr_old(0,adfsr);
  return(adfsr);
}

/* -------------------------------------------------------------------------*/
/* a3gxmrhe2 --- get SWICS matrix rate for He++ (summed over sectors) */
/* -------------------------------------------------------------------------*/
double *a3gxmrhe2(void)
{
  static double adfsr[NXEQ];
  a3gxmr_old(1,adfsr);
  return(adfsr);
}

/* ---------------------------------------------------------------------------
** a3gxmr_i --- SWICS matrix rate for He++
** -------------------------------------------------------------------------*/
long a3gxmr_i(int ie, int irate, int isec)
{
  /* check range */
  if( crng(ie,0,NEDB-1,"a3gxmr_i") )    return(-1.0);
  if( crng(irate,0,NXMR-1,"a3gxmr_i") ) return(-2.0);
  if( crng(isec,0,NSEC,"a3gxmr_i") )    return(-3.0);

  return(cyc.alxmr[ie][irate][isec]);
}

/* -------------------------------------------------------------------------*/
/* a3gxmrhe1 --- get SWICS matrix rate for He+ (summed over sectors) */
/* -------------------------------------------------------------------------*/
double *a3gxmrhe1(void)
{
  static double adfsr[NXEQ];
  a3gxmr_old(2,adfsr);
  return(adfsr);
}

/* -------------------------------------------------------------------------*/
/* a3gxmro_7 --- get SWICS matrix rate for O7+ (summed over sectors) */
/* -------------------------------------------------------------------------*/
double *a3gxmro_7(void)
{
  static double adfsr[NXEQ];
  a3gxmr_old(3,adfsr);
  return(adfsr);
}

/* -------------------------------------------------------------------------*/
/* a3gxmro_6 --- get SWICS matrix rate for O6+ (summed over sectors) */
/* -------------------------------------------------------------------------*/
double *a3gxmro_6(void)
{
  static double adfsr[NXEQ];
  a3gxmr_old(4,adfsr);
  return(adfsr);
}

/* -------------------------------------------------------------------------*/
/* a3gxmrfes --- get SWICS matrix rate for Si (summed over sectors) */
/* -------------------------------------------------------------------------*/
double *a3gxmrfes(void)
{
  static double adfsr[NXEQ];
  a3gxmr_old(5,adfsr);
  return(adfsr);
}

/* -------------------------------------------------------------------------*/
/* a3gxmrsis --- get SWICS matrix rate for Si (summed over sectors) */
/* -------------------------------------------------------------------------*/
double *a3gxmrsis(void)
{
  static double adfsr[NXEQ];
  a3gxmr_old(6,adfsr);
  return(adfsr);
}

/* -------------------------------------------------------------------------*/
/* a3gxmrerr --- get SWICS matrix rate "Err" (summed over sectors) */
/* -------------------------------------------------------------------------*/
double *a3gxmrerr(void)
{
  static double adfsr[NXEQ];
  a3gxmr_old(7,adfsr);
  return(adfsr);
}

/* ---------------------------------------------------------------------------
   a3gxmr --- SWICS Matrix Rate imr in Step ie and Sector isec
   -------------------------------------------------------------------------*/
double a3gxmr(int imr, int ie, int isec)
{
  if( crng(ie,0,NEDB-1,"a3gxmr") ) return(0.0); /* check range */
  if( crng(isec,0,NSEC,"a3gxmr") ) return(0.0);
  if( crng(imr,0,NXMR-1,"a3gxmr") ) return(0.0);

  return((double)cyc.alxmr[ie][imr][isec]);
}

/* ===========================================================================
** SWICS PHA
** ======================================================================== */

/* ---------------------------------------------------------------------------
   a3xnpha --- number of SWICS PHAs in E/q step ie
   -------------------------------------------------------------------------*/
int a3xnpha(int ie)
{
  return(cyc.asxNof[ie]);
}

/* ---------------------------------------------------------------------------
   a3gxmoq --- SWICS PHAs: m/q
   -------------------------------------------------------------------------*/
float *a3gxmoq(int ie)
{
  return(cyc.afxmoq[ie]);
}

/* ---------------------------------------------------------------------------
   a3gxmoq_i --- SWICS PHA[i]: m/q
   -------------------------------------------------------------------------*/
double a3gxmoq_i(int ie, int i)
{
  if( i < cyc.asxNof[ie] ) {
    return((int)cyc.afxmoq[ie][i]);
  } else {
    hperr(stderr,PNOVICE,"a3gxmoq_i --- Only %d PHAs found. Cannot return PHA %d.\n",
	   cyc.asxNof[ie],i);
    return(-1.0);
  }
}

/* ---------------------------------------------------------------------------
   a3gxmas --- SWICS PHAs: mass
   -------------------------------------------------------------------------*/
float *a3gxmas(int ie)
{
  return(cyc.afxmas[ie]);
}

/* ---------------------------------------------------------------------------
   a3gxmas_i --- SWICS PHA[i]: mass
   -------------------------------------------------------------------------*/
double a3gxmas_i(int ie, int i)
{
  if( i < cyc.asxNof[ie] ) {
    //printf("a3gxmas_i -I- nedb=%d npha=%d mass=%f\n",ie,i,cyc.afxmas[ie][i]);
    return((int)cyc.afxmas[ie][i]);
  } else {
    hperr(stderr,PNOVICE,"a3gxmas_i --- Only %d PHAs found. Cannot return PHA %d.\n",
	   cyc.asxNof[ie],i);
    return(-1.0);
  }
}

/* ---------------------------------------------------------------------------
   a3gxtof_i --- SWICS PHA[i]: TOF
   -------------------------------------------------------------------------*/
int a3gxtof_i(int ie, int i)
{
  if( i < cyc.asxNof[ie] ) {
    return((int)cyc.asxtof[ie][i]);
  } else {
    hperr(stderr,PNOVICE,"a3gxtof_i --- Only %d PHAs found. Cannot return PHA %d.\n",
	   cyc.asxNof[ie],i);
    return(-1);
  }
}

/* ---------------------------------------------------------------------------
   a3gxesd_i --- SWICS PHA[i]: E_SSD
   -------------------------------------------------------------------------*/
int a3gxesd_i(int ie, int i)
{
  if( i < cyc.asxNof[ie] ) {
    return((int)cyc.abxesd[ie][i]);
  } else {
    hperr(stderr,PNOVICE,"a3gxesd_i --- Only %d PHAs found. Cannot return PHA %d.\n",
	   cyc.asxNof[ie],i);
    return(-1);
  }
}

/* ---------------------------------------------------------------------------
   a3gxdid_i --- SWICS PHA[i]: DPU Id (opposed to off-line calculated range)
   -------------------------------------------------------------------------*/
int a3gxdid_i(int ie, int i)
{
  if( i < cyc.asxNof[ie] ) {
    return((int)cyc.abxdid[ie][i]);
  } else {
    hperr(stderr,PNOVICE,"a3gxdid_i --- Only %d PHAs found. Cannot return PHA %d.\n",
	   cyc.asxNof[ie],i);
    return(-1);
  }
}

/* ---------------------------------------------------------------------------
   a3gxsec_i --- SWICS PHA[i]: Sector
   -------------------------------------------------------------------------*/
int a3gxsec_i(int ie, int i)
{
  if( i < cyc.asxNof[ie] ) {
    return((int)cyc.abxsec[ie][i]);
  } else {
    hperr(stderr,PNOVICE,"a3gxsec_i --- Only %d PHAs found. Cannot return PHA %d.\n",
	   cyc.asxNof[ie],i);
    return(-1);
  }
}

/* ---------------------------------------------------------------------------
   a3gxrng_i --- SWICS PHA[i]: Off-line calculated range
   -------------------------------------------------------------------------*/
int a3gxrng_i(int ie, int i)
{
  if( i < cyc.asxNof[ie] ) {
    return((int)cyc.abxrng[ie][i]);
  } else {
    hperr(stderr,PNOVICE,"a3gxrng_i --- Only %d PHAs found. Cannot return PHA %d.\n",
	   cyc.asxNof[ie],i);
    return(-1);
  }
}


/* ---------------------------------------------------------------------------
   a3xbrwgt --- SWICS Basic Rate weigth at E/q step ie, BR ibr
   -------------------------------------------------------------------------*/
double a3xbrwgt(int ie, int ibr)
{
  return(cyc.afxwgt[ie][ibr]);
}

/* ---------------------------------------------------------------------------
   a3gxbr --- SWICS Basic Rate of Range ibr at EDB ie of secot sec
   -------------------------------------------------------------------------*/
long a3gxbr(int ie, int ibr, int isec)
{
  if( crng(ie,0,NEDB-1,"a3gxbr") ) return(0);
  if( crng(ibr,0,NXBR-1,"a3gxbr") ) return(0);
  if( crng(isec,0,NSEC,"a3gxbr") ) return(0);

  return(cyc.alxbr[ie][ibr][isec]);
}

/* ---------------------------------------------------------------------------
   a3gxnr --- SWICS PHA: number of PHAs in range ibr,sector sec, EDB ie
   -------------------------------------------------------------------------*/
int a3gxnr(int ie, int ibr, int isec)
{
  if( crng(ie,0,NEDB-1,"a3gxnr") ) return(0);
  if( crng(ibr,0,NXBR-1,"a3gxnr") ) return(0);
  if( crng(isec,0,NSEC,"a3gxnr") ) return(0);

  return((int)cyc.asxnr[ie][ibr][isec]);
}

/* ---------------------------------------------------------------------------
   a3cxmoq --- convert SWICS m/q from DPU units to phyiscal units ([1])
   ------------------------------------------------------------------------ */
double a3cxmoq(double dmoq_ch)
{
  if(dmoq_ch < S3XNQMIN ) {
    printf("a3cxmoq -d- dmoq_ch=%f\n",dmoq_ch);
    hperr(stderr,PNOVICE,"%s\n",
	 "a3cxmoq --- Note: m/q channels below 1 have special meanings.");
    hperr(stderr,PNOVICE,"%s\n",
	    "+                 Returning -1.0");
    return(-1.0);
  }
  if(dmoq_ch > S3XNQMAX ) {
    printf("a3cxmoq -d- dmoq_ch=%f\n",dmoq_ch);
    hperr(stderr,PNOVICE,"%s\n",
	    "a3cxmoq --- Note: m/q channels above 124 are reserved.");
    hperr(stderr,PNOVICE,"%s\n",
	    "+                 Returning -1.0");
    return(-1.0);
  }
  return(exp((dmoq_ch - 1.0)/S3DPULNQ));
}
  
/* ---------------------------------------------------------------------------
   a3cxmas --- convert SWICS m from DPU units to phyiscal units ([amu])
   ------------------------------------------------------------------------ */
double a3cxmas(double dmas_ch)
{
  if(dmas_ch < S3XNMMIN ) {
    printf("a3cxmas -d- dmas_ch=%f\n",dmas_ch);
    hperr(stderr,PNOVICE,"%s\n",
	    "a3xcmas --- Note: m channels below 1 are reserved.");
    hperr(stderr,PNOVICE,"%s\n",
	    "+                 Returning -1.0\n");
    return(-1.0);
  }
  if(dmas_ch > S3XNMMAX ) {
    printf("a3cxmas -d- dmas_ch=%f\n",dmas_ch);
    hperr(stderr,PNOVICE,"%s\n",
	    "a3xcmas --- Note: m channels above 122 are reserved.");
    hperr(stderr,PNOVICE,"%s\n",
	    "+                 Returning -1.0");
    return(-1.0);
  }
  return(exp((dmas_ch - 1.0)/S3DPULNM));
}

/* ---------------------------------------------------------------------------
   a3xellmmq --- count PHA falling into ellipse at step ie (m-m/q domain)
   -------------------------------------------------------------------------*/
int a3xellmmq(int ie, double moq0, double smq1, double smq2, 
	              double mas0, double sma1, double sma2)
{
  int    i;
  double dmoq;
  double dmas;

  double dsmoq;
  double dsmas;

  double dtmp;

  int    ires;

  ires = 0;

  /* -------------------------------------------------------------------------
  ** loop PHA words
  ** ---------------------------------------------------------------------- */
  for(i = 0; i < cyc.asxNof[ie]; i++) /* loop words (i) */ {

    /*
    hperr(stderr,PNOVICE,"a3xellmmq --- %2d %3d %4d %3d %5.1f %5.1f",
	   ie,i,
	   cyc.asxtof[ie][i],
	   cyc.abxesd[ie][i],
	   cyc.adxmoq[ie][i],
	   cyc.adxmas[ie][i]);
    */

    dmoq = cyc.afxmoq[ie][i];
    dmas = cyc.afxmas[ie][i];

    dmoq = exp(dmoq/S3DPULNQ);
    dmas = exp(dmas/S3DPULNM);

    /* hperr(stderr,PNOVICE," %6.2f %6.2f",dmoq,dmas); */

    /* -----------------------------------------------------------------------
    ** check ellipse
    ** -------------------------------------------------------------------- */

    if( dmoq < moq0 ) dsmoq = smq1;
    else              dsmoq = smq2;

    if( dmas < mas0 ) dsmas = sma1;
    else              dsmas = sma2;

    dtmp = dratio(dsqr(moq0-dmoq),dsqr(dsmoq)) +
           dratio(dsqr(mas0-dmas),dsqr(dsmas));

    /* hperr(stderr,PNOVICE," %7.1f %3d\n",dtmp,ires); */
    if( dtmp <= 1.0 ) ires++;
  }

  return(ires);
}

/* ---------------------------------------------------------------------------
   a3xelletm --- count PHA falling into ellipse at step ie (E-T domain)
   -------------------------------------------------------------------------*/
double a3xelletm(int ie, int ir, double vH, long lflag,
	      double t0, double st1, double st2, 
	      double e0, double se1, double se2)
{
  int    i;
  int    ifilt;

  double deoq;
  double pav;

  double dtof;
  double desd;

  double dstof;
  double dsesd;

  double dtmp;
  double dwgt;

  double dres;

  dres = 0.0;

  /* -------------------------------------------------------------------------
  ** check ie
  ** ---------------------------------------------------------------------- */

  if( ie < 2 ) {
    hperr(stderr,PNOVICE,"a3xelletm --- Note: use of ie=%d is problematic (Tech Note 3).\n",
	   ie);
    if( ie == 0 ) {
      hperr(stderr,PNOVICE,"a3xelletm --- ie = 0 not allowed.\n");
      return(0.0);
    }
  }

  /* -------------------------------------------------------------------------
  ** E/q
  ** ---------------------------------------------------------------------- */
  deoq = a3gxeqdpu_i(ie-1);             /* Tech Note 3 */
  pav  = a3gxpavdpu();

  /* -------------------------------------------------------------------------
  ** loop PHA words
  ** ---------------------------------------------------------------------- */
  for(i = 0; i < cyc.asxNof[ie]; i++) /* loop words (i) */ {

    if( cyc.abxrng[ie][i] == ir ) /* same range */ {

      /* ---------------------------------------------------------------------
      ** BR weighting ?
      ** ------------------------------------------------------------------ */
      if( lflag & A3XELLETM_WGT ) dwgt = a3xbrwgt(ie,cyc.abxrng[ie][i]);
      else                        dwgt = 1.0;

      /* ---------------------------------------------------------------------
      ** filter (acc. coincidence) ?
      ** ------------------------------------------------------------------ */

      ifilt = 1;
      if( lflag & A3XELLETM_FLT )
	ifilt = xphafilt(vH,0.0,deoq,pav,cyc.asxtof[ie][i],cyc.abxesd[ie][i]);
      
      /*
      hperr(stderr,PNOVICE,"DBG a3xelletm --- w %4.1f f %1d T %4d E %3d ",
	     dwgt,ifilt,cyc.asxtof[ie][i],cyc.abxesd[ie][i]);
      */

      if( ifilt ) {

	dtof = (double)cyc.asxtof[ie][i];
	desd = (double)cyc.abxesd[ie][i];

	/* -------------------------------------------------------------------
	** check ellipse
	** ---------------------------------------------------------------- */

	if( dtof < t0 ) dstof = st1;
	else            dstof = st2;
	
	if( desd < e0 ) dsesd = se1;
	else            dsesd = se2;
	
	dtmp = dratio(dsqr(t0-dtof),dsqr(dstof)) +
	       dratio(dsqr(e0-desd),dsqr(dsesd));

	/*
	hperr(stderr,PNOVICE,"T/s: %4.0f %4.1f E/s: %3.0f %3.1f i: %7.1f ",
	       t0,dstof,e0,dsesd,dtmp);
	*/

	if( dtmp <= 1.0 ) dres += dwgt;
      }
      /*
      hperr(stderr,PNOVICE,"\n");
      */
    }
  }
  return(dres);
}

/* ---------------------------------------------------------------------------
   a3xrell --- count PHA falling into ruedi's ellipses at step ie (m-m/q)
   -------------------------------------------------------------------------*/
double a3xrell(int ie, int ir, double vH, long lflag,
	       double moq0, double bmoq,
	       double mas0, double bmas)
{
  int    i;
  int    ifilt;

  double deoq;
  double pav;

  double dtmp;
  double dwgt;

  double dres;

  double dmoq;
  double dmas;

  double lnbmoq2;
  double lnbmas2;

  dres = 0.0;

  /* -------------------------------------------------------------------------
  ** debug flag setting
  ** ---------------------------------------------------------------------- */

  /*
  hperr(stderr,PNOVICE,"DBG a3xrell --- BR WGT: %d FILTER: %d UPPER: %d\n",
	 lflag & A3XRELL_WGT,
	 lflag & A3XRELL_FLT,
	 lflag & A3XRELL_UPPER);
  */

  /* -------------------------------------------------------------------------
  ** check ie
  ** ---------------------------------------------------------------------- */

  if( ie < 2 ) {
    hperr(stderr,PNOVICE,"a3xrell --- Note: use of ie=%d is problematic (Tech Note 3).\n",
	   ie);
    if( ie == 0 ) {
      hperr(stderr,PNOVICE,"a3xrell --- ie = 0 not allowed.\n");
      return(0.0);
    }
  }

  /* -------------------------------------------------------------------------
  ** check Ellipse parameters > 0
  ** ---------------------------------------------------------------------- */
  if( (moq0 <= 0.0) ||
      (mas0 <= 0.0) ||
      (bmoq <= 0.0) ||
      (bmas <= 0.0) ) {
    hperr(stderr,PNOVICE,"a3xrell --- Ellipse parameters must be > 0.0\n");
    return(0.0);
  }

  lnbmoq2 = dsqr(log(bmoq));
  lnbmas2 = dsqr(log(bmas));


  /* -------------------------------------------------------------------------
  ** E/q
  ** ---------------------------------------------------------------------- */
  deoq = a3gxeqdpu_i(ie-1);             /* Tech Note 3 */
  pav  = a3gxpavdpu();

  /* -------------------------------------------------------------------------
  ** loop PHA words
  ** ---------------------------------------------------------------------- */
  for(i = 0; i < cyc.asxNof[ie]; i++) /* loop words (i) */ {

    if( cyc.abxrng[ie][i] == ir ) /* same range */ {

      if( (cyc.afxmoq[ie][i] >= S3XNQMIN) &&
	  (cyc.afxmoq[ie][i] <= S3XNQMAX) &&
	  (cyc.afxmas[ie][i] >= S3XNMMIN) &&
	  (cyc.afxmas[ie][i] <= S3XNMMAX) ) {

	/* -------------------------------------------------------------------
	** BR weighting ?
	** ---------------------------------------------------------------- */
	if( lflag & A3XRELL_WGT ) dwgt = a3xbrwgt(ie,cyc.abxrng[ie][i]);
	else                      dwgt = 1.0;

	/* -------------------------------------------------------------------
	** filter (acc. coincidence) ?
	** ---------------------------------------------------------------- */

	ifilt = 1;
	if( lflag & A3XRELL_FLT )
	  ifilt = xphafilt(vH,0.0,deoq,pav,
			   cyc.asxtof[ie][i],cyc.abxesd[ie][i]);
      
	if( ifilt ) {

	  /* -----------------------------------------------------------------
	  ** check ellipse
	  ** -------------------------------------------------------------- */

	  /* ==FIXME== conversion DPU ch --> m, m/q */

	  dmoq = a3cxmoq(cyc.afxmoq[ie][i]);
	  dmas = a3cxmas(cyc.afxmas[ie][i]);

	  /* 	dmoq = exp((cyc.adxmoq[ie][i])/S3DPULNQ); */
	  /* 	dmas = exp((cyc.adxmas[ie][i])/S3DPULNM); */
	  
	  /* hperr(stderr,PNOVICE,"DBG a3xrell --- m/q: %.3f m: %.3f ",
	  **     dmoq,dmas);
	  */

	  if( (dmoq > 0.0) && (dmas > 0.0) ) {

	    dtmp = dratio(dsqr(log(dmoq/moq0)),lnbmoq2) +
	           dratio(dsqr(log(dmas/mas0)),lnbmas2);

	    /* hperr(stderr,PNOVICE,"in_ellipse: %.3f\n",dtmp); */

	    /* ---------------------------------------------------------------
	    ** upper half only
	    ** ------------------------------------------------------------ */

	    if( lflag & A3XRELL_UPPER ) {
	      if( dmas <= mas0 ) dwgt = 0.0;
	    }

	    /* ---------------------------------------------------------------
	    ** add
	    ** ------------------------------------------------------------ */

	    if( dtmp <= 1.0 ) dres += dwgt;
	  }
	}
      }
    }
  }
  return(dres);
}

/* ---------------------------------------------------------------------------
   a3mmq --- histogram of SWICS PHA of one cycle in m-m/q domain
             (added to existing)
   a3mmq(hst,x,y,0,200.0,300,1.0,20.0,128,1.0,100.0)
   -------------------------------------------------------------------------*/
int a3mmq(double *adhst, double *adx, double *ady, long lflag, double vH,
  int Nx, double dxl, double dxh,
  int Ny, double dyl, double dyh)
{

  int    ie;
  int    i;

  double lnm;
  double lnq;
  double dwgt;

  double dmoq;
  int    imoq;
  double dmas;
  int    imas;
  int    ifilt;
  double deoq;
  double pav;

  lnq = ((double)(Nx - 1)) / log(dxh/dxl);
  lnm = ((double)(Ny - 1)) / log(dyh/dyl);

  pav  = a3gxpavdpu();

  /* -------------------------------------------------------------------------
  ** loop E/q
  ** ---------------------------------------------------------------------- */

  /* (skip ie=0,1 --- Tech Note 3) */
  for(ie = 2; ie < NEDB; ie++) /* loop EDBs */ {

    deoq = a3gxeqdpu_i(ie-1);           /* diff between acc and tlm
					** Tech Note 3 */
    /* libhef.doc:
    ** E/q calc. from CNQ structure and E/q Table as found in DPU Spare */

    /* -----------------------------------------------------------------------
    ** loop PHA words
    ** -------------------------------------------------------------------- */

    for(i = 0; i < cyc.asxNof[ie]; i++) /* loop words (i) */ {

      if( (cyc.afxmoq[ie][i] >= S3XNQMIN) &&
	  (cyc.afxmoq[ie][i] <= S3XNQMAX) &&
	  (cyc.afxmas[ie][i] >= S3XNMMIN) &&
	  (cyc.afxmas[ie][i] <= S3XNMMAX) ) {

	/* -------------------------------------------------------------------
	** BR weighting ?
	** ---------------------------------------------------------------- */
	if( lflag & A3MMQ_WGT ) dwgt = a3xbrwgt(ie,cyc.abxrng[ie][i]);
	else                    dwgt = 1.0;

	/* -------------------------------------------------------------------
	** filter (acc. coincidence) ?
	** ---------------------------------------------------------------- */
	ifilt = 1;
	if( lflag & A3MMQ_FLT )
	  ifilt = xphafilt(vH,0.0,deoq,pav,
			   cyc.asxtof[ie][i],cyc.abxesd[ie][i]);
	
	if( ifilt ) {

	  dmoq = a3cxmoq(cyc.afxmoq[ie][i]);
	  dmas = a3cxmas(cyc.afxmas[ie][i]);

	  imoq = 0;
	  imas = 0;
	  if(dmoq >= 1.0) imoq = (int)(lnq * log(dmoq));
	  if(dmas >= 1.0) imas = (int)(lnm * log(dmas));
	  
	  dwgt = a3xbrwgt(ie,cyc.abxrng[ie][i]);

	  if( (imoq >= 0) && (imoq < Nx) &&
	      (imas >  0) && (imas < Ny) ) {

	    /* imas == 0 reserved for double-coincidences */

	    adhst[I(imoq,Ny,imas)] += dwgt;
	  }
	}
      }
    }
  }

  for(i = 0; i < Nx; i++) adx[i] = exp((double)i/lnq);
  for(i = 0; i < Ny; i++) ady[i] = exp((double)i/lnm);

  return(0);
}
   
/* ---------------------------------------------------------------------------
   a3eth --- histogram of SWICS PHA in E-T domain (added to existing)
   -------------------------------------------------------------------------*/
int a3eth(double *adhst, long lflag, int ie, double vH, 
  int offx, int Nx, int offy, int Ny)
{
  int    i;
  double dwgt;
  int    itof;
  int    iesd;
  int    ifilt = 0;
  double deoq;
  double pav;


  /* -------------------------------------------------------------------------
  ** check ie
  ** ---------------------------------------------------------------------- */

  if( ie < 2 ) {
    hperr(stderr,PNOVICE,"a3eth --- Note: use of ie=%d is problematic (Tech Note 3).\n",
	   ie);
    if( ie == 0 ) {
      hperr(stderr,PNOVICE,"a3eth --- ie = 0 not allowed.\n");
      return(1);
    }
  }

  pav  = a3gxpavdpu();
  deoq = a3gxeqdpu_i(ie-1);

  /* -------------------------------------------------------------------------
  ** loop PHA words
  ** ---------------------------------------------------------------------- */

  for(i = 0; i < cyc.asxNof[ie]; i++) /* loop words (i) */ {

    itof = cyc.asxtof[ie][i] - offx;
    iesd = cyc.abxesd[ie][i] - offy;

    /* -----------------------------------------------------------------------
    ** BR weighting ?
    ** -------------------------------------------------------------------- */
    if( lflag & A3ETH_WGT ) dwgt = a3xbrwgt(ie,cyc.abxrng[ie][i]);
    else                    dwgt = 1.0;

    /* -----------------------------------------------------------------------
    ** filter (acc. coincidence) ?
    ** -------------------------------------------------------------------- */
    ifilt = 1;
    if( lflag & A3ETH_FLT )
      ifilt = xphafilt(vH,0.0,deoq,pav,cyc.asxtof[ie][i],cyc.abxesd[ie][i]);

    if( ifilt ) {

      if( (itof >= 0) && (itof < Nx) &&
	  (iesd >= 0) && (iesd < Ny) ) {

	adhst[I(itof,Ny,iesd)] += dwgt;
      }
    }
  }

  return(0);
}

/* ---------------------------------------------------------------------------
   a3qth --- histogram of SWICS PHA in E/q-T domain (added to existing)
   -------------------------------------------------------------------------*/
int a3qth(double *adhst, long lflag, double vH, 
  int offx, int Nx, int offy, int Ny)
{
  int    i;
  double dwgt;
  int    itof;
  int    ifilt = 0;
  double deoq;
  int    ie;
  int    ieoq;
  double pav;


  pav = a3gxpavdpu();

  /* -------------------------------------------------------------------------
  ** loop E/q
  ** ---------------------------------------------------------------------- */

  /* (skip ie=0,1 --- Tech Note 3) */
  for(ie = 2; ie < NEDB; ie++) /* loop EDBs */ {

    deoq = a3gxeqdpu_i(ie-1);           /* diff between acc and tlm
					** Tech Note 3 */

    /* hperr(stderr,PNOVICE,"v %5.1f ie: %2d E/q %5.2f PAV %4.1f TOF: %4d ESSD: %3d\n",
	   vH,ie,deoq,pav,cyc.asxtof[ie][0],cyc.abxesd[ie][0]);
    */

    /* -----------------------------------------------------------------------
    ** loop PHA words
    ** -------------------------------------------------------------------- */

    for(i = 0; i < cyc.asxNof[ie]; i++) /* loop words (i) */ {

      itof = cyc.asxtof[ie][i] - offx;
      ieoq = ie                - offy;

      /* ---------------------------------------------------------------------
      ** BR weighting ?
      ** ------------------------------------------------------------------ */
      if( lflag & A3ETH_WGT ) dwgt = a3xbrwgt(ie,cyc.abxrng[ie][i]);
      else                    dwgt = 1.0;

      /* ---------------------------------------------------------------------
      ** filter (acc. coincidence) ?
      ** ------------------------------------------------------------------ */
      ifilt = 1;
      if( lflag & A3ETH_FLT ) {
	ifilt = xphafilt(vH,0.0,deoq,pav,cyc.asxtof[ie][i],cyc.abxesd[ie][i]);
      }

      if( ifilt ) {

	if( (itof >= 0) && (itof < Nx) &&
	    (ieoq >= 0) && (ieoq < Ny) ) {

	  adhst[I(itof,Ny,ieoq)] += dwgt;
	}
      }
    }
  }

  return(0);
}



/* ===========================================================================
   SWIMS Sensor Rates
   ======================================================================== */

/* ---------------------------------------------------------------------------
   a3gmfsr_i
   -------------------------------------------------------------------------*/
double a3gmfsr_i(int ie, int isec)
{
  if( crng(ie,0,NEDB-1,"a3gmfsr_i") ) return(0.0);
  if( crng(isec,0,NSEC,"a3gmfsr_i") ) return(0.0);

  return((double)cyc.almsr[ie][LMFSR][isec]);
}

/* ---------------------------------------------------------------------------
   a3gmfsra_i
   -------------------------------------------------------------------------*/
double a3gmfsra_i(int ie, int isec)
{
  if( crng(ie,0,NEDB-1,"a3gmfsra_i") ) return(0.0);
  if( crng(isec,0,NSEC,"a3gmfsra_i") ) return(0.0);

  return((double)cyc.almsr[ie][LMFSRA][isec]);
}

/* ---------------------------------------------------------------------------
   a3gmfsrb_i
   -------------------------------------------------------------------------*/
double a3gmfsrb_i(int ie, int isec)
{
  if( crng(ie,0,NEDB-1,"a3gmfsrb_i") ) return(0.0);
  if( crng(isec,0,NSEC,"a3gmfsrb_i") ) return(0.0);

  return((double)cyc.almsr[ie][LMFSRB][isec]);
}

/* ---------------------------------------------------------------------------
   a3gmfsrab_i
   -------------------------------------------------------------------------*/
double a3gmfsrab_i(int ie, int isec)
{
  if( crng(ie,0,NEDB-1,"a3gmfsrab_i") ) return(0.0);
  if( crng(isec,0,NSEC,"a3gmfsrab_i") ) return(0.0);

  return((double)cyc.almsr[ie][LMFSRAB][isec]);
}

/* ---------------------------------------------------------------------------
   a3gmrsr_i
   -------------------------------------------------------------------------*/
double a3gmrsr_i(int ie, int isec)
{
  if( crng(ie,0,NEDB-1,"a3gmrsr_i") ) return(0.0);
  if( crng(isec,0,NSEC,"a3gmrsr_i") ) return(0.0);

  return((double)cyc.almsr[ie][LMRSR][isec]);
}

/* ---------------------------------------------------------------------------
   a3gmdcr_i
   -------------------------------------------------------------------------*/
double a3gmdcr_i(int ie, int isec)
{
  if( crng(ie,0,NEDB-1,"a3gmdcr_i") ) return(0.0);
  if( crng(isec,0,NSEC,"a3gmdcr_i") ) return(0.0);

  return((double)cyc.almsr[ie][LMDCR][isec]);
}


/* ---------------------------------------------------------------------------
   a3gmmfsr_i
   -------------------------------------------------------------------------*/
double a3gmmfsr_i(int ie, int isec)
{
  if( crng(ie,0,NEDB-1,"a3gmmfsr_i") ) return(0.0);
  if( crng(isec,0,NSEC,"a3gmmfsr_i") ) return(0.0);

  return((double)cyc.almsr[ie][LMMFSR][isec]);
}


/* ---------------------------------------------------------------------------
   a3gmmdcr_i
   -------------------------------------------------------------------------*/
double a3gmmdcr_i(int ie, int isec)
{
  if( crng(ie,0,NEDB-1,"a3gmmdcr_i") ) return(0.0);
  if( crng(isec,0,NSEC,"a3gmmdcr_i") ) return(0.0);

  return((double)cyc.almsr[ie][LMMDCR][isec]);
}

/* ===========================================================================
   SWIMS PHA
   ======================================================================== */
int a3mnpha(int ie)
{
  if( crng(ie,0,NEDB-1,"a3mnpha") ) return(0.0);

  return(cyc.asmNof[ie]);
}

int a3gmdid(int ie, int i)
{
  if( crng(ie,0,NEDB-1,"a3gmdid") ) return(0.0);
  if( crng(i,0,cyc.asmNof[ie]-1,"a3gmdid") ) return(0.0);

  return((int)cyc.abmdid[ie][i]);
}

int a3gmsec(int ie, int i)
{
  if( crng(ie,0,NEDB-1,"a3gmsec") ) return(0.0);
  if( crng(i,0,cyc.asmNof[ie]-1,"a3gmsec") ) return(0.0);

  return((int)cyc.abmsec[ie][i]);
}

int a3gmstamp(int ie, int i){
  return((int)cyc.asmsta[ie][i]);
}

int a3gmstopk1(int ie, int i){
  return((int)cyc.asmak1[ie][i]);
}

int a3gmstopk2(int ie, int i){
  return((int)cyc.asmak2[ie][i]);
}

int a3gmtof(int ie, int i)
{
  if( crng(ie,0,NEDB-1,"a3gmtof") ) return(0.0);
  if( crng(i,0,cyc.asmNof[ie]-1,"a3gmtof") ) return(0.0);

  return((int)cyc.asmtof[ie][i]);
}

double a3cmtof(int itof_ch)
{
  if( crng(itof_ch,0,A3MTOFCH_MAX - 1,"a3cmtof") ) return(-1.0);

  return((double)(itof_ch*A3MTOF_NSPERCH));
}

/* ===========================================================================
   Accumulate SWIMS PHA
   ======================================================================== */

/* ---------------------------------------------------------------------------
   a3mbr --- SWIMS Basic Rate at E/q step ie, BR ibr, sector isec
   -------------------------------------------------------------------------*/
long a3gmbr(int ie, int ibr, int isec)
{
  if( crng(ie,  0,NEDB-1,"a3gmbr") ) return(0);
  if( crng(ibr, 0,NMBR-1,"a3gmbr") ) return(0);
  if( crng(isec,0,NSEC,  "a3gmbr") ) return(0);

  return(cyc.almbr[ie][ibr][isec]);
}

double a3mbr(int ie, int ibr)
{
  return(cyc.afmwgt[ie][ibr]);
}

/* ---------------------------------------------------------------------------
   a3mbrwgt --- SWIMS Basic Rate weigth at E/q step ie, BR ibr
   -------------------------------------------------------------------------*/
double a3mbrwgt(int ie, int ibr)
{
  return(cyc.afmwgt[ie][ibr]);
}


/* ---------------------------------------------------------------------------
   a3mcntpha --- count PHA of type id in given TOF range at E/q step ie
   tid == -1 means: all types
   -------------------------------------------------------------------------*/
int a3mcntpha(int ie, int tid, int tlow, int thig)
{
  int    i;
  int    ires;

  ires  = 0;

  /* -------------------------------------------------------------------------
  ** loop PHA words
  ** ---------------------------------------------------------------------- */
  for(i = 0; i < cyc.asmNof[ie]; i++) /* loop words (i) */ {

    if( ((cyc.abmdid[ie][i] == tid) || (tid == -1)) && 
	(cyc.asmtof[ie][i] >= tlow) && 
	(cyc.asmtof[ie][i] <= thig) ) ires++;
  }

  return(ires);
}

/* ---------------------------------------------------------------------------
   a3mtofhist --- SWIMS TOF histogram for iel <= E/q step <= ieh,
   itl <= TOF <= ith and PHA type tid
   tid == -1 means: all types
   -------------------------------------------------------------------------*/
double *a3mtofhist(int iel, int ieh, int itl, int ith, int tid)
{
  int    i;
  int    ie;
  static double adtofhist[4096];

  /* -------------------------------------------------------------------------
  ** reset
  ** ---------------------------------------------------------------------- */
  aeset(adtofhist,0,4096,0.0);

  /* -------------------------------------------------------------------------
  ** loop E/q range
  ** ---------------------------------------------------------------------- */

  for(ie = iel; ie <= ieh; ie++) {

    /* -----------------------------------------------------------------------
    ** loop PHA words
    ** -------------------------------------------------------------------- */

    for(i = 0; i < cyc.asmNof[ie]; i++) /* loop words (i) */ {

      if( ((cyc.abmdid[ie][i] == tid) || (tid == -1)) && 
	  (cyc.asmtof[ie][i] >= itl) && 
	  (cyc.asmtof[ie][i] <= ith) ) adtofhist[cyc.asmtof[ie][i]]++;
    }
  }

  /* -------------------------------------------------------------------------
  ** done
  ** ---------------------------------------------------------------------- */

  return(adtofhist);
}


/* ---------------------------------------------------------------------------
   SWICS: kinetic properties for Matrix Rate imr
   -------------------------------------------------------------------------*/
double *a3xmrspd(int imr)
{
  static double adgue[4];
  static double adsgu[4];

  xmrspd(&cyc,adgue,adsgu,imr);

  return(adgue);
}

/*  --------------------------------------------------------------------------
    a3auxspd --- kinetic prop from AUX channel
    ------------------------------------------------------------------------*/
double *a3auxspd(void)
{
  static double adgue[4];
  static double adsgu[4];

  auxspd(&cyc,adgue,adsgu);

  return(adgue);
}

/* ---------------------------------------------------------------------------
   a3xeoqsumv1 --- correct sum(counts) to get density
   ------------------------------------------------------------------------ */
double a3xeoqsumv1(double v0, double vth, double mas, double crg,
		   int ifrst, int ilast)
{
  int    i;
  double dsum;
  double sigtot;
  double deoq_v;
  double sigeoq;
  double dron;
  double deag;

  dsum = 0.0;

  if( vth <= 0.0 ) {
    hperr(stderr,PNOVICE,"a3xeoqsumv1 --- cannot handle %.3g\n",vth);
    return(-1.0);
  }

  for(i = ifrst; i <= ilast; i++) {
    deoq_v = a3gxeqdpu_i(i);
    deoq_v = sqrt(2.0e3 * deoq_v/mas/1.6606e-27*crg*1.6022e-19)/1.0e3;
    sigeoq = 0.0085 * deoq_v;
    sigtot = sigeoq * sigeoq + vth * vth;
    dron   = sigeoq / sqrt(sigtot);
    deag   = pow(v0-deoq_v,2.0)/2.0/sigtot;
    if( deag > 30.0 ) dron = 0.0;
    else              dron   = dron * exp(-deag);
    dsum  += dron;
/* fprintf(stderr,"DBG a3xeoqsumv1 --- res = %2d %10.4g %10.4g %10.4g\n", */
/* 	    i,deoq_v,dron,dsum); */
  }

  fprintf(stderr,"DBG a3xeoqsumv1 --- res = %10.4g\n",dsum);
  return(dsum);
}
