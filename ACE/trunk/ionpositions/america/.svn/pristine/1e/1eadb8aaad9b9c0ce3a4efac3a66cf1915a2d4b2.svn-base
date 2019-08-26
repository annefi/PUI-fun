/* ---------------------------------------------------------------------------
   expand_tools.c --- ACE/SWICS: utilities connected to "expanding" of cycles
   1998 by Hefti, University of Michigan (hefti@umich.edu)
   $Id: expand_tools.c,v 1.1.1.1 2000/06/02 13:37:20 jraines Exp $
   -------------------------------------------------------------------------*/

#include <stdio.h>

#include "datatypes.h"
#include "decoded.h"

#include "expand_tools.h"

/* ===========================================================================
** general checks
** ======================================================================== */

/*  --------------------------------------------------------------------------
    ccycg --- quality check: general (not instrument specific)
    ------------------------------------------------------------------------*/
int ccycg(SBCYC *pcyc)
{
  int  ie;
  int  i;

  int  ipqac;

  /* -------------------------------------------------------------------------
  ** reset
  ** -----------------------------------------------------------------------*/

  for(i = 0; i < NEDB; i++) pcyc->abgood[i] = 0;

  /* -------------------------------------------------------------------------
  ** make sure the EDBs which are present look correct
  ** -----------------------------------------------------------------------*/

  for(ie = 0; ie < NEDB; ie++) {

    if( pcyc->abedbfrst[ie][5] == ie ) {

      if( (pcyc->abedbfrst[ie][0] != 0xEB) ||
	  (pcyc->abedbfrst[ie][1] != 0x90) ||
	  (pcyc->abedbfrst[ie][2] != 0xDA) ||
	  (pcyc->abedbfrst[ie][3] != 0x09) ||
	  (pcyc->abedbfrst[ie][4] != 0x84) ||
	  (pcyc->abedbfrst[ie][6] != 0x1C) ) {
	printf("ccycg: Problem with EDB %2d (",ie);
	for(i = 0; i < NEDBFRST; i++) printf("%2.2x ",
					     pcyc->abedbfrst[ie][i]);
	printf(".\n");
	printf("+ %s.\n",zrecid(pcyc));
	return(1);
      }
    } else {

      pcyc->abgood[ie] = 1;
    }
      
  }

  /* -------------------------------------------------------------------------
  ** make sure quality looks good
  ** -----------------------------------------------------------------------*/

  for(ie = 0; ie < NEDB; ie++) {

    if( pcyc->abedbfrst[ie][5] == ie ) {

      if( pcyc->abQAC[ie] ) {
	
	printf("ccycg: L1 QAC says: bad EDB %2d.\n",ie);
	printf("+ %s.\n",zrecid(pcyc));
	pcyc->abgood[ie] = 2;
      }
    }
  }

  /* -------------------------------------------------------------------------
  ** check for EDBs missing in a row
  ** -----------------------------------------------------------------------*/

  ipqac = 0;
  for(ie = 1; ie < NEDB; ie++) {

    if( pcyc->abgood[ie-1] ) /* previous is bad as well */ {
      ipqac++;
    } else /* previous ok */ {
      ipqac = 0;
    }
    if( ipqac > 2 ) {
      printf("ccycg --- more than 3 EDBs in a row missing.\n");
      printf("+ %s.\n",zrecid(pcyc));
      return(1);
    }
  }

  return(0);
}

/*  --------------------------------------------------------------------------
    ccycg_recnrinc --- check for increasing rec number
    ------------------------------------------------------------------------*/
int ccycg_recnrinc(SBCYC *pcyc)
{
  static long loldrecnr = 0;
  int         res;

  if( pcyc->lrecNr > loldrecnr ) {

    res = 0;

  } else {

    printf("ccycg_recnrinc --- rec number not increasing:\n");
    printf("  old: %5ld cur: %5ld time: %s.\n",
	   loldrecnr,
	   pcyc->lrecNr,
	   timstr(pcyc->adtime[0]));
  
    res = 1;
  }

  loldrecnr = pcyc->lrecNr;

  return(res);
}

/*  --------------------------------------------------------------------------
    ccycg_timeinc --- check for increasing s/c readout time
    ------------------------------------------------------------------------*/
int ccycg_timeinc(SBCYC *pcyc)
{
  static double doldtime = 0.0;
  int ie;

  for(ie = 0; ie < NEDB; ie++) {

    if( pcyc->abgood[ie] == 0 ) /* don't check bad EDBs */ {

      if( pcyc->adtime[ie] > doldtime ) {

	doldtime = pcyc->adtime[ie];
      } else {

	printf("ccycg_timeinc --- s/c time not increasing (rec %5ld, %2d):\n",
	       pcyc->lrecNr,ie);
	printf("  old time: %s\n  cur time: %s.\n",
	       timstr(doldtime),
	       timstr(pcyc->adtime[ie]));
  
	return(1);
      }
    }
  }
  return(0);
}

/* ===========================================================================
** SWICS-specific checks
** ======================================================================== */

/*  --------------------------------------------------------------------------
    ccycx --- quality check for SWICS
    ------------------------------------------------------------------------*/
int ccycx(SBCYC *pcyc)
{
  if( pcyc->abgood[22] && pcyc->abgood[42] ) {
    /* (22) PAPS level is needed */
    printf("ccycx --- both EDB 22 and 42 missing. One is needed (PAPS).\n");
    printf("+ %s.\n",zrecid(pcyc));
    return(1);
  }

  if( pcyc->abgood[47] ) {
    /* (47) BR definition is needed */
    printf("xcycx --- needed EDB 47 (BR def) is missing.\n");
    printf("+ %s.\n",zrecid(pcyc));
    return(1);
  }

  if( pcyc->abgood[53] ) {
    printf("xcycx --- needed EDB 53 (mass class) is missing.\n");
    printf("+ %s.\n",zrecid(pcyc));
    return(1);
  }

  if( pcyc->abgood[54] ) {
    printf("xcycx --- needed EDB 54 (m/q class) is missing.\n");
    printf("+ %s.\n",zrecid(pcyc));
    return(1);
  }

  return(0);
}


/*  --------------------------------------------------------------------------
    ccycx_mcplev --- check for desired MCP level
    ------------------------------------------------------------------------*/
int ccycx_mcplev(SBCYC *pcyc, int iexplev)
{
  if( pcyc->abxcmd[LXMCPL] == (8 + iexplev) ) {
    /* 8 is: enable */
    return(0);
  } else {
    printf("ccycx_mcplev --- MCP Level not %d, as expected, but: %d.\n",
	   iexplev,pcyc->abxcmd[LXMCPL]);
    printf("+ %s.\n",zrecid(pcyc));
    return(1);
  }
  return(0);
}

/*  --------------------------------------------------------------------------
    ccycx_pavlev --- check for desired PAPS level
    ------------------------------------------------------------------------*/
int ccycx_pavlev(SBCYC *pcyc, int iexplev)
{
  if( pcyc->abxcmd[LXPAPS] == (iexplev) ) {
    return(0);
  } else {
    printf("ccycx_pavlev --- PAPS Level not %d, as expected, but: %d.\n",
	   iexplev,pcyc->abxcmd[LXPAPS]);
    printf("+ %s.\n",zrecid(pcyc));
    return(1);
  }
  return(0);
}


/*  --------------------------------------------------------------------------
    ccycx_eqhk --- make sure E/q stepping (housekeeping) is ok
    Routine checks for monotonically decreasing HK values.
    ------------------------------------------------------------------------*/
int ccycx_eqhk(SBCYC *pcyc)
{
  int    ie;
  double doldeoq;

  doldeoq = pcyc->afxhk[1][LXGEOQ];

  for(ie = 1; ie < NEDB; ie++) {

    if( pcyc->abgood[ie] == 0 ) /* don't check bad EDBs */ {

      if( pcyc->afxhk[ie][LXGEOQ] > doldeoq ) {

	printf("ccycx_eqhk --- SWICS E/q not decreasing (%2d):",ie);

	for(ie = 0; ie < NEDB; ie++) {
	  if( ie % 15 == 0 ) printf("\n+ ");
	  printf("%4.0f ", pcyc->afxhk[ie][LXGEOQ]);
	}
	printf(".\n");
	printf("+ %s\n",zrecid(pcyc));

	return(1);
      }

      doldeoq = pcyc->afxhk[ie][LXGEOQ];
    }
  }
  return(0);
}

/*  --------------------------------------------------------------------------
    ccycx_eqtabnom --- make sure E/q stepping is nominal
    E/q stepping table from EDBs is compared with known tables.
    ------------------------------------------------------------------------*/
int ccycx_eqtabnom(SBCYC *pcyc, int itab)
{
  int    ie;
  static int ioldtab = XEQTABNOM;
  static BYTE   abnom[XNEQNOMTAB][NXEQ] = {
    {
10,  12, 14, 16, 18, 20, 22, 24, 26, 28, 30, 32, 34, 36, 38, 40,
42,  44, 46, 48, 50, 52, 54, 56, 58, 60, 62, 64, 66, 68, 70, 72,
74,  76, 78, 80, 82, 84, 86, 88, 90, 92, 94, 96, 98,100,102,104,
108,112,116,120,124,128,132,136,140,144,148,152},
    {
12,  14, 16, 18, 20, 22, 24, 26, 28, 30, 32, 34, 36, 38, 40, 42, 
44,  46, 48, 50, 52, 54, 56, 58, 60, 62, 64, 66, 68, 70, 72, 74, 
76,  78, 80, 82, 84, 86, 88, 90, 92, 94, 96, 98,100,102,104,106, 
110,114,118,122,126,129,133,137,141,145,149,152
    }
  };

  if( (itab != XEQTABNOM) && (itab != ioldtab) ) {
    printf("ccycx_eqtabnom --- Using table %d.\n",itab);
    printf("+ %s.\n",zrecid(pcyc));
  }

  ioldtab = itab;

  for(ie = 0; ie < NXEQ; ie++) {
    if( pcyc->abxeqtab[ie] != abnom[itab][ie] ) {
      printf("ccycx_eqtabnom --- SWICS E/q table not nominal: %2d %3d %3d.\n",
	     ie,pcyc->abxeqtab[ie],abnom[itab][ie]);
      printf("+ %s.\n",zrecid(pcyc));
      return(1);
    }
  }
  return(0);
}

/*  --------------------------------------------------------------------------
    ccycx_rates --- consitency checks on sensor rates
    all rates >= 0.0 and DCR >= TCR
    ------------------------------------------------------------------------*/
int ccycx_rates(SBCYC *pcyc)
{
  int  ie;
  int  is;
  long fsr;
  long dcr;
  long tcr;
  long sdr;


  for(ie = 2; ie < 60; ie++) {

    for(is = 0; is < NSEC; is++) /* loop sec */ {

      fsr = pcyc->alxsr[ie][LXFSR][is];
      dcr = pcyc->alxsr[ie][LXDCR][is];
      tcr = pcyc->alxsr[ie][LXTCR][is];
      sdr = pcyc->alxsr[ie][LXSSR][is];
      
      if( (fsr <  0.0) ||
	  (dcr <  0.0) ||
	  (tcr <  0.0) ||
	  (sdr <  0.0) ||
	  /* (fsr <  dcr) || */
	  (dcr <  tcr) ) {
	if( (ie > 1) && (ie < 59) ) {
	  if( (pcyc->alxsr[ie-1][LXFSR][is] > pcyc->alxsr[ie][LXFSR][is]) &&
	      (pcyc->alxsr[ie+1][LXFSR][is] > pcyc->alxsr[ie][LXFSR][is]) ) {

	    /* example of FSR overflow --- keep */
	  }
	} else {

	  printf(
  "ccycx_rates --- EDB %2d Sec %1d FSR %ld DCR %ld TCR %ld SDR %ld.\n",
  ie,is,fsr,dcr,tcr,sdr);

	  for(ie = 2; ie < 60; ie++) {
	    if( (ie - 2) % 10 == 0 ) printf("\n+ ");
	    printf("%ld",pcyc->alxsr[ie][LXFSR][is]);
	    if( (ie - 2) % 10 != 0 ) printf("\t");
	  }
	  printf("\n");
	  printf("+ %s.\n",zrecid(pcyc));
	  return(1);
	}
      }
    }
  }

  return(0);
}


/* ===========================================================================
** SWIMS-specific checks
** ======================================================================== */

/*  --------------------------------------------------------------------------
    ccycm --- quality check for SWIMS
    ------------------------------------------------------------------------*/
int ccycm(SBCYC *pcyc)
{
  if( pcyc->abgood[21] && pcyc->abgood[41] ) {
    /* (21) SWIMS CMD is needed */
    printf("ccycm --- both EDB 21 and 41 are missing. One is needed (%s).\n",
	   "CMD block");
    printf("+ %s.\n",zrecid(pcyc));
    return(1);
  }

  if( pcyc->abgood[35] || pcyc->abgood[36] ) {
    /* (21) SWIMS E/q tab is needed */
    printf("ccycm --- EDB 35 or 36 is missing. Needed for E/q tab.\n");
    printf("+ %s.\n",zrecid(pcyc));
    return(1);
  }

  return(0);
}


/*  --------------------------------------------------------------------------
    ccycm_mcalev --- check for desired MCP level (start MCP)
    ------------------------------------------------------------------------*/
int ccycm_mcalev(SBCYC *pcyc, int iexplev)
{
  if( pcyc->asmcmd[LMAMCA] == (iexplev) ) {
    return(0);
  } else {
    printf("ccycm_mcalev --- Level of Start MCP not %d, but: %d.\n",
	   iexplev,pcyc->asmcmd[LMAMCA]);
    printf("+ %s.\n",zrecid(pcyc));
    return(1);
  }
  return(0);
}

/*  --------------------------------------------------------------------------
    ccycm_mcolev --- check for desired MCP level (Stop MCP)
    ------------------------------------------------------------------------*/
int ccycm_mcolev(SBCYC *pcyc, int iexplev)
{
  if( pcyc->asmcmd[LMAMCO] == (iexplev) ) {
    return(0);
  } else {
    printf("ccycm_mcolev --- Level of Stop MCP not %d, but: %d.\n",
	   iexplev,pcyc->asmcmd[LMAMCO]);
    printf("+ %s.\n",zrecid(pcyc));
    return(1);
  }
  return(0);
}

/*  --------------------------------------------------------------------------
    ccycm_hyplev --- check for desired Level of Hypeerbola
    ------------------------------------------------------------------------*/
int ccycm_hyplev(SBCYC *pcyc, int iexplev)
{
  if( pcyc->asmcmd[LMAHYP] == (iexplev) ) {
    return(0);
  } else {
    printf("ccycm_hyplev --- Level of Hyperbola not %d, but: %d.\n",
	   iexplev,pcyc->asmcmd[LMAHYP]);
    printf("+ %s.\n",zrecid(pcyc));
    return(1);
  }
  return(0);
}

/*  --------------------------------------------------------------------------
    ccycm_eqhk --- make sure SWIMS E/q stepping (housekeeping) is ok
    Routine checks for monotonically decreasing HK values of E/q.
    ------------------------------------------------------------------------*/
int ccycm_eqhk(SBCYC *pcyc)
{
  int    ie;
  double doldeoq;

  doldeoq = pcyc->afmhk[1][LMGEOQ];

  for(ie = 1; ie < NEDB; ie++) {

    if( pcyc->abgood[ie] == 0 ) /* don't check bad EDBs */ {

      if( pcyc->afmhk[ie][LMGEOQ] > doldeoq ) {

	printf("ccycm_eqhk --- SWIMS E/q not decreasing (%2d):",ie);

	for(ie = 0; ie < NEDB; ie++) {
	  if( ie % 15 == 0 ) printf("\n+ ");
	  printf("%4.0f ", pcyc->afmhk[ie][LMGEOQ]);
	}
	printf(".\n");
	printf("+ %s.\n",zrecid(pcyc));

	return(1);
      }

      doldeoq = pcyc->afmhk[ie][LMGEOQ];
    }
  }
  return(0);
}

/*  --------------------------------------------------------------------------
    ccycm_eqtabnom --- make sure SWIMS E/q stepping is nominal
    E/q stepping table from DPU Spare is compared with predefined table.
    ------------------------------------------------------------------------*/
int ccycm_eqtabnom(SBCYC *pcyc, int itab)
{
  int    ie;
  static int ioldtab = MEQTABNOM;
  short  asnom[MNEQNOMTAB][NXEQ] = {
    {
498, 492, 486, 480, 474, 468, 462, 456, 450, 444, 438, 432, 426, 420, 414,
408, 402, 396, 390, 384, 378, 372, 366, 360, 354, 348, 342, 336, 330, 324,
318, 312, 306, 300, 294, 288, 282, 276, 270, 265, 260, 255, 250, 245, 240,
235, 230, 225, 220, 215, 210, 205, 200, 195, 190, 185, 180, 175, 170, 165},
    {
501, 489, 477, 465, 453, 442, 431, 420, 410, 400, 390, 380, 371, 361, 352,
344, 335, 327, 319, 311, 303, 295, 288, 281, 274, 267, 260, 254, 247, 241,
235, 229, 223, 217, 212, 206, 201, 196, 191, 186, 181, 177, 172, 168, 163,
159, 155, 151, 147, 143, 139, 135, 132, 128, 125, 121, 118, 115, 112, 109},
    {
454, 442, 431, 420, 409, 399, 388, 378, 369, 359, 350, 341, 332, 324, 315, 
307, 300, 292, 284, 277, 270, 263, 256, 250, 243, 237, 231, 225, 219, 214,
208, 203, 198, 193, 188, 183, 178, 174, 169, 165, 161, 156, 152, 148, 145,
141, 137, 134, 130, 127, 124, 121, 117, 114, 112, 109, 106, 103, 101,  98},
    {
455, 448, 441, 434, 428, 421, 415, 409, 403, 397, 391, 385, 379, 373, 368,
362, 357, 351, 346, 341, 335, 330, 325, 320, 316, 311, 306, 301, 297, 292, 
288, 284, 279, 275, 271, 267, 263, 259, 255, 251, 247, 243, 239, 236, 232, 
229, 225, 222, 218, 215, 212, 208, 205, 202, 199, 196, 193, 190, 187, 184}
};

  if( (itab < 0) || (itab >= MNEQNOMTAB) ) {
    printf("ccycm_eqtabnom --- Table %d out-of-range.\n",itab);
    return(1);
  }

  if( (itab != MEQTABNOM) && (itab != ioldtab) ) {
    printf("ccycm_eqtabnom --- Using table %d.\n",itab);
    printf("+ %s.\n",zrecid(pcyc));
  }

  ioldtab = itab;


  for(ie = 0; ie < NMEQ; ie++) {
    if( pcyc->asmeqtab[ie] != asnom[itab][ie] ) {
      printf("ccycm_eqtabnom --- SWIMS E/q table not nominal: %2d %3d %3d.\n",
	     ie,pcyc->asmeqtab[ie],asnom[itab][ie]);
      printf("+ %s.\n",zrecid(pcyc));
      return(1);
    }
  }
  return(0);
}



/*  --------------------------------------------------------------------------
    Function: cycok
    Synopsis: check/report problems of binary data
    ------------------------------------------------------------------------*/
int cycok(BYTE abedb[NEDB][NBINEDB], BYTE abQAC[NEDB], SBCYC *pcyc)
{
  int    ie = 0;
  int    ipqac = 0; /* QAC of previous EDB */
  BYTE   abmyQAC[NEDB]; /* my internal list */
  double doldeoq;

  char zreason[6][8] = {"OK","QAC","SYNC","LEN","NUM","XEQ"};

  /* PHA */
  double adwgt[NXBR]; /* weights for each basic range */
  /* limit maximal weight --> work-around */
  double adlim[NXBR] = {900.0,400.0,700.0,700.0};

  int    i;
  int    j;

  ipqac   = 0;

  /* --- get quality --- */

  for(ie = 0; ie < NEDB; ie++) {

    /* reset */
    abmyQAC[ie] = 0;

    /* QAC */
    if(abQAC[ie]) {

      abmyQAC[ie] = 1;

    } else {

      /* sync */
      if((abedb[ie][0] != 0xEB) &&
         (abedb[ie][1] != 0x90) &&
         (abedb[ie][2] != 0xDA)) {
	abmyQAC[ie] = 2;
      } else {
	
	/* length */
	if((abedb[ie][3] != 0x09) &&
	   (abedb[ie][4] != 0x84)) {
	  abmyQAC[ie] = 3;
	} else {
	  
	  /* number */
	  if(abedb[ie][5] != (BYTE)ie) abmyQAC[ie] = 4;
	}
      }
    }
  }

  /* --- check for needed EDBs --- */

  if( abmyQAC[22] ) {
    /* (22) PAPS level is needed */
    printf("cycok --- needed EDB 22 is missing (%s).\n",
	   zreason[abmyQAC[22]]);
    printf("+ %s.\n",zrecid(pcyc));
    return(1);
  }

  if( abmyQAC[47] ) {
    /* (47) BR definition is needed */
    printf("cycok --- needed EDB 47 is missing (%s).\n",
	   zreason[abmyQAC[47]]);
    printf("+ %s.\n",zrecid(pcyc));
    return(1);
  }

  /* --- check for EDBs missing in a row --- */

  for(ie = 1; ie < NEDB; ie++) {

    if( abmyQAC[ie-1] ) /* previous is bad as well */ {
      ipqac++;
    } else /* previous ok */ {
      ipqac = 0;
    }
    if( ipqac > 2 ) {
      printf("cycok --- more than 3 EDBs in a row missing.\n");
      printf("+ %s.\n",zrecid(pcyc));
      return(1);
    }
  }


  /* --- check for increasing SWICS E/q--- */

  doldeoq = pcyc->afxhk[2][LXGEOQ];

  for(ie = 3; ie < NEDB; ie++) {

    if( abmyQAC[ie] == 0 ) /* don't check bad EDBs */ {

      if( pcyc->afxhk[ie][LXGEOQ] > doldeoq ) {

	printf("cycok --- SWICS E/q not decreasing (%2d):",ie);

	for(ie = 0; ie < NEDB; ie++) {
	  if( ie % 15 == 0 ) printf("\n+ ");
	  printf("%4.0f ", pcyc->afxhk[ie][LXGEOQ]);
	}
	printf(".\n");
	printf("+ %s.\n",zrecid(pcyc));

	return(1);
      }

      doldeoq = pcyc->afxhk[ie][LXGEOQ];
    }
  }

  /* --- check MR of oxygen for outliers --- */

  for(j = 0; j < NSEC; j++) {
    for(ie = 0; ie < NEDB; ie++) {
      if( pcyc->alxmr[ie][4][j] > 5000 ) {
	printf("cycok --- EDB %2d SEC %2d: MR(O6) > 5000\n",
	       ie,j);
	printf("+ %s.\n",zrecid(pcyc));
	return(1);
      }
    }
  }

  /* --- check NPHA/BR ratio --- */

  for(ie = 0; ie < NEDB; ie++) {

    for(i = 0; i < NXBR; i++) {

      adwgt[i] = 0.0;
      
      if( pcyc->asxnr[ie][i][NSEC] > 0 ) {

	adwgt[i] = 
	  (double)pcyc->alxbr[ie][i][NSEC] /
	  (double)pcyc->asxnr[ie][i][NSEC];

	if(adwgt[i] > adlim[i]) {

	  printf("%s %2d %1d %8.2f BR: %5ld PH: %5d\n",
		 "cycok --- Check weight: ",
		 ie,i,adwgt[i],pcyc->alxbr[ie][i][NSEC],
		 pcyc->asxnr[ie][i][NSEC]);

	  printf("+ %s.\n",zrecid(pcyc));
	  return(1);
	}
      }
    }
  }

  return(0);
}

/*  --------------------------------------------------------------------------
    Function: nc_readcyc
    Synopsis: read 60 EDBs out of netCDF file
    ------------------------------------------------------------------------*/
void nc_readcyc(int edbid,int ic,BYTE abedb[NEDB][NBINEDB],
		double adtime[NEDB],BYTE abQAC[NEDB])
{
  int vid;    /* variable ids */
  int itmp;

  size_t aidx3[3];
  size_t aidx2[2];
  size_t acnt3[3];
  size_t acnt2[2];

  /* --- get EDBs --- */

  itmp = nc_inq_varid (edbid, "cyc", &vid);
  if (itmp != NC_NOERR) nc_handle_error(itmp,__LINE__);

  aidx3[0] = ic; acnt3[0] =       1; /* cyc */
  aidx3[1] =  0; acnt3[1] =    NEDB; /* EDB */
  aidx3[2] =  0; acnt3[2] = NBINEDB; /* EDBbytes */

  itmp = nc_get_vara_uchar(edbid, vid, aidx3, acnt3,&abedb[0][0]);
  if (itmp != NC_NOERR) nc_handle_error(itmp,__LINE__);

  /* get time */

  itmp = nc_inq_varid (edbid, "time", &vid);
  if (itmp != NC_NOERR) nc_handle_error(itmp,__LINE__);

  aidx2[0] = ic; acnt2[0] =       1; /* cyc */
  aidx2[1] =  0; acnt2[1] =    NEDB; /* EDB */

  itmp = nc_get_vara_double(edbid,vid,aidx2,acnt2,adtime);
  if (itmp != NC_NOERR) nc_handle_error(itmp,__LINE__);

  /* get QAC */

  itmp = nc_inq_varid (edbid, "QAC", &vid);
  if (itmp != NC_NOERR) nc_handle_error(itmp,__LINE__);

  aidx2[0] = ic; acnt2[0] =       1; /* cyc */
  aidx2[1] =  0; acnt2[1] =    NEDB; /* EDB */

  itmp = nc_get_vara_uchar(edbid,vid, aidx2, acnt2,&abQAC[0]);
  if (itmp != NC_NOERR) nc_handle_error(itmp,__LINE__);

  return;
}

/*  --------------------------------------------------------------------------
    Function: nc_handle_error
    Synopsis: for netcdf problems
    ------------------------------------------------------------------------*/
void nc_handle_error(int itmp, int line)
{
  if (itmp != NC_NOERR) {
    printf("expand_tools --- %4d %s.\n", line,nc_strerror(itmp));
    exit(1);
  }
}

/* ---------------------------------------------------------------------------
   zrecid --- record identifier as string
   -------------------------------------------------------------------------*/
char *zrecid(SBCYC *pcyc)
{
  static char zrid[256];

  sprintf(zrid,"rec %ld, %s",pcyc->lrecNr,timstr(pcyc->adtime[0]));
  return(zrid);
}
