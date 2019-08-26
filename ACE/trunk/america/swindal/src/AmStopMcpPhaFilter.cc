/*
  File: AmStopMcpPhaFilter.cc

  Description:
    Code for AmStopMcpPhaFilter class.  This filter excludes PHAs
    that do not have sensible position on the stop MCP, given PHA
    energy, m/q, He2+ speed, and hyperbola/fin voltages.

  Author(s): Jim Raines (jmr)

  Method:

  Revision controlled by CVS:
  $Id: AmStopMcpPhaFilter.cc,v 1.1 2004/04/27 20:39:42 jraines Exp $

  Major Modification History:
    17Mar2004   jmr   initial coding

*/
#include "swindal.h"
#include <cmath>
#include <cfloat>

AmStopMcpPhaFilter::AmStopMcpPhaFilter(const InstrumentConstants& ic,
				       const AceSwimsHousekeeping& hk){
  string thisprog = "AmStopMcpPhaFilter::AmStopMcpPhaFilter";
  string build_info = __DATE__;
  build_info = build_info + " ";
  build_info = build_info + __TIME__;
  string rcs_id = "$Id: AmStopMcpPhaFilter.cc,v 1.1 2004/04/27 20:39:42 jraines Exp $";

  testStopPos = false;

  HK = &hk;
  IC = ic;
}

bool AmStopMcpPhaFilter::passFilter(const AceSwimsPha& pha) const{
  // Explanation given where it was possible to determine.  Otherwise, it is
  // the same as getdata5.cpp.  See AmStopMcpPhaFilter.h for details.
  string thisprog = "AmStopMcpPhaFilter::passFilter";
  //cout << thisprog << " -I- entering" << endl;

  // atomic number of ion, approximated as mass/2
  int Z = static_cast<int>(pha.mm/2);

  // energy/mass, conv. factor: 439.29 (units?)
  float epm = pow(pha.swspeed/429.29, 2);

  // charge before entering foil (e)
  float q = epm * pha.mm / pha.eq;

  // test q
  bool q_ok = false;
  if (pha.mm/q > 0.0 && q > 0. && q < pha.mm) q_ok = true;

  // exit here if not configured to test stop position
  if (! testStopPos) return(q_ok);

  // re-calculate energy/mass, now with approx. charge
  epm = ( q * (pha.eq - HK->getV_f()) )/pha.mm;

  // predicted residual energy
  // no idea where this is from or what this formula represents
  float eres = (0.99 * pha.mm - 0.26) * epm - (0.34 * pha.mm + 0.11);

  if (eres <= 0){
    if (gDbgLvl >= 3){
      cout << thisprog << " -I- residual energy < 0" << endl;
    }
    return(false);
  }

  // predict energy lost in foil
  float de = epm * pha.mm - eres;

  // angular abberation, See Marc Gonin's thesis for details.
  float dphi = 2.1027 * pow(epm, -1.6726);

  float sig = 13.642 * pow(Z,.7455) * pow(IC.getFoilThickness(),.6748) *
    pow(eres, -.9002);

  // parameter governing foil loss contribution to position
  float LossScalar = 2;

  // calculate lowest reasonable position on MCP
  float pos_low = 1040 * sqrt((epm * pha.mm - LossScalar*de)/HK->getV_hyp())*
    cos((45 + dphi + 3*sig)/180*M_PI) - 165.7;
  
  // calculate highest reasonable position on MCP 
  // (same formular as low w/diff. scalar)
  LossScalar = 0; // remove foil loss contribution
  float pos_high = 1040 * sqrt((epm * pha.mm - LossScalar*de)/HK->getV_hyp())*
    cos((45 + dphi + 3*sig)/180*M_PI) - 165.7;

  // force into bounds
  // --- lower
  if (pos_low < 100) pos_low = 100;
  if (pos_high < 100) pos_high = 100;
  // --- upper
  if (pos_low > 930) pos_low = 930;
  if (pos_high > 930) pos_high = 930;

  // calculate actual position
  float pos;
  pos = 1024*pha.stopk2/(pha.stopk1 + pha.stopk2 + 1);

  // test versus allowed range
  bool pos_ok = false;
  if (pos >= pos_low && pos < pos_high) pos_ok = true;
  
  // just for debugging, to see that false does something
  //if( (float)random()/(float)RAND_MAX >= .5 ) pos_ok = false;

  return(q_ok && pos_ok);
}

void AmStopMcpPhaFilter::setTestStopPos(bool value){
  testStopPos = value;
}
 
bool AmStopMcpPhaFilter::getTestStopPos(){
  return(testStopPos); 
}
