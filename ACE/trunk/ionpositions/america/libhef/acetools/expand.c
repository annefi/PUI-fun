/* ---------------------------------------------------------------------------
   expand.c --- expand ACE EDB on-the-fly (in memory)
   (c) 1998/1999 Simon Hefti (hefti@umich.edu)
   $Id: expand.c,v 1.6 2004/05/20 14:58:18 jraines Exp $
  ------------------------------------------------------------------------- */

static char* rcsid =
"$Id: expand.c,v 1.6 2004/05/20 14:58:18 jraines Exp $";

#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <string.h> /* memset */

#include "acetools.h"

/*  --------------------------------------------------------------------------
    expand --- decode ACE EDB
    Input:  array of bytes of 60 EDBs, corresponding time and QAC.
    Output: Structure containing decoded data.
    ----------------------------------------------------------------------- */
int expand(BYTE abedb[NEDB][NBINEDB], double adtime[NEDB], 
           BYTE abQAC[NEDB], SBCYC *pcyc)
{
  int   i       =   0;
  int   ie      =   0;
  int   j       =   0;
  int   itmp    =   0;
  int   ipos    =   0;
  int   isec    =   0;

  BYTE  *pabdum;
  CPHA  stcpha;
  MPHA  stmpha;

  long  ltmp;

  // printf("DBG expand --- Starting.\n");

  /* -------------------------------------------------------------------------
  ** reset cyc
  ** -----------------------------------------------------------------------*/

  /* printf("DBG expand --- sizeof(cyc) = %d.\n",sizeof(*pcyc)); */
  memset(pcyc,0,sizeof(*pcyc));

  /* test whether data is resetted */

  for(ie = 0; ie < NEDB; ie++) {
    if( pcyc->asxNof[ie] ||
	pcyc->asxnr[ie][1][NSEC] ) {
      printf("expand --- cyc not properly resetted !\n");
    }
  }

  /* -------------------------------------------------------------------------
  ** doc struct version
  ** -----------------------------------------------------------------------*/

  pcyc->sver = DSTRUCTVER;
  // printf("DBG expand --- Structure Version %d.\n",pcyc->sver);

  /* -------------------------------------------------------------------------
  ** copy information from L1 file
  ** -----------------------------------------------------------------------*/

  for( ie = 0; ie < NEDB; ie++) {
    pcyc->abQAC[ie]  = abQAC[ie];
    pcyc->adtime[ie] = adtime[ie];

    /* copy first few bytes */
    for(i = 0; i < NEDBFRST; i++) pcyc->abedbfrst[ie][i] = abedb[ie][i];
    /*
    printf("DBG: first few bytes of EDB %2d: ",ie);
    for(i = 0; i < NEDBFRST; i++) printf("%2.2x ",abedb[ie][i]);
    printf("\n");
    for(i = 0; i < NEDBFRST; i++) printf("%2.2x ",pcyc->abedbfrst[ie][i]);
    printf("\n");
    */
  }

  /* -------------------------------------------------------------------------
  ** loop over EDBs
  ** -----------------------------------------------------------------------*/

  for( ie = 0; ie < NEDB; ie++) {

    // printf("DBG expand --- EDB %d.\n",ie);

    /* -----------------------------------------------------------------------
    ** check sync word and EDB number
    ** ---------------------------------------------------------------------*/

    if( (abQAC[ie]    == 0 ) &&
        (abedb[ie][0] == 0xEB ) &&
        (abedb[ie][1] == 0x90 ) &&
        (abedb[ie][2] == 0xDA ) &&
        (abedb[ie][5] == ie) ) /* QAC/sync/number */ { 

      /* --- everything is fine --- */

      /* printf("expand --- ie: %2d %2.2x %2.2x %2.2x\n",
             ie,abedb[ie][0],abedb[ie][1],abedb[ie][2]);
      */
      
      /* -------------------------------------------------------------------
      ** for now we assume: usefull data
      ** -----------------------------------------------------------------*/

      pcyc->abgood[ie] = 0;

      /* -------------------------------------------------------------------
      ** get EDB structure
      ** -----------------------------------------------------------------*/

      gedbpos(abedb[ie],pcyc->aspos[ie]);


      /* -------------------------------------------------------------------
      ** get long EDB number
      ** -----------------------------------------------------------------*/

      // printf("DBG expand --- get EDB number.\n");

      itmp         = 34;
      pcyc->lrecNr =  0L;
      pcyc->lrecNr = (abedb[ie][itmp+11] << 16) |
        (abedb[ie][itmp+12] <<  8) | (abedb[ie][itmp+13]);

      pcyc->alNr[ie] = pcyc->lrecNr * 60L + (long)ie;

/*       printf("DBG expand --- recNr: %ld %ld\n", */
/* 	     pcyc->lrecNr, */
/* 	     pcyc->alNr[ie]); */

      /* -------------------------------------------------------------------
      ** get S3DPU HK block
      ** -----------------------------------------------------------------*/

      for(i = 0; i < NDHK; i++) {
	itmp = abedb[ie][pcyc->aspos[ie][LDHK][0] +  i];
	pcyc->abs3dpuhk[ie][i] = (BYTE)itmp;
      }

      /* -------------------------------------------------------------------
      ** get SEPICA HK block
      ** -------------------------------------------------------------------
      ** Block is commutated in NSHK (22) byte chunks over 5 EDBs.
      ** -----------------------------------------------------------------*/

      for(i = 0; i < NSHK; i++) {
	itmp = abedb[ie][pcyc->aspos[ie][LSHK][0] +  i];
	//pcyc->abshk[ie][i + (ie % 5)*NSHKPEREDB] = (BYTE)itmp;
	pcyc->abshk[ie][i] = (BYTE)itmp;
      }

      /* -------------------------------------------------------------------
      ** get SWICS/Eqtab (E/q CMD values from DPU spare block)
      ** -----------------------------------------------------------------*/

      if( ie == 46 ) {
        for(i = 0; i < NXEQ; i++) {
          itmp = abedb[ie][pcyc->aspos[ie][LDSPARE][0] +  i];
          /* account for missing bits */
          if( itmp > 127 ) itmp -= 103;
          /* reverse order */
          pcyc->abxeqtab[i] = (BYTE)itmp;
        }
      }

      /* -------------------------------------------------------------------
      ** get SWIMS/Eqtab (E/q CMD values from DPU spare block)
      ** -----------------------------------------------------------------*/

      if( (ie == 35) || (ie == 36) ) {
          
        ipos = pcyc->aspos[ie][LDSPARE][LTLMPOS];

        for(i = 0;i < 30; i++) {
          ltmp = 0;
          ltmp = (abedb[ie][ipos +  i*2] << 8) | 
                 (abedb[ie][ipos +  i*2 + 1]);
          pcyc->asmeqtab[i + (ie == 35) * 30] = (short)ltmp;
        }
      }

      /* -------------------------------------------------------------------
      ** get SWICS CMD block (PAPS command level)
      ** -----------------------------------------------------------------*/
      if( (ie == 22) || (ie == 42) ) {
        for(i = 0; i < NXCMD; i++) {
          pcyc->abxcmd[i] = 
            abedb[ie][pcyc->aspos[ie][LDSPARE][LTLMPOS] +  i];
        }
      }

      /* -------------------------------------------------------------------
      ** get SWIMS CMD block
      ** -----------------------------------------------------------------*/
      if( (ie == 21) || (ie == 41) ) {

        for(i = 0; i < 14; i++) {
          pcyc->asmcmd[i] = 
            abedb[ie][pcyc->aspos[ie][LDSPARE][LTLMPOS] + i];
        }

        for(i = 14; i < NMCMD; i++) {
          pcyc->asmcmd[i] = 
            abedb[ie][pcyc->aspos[ie][LDSPARE][LTLMPOS] + i];
        }
      }

      /* -------------------------------------------------------------------
      ** get SWIMS Status bytes
      ** -----------------------------------------------------------------*/
      for(i = 0; i < NMSTATUS; i++) {
	pcyc->abmstatus[i] = 
	  abedb[ie][pcyc->aspos[ie][LMSTATUS][LTLMPOS] + i];
      }

      /* -------------------------------------------------------------------
      ** get SWICS CTRL block (limits and deltas)
      ** -----------------------------------------------------------------*/

      if( (ie == 25) || (ie == 45) ) {
        for(i = 0; i < NXCTRL; i++) {
          pcyc->abxctrl[i] = 
            abedb[ie][pcyc->aspos[ie][LDSPARE][LTLMPOS] +  i];
        }
      }

      /* -------------------------------------------------------------------
      ** get SWIMS CTRL block (limits and deltas)
      ** -----------------------------------------------------------------*/

      if( (ie == 24) || (ie == 44) ) {
        for(i = 0; i < NMCTRL; i++) {
          pcyc->abmctrl[i] = 
            abedb[ie][pcyc->aspos[ie][LDSPARE][LTLMPOS] +  i];
        }
      }

      /* -------------------------------------------------------------------
      ** SWICS HK
      ** -----------------------------------------------------------------*/

      for(i = 0; i < NXHK; i++) {
               
        pcyc->afxhk[ie][i] = 
          (float)abedb[ie][pcyc->aspos[ie][LCHK][0] +  i];
      }

      /* PAPS */
      pcyc->afxhk[ie][LXGPAV] =
        (float)abedb[ie][pcyc->aspos[ie][LCHK][0] +  LXGPAV] * 0.150;

      /* MCP */
      pcyc->afxhk[ie][LXPMCP] = -4.94370 +
        (float)abedb[ie][pcyc->aspos[ie][LCHK][0] +  LXPMCP] * 0.03905;

      /* main current */
      pcyc->afxhk[ie][LXGPI1] =
        (float)abedb[ie][pcyc->aspos[ie][LCHK][0] +  LXGPI1] * 2.0;

      /* Temp */
      pcyc->afxhk[ie][LXGTE1] =
        convTmp(abedb[ie][pcyc->aspos[ie][LCHK][0] +  LXGTE1]);

      pcyc->afxhk[ie][LXGTE2] =
        convTmp(abedb[ie][pcyc->aspos[ie][LCHK][0] +  LXGTE2]);

      pcyc->afxhk[ie][LXPTE1] =
        convTmp2(abedb[ie][pcyc->aspos[ie][LCHK][0] + LXPTE1]);

      pcyc->afxhk[ie][LXPTE2] =
        convTmp2(abedb[ie][pcyc->aspos[ie][LCHK][0] + LXPTE2]);

      /* --- E/q --- */

      /* gain bit */

      if( abedb[ie][pcyc->aspos[ie][LCHK][0] + 24] & 0001 ) {
        pcyc->afxhk[ie][LXGEOQ] *= 50.0;
      } else {
        pcyc->afxhk[ie][LXGEOQ] *=  6.25;
      }

      /* -------------------------------------------------------------------
      ** SWICS Sensor Rates (FSR,DCR etc)
      ** -----------------------------------------------------------------*/

      /* --- get position of Sensor Rates in EDB --- */

      ipos = pcyc->aspos[ie][LCMONITOR][LTLMPOS];

      for( i = 0; i < NXSR; i++) {

        pcyc->alxsr[ie][i][NSEC] = 0;

        /* sectors */

        for(j = 0; j < NSEC; j++) {

          ltmp = decmpa(abedb[ie][ipos + i*8 + j]);
	  if( ltmp < 0 ) {
	    ltmp = 0;
	    printf("expand --- Decomp. Problem for SWICS SR %d, sec %d\n",
		   i,j);
	    pcyc->sdecomp_problem++;
	  }
	  pcyc->alxsr[ie][i][NSEC - 1 - j] = ltmp;
	  /* sector inverted (by subtracting from 7) to align
	     max. sector from SR and PHA.  Also corresponds with 
	     info from Mark Popecki (UNH, Sepica) that the sun pulse
	     occurs at the end of sector 7, 135 deg after S/C +X
	     crosses Earth-Sun line.

	     J. Raines, 8Oct2002
	  */
          pcyc->alxsr[ie][i][NSEC] += pcyc->alxsr[ie][i][j];

        }
      }

      /* -------------------------------------------------------------------
      ** SWIMS Sensor Rates (FSR etc)
      ** -----------------------------------------------------------------*/

      ipos = pcyc->aspos[ie][LMMONITOR][LTLMPOS];

      for( i = 0; i < NMSR; i++) {

	// printf("DBG expand --- trying on SWIMS rate %d\n",i);

	pcyc->almsr[ie][i][NSEC] = 0;

	for(j = 0; j < 8; j++) {

	  ltmp = decmpa(abedb[ie][ipos + i*8 + j]);

	  if( ltmp < 0 ) {
	    ltmp = 0;
	    printf("expand --- Decomp. Problem for SWIMS rate %d, sec %d\n",
		   i,j);
	    pcyc->sdecomp_problem++;
	  }
	  pcyc->almsr[ie][i][j] = ltmp;
	  //pcyc->almsr[ie][i][NSEC] += pcyc->almsr[ie][LMFSR][j];
	  pcyc->almsr[ie][i][NSEC] += pcyc->almsr[ie][i][j];
	}
      }

      /* -------------------------------------------------------------------
      ** get DPU classification parameters: SWICS/mass
      ** -----------------------------------------------------------------*/

      if( ie == 53 ) vxmascla(abedb[ie],pcyc);

      /* -------------------------------------------------------------------
      ** get DPU classification parameters: SWICS/m/q
      ** -----------------------------------------------------------------*/

      if( ie == 54 ) vxmoqcla(abedb[ie],pcyc);

      /* -------------------------------------------------------------------
      ** get SWICS basic rates corners
      ** -----------------------------------------------------------------*/

      if( ie == 47 ) vxbrtab(abedb[ie],pcyc);

      /* -------------------------------------------------------------------
      ** get SWICS matrix rates corners
      ** -----------------------------------------------------------------*/

      if( (ie == 48) || (ie == 49) ) vxmrtab(abedb[ie],pcyc);

      /* -------------------------------------------------------------------
      ** get SWICS PHA
      ** -----------------------------------------------------------------*/

      itmp = (int)(pcyc->aspos[ie][LCPHA][LTLMLEN] / 3);
      pcyc->asxNof[ie] = (short)itmp;

      for(i = 0; i <  pcyc->asxNof[ie]; i++) {

        ipos   = pcyc->aspos[ie][LCPHA][LTLMPOS] +
                 pcyc->aspos[ie][LCPHA][LTLMLEN] - 3 - i*3;

        pabdum = &(abedb[ie][ipos]);


        deccpha(pabdum,&stcpha);
            
        pcyc->abxsec[ie][i] = (BYTE)stcpha.sector;
        pcyc->abxdid[ie][i] = (BYTE)stcpha.range;
        pcyc->abxesd[ie][i] = (BYTE)stcpha.ESSD;
        pcyc->asxtof[ie][i] = (short)stcpha.TOF;
      }

      /* -------------------------------------------------------------------
      ** SWICS Matrix and Basic Rates
      ** -----------------------------------------------------------------*/

      ipos =  pcyc->aspos[ie][LCBASIC][LTLMPOS];

      //printf("expand -D- trying other decomp. codes for MR\n");
      for(i = 0; i < NXMR; i++ ) /* loop rates */ {
        
        pcyc->alxmr[ie][NXMR-1-i][NSEC] = 0L;

        for(j = 0; j < NSEC; j++) /* loop sectors */ {

          ltmp = decmpc(abedb[ie][ipos + i*NSEC + j]);
	  if( ltmp < 0 ) {
	    ltmp = 0;
	    printf("expand --- Decomp. Problem for SWICS MR %d, sec %d\n",
		   i,j);
	    pcyc->sdecomp_problem++;
	  }
          pcyc->alxmr[ie][NXMR-1-i][NSEC-1-j] = ltmp; // back to
						      // orig. JR, 8Oct2002
          /* sum */
          pcyc->alxmr[ie][NXMR-1-i][NSEC]    += ltmp;
        }
      }

      /* basic rates */

      for(i = 0; i < NXBR; i++ ) /* loop rates */ {

        /* reset sum */
        pcyc->alxbr[ie][NXBR-1-i][NSEC] = 0L;

        for(j = 0; j < NSEC; j++) /* loop sectors */ {

          ltmp = decmpa(abedb[ie][ipos + (i+NXMR)*NSEC + j]);
	  /* Note: NXMR is correct here -----^
	           SWICS has 4 * 8 Basic Rates and 8 * 8 Matrix Rates
		   ( = 96) in one block called "C_Basic" */
	  if( ltmp < 0 ) {
	    ltmp = 0;
	    printf("expand --- Decomp. Problem for SWICS BR %d, sec %d\n",
		   i,j);
	    pcyc->sdecomp_problem++;
	  }
	  pcyc->alxbr[ie][NXBR-1-i][NSEC-1-j] = ltmp; // back to
						      // orig. JR, 8Oct2002

          /* sum */
          pcyc->alxbr[ie][NXBR-1-i][NSEC]    += ltmp;
        }
      }

      /* -------------------------------------------------------------------
      ** get SWIMS TOF histograms
      ** -----------------------------------------------------------------*/
      if( (ie > 0) && (ie < 30) ) {
        for(i = 0; i < NMTOFPEREDB; i++) {
	  /* Note: I just _assume_ that SWIMS uses Decompr. Code A. */
	  ltmp = decmpa(abedb[ie][pcyc->aspos[ie][LMTOF][LTLMPOS] + 
				 i + ie * NMTOFPEREDB]);
          pcyc->almtof1[i] = ltmp;

        }
      }
      if( (ie >= 30) && (ie < 60) ) {
        for(i = 0; i < NMTOFPEREDB; i++) {
	  /* Note: I just _assume_ that SWIMS uses Decompr. Code A. */
	  ltmp = decmpa(abedb[ie][pcyc->aspos[ie][LMTOF][LTLMPOS] + 
				 i + (ie-30) * NMTOFPEREDB]);
          pcyc->almtof2[i] = ltmp;
        }
      }

      /* -------------------------------------------------------------------
      ** SWIMS Basic Rates
      ** -----------------------------------------------------------------*/

      // printf("DBG expand --- Starting to access SWIMS BR.\n");

      ipos =  pcyc->aspos[ie][LMBASIC][LTLMPOS];


      for(i = 0; i < NMBR; i++ ) /* loop rates */ {

        /* reset sum */

        pcyc->almbr[ie][NMBR-1-i][NSEC] = 0L;

        for(j = 0; j < NSEC; j++) /* loop sectors */ {

	  //printf("DBG expand --- EDB %2d BR %1d SEC %1d ipos %3d pos %3d.\n",
	  // ie,i,j,ipos,ipos + i * NSEC + j);

          ltmp = decmpa(abedb[ie][ipos + i * NSEC + j]);
	  /* Note: I just _assume_ that SWIMS uses Decompr. Code A. */

	  if( ltmp < 0 ) {
	    ltmp = 0;
	    printf("expand --- Decomp. Problem for SWIMS BR %d, sec %d\n",
		   i,j);
	    pcyc->sdecomp_problem++;
	  }

          pcyc->almbr[ie][NMBR-1-i][NSEC-1-j] = ltmp;
          /* sum */
          pcyc->almbr[ie][NMBR-1-i][NSEC]    += ltmp;
        }
      }

      /* -------------------------------------------------------------------
      ** get SWIMS HK
      ** -----------------------------------------------------------------*/

      /* Hyperbola */
      pcyc->afmhk[ie][LMVHPS] =
        (float)abedb[ie][pcyc->aspos[ie][LMHK][0] +  LMVHPS] * 0.150;

      /* MCPs */
      pcyc->afmhk[ie][LMVMCA] =
        (float)abedb[ie][pcyc->aspos[ie][LMHK][0] +  LMVMCA] * 15.0e-3;

      pcyc->afmhk[ie][LMVMCO] =
        (float)abedb[ie][pcyc->aspos[ie][LMHK][0] +  LMVMCO] * 15.0e-3;


      /* Vf */
      ltmp = 0;
      ltmp = 
        (abedb[ie][pcyc->aspos[ie][LMHK][0] + LMGV_F + 0] << 8) |
        (abedb[ie][pcyc->aspos[ie][LMHK][0] + LMGV_F + 1]);

      ltmp = getbits(ltmp,0+16,12);

      pcyc->afmhk[ie][LMGV_F] = - 5.0 + 
        (float)ltmp * 0.00244140625;

      /* main current */
      pcyc->afmhk[ie][LMGPI1] =
        (float)abedb[ie][pcyc->aspos[ie][LMHK][0] +  LMGPI1] * 2.0;

      /* Temp */
      pcyc->afmhk[ie][LMGTE1] =
        convTmp(abedb[ie][pcyc->aspos[ie][LMHK][0] +  LMGTE1]);

      pcyc->afmhk[ie][LMGTE2] =
        convTmp(abedb[ie][pcyc->aspos[ie][LMHK][0] +  LMGTE2]);

      pcyc->afmhk[ie][LMVTE1] =
        convTmp(abedb[ie][pcyc->aspos[ie][LMHK][0] +  LMVTE1]);

      pcyc->afmhk[ie][LMVTE2] =
        convTmp(abedb[ie][pcyc->aspos[ie][LMHK][0] +  LMVTE2]);


      /* -------------------------------------------------------------------
      ** get SWIMS PHA
      ** -----------------------------------------------------------------*/

      itmp = (int)(pcyc->aspos[ie][LMPHA][LTLMLEN] / 6);
      pcyc->asmNof[ie] = (short)itmp;

      for(i = 0; i <  pcyc->asmNof[ie]; i++) {

        ipos   = pcyc->aspos[ie][LMPHA][LTLMPOS] +
                 pcyc->aspos[ie][LMPHA][LTLMLEN] - 6 - i*6;

        /* === W R O N G ===
         *
         * ipos   = pcyc->aspos[ie][LMPHA][LTLMPOS] + i*6;
         */

        pabdum = &(abedb[ie][ipos]);

        decmpha(pabdum,&stmpha);
            
        pcyc->abmsec[ie][i] = (BYTE)stmpha.sector;
        pcyc->abmdid[ie][i] = (BYTE)stmpha.range;
        pcyc->asmsta[ie][i] = (short)stmpha.amp;
        pcyc->asmak1[ie][i] = (short)stmpha.k1;
        pcyc->asmak2[ie][i] = (short)stmpha.k2;
        pcyc->asmtof[ie][i] = (short)stmpha.tof;

      }
    }
  }

  /* -------------------------------------------------------------------------
  ** SWICS E/q
  ** ---------------------------------------------------------------------- */

  for(ie = 0; ie < NXEQ; ie++) {
    pcyc->afxeoqdpu[NXEQ-1-ie] = dswxeoq(ie,pcyc->abxeqtab,pcyc->adcnq);
  }

  for(ie = 0; ie < NXEQ; ie++) {
    pcyc->afxeoqaux[NXEQ-1-ie] = pcyc->afxeoqdpu[NXEQ-1-ie] / 4.15;
  }

  /* -------------------------------------------------------------------------
  ** SWICS PAPS
  ** ---------------------------------------------------------------------- */

  pcyc->fxpav = dswxpal(pcyc->abxcmd[LXPAPS],0,pcyc->adcnq);

  /* -------------------------------------------------------------------------
  ** SWIMS E/q
  ** ---------------------------------------------------------------------- */

  for(ie = 0; ie < NMEQ; ie++) {

    /* from HK */
    itmp =  abedb[ie][pcyc->aspos[ie][LMHK][0] +  LMGEOQ + 0] * 16 +
      (abedb[ie][pcyc->aspos[ie][LMHK][0] +  LMGEOQ + 1]/16 && 15 );
    pcyc->afmhk[ie][LMGEOQ] = 2.975 * itmp;

    /* from eqtab (DPU values) */
    pcyc->afmeoqdpu[ie] = 1.0e-3 * 
      (69.8 + 0.119 * (double)pcyc->asmeqtab[ie] +
       0.048 * dsqr((double)pcyc->asmeqtab[ie]));
  }

  /* -------------------------------------------------------------------------
  ** classify SWICS PHA
  ** ---------------------------------------------------------------------- */

  vxclassify(pcyc);

  /* -------------------------------------------------------------------------
  ** weighting with Basic Rates (SWICS)
  ** ---------------------------------------------------------------------- */
  for(ie = 0; ie < NXEQ; ie++) {
    for(i = 0; i < NXBR; i++) {

      pcyc->afxwgt[ie][i] = 0.0;

      if( pcyc->asxnr[ie][i][NSEC] > 0 ) {

	pcyc->afxwgt[ie][i] = 
	  (float)pcyc->alxbr[ie][i][NSEC] /
	  (float)pcyc->asxnr[ie][i][NSEC];
      }
    }
  }

  /* -------------------------------------------------------------------------
     SWIMS: count PHA's in each range
     ---------------------------------------------------------------------- */

  // printf("DBG expand --- Start SWIMS PHA counting.\n");

  for(ie = 0; ie < NMEQ; ie++) {

    /* .......................................................................
       reset
       .................................................................... */
    for(i = 0; i < NMBR; i++) {

      for(j = 0; j < (NSEC + 1); j++) pcyc->asmnr[ie][i][j] = 0;
    }

    /* .......................................................................
       count
       .................................................................... */


    for(j = 0; j < pcyc->asmNof[ie]; j++) {

      itmp = (int)pcyc->abmdid[ie][j]; // BR range
      isec = (int)pcyc->abmsec[ie][j]; // sector

      if( (itmp >= 0) && (itmp < 4) ) {

	if( (isec >= 0) && (isec < 8) ) {

	  pcyc->asmnr[ie][itmp][isec]++;
	  pcyc->asmnr[ie][itmp][NSEC]++; /* NSEC holds sum over sectors */
	} else {

	  printf("expand --- Problem with SWIMS BR weight (sector OOR).\n");
	  printf("           sector %d.\n",itmp);

	} 

      } else {

	printf("expand --- Problem with SWIMS BR weight (range OOR).\n");
	printf("           range %d.\n",itmp);
      }
      
    }
  }


  // printf("DBG expand --- Start SWIMS BR weight.\n");

  /* -------------------------------------------------------------------------
     weighting with Basic Rates (SWIMS)
     ---------------------------------------------------------------------- */

  for(ie = 0; ie < NMEQ; ie++) {
    for(i = 0; i < NMBR; i++) {

      pcyc->afmwgt[ie][i] = 0.0;

      if( pcyc->asmnr[ie][i][NSEC] > 0 ) {

	pcyc->afmwgt[ie][i] = 
	  (float)pcyc->almbr[ie][i][NSEC] /
	  (float)pcyc->asmnr[ie][i][NSEC];
      }
    }
  }

  return(0);
}

/*  --------------------------------------------------------------------------
    Function: ddpudbl
    Synopsis: represent DPU variable as double
    ------------------------------------------------------------------------*/
double ddpudbl(int idx, BYTE abedb[NBINEDB], double dconv)
{
  long   ltmp = 0L;
  double dres = 0.0;

  ltmp = 0L;
  ltmp = (abedb[idx + 0] << 24) | (abedb[idx + 1] << 16) |
         (abedb[idx + 2] <<  8) | (abedb[idx + 3]);

  dres = ltmp / ((double)(1L << 16)) / dconv;

  return(dres);
}

/*  --------------------------------------------------------------------------
    Function: vxclassify
    Synopsis: classify SWICS PHA data using DPU simulator
    ------------------------------------------------------------------------*/
void vxclassify(SBCYC *pcyc)
{
  int  ie = 0;
  int  j  = 0;
  int  k  = 0;
  int  itmp = 0;
  int  isec = 0;
  BYTE bstp = 0;
  BYTE bmas;
  BYTE bmoq;

  double dpav;
  double deoq;
  double dw;

  /* -------------------------------------------------------------------
  ** SWICS PHA classification
  ** -----------------------------------------------------------------*/

  dpav = dswxpal(pcyc->abxcmd[LXPAPS],0,pcyc->adcnq);

  for(ie = 0; ie < NXEQ; ie++) /* loop EDBs (ie) */ {

    if( pcyc->asxNof[ie] ) /* there are PHAs */ {

      bstp = 59 - (BYTE)((ie + NXEQ - 1) % NXEQ);

      deoq = dswxeoq(bstp,pcyc->abxeqtab, pcyc->adcnq);

      dw   = dpav + deoq;

      if( dw > 0.0 ) /* prevent ln(0) */ {

        dw = log(dw);
        for(j = 0; j < pcyc->asxNof[ie]; j++) /* loop words (j) */ {

          pcyc->afxmoq[ie][j] = dswxlnmq(dw,
                                         pcyc->asxtof[ie][j],
                                         pcyc->adcnq);

          pcyc->afxmas[ie][j] = dswxlnm(pcyc->asxtof[ie][j],
                                        pcyc->abxesd[ie][j],
                                        pcyc->adcnm);

          bmoq = (BYTE)pcyc->afxmoq[ie][j];
          bmas = (BYTE)pcyc->afxmas[ie][j];

          /* --- Range --- */
          
          /* according to Reiche ranges are always "inclusive".
          ** --- Tel, 14-Apr-1998 */


          /* Error Range */

          for(k = 0; k < NXBRBOX; k++) {

            itmp = pcyc->abxbrtab[k][LXBOX];

            if( itmp != 255) {

              /* 255 is "void" code */

              if( (bmas >= pcyc->abxbrtab[k][LXMN]) &&
                  (bmas <= pcyc->abxbrtab[k][LXMX]) &&
                  (bmoq >= pcyc->abxbrtab[k][LXQN]) &&
                  (bmoq <= pcyc->abxbrtab[k][LXQX]) ) {
                pcyc->abxrng[ie][j] = itmp;
              }
            }
          }
        }

        /* -------------------------------------------------------------------
        ** count PHA's in each range
        ** ---------------------------------------------------------------*/

        for(k = 0; k < NXBR; k++) 
          for(j = 0; j < (NSEC + 1); j++) pcyc->asxnr[ie][k][j] = 0;

        for(j = 0; j < pcyc->asxNof[ie]; j++) {
          itmp = (int)pcyc->abxrng[ie][j];
          isec = (int)pcyc->abxsec[ie][j];
          pcyc->asxnr[ie][itmp][isec]++;
          pcyc->asxnr[ie][itmp][NSEC]++; /* NSEC holds sum over sectors */
        }
      }
    }
  }

  /* printf("expand.c --- classification done.\n"); */
  return;
}


/*  --------------------------------------------------------------------------
    Function: g3edbpos
    Synopsis: Get structure of ACE/S3 EDB
    ------------------------------------------------------------------------*/
void gedbpos(BYTE abedb[NBINEDB],short aspos[NLOC][2])
{
  int itmp = 0;
  int i;

  /*
  printf("DBG: ");
  for(i = 0; i < 12; i++) {
    printf("%2.2x ",abedb[i]);
  }
  printf("\n");
  */

  /* length */
  for(i = 0; i < 18; i++) aspos[i][1] = (short)abedb[i + 6];

  for(i = 0; i <  5; i++) {
    itmp = 0;
    itmp = (abedb[6+18+i*2] << 8) | abedb[6+18+i*2+1];
    aspos[i+18][1] = (short)itmp;
  }


  /* position */
  aspos[0][0] = 6;
  for(i = 1; i < NLOC; i++) aspos[i][0] = aspos[i-1][0] + aspos[i-1][1];

  /* checksum */
  itmp = 6;
  for(i = 0; i < NLOC; i++) {
    /*
      printf("DBG: %2d %4d %4d\n",i,aspos[i][0],aspos[i][1]);
    */
    itmp += aspos[i][1];
  }
  if( itmp != NBINEDB) {
    printf("W:gedbpos:EDB has unexpected length %d\n",itmp);
  }

  return;
}

/*  --------------------------------------------------------------------------
    Function: vxmascla
    Synopsis: get DPU classification parameters: SWICS/mass
    ------------------------------------------------------------------------*/
void vxmascla(BYTE abedb[NBINEDB], SBCYC *pcyc)
{
  int  i;
  int  itmp;
  long ltmp;
  int  ipos;

  if( abedb[5] == 53 ) {

    ipos = pcyc->aspos[abedb[5]][LDSPARE][LTLMPOS];

    for(i = 0; i < 6; i++) {
      itmp  = ipos + 4*i;
      pcyc->adcnm[LCNMCLA5 - i] = ddpudbl(itmp,abedb,1.0);
      /* used to be:  ddpudbl(itmp,abedb,S3DPULNM);
      ** which results in "human readable" units, but
      ** we need do remain in the DPU units domain */
    }
    for(i = 0; i < 6; i++) {
      itmp  = ipos + 4*i + 24;
      pcyc->adcnm[LCNMEDAC - i] = ddpudbl(itmp,abedb,1.0);
    }
    for(i = 0;i < 4;i++) {
      itmp  =  ipos + 2*i + 48;
      ltmp = 0L;
      ltmp = (abedb[itmp] << 8) | abedb[itmp + 1];
      pcyc->adcnm[LCNMEMAX - i] = (double)ltmp;
    }
  }
  else {
    printf("W:vxmascla:Wrong EDB taken (%2d/%2d)\n",abedb[5],53);
  }
  return;
}


/*  --------------------------------------------------------------------------
    Function: vxmoqcla
    Synopsis: get DPU classification parameters: SWICS/m/q
    ------------------------------------------------------------------------*/
void vxmoqcla(BYTE abedb[NBINEDB], SBCYC *pcyc)
{
  int  i;
  int  itmp;
  long ltmp;
  int  ipos;

  if( abedb[5] == 54 ) {

    ipos = pcyc->aspos[abedb[5]][LDSPARE][LTLMPOS];

    for(i = 0; i < 3; i++) {
      itmp  = ipos + 4*i;
      pcyc->adcnq[LCNQCLA2 - i] = ddpudbl(itmp,abedb,1.0);
      /* used to be:  ddpudbl(itmp,abedb,S3DPULNQ);
      ** which results in "human readable" units, but
      ** we need do remain in the DPU units domain */
    }

    for(i = 0; i < 10; i++) {
      itmp  = ipos + 4*i + 12;
      pcyc->adcnq[LCNQEOQ1 - i] = ddpudbl(itmp,abedb,1.0);
    }

    for(i = 0;i < 2;i++) {
      itmp =  ipos + 2*i + 52;
      ltmp = 0L;
      ltmp = (abedb[itmp] << 8) | abedb[itmp + 1];
      pcyc->adcnq[LCNQTMAX - i] = (double)ltmp;
    }
  }
  else {
    printf("W:vxmoqcla:Wrong EDB taken (%2d/%2d)\n",abedb[5],54);
  }
  return;
}

/*  --------------------------------------------------------------------------
    Function: vxbrtab
    Synopsis: get SWICS basic rates corners
    ------------------------------------------------------------------------*/
void vxbrtab(BYTE abedb[NBINEDB], SBCYC *pcyc)
{
  int i;
  int j;
  int itmp;
  int ipos;
  int itab;

  if( abedb[5] == 47 ) {

    /* reset */

    for(j = 0; j < NXBRBOX; j++) {
      pcyc->abxbrtab[j][LXBOX] = 255;
      pcyc->abxbrtab[j][LXMX]  = 255;
      pcyc->abxbrtab[j][LXQX]  = 255;
      pcyc->abxbrtab[j][LXMN]  = 255;
      pcyc->abxbrtab[j][LXQN]  = 255;
    }

    itab = 0;

    /* loop over all bytes in DSpare, even though only 8 entries
    ** are used */

    /* 10 possible values in 60 bytes */
    for(i = 9; i >= 0; i--) {

      ipos =  pcyc->aspos[abedb[5]][LDSPARE][LTLMPOS];

      itmp = 0;
      itmp = (abedb[ipos + i*6 + 0] << 8) | (abedb[ipos + i*6 + 1]);

      /* itmp is the table entry. BR entries are located
      ** in positins 8..15 */

      if( (itmp >= 8) && (itmp < (8 + NXBRBOX)) ) {

        itmp -= 8;
        pcyc->abxbrtab[itab][LXBOX] = itmp;
        pcyc->abxbrtab[itab][LXMX]  = abedb[ipos + i*6 + 2 + 0];
        pcyc->abxbrtab[itab][LXQX]  = abedb[ipos + i*6 + 2 + 1];
        pcyc->abxbrtab[itab][LXMN]  = abedb[ipos + i*6 + 2 + 2];
        pcyc->abxbrtab[itab][LXQN]  = abedb[ipos + i*6 + 2 + 3];

        itab++;

      }

      /*
      printf("DBG: ");
      for(j = 0; j < 6; j++) printf("%3d ",abedb[ipos + i*6 + j]);
      printf("\n");
      */
    }
  }
  else {
    printf("W:vxbrtab:Wrong EDB taken (%2d/%2d)\n",abedb[5],47);
  }
  return;
}


/*  --------------------------------------------------------------------------
    vxmrtab --- get SWICS matrix rates corners
    ------------------------------------------------------------------------*/
void vxmrtab(BYTE abedb[NBINEDB], SBCYC *pcyc)
{
  int i;
  int itmp;
  int ipos;
  int ioff = 0;
  int itab = 0;

  if( (abedb[5] == 48) || (abedb[5] == 49) ) {

    if( abedb[5] == 48 ) ioff =  0;
    else                 ioff = 10;

    /* reset */

    for(i = 0; i < 10; i++) {

      /* Note: NXMRBOX is 20, but only 10 entries in one DSpare */

      pcyc->abxmrtab[i+ioff][LXBOX] = 255;
      pcyc->abxmrtab[i+ioff][LXMX]  = 255;
      pcyc->abxmrtab[i+ioff][LXQX]  = 255;
      pcyc->abxmrtab[i+ioff][LXMN]  = 255;
      pcyc->abxmrtab[i+ioff][LXQN]  = 255;
    }

    itab = 0;

    /* loop over all bytes in DSpare */

    for(i = 9; i >= 0; i--) /* loop DSpare */ {

      /* correct entry */

      ipos = pcyc->aspos[abedb[5]][LDSPARE][LTLMPOS];

      itmp = 0;
      itmp = (abedb[ipos + i*6 + 0] << 8) | (abedb[ipos + i*6 + 1]);

      /* itmp is the table entry. MR entries are located
      ** in positins 16..63 */
          
      if( (itmp >= 16) && (itmp < (16 + NXMRBOX)) ) {

        itmp -= 16;

        pcyc->abxmrtab[itab + ioff][LXBOX] = itmp;
        pcyc->abxmrtab[itab + ioff][LXMX]  = abedb[ipos + i*6 + 2 + 0];
        pcyc->abxmrtab[itab + ioff][LXQX]  = abedb[ipos + i*6 + 2 + 1];
        pcyc->abxmrtab[itab + ioff][LXMN]  = abedb[ipos + i*6 + 2 + 2];
        pcyc->abxmrtab[itab + ioff][LXQN]  = abedb[ipos + i*6 + 2 + 3];

        itab++;
      }
    }
  }
  else {
    printf("W:vxmrtab:Wrong EDB taken (%2d/%2d %2d)\n",abedb[5],48,49);
  }
  return;
}

/*  --------------------------------------------------------------------------
    deccpha --- Decipher SWICS PHA words.
    ----------------------------------------------------------------------- */
void deccpha(BYTE onepha[3],CPHA *stcpha)
{

  long ltmp = 0L;

  /* --- reset structure --- */

  stcpha->range  = 0;
  stcpha->sector = 0;
  stcpha->ESSD   = 0;
  stcpha->TOF    = 0;

  /* -----------------------------------------------------------------------
  ** 0123 4567   8901 2345   6789 0123
  **    v vv Sector =   vv   vvvv vvvv TOF =
  ** 1110:1111 | 0100:0011 | 1011:1001
  **        ^^   ^^^^ ^^ Energy = 
  ** ^^^ Range = 
  ** ---------------------------------------------------------------------*/
    
  ltmp = 0L;
  ltmp = (onepha[0] << 16) |
         (onepha[1] <<  8) |
         (onepha[2]);

  stcpha->range  = getbits(ltmp, 0+8,3);
  stcpha->sector = getbits(ltmp, 3+8,3);
  stcpha->ESSD   = getbits(ltmp, 6+8,8);
  stcpha->TOF    = getbits(ltmp,14+8,10);
  return;
}

/*  --------------------------------------------------------------------------
    decmpha --- Decipher SWIMS MHA words.
    ----------------------------------------------------------------------- */
void decmpha(BYTE onepha[6],MPHA *stmpha)
{

  long ltmp = 0L;

  /* --- reset structure --- */

  stmpha->range  = 0; /* 3  bits in PHA word */
  stmpha->sector = 0; /* 3  " */
  stmpha->amp    = 0; /* 10 " */
  stmpha->k1     = 0; /* 10 " */
  stmpha->k2     = 0; /* 10 " */
  stmpha->tof    = 0; /* 12 " */

  /* .........................................................................
     Note: even though there are 3 bits for the range, it looks like
           only 2 are actually used for Ranges 0,1, and 2.
     ...................................................................... */

  /* --- fill structure --- */

  /* --  take first 2 bytes: range,sector and amp -- */


  ltmp = 0L;
  ltmp = (onepha[0] <<  8) |
         (onepha[1]);

  stmpha->range  = getbits(ltmp, 0+16, 3);
  stmpha->sector = getbits(ltmp, 3+16, 3);
  stmpha->amp    = getbits(ltmp, 6+16,10);

  /* --  take other 4 bytes: k1,k2 and tof -- */

  ltmp = 0L;
  ltmp = (onepha[2] << 24) |
         (onepha[3] << 16) |
         (onepha[4] <<  8) |
         (onepha[5]);

  stmpha->k1     = getbits(ltmp, 0,10);
  stmpha->k2     = getbits(ltmp,10,10);
  stmpha->tof    = getbits(ltmp,20,12);

  /* --- that's it --- */

  return;
}

/* ---------------------------------------------------------------------------
   convTmp --- convert byte to temperature
   ------------------------------------------------------------------------ */
double convTmp(BYTE bval)
{
  static double adtemps[256] = { 154.7, 154.7, 125.9, 110.6, 100.4,
92.8, 86.7, 81.8, 77.5, 73.9, 70.6, 67.7, 65.1, 62.7, 60.6, 58.5,
56.7, 54.9, 53.3, 51.7, 50.3, 48.9, 47.6, 46.3, 45.1, 44.0, 42.9,
41.8, 40.8, 39.8, 38.9, 38.0, 37.1, 36.3, 35.4, 34.6, 33.8, 33.1,
32.4, 31.6, 30.9, 30.2, 29.6, 28.9, 28.3, 27.7, 27.1, 26.5, 25.9,
25.3, 24.7, 24.2, 23.6, 23.1, 22.6, 22.1, 21.6, 21.1, 20.6, 20.1,
19.6, 19.2, 18.7, 18.2, 17.8, 17.3, 16.9, 16.5, 16.0, 15.6, 15.2,
14.8, 14.4, 14.0, 13.6, 13.2, 12.8, 12.4, 12.0, 11.7, 11.3, 10.9,
10.5, 10.2, 9.8, 9.5, 9.1, 8.8, 8.4, 8.1, 7.7, 7.4, 7.0, 6.7, 6.4,
6.0, 5.7, 5.4, 5.1, 4.7, 4.4, 4.1, 3.8, 3.5, 3.2, 2.9, 2.5, 2.2, 1.9,
1.6, 1.3, 1.0, 0.7, 0.4, 0.1, -0.2, -0.5, -0.8, -1.0, -1.3, -1.6,
-1.9, -2.2, -2.5, -2.8, -3.1, -3.4, -3.6, -3.9, -4.2, -4.5, -4.8,
-5.0, -5.3, -5.6, -5.9, -6.2, -6.4, -6.7, -7.0, -7.3, -7.5, -7.8,
-8.1, -8.4, -8.6, -8.9, -9.2, -9.5, -9.7, -10.0, -10.3, -10.6, -10.8,
-11.1, -11.4, -11.7, -11.9, -12.2, -12.5, -12.8, -13.0, -13.3, -13.6,
-13.9, -14.1, -14.4, -14.7, -15.0, -15.3, -15.5, -15.8, -16.1, -16.4,
-16.7, -16.9, -17.2, -17.5, -17.8, -18.1, -18.4, -18.7, -19.0, -19.2,
-19.5, -19.8, -20.1, -20.4, -20.7, -21.0, -21.3, -21.6, -21.9, -22.2,
-22.5, -22.8, -23.1, -23.5, -23.8, -24.1, -24.4, -24.7, -25.0, -25.4,
-25.7, -26.0, -26.4, -26.7, -27.0, -27.4, -27.7, -28.1, -28.4, -28.8,
-29.1, -29.5, -29.9, -30.2, -30.6, -31.0, -31.4, -31.8, -32.1, -32.5,
-32.9, -33.4, -33.8, -34.2, -34.6, -35.1, -35.5, -35.9, -36.4, -36.9,
-37.3, -37.8, -38.3, -38.8, -39.3, -39.9, -40.4, -41.0, -41.5, -42.1,
-42.7, -43.3, -44.0, -44.6, -45.3, -46.0, -46.7, -47.5, -48.2, -49.1,
-49.9, -50.8};

  return( adtemps[bval] );
}

/* ---------------------------------------------------------------------------
   convTmp2 --- convert byte to temperature for SWICS/PAPS ref. temp.
   ------------------------------------------------------------------------ */
double convTmp2(BYTE bval)
{
  double dres;

  dres = -1.0;

  if( bval < 235 ) {
    dres = -128.0  + bval * 0.6714;
  } else {
    dres = -949.85 + bval * 4.117;
  }

  return(dres);
}

/* ---------------------------------------------------------------------------
   history

   date      | change
   ----------+----------------------------------------------------------------
   15-Jul-98 | SWICS/SWIMS CMD/CTL blocks: use both EDBs of one record
             | where the bytes can be found.
             | ...............................................................
             | SWICS PHA: store m, m/q.
   ----------+----------------------------------------------------------------

   -------------------------------------------------------------------------*/
