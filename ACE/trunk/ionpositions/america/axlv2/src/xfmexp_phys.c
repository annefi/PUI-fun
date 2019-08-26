/*
  File: xfmexp_phys.c

  Description:
    ACE/SWICS Forward Model (Experimental) -- Physics version.
    This will likely be incorporated into libhef, possibly replacing xfm.

  Author(s): Jim Raines (jmr)
             Susan Lepri (stl)

  Method:
    Predict (tofch,esdch) from (e/q,m,q) using kinetic energy formula and 
    experimental E losses from UMD.  Losses in the carbon foil and
    fraction of residual energy measured by SSD are interpolated from
    tabulated experimental data.
    
  Revision controlled by CVS:
  $Id: xfmexp_phys.c,v 1.4 2005/03/18 21:27:10 jraines Exp $

  Major Modification History:
    10Feb2004   jmr   initial coding
    17Mar2005   jmr/stl Included sulfur (mass=32) by rough interpolation

  Arguments:
    eoq -- energy/charge (keV/e)
    pav -- post-acceleration voltage (kV)
    mas -- ion mass (amu)
    crg -- ion charge (e, i.e. 6.0 for 6+)
*/

#include <stdio.h>
#include "math.h"
#include "nr_c.h"
#include "nrutil_c.h"

// set sizes for energy loss data arrays (for interpolation)
#define N_CFOIL_EON 20
#define N_CFOIL_ELEMENTS 85
#define N_DFECT_EON 22
#define N_DFECT_ELEMENTS 85
#define N_POINT_INTERPOL 4

void initCFOIL(float *CFOIL_EON, float **CFOIL);
void initDFECT(float *DFECT_EON, float **DFECT);

double *xfmexp_phys(double eoq, double pav, double mas, double crg)
{
  const char thisprog[] = "xfmexp_phys"; // FIX:change this if put
					 // into libhef
  int i,j;  // short-range loop counters
  int DbgLvl = 0;  // routine debug level

  static int ifirsttime = 1;  // 1=>first run through routine; 0
			      // otherwise
  int im; // integer mass, for indexing

  // forward model positions in channels: tof, sig. tof, esd, sig. esd
  static double adfm[4];

  // Arrays holding cfoil and dfect data for interpolation
  static float *CFOIL_EON;
  static float **CFOIL;
  static float *DFECT_EON;
  static float **DFECT;

  // Constants for sigma calculations, from libhef::xfm
  // Note: N_CFOIL_ELEMENTS == N_DFECT_ELEMENTS must be true for this 
  // routine to fully work.
  static double H2[N_CFOIL_ELEMENTS+1];
  static double H5[N_DFECT_ELEMENTS+1];
  static double H6[N_DFECT_ELEMENTS+1];

  // --- physical constants ---
  // carbon foil thickness in ug/cm^2
  const float FOIL_THICK = 2.0;
  // Length of TOF region (cm)
  const float TOF_DISTANCE = 10.0; 
  // ESD (keV) -> ESD (ch)
  const float ESD_kev_per_ch = 2.395;
  // TOF (ns) -> TOF (ch)
  const float TOF_ns_per_ch = 0.1955;
  // allowed fractional accuracy for loss rate interpolation
  const float LossAccurCutoff = 0.1;
  // allowed fractional accuracy for nuclear defect interpolation
  const float DefectAccurCutoff = 0.1;

  // --- physical variables ---
  // total energy
  float etot;
  // energy/nucleon for specified ion
  float eon;
  // energy loss rate in foil
  float loss_rate = -1.0;
  // energy lost to foil
  float ul;
  // predicted time of flight (ns)
  float tof;
  // fraction of actual energy measured by SSD
  float meas_frac = -1.0; 
  // predicted energy measurement (keV)
  float emeas;  

  // --- interpolation variables ---
  // index immediately preceeding calculated eon in EON table
  unsigned long eon_index;
  // lower bound in interpolation data matrix (CFOIL or DFECT)
  int sublb;
  // subarray for passing into polint
  float *subarray;
  // accuracy of most recent interpolation
  float accuracy = -1.0;
  // accuracy of most recent interpolation as fraction of interpol. value
  float frac_accuracy = -1.0;

  /* -------------------------------------------------------------------------
  ** Define interopolation data arrays -- first time only
  ** ---------------------------------------------------------------------- */
  if( ifirsttime == 1 ) {

    // print banner
    if (DbgLvl>=1){
      printf("%s -I- this routine built on %s %s\n",thisprog,__DATE__,__TIME__);
    }
    // why was this commented out?
    ifirsttime = 0; 

    if (CFOIL_EON==NULL)
      CFOIL_EON = vector(1, N_CFOIL_EON);

    if (CFOIL == NULL)
      CFOIL = matrix(1,N_CFOIL_ELEMENTS,1,N_CFOIL_EON);

    // initialize so that unsupported elements will by -1.0
    // note: DFECT was allocated as starting with index 1
    for(i=1; i<=N_CFOIL_ELEMENTS; i++){
      for(j=1; j<=N_CFOIL_EON; j++){
	CFOIL[i][j] = -1.0;
      }
    }
    initCFOIL(CFOIL_EON,CFOIL);

    if (DFECT_EON == NULL)
      DFECT_EON = vector(1,N_DFECT_EON);
    if (DFECT == NULL)
      DFECT = matrix(1,N_DFECT_ELEMENTS,1,N_DFECT_EON);

    // initialize so that unsupported elements will by -1.0
    // note: DFECT was allocated as starting with index 1
    for(i=1; i<=N_DFECT_ELEMENTS; i++){
      for(j=1; j<=N_DFECT_EON; j++){
	DFECT[i][j] = -1.0;
      }
    }
    initDFECT(DFECT_EON,DFECT);	      
    
    /* Initialze sigma constants, from libhef::xfm 
       ------------------------------------------- */

    for (i=0; i<N_CFOIL_ELEMENTS+1; i++) H2[i] = -1.0;

    for (i=0; i<N_DFECT_ELEMENTS+1; i++){
      H5[i] = -1.0;
      H5[i] = -1.0;
    }
    

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
    H2[40] = 0.0124;  // copied from rest
    H2[56] = 0.0124;
    H2[84] = 0.0124;

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
    H5[40] = 0.78; // copied from 32
    H5[56] = 0.41;
    H5[84] = 0.41; // copied from 56

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
    H6[40] = -0.79; // copied from 32
    H6[56] = -0.63; 
    H6[84] = -0.63; // copied from 56
  }

  /* -------------------------------------------------------------------------
  ** Initialize other variables
  ** ---------------------------------------------------------------------- */
  for(i=0; i<4; i++) adfm[i] = -1.0;

  im = (int) mas;

  if (DbgLvl >= 4){
    printf("%s -I- E/q=%6.2f mass=%6.2f charge=%2.0f\n",thisprog,
	   eoq, mas, crg);
  }
  /* -------------------------------------------------------------------------
  ** Find energy lost in foil and calculate TOF in ns
  ** ---------------------------------------------------------------------- */
  // total energy
  etot = (eoq + pav)*crg;

  // energy/nucleon
  eon = etot/mas;

  if (CFOIL[im][1] == -1.0){
    if (DbgLvl>=1){
      printf("%s -F- mass %6.2f not in foil loss table.  Returning.\n",
	   thisprog, mas);
    }
    return(adfm);
  }

  /* ----------------------------------------------------------------------
     Find index of of CFOIL_EON so that eon is between that index and the next
     ---------------------------------------------------------------------- */
  locate(CFOIL_EON, N_CFOIL_EON, eon, &eon_index);

  /* ----------------------------------------------------------------------
     Calculate the lower bound on a range of indices, roughly
     centered on the location (just found) containg the intended number of
     points for interpolation
     ---------------------------------------------------------------------- */
  sublb = IMIN(IMAX((eon_index-(N_POINT_INTERPOL-1)/2),1),
	       N_CFOIL_EON+1-N_POINT_INTERPOL);

  /* ----------------------------------------------------------------------
     Do actual interpolation of subarrays
     ---------------------------------------------------------------------- */
  subarray = vector(1,N_POINT_INTERPOL);

  /* subarray is unit offset meaning:
     1. element 0 is not used
     2. sublb-1 must be used to index CFOIL so that
     CFOIL[im][sublb].. CFOIL[im][sublb+N_POINT_INTERPOL-1] are put in
     subarray with loop counter going from 1..N_POINT_INTERPOL.
  */
  subarray[0] = -1.0;  // unit offset array
  for(i=1 ; i<=N_POINT_INTERPOL; i++) subarray[i] = CFOIL[im][sublb-1+i];

  // sublb-1 -> sublb here too
  // polint(&CFOIL_EON[sublb-1], subarray, N_POINT_INTERPOL,
  polint(&CFOIL_EON[sublb], subarray, N_POINT_INTERPOL,
	 eon, &loss_rate, &accuracy);

  // check accuracy
  if (loss_rate != 0.0){
    frac_accuracy = fabs(accuracy/loss_rate);
  }
  else{
    frac_accuracy = LossAccurCutoff;
  }
  if (frac_accuracy >= LossAccurCutoff) {
    if (DbgLvl>=1){
      printf("%s -W- foil loss interpolation fractional",thisprog);
      printf(" accuracy seems bad at %6.2g (%6.2g/%6.2g)\n",frac_accuracy,
	   accuracy,loss_rate);
    }
  }

  // calculate foil loss
  ul = loss_rate*FOIL_THICK;

  // reduce total energy accordingly
  etot = etot - ul;

  // calculate tof with reduced energy
  // conv. factor: 520.0 ns^2 keV / cm^2 amu
  tof = TOF_DISTANCE*sqrt(mas*520.0/etot);

  // convert tof to channels and put in return array
  adfm[0] = tof / TOF_ns_per_ch;

  /* -------------------------------------------------------------------------
  ** Calculate TOF sigma
  ** ---------------------------------------------------------------------- */
  adfm[1] = H2[im] * adfm[0];

  /* -------------------------------------------------------------------------
  ** Find energy lost (and not measured) in solid state detector
  ** ---------------------------------------------------------------------- */
  // recalculate energy/nucleon after foil loss
  eon = etot/mas;

  if (DFECT[im][1] == -1.0){
    if (DbgLvl>=1){
      printf("%s -F- mass %6.2f not in nuclear defect table.  Returning.\n",
	   thisprog, mas);
    }
    free_vector(subarray, 1, N_POINT_INTERPOL);
    return(adfm);
  }

  /* ----------------------------------------------------------------------
     Find index of of DFECT_EON so that eon is between that index and the next
     ---------------------------------------------------------------------- */
  locate(DFECT_EON, N_DFECT_EON, eon, &eon_index);

  /* ----------------------------------------------------------------------
     Calculate the lower bound on a range of indices, roughly
     centered on the location (just found) containg the intended number of
     points for interpolation
     ---------------------------------------------------------------------- */
  sublb = IMIN(IMAX((eon_index-(N_POINT_INTERPOL-1)/2),1),
	       N_DFECT_EON+1-N_POINT_INTERPOL);

  /* ----------------------------------------------------------------------
     Do actual interpolation of subarrays
     ---------------------------------------------------------------------- */
  /* subarray is unit offset meaning:
     1. element 0 is not used
     2. sublb-1 must be here used to index DFECT so that
     DFECT[im][sublb].. DFECT[im][sublb+N_POINT_INTERPOL-1] are put in
     subarray with loop counter going from 1..N_POINT_INTERPOL.
  */
  subarray[0] = -1.0;  // 1-indexed array
  for(i=1 ; i<=N_POINT_INTERPOL; i++) subarray[i] = DFECT[im][sublb-1+i];

  polint(&DFECT_EON[sublb], subarray, N_POINT_INTERPOL,
	 eon, &meas_frac, &accuracy);

  // check accuracy
  if (meas_frac != 0.0){
    frac_accuracy = fabs(accuracy/meas_frac);
  }
  else{
    frac_accuracy = DefectAccurCutoff;
  }
  if (frac_accuracy >= DefectAccurCutoff) {
    if (DbgLvl>=1){
      printf("%s -W- nuclear defect interpolation fractional",thisprog);
      printf(" accuracy seems bad at %6.2g (%6.2g/%6.2g)\n",frac_accuracy,
	   accuracy,meas_frac);
    }
  }

  emeas = etot*(meas_frac/100.0);

  adfm[2] = emeas / ESD_kev_per_ch;
  /* -------------------------------------------------------------------------
  ** Calculate ESD sigma
  ** ---------------------------------------------------------------------- */
  adfm[3] = H5[im] * pow((emeas / mas),H6[im]) * adfm[2];

  /* -------------------------------------------------------------------------
  ** done
  ** ---------------------------------------------------------------------- */

  free_vector(subarray, 1, N_POINT_INTERPOL);
  return(adfm);
}


void initCFOIL(float *CFOIL_EON, float **CFOIL){ 
  /* Energy loss to carbon foil data.
     Based on CFOIL.FOR, 4/21/1989, Gloeckler, et. al., Univ. of Maryland */

  /* energy (keV) / nucleon */
  CFOIL_EON[ 0] = -1.0; //not used
  CFOIL_EON[ 1] = 1.00;
  CFOIL_EON[ 2] = 1.50;
  CFOIL_EON[ 3] = 2.50;
  CFOIL_EON[ 4] = 4.00;
  CFOIL_EON[ 5] = 6.00;
  CFOIL_EON[ 6] = 8.00;
  CFOIL_EON[ 7] = 10.00;
  CFOIL_EON[ 8] = 15.00;
  CFOIL_EON[ 9] = 25.00;
  CFOIL_EON[10] = 40.00;
  CFOIL_EON[11] = 60.00;
  CFOIL_EON[12] = 80.00;
  CFOIL_EON[13] = 100.00;
  CFOIL_EON[14] = 150.00;
  CFOIL_EON[15] = 250.00;
  CFOIL_EON[16] = 400.00;
  CFOIL_EON[17] = 600.00;
  CFOIL_EON[18] = 800.00;
  CFOIL_EON[19] = 1000.00;
  CFOIL_EON[20] = 10000.00;

  /* Energy loss (cm^2 / nucleon ug ) in a carbon foil
     1st index is mass (integer), 2nd index goes with CFOIL_EON, above
     This wastes memory, but only about 6kb. */
  // Hydrogen
  CFOIL[ 1][ 1] =   0.16;
  CFOIL[ 1][ 2] =   0.18;
  CFOIL[ 1][ 3] =   0.23;
  CFOIL[ 1][ 4] =   0.28;
  CFOIL[ 1][ 5] =   0.34;
  CFOIL[ 1][ 6] =   0.38;
  CFOIL[ 1][ 7] =   0.42;
  CFOIL[ 1][ 8] =   0.50;
  CFOIL[ 1][ 9] =   0.60;
  CFOIL[ 1][10] =   0.70;
  CFOIL[ 1][11] =   0.75;
  CFOIL[ 1][12] =   0.75;
  CFOIL[ 1][13] =   0.73;
  CFOIL[ 1][14] =   0.64;
  CFOIL[ 1][15] =   0.51;
  CFOIL[ 1][16] =   0.40;
  CFOIL[ 1][17] =   0.32;
  CFOIL[ 1][18] =   0.27;
  CFOIL[ 1][19] =   0.23;
  CFOIL[ 1][20] =   0.04;

  // He
  CFOIL[ 4][ 1] =   0.43;
  CFOIL[ 4][ 2] =   0.48;
  CFOIL[ 4][ 3] =   0.57;
  CFOIL[ 4][ 4] =   0.66;
  CFOIL[ 4][ 5] =   0.75;
  CFOIL[ 4][ 6] =   0.84;
  CFOIL[ 4][ 7] =   0.91;
  CFOIL[ 4][ 8] =   1.05;
  CFOIL[ 4][ 9] =   1.25;
  CFOIL[ 4][10] =   1.47;
  CFOIL[ 4][11] =   1.65;
  CFOIL[ 4][12] =   1.82;
  CFOIL[ 4][13] =   1.86;
  CFOIL[ 4][14] =   1.93;
  CFOIL[ 4][15] =   1.81;
  CFOIL[ 4][16] =   1.53;
  CFOIL[ 4][17] =   1.24;
  CFOIL[ 4][18] =   1.04;
  CFOIL[ 4][19] =   0.89;
  CFOIL[ 4][20] =   0.16;

  // Carbon
  CFOIL[12][ 1] =   1.28;
  CFOIL[12][ 2] =   1.38;
  CFOIL[12][ 3] =   1.52;
  CFOIL[12][ 4] =   1.72;
  CFOIL[12][ 5] =   1.91;
  CFOIL[12][ 6] =   2.10;
  CFOIL[12][ 7] =   2.28;
  CFOIL[12][ 8] =   2.60;
  CFOIL[12][ 9] =   3.25;
  CFOIL[12][10] =   4.10;
  CFOIL[12][11] =   4.95;
  CFOIL[12][12] =   5.58;
  CFOIL[12][13] =   6.05;
  CFOIL[12][14] =   6.75;
  CFOIL[12][15] =   7.20;
  CFOIL[12][16] =   7.10;
  CFOIL[12][17] =   6.80;
  CFOIL[12][18] =   6.25;
  CFOIL[12][19] =   5.80;
  CFOIL[12][20] =   1.45;

  // Nitrogen
  CFOIL[14][ 1] =   1.41;
  CFOIL[14][ 2] =   1.51;
  CFOIL[14][ 3] =   1.71;
  CFOIL[14][ 4] =   1.91;
  CFOIL[14][ 5] =   2.18;
  CFOIL[14][ 6] =   2.39;
  CFOIL[14][ 7] =   2.58;
  CFOIL[14][ 8] =   2.97;
  CFOIL[14][ 9] =   3.67;
  CFOIL[14][10] =   4.55;
  CFOIL[14][11] =   5.50;
  CFOIL[14][12] =   6.25;
  CFOIL[14][13] =   6.80;
  CFOIL[14][14] =   7.95;
  CFOIL[14][15] =   8.70;
  CFOIL[14][16] =   8.80;
  CFOIL[14][17] =   8.30;
  CFOIL[14][18] =   7.75;
  CFOIL[14][19] =   7.20;
  CFOIL[14][20] =   1.95;

  // Oxygen
  CFOIL[16][ 1] =   1.42;
  CFOIL[16][ 2] =   1.52;
  CFOIL[16][ 3] =   1.72;
  CFOIL[16][ 4] =   1.99;
  CFOIL[16][ 5] =   2.29;
  CFOIL[16][ 6] =   2.51;
  CFOIL[16][ 7] =   2.73;
  CFOIL[16][ 8] =   3.22;
  CFOIL[16][ 9] =   4.05;
  CFOIL[16][10] =   5.00;
  CFOIL[16][11] =   6.02;
  CFOIL[16][12] =   7.00;
  CFOIL[16][13] =   7.62;
  CFOIL[16][14] =   8.90;
  CFOIL[16][15] =  10.10;
  CFOIL[16][16] =  10.20;
  CFOIL[16][17] =   9.80;
  CFOIL[16][18] =   9.35;
  CFOIL[16][19] =   8.85;
  CFOIL[16][20] =   2.50;

  // Neon
  CFOIL[20][ 1] =   1.30;
  CFOIL[20][ 2] =   1.37;
  CFOIL[20][ 3] =   1.54;
  CFOIL[20][ 4] =   1.80;
  CFOIL[20][ 5] =   2.10;
  CFOIL[20][ 6] =   2.35;
  CFOIL[20][ 7] =   2.60;
  CFOIL[20][ 8] =   3.13;
  CFOIL[20][ 9] =   4.15;
  CFOIL[20][10] =   5.27;
  CFOIL[20][11] =   6.50;
  CFOIL[20][12] =   7.58;
  CFOIL[20][13] =   8.56;
  CFOIL[20][14] =  10.70;
  CFOIL[20][15] =  13.60;
  CFOIL[20][16] =  15.20;
  CFOIL[20][17] =  15.20;
  CFOIL[20][18] =  14.40;
  CFOIL[20][19] =  13.40;
  CFOIL[20][20] =   3.90;

  // Sulfur
  // interpolated by eye ((hi-lo)/2)+lo) between Ne and Ca
  CFOIL[32][ 1] =   2.19;
  CFOIL[32][ 2] =   2.23;
  CFOIL[32][ 3] =   2.36;
  CFOIL[32][ 4] =   2.96;
  CFOIL[32][ 5] =   2.95;
  CFOIL[32][ 6] =   3.25;
  CFOIL[32][ 7] =   3.53;
  CFOIL[32][ 8] =   4.17;
  CFOIL[32][ 9] =   5.23;
  CFOIL[32][10] =   6.52;
  CFOIL[32][11] =   8.05;
  CFOIL[32][12] =   9.44;
  CFOIL[32][13] =  10.68;
  CFOIL[32][14] =  13.50;
  CFOIL[32][15] =  17.30;
  CFOIL[32][16] =  19.85;
  CFOIL[32][17] =  20.90;
  CFOIL[32][18] =  20.60;
  CFOIL[32][19] =  19.85;
  CFOIL[32][20] =   7.15;

  // Calcium
  CFOIL[40][ 1] =   3.08;
  CFOIL[40][ 2] =   3.08;
  CFOIL[40][ 3] =   3.18;
  CFOIL[40][ 4] =   3.45;
  CFOIL[40][ 5] =   3.80;
  CFOIL[40][ 6] =   4.15;
  CFOIL[40][ 7] =   4.45;
  CFOIL[40][ 8] =   5.20;
  CFOIL[40][ 9] =   6.30;
  CFOIL[40][10] =   7.77;
  CFOIL[40][11] =   9.60;
  CFOIL[40][12] =  11.30;
  CFOIL[40][13] =  12.80;
  CFOIL[40][14] =  16.30;
  CFOIL[40][15] =  21.00;
  CFOIL[40][16] =  24.50;
  CFOIL[40][17] =  26.60;
  CFOIL[40][18] =  26.80;
  CFOIL[40][19] =  26.30;
  CFOIL[40][20] =  10.40;

  // Iron
  CFOIL[56][ 1] =   3.25;
  CFOIL[56][ 2] =   3.25;
  CFOIL[56][ 3] =   3.25;
  CFOIL[56][ 4] =   3.40;
  CFOIL[56][ 5] =   3.72;
  CFOIL[56][ 6] =   4.13;
  CFOIL[56][ 7] =   4.60;
  CFOIL[56][ 8] =   5.65;
  CFOIL[56][ 9] =   7.40;
  CFOIL[56][10] =   9.48;
  CFOIL[56][11] =  11.80;
  CFOIL[56][12] =  13.90;
  CFOIL[56][13] =  15.90;
  CFOIL[56][14] =  20.90;
  CFOIL[56][15] =  27.30;
  CFOIL[56][16] =  33.10;
  CFOIL[56][17] =  36.90;
  CFOIL[56][18] =  38.00;
  CFOIL[56][19] =  37.90;
  CFOIL[56][20] =  18.30;

  // Krypton
  CFOIL[84][ 1] =   4.10;
  CFOIL[84][ 2] =   4.10;
  CFOIL[84][ 3] =   4.10;
  CFOIL[84][ 4] =   4.20;
  CFOIL[84][ 5] =   4.43;
  CFOIL[84][ 6] =   4.78;
  CFOIL[84][ 7] =   5.19;
  CFOIL[84][ 8] =   6.30;
  CFOIL[84][ 9] =   8.38;
  CFOIL[84][10] =  10.80;
  CFOIL[84][11] =  13.60;
  CFOIL[84][12] =  16.10;
  CFOIL[84][13] =  18.50;
  CFOIL[84][14] =  24.80;
  CFOIL[84][15] =  33.70;
  CFOIL[84][16] =  42.40;
  CFOIL[84][17] =  48.60;
  CFOIL[84][18] =  51.00;
  CFOIL[84][19] =  51.50;
  CFOIL[84][20] =  29.30;

  return;
}

void initDFECT(float *DFECT_EON, float **DFECT){
  /* Nuclear Defect data from DFECT.FOR, 4/21/1989, 
     Gloeckler, et. al., Univ. of Maryland */

  /* energy (keV) / nucleon */
  DFECT_EON[ 0] = -1.0; // not used
  DFECT_EON[ 1] = 0.40;
  DFECT_EON[ 2] = 0.70;
  DFECT_EON[ 3] = 1.00;
  DFECT_EON[ 4] = 1.50;
  DFECT_EON[ 5] = 2.50;
  DFECT_EON[ 6] = 4.00;
  DFECT_EON[ 7] = 6.00;
  DFECT_EON[ 8] = 8.00;
  DFECT_EON[ 9] = 10.00;
  DFECT_EON[10] = 15.00;
  DFECT_EON[11] = 25.00;
  DFECT_EON[12] = 40.00;
  DFECT_EON[13] = 60.00;
  DFECT_EON[14] = 80.00;
  DFECT_EON[15] = 100.00;
  DFECT_EON[16] = 150.00;
  DFECT_EON[17] = 250.00;
  DFECT_EON[18] = 400.00;
  DFECT_EON[19] = 600.00;
  DFECT_EON[20] = 800.00;
  DFECT_EON[21] = 1000.00;
  DFECT_EON[22] = 10000.00;


  /* Energy loss (cm^2 / nucleon ug ) in a carbon foil
     1st index is mass (integer), 2nd index goes with DFECT_EON, above
     This wastes memory, but only about 6kb. */
  // Hydrogen
  DFECT[ 1][ 1] =  35.50;
  DFECT[ 1][ 2] =  45.50;
  DFECT[ 1][ 3] =  51.90;
  DFECT[ 1][ 4] =  58.40;
  DFECT[ 1][ 5] =  65.70;
  DFECT[ 1][ 6] =  71.80;
  DFECT[ 1][ 7] =  77.00;
  DFECT[ 1][ 8] =  80.50;
  DFECT[ 1][ 9] =  82.90;
  DFECT[ 1][10] =  86.40;
  DFECT[ 1][11] =  90.20;
  DFECT[ 1][12] =  92.80;
  DFECT[ 1][13] =  94.60;
  DFECT[ 1][14] =  95.60;
  DFECT[ 1][15] =  96.40;
  DFECT[ 1][16] =  97.50;
  DFECT[ 1][17] =  98.50;
  DFECT[ 1][18] =  99.20;
  DFECT[ 1][19] =  99.50;
  DFECT[ 1][20] =  99.60;
  DFECT[ 1][21] =  99.70;
  DFECT[ 1][22] = 100.00;

  // Helium
  DFECT[ 4][ 1] =  32.80;
  DFECT[ 4][ 2] =  43.40;
  DFECT[ 4][ 3] =  50.00;
  DFECT[ 4][ 4] =  57.20;
  DFECT[ 4][ 5] =  65.50;
  DFECT[ 4][ 6] =  72.30;
  DFECT[ 4][ 7] =  77.50;
  DFECT[ 4][ 8] =  80.70;
  DFECT[ 4][ 9] =  83.10;
  DFECT[ 4][10] =  87.00;
  DFECT[ 4][11] =  90.90;
  DFECT[ 4][12] =  93.40;
  DFECT[ 4][13] =  95.20;
  DFECT[ 4][14] =  96.00;
  DFECT[ 4][15] =  96.60;
  DFECT[ 4][16] =  97.50;
  DFECT[ 4][17] =  98.40;
  DFECT[ 4][18] =  99.00;
  DFECT[ 4][19] =  99.40;
  DFECT[ 4][20] =  99.50;
  DFECT[ 4][21] =  99.60;
  DFECT[ 4][22] = 100.00;

  // Carbon
  DFECT[12][ 1] =  18.20;
  DFECT[12][ 2] =  26.20;
  DFECT[12][ 3] =  31.60;
  DFECT[12][ 4] =  38.30;
  DFECT[12][ 5] =  47.30;
  DFECT[12][ 6] =  56.20;
  DFECT[12][ 7] =  64.10;
  DFECT[12][ 8] =  69.10;
  DFECT[12][ 9] =  72.50;
  DFECT[12][10] =  78.20;
  DFECT[12][11] =  84.20;
  DFECT[12][12] =  88.30;
  DFECT[12][13] =  91.30;
  DFECT[12][14] =  93.10;
  DFECT[12][15] =  94.00;
  DFECT[12][16] =  95.70;
  DFECT[12][17] =  97.20;
  DFECT[12][18] =  98.20;
  DFECT[12][19] =  98.70;
  DFECT[12][20] =  99.00;
  DFECT[12][21] =  99.20;
  DFECT[12][22] =  99.80;

  // Nitrogen
  DFECT[14][ 1] =  17.30;
  DFECT[14][ 2] =  24.80;
  DFECT[14][ 3] =  29.90;
  DFECT[14][ 4] =  36.40;
  DFECT[14][ 5] =  45.70;
  DFECT[14][ 6] =  54.60;
  DFECT[14][ 7] =  62.20;
  DFECT[14][ 8] =  67.20;
  DFECT[14][ 9] =  70.70;
  DFECT[14][10] =  76.60;
  DFECT[14][11] =  82.80;
  DFECT[14][12] =  87.40;
  DFECT[14][13] =  90.70;
  DFECT[14][14] =  92.60;
  DFECT[14][15] =  93.70;
  DFECT[14][16] =  95.30;
  DFECT[14][17] =  97.00;
  DFECT[14][18] =  98.00;
  DFECT[14][19] =  98.60;
  DFECT[14][20] =  98.90;
  DFECT[14][21] =  99.10;
  DFECT[14][22] =  99.80;

  // Oxygen
  DFECT[16][ 1] =  17.20;
  DFECT[16][ 2] =  23.20;
  DFECT[16][ 3] =  27.10;
  DFECT[16][ 4] =  32.90;
  DFECT[16][ 5] =  41.50;
  DFECT[16][ 6] =  50.40;
  DFECT[16][ 7] =  59.10;
  DFECT[16][ 8] =  64.60;
  DFECT[16][ 9] =  68.40;
  DFECT[16][10] =  74.50;
  DFECT[16][11] =  80.80;
  DFECT[16][12] =  85.80;
  DFECT[16][13] =  88.70;
  DFECT[16][14] =  90.40;
  DFECT[16][15] =  91.50;
  DFECT[16][16] =  93.60;
  DFECT[16][17] =  95.70;
  DFECT[16][18] =  97.10;
  DFECT[16][19] =  97.90;
  DFECT[16][20] =  98.40;
  DFECT[16][21] =  98.70;
  DFECT[16][22] =  99.70;

  // Neon
  DFECT[20][ 1] =  17.10;
  DFECT[20][ 2] =  22.50;
  DFECT[20][ 3] =  25.80;
  DFECT[20][ 4] =  30.20;
  DFECT[20][ 5] =  37.10;
  DFECT[20][ 6] =  45.10;
  DFECT[20][ 7] =  52.70;
  DFECT[20][ 8] =  58.10;
  DFECT[20][ 9] =  62.20;
  DFECT[20][10] =  69.50;
  DFECT[20][11] =  77.60;
  DFECT[20][12] =  82.70;
  DFECT[20][13] =  86.40;
  DFECT[20][14] =  88.60;
  DFECT[20][15] =  90.00;
  DFECT[20][16] =  92.00;
  DFECT[20][17] =  94.30;
  DFECT[20][18] =  95.80;
  DFECT[20][19] =  96.80;
  DFECT[20][20] =  97.40;
  DFECT[20][21] =  97.70;
  DFECT[20][22] =  99.50;

  // Sulfur
  // Interpolated by eye between Ne and Ca
  DFECT[32][ 1] =  16.15;
  DFECT[32][ 2] =  21.50;
  DFECT[32][ 3] =  24.85;
  DFECT[32][ 4] =  29.20;
  DFECT[32][ 5] =  36.05;
  DFECT[32][ 6] =  43.60;
  DFECT[32][ 7] =  50.75;
  DFECT[32][ 8] =  55.75;
  DFECT[32][ 9] =  59.60;
  DFECT[32][10] =  66.40;
  DFECT[32][11] =  74.40;
  DFECT[32][12] =  79.95;
  DFECT[32][13] =  84.15;
  DFECT[32][14] =  86.60;
  DFECT[32][15] =  88.30;
  DFECT[32][16] =  90.05;
  DFECT[32][17] =  93.70;
  DFECT[32][18] =  95.35;
  DFECT[32][19] =  96.45;
  DFECT[32][20] =  97.00;
  DFECT[32][21] =  97.35;
  DFECT[32][22] =  99.40;

  // Argon
  DFECT[40][ 1] =  15.20;
  DFECT[40][ 2] =  20.50;
  DFECT[40][ 3] =  23.90;
  DFECT[40][ 4] =  28.20;
  DFECT[40][ 5] =  35.00;
  DFECT[40][ 6] =  42.10;
  DFECT[40][ 7] =  48.80;
  DFECT[40][ 8] =  53.40;
  DFECT[40][ 9] =  57.00;
  DFECT[40][10] =  63.30;
  DFECT[40][11] =  71.20;
  DFECT[40][12] =  77.20;
  DFECT[40][13] =  81.90;
  DFECT[40][14] =  84.60;
  DFECT[40][15] =  86.60;
  DFECT[40][16] =  89.90;
  DFECT[40][17] =  93.10;
  DFECT[40][18] =  94.90;
  DFECT[40][19] =  96.10;
  DFECT[40][20] =  96.60;
  DFECT[40][21] =  97.00;
  DFECT[40][22] =  99.30;

  // Iron
  DFECT[56][ 1] =  14.50;
  DFECT[56][ 2] =  18.80;
  DFECT[56][ 3] =  22.40;
  DFECT[56][ 4] =  26.20;
  DFECT[56][ 5] =  31.00;
  DFECT[56][ 6] =  35.60;
  DFECT[56][ 7] =  40.30;
  DFECT[56][ 8] =  43.70;
  DFECT[56][ 9] =  46.60;
  DFECT[56][10] =  52.80;
  DFECT[56][11] =  62.00;
  DFECT[56][12] =  70.90;
  DFECT[56][13] =  77.50;
  DFECT[56][14] =  81.20;
  DFECT[56][15] =  83.30;
  DFECT[56][16] =  86.60;
  DFECT[56][17] =  90.30;
  DFECT[56][18] =  92.90;
  DFECT[56][19] =  94.60;
  DFECT[56][20] =  95.40;
  DFECT[56][21] =  95.90;
  DFECT[56][22] =  99.00;

  // Krypton
  DFECT[84][ 1] =  14.00;
  DFECT[84][ 2] =  17.40;
  DFECT[84][ 3] =  21.20;
  DFECT[84][ 4] =  25.20;
  DFECT[84][ 5] =  29.80;
  DFECT[84][ 6] =  34.20;
  DFECT[84][ 7] =  38.60;
  DFECT[84][ 8] =  42.20;
  DFECT[84][ 9] =  45.10;
  DFECT[84][10] =  50.40;
  DFECT[84][11] =  58.20;
  DFECT[84][12] =  66.00;
  DFECT[84][13] =  72.40;
  DFECT[84][14] =  76.50;
  DFECT[84][15] =  78.90;
  DFECT[84][16] =  82.90;
  DFECT[84][17] =  87.80;
  DFECT[84][18] =  91.30;
  DFECT[84][19] =  93.30;
  DFECT[84][20] =  94.40;
  DFECT[84][21] =  95.10;
  DFECT[84][22] =  98.80;

  return;
}
