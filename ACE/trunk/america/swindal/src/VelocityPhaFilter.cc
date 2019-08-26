/*
  File: VelocityPhaFilter.cc

  Description:
    Code for the PHA Filter class, a class which defines a PHA
    velocity filter.  The class is derived from PhaFilter.

  Author(s): Jim Raines (jmr)

  Method:

  Revision controlled by CVS:
  $Id: VelocityPhaFilter.cc,v 1.2 2004/07/02 20:46:17 jraines Exp $

  Major Modification History:
    01Mar2004   jmr   initial coding

*/
#include "swindal.h"

VelocityPhaFilter::VelocityPhaFilter(){
  VelFraction = 0.3;
}

void VelocityPhaFilter::setVelFraction(float frac){
  VelFraction = frac;
}

bool VelocityPhaFilter::passFilter(const AceSwimsPha& pha) const {
  bool retval = false;
  if (VelFraction > 0.0){
    // calculate E/q for He from speed
    double eoq_he = 4.0/2.0 * pow(pha.swspeed/438., 2.0);

    if ( pha.eq >= eoq_he*VelFraction ){
      retval = true;
    }
  }
  else{ // 0.0 => filter off, i.e. all speeds pass
    retval = true;
  }

  return(retval);
}
