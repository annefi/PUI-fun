/*
  File: AceSwimsConstants.h

  Description:
    Code for AceSwicsConstants class, a derived class set up to
    handle all fixed constants from ACE/SWICS.  The constants are set
    in the constructor and may only be read from there.

  Author(s): Jim Raines (jmr)

  Method:

  Revision controlled by CVS:
  $Id: AceSwicsConstants.cc,v 1.1 2004/04/27 20:39:36 jraines Exp $

  Major Modification History:
    20Feb2004   jmr   initial coding

*/

#include "swindal.h"

AceSwicsConstants::AceSwicsConstants(){
  GeomFactor  = 0.0185;  // cm^2, from swindal.h ref. 1
  EqAcceptFac = 0.064;   // dimensionless, from ACE paper
  NumEdb = 60;

  /* first EDB to read
     According to Simon Hefti: 
     EDB 0 is from last cycle 
     EDB 1 is voltage ramp up 
     EDB 2 should be first good one (still need to
     shift them back one (i.e., use nedb - 1 for
     e/q function.)
  */  
  FirstEdb = 2;

  /* Length of TOF region in cm */
  TofDistance = 10.0;

  /* dimensions in tof and esd space */
  NumTofCh = 1024;
  NumEsdCh = 256;

  /* dimensions in mass and m/q space */
  NumMassCh = 122;
  NumMqCh = 124;

  /* conversion from channels to physical units
   Constants from Simon Hefti. */
  Tof_Ns_Per_Ch = 0.1955;   /* 0.1955 ns/ch */
  Esd_Kev_Per_Ch = 2.395;   /* 2.395 keV/ch */

}
