/*
  File: xfmexp.cc

  Description:
    ACE/SWICS Forward Model, Experimental.  This version is used to test 
    FM parameters.

  Author(s): Jim Raines (jmr)

  Method:
    
  Revision controlled by CVS:
  $Id: xfmexp.cc,v 1.4 2005/03/18 21:27:10 jraines Exp $

  Major Modification History:
    08Oct2002   jmr   Adapted from libhef::xfm by Simon Hefti
    21Jan2004   jmr   Adapted from current version of libhef::xfm 

*/

#include "math.h"

namespace libhef {
  extern "C" {
#include "libhef.h"
  }
}

/* ---------------------------------------------------------------------------
   xfmexp --- Forward Model for SWICS, Experimental version
   Based on swxtools.c::xfm by Simon Hefti

   ------------------------------------------------------------------------ */
double *xfmexp(double eoq, double pav, double mas, double crg)
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
  using namespace libhef;
  
  const double KNOWN_PAV[2] = {21.2998,24.8682};
  const char thisprog[] = "xfmexp";  // change this when incorp. into libhef

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

    // print banner
    printf("%s -I- this routine built on %s %s\n",thisprog,__DATE__,__TIME__);

    if (pav >= .99*KNOWN_PAV[0] && pav <= 1.01*KNOWN_PAV[0]){ // level 127

      printf("%s -I- using pav = %6.2f coef.\n",thisprog,KNOWN_PAV[0]);

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

      // Energy lost in carbon foil (kV)
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

      // TOF sigma
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

      // ESD correction offset, H3
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

      // ESD correction slope, H4
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
      //H5[56] = 0.41;
      // attempt to make Fe smaller! (jmr/stl 18Mar2005)
      H5[56] = 0.25;

      // ESD sigma exponent
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
      printf("%s -I- using pav = %6.2f coef.\n",thisprog,KNOWN_PAV[1]);

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
      //H1[56] = 1525209.38;

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
      printf("%s -F- post-accel. voltage (%6.2f) not one of known values (%6.2f or %6.2f)\n",
	     thisprog,pav, KNOWN_PAV[0], KNOWN_PAV[1]);
      return(adfm);
    }
  }

  if( (mas <= 0.0) || (mas > 56.0) ) {
    printf("%s -F- cannot deal with mass = %.0f.\n",thisprog,mas);
    return(adfm);
  }

  im = (int)mas;
  if( H1[im] <= 0.0 ) {
    printf("%s -F- mass %.0f not in model.\n",thisprog,mas);
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
    printf("%s -F- problems with (E/q + PAPS - UL) = %.2f\n",thisprog,x);
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
    printf("%s -F- running into troubles with TOF = %.1f\n",thisprog,TOF);
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
