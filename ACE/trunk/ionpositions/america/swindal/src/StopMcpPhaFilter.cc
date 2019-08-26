/*
  File: StopMcpPhaFilter.cc

  Description:
    Code for StopMcpPhaFilter class.  This filter excludes PHAs
    that do not have sensible position on the stop MCP, given PHA
    energy, m/q, He2+ speed, and hyperbola/fin voltages.

  Author(s): Jim Raines (jmr)

  Method:

  Revision controlled by CVS:
  $Id: StopMcpPhaFilter.cc,v 1.1 2004/04/27 20:39:49 jraines Exp $

  Major Modification History:
    17Mar2004   jmr   initial coding

*/
#include "swindal.h"

  StopMcpPhaFilter::StopMcpPhaFilter(const InstrumentHousekeeping& hk, 
				     const InstrumentConstants& ic){
  string thisprog = "StopMcpPhaFilter::StopMcpPhaFilter";
  string build_info = __DATE__;
  build_info = build_info + " ";
  build_info = build_info + __TIME__;
  string rcs_id = "$Id: StopMcpPhaFilter.cc,v 1.1 2004/04/27 20:39:49 jraines Exp $";

  HK = hk;
  IC = ic;
}

bool StopMcpPhaFilter::passFilter(const Pha& pha) const{
  // Explanation given where it was possible to determine.  Otherwise, it is
  // the same as getdata5.cpp.  See StopMcpPhaFilter.h for details.

  // atomic number of ion, approximated as mass/2
  int Z = static_cast<int>(pha.mass/2);

  // energy/mass, conv. factor: 439.29 (units?)
  float epm = pow(pha.swspeed/429.29, 2);

  // charge before entering foil (e)
  float q = epm * pha.mm / pha.eq;

  // re-calculate energy/mass, now with approx. charge
  epm = ( q * (pha.eq - ad.HK.getV_f()) )/pha.mm;

  // predicted residual energy
  // no idea where this is from or what this formula represents
  float eres = (0.99 * pha.mm - 0.26) * epm - (0.34 * pha.mm + 0.11);

  if (eres <= 0){
    if (gDbgLvl >= 3){
      cout << thisprog << " -I- resudual energy < 0" << endl;
    }
    return(false);
  }

  // predict energy lost in foil
  float de = epm * mass - eres;

  // angular abberation, See Marc Gonin's thesis for details.
  float dphi = 2.1027 * pow(epm, -1.6726);

  float sig = 13.642 * pow(Z,.7455) * pow(IC.getFoilThickness(),.6748) *
    pow(eres, -.9002);

  // parameter governing foil loss contribution to position
  float LossScalar = 2;

  // calculate low position on MCP
  float pos_low = 1040 * sqrt((epm * pha.mm - LossScalar*de)/ad.HK.getV_hyp())*
    cos((45 + dphi + 3*sig)/180*MPI) - 165.7;
  
  // calculate high position on MCP (same formular as low w/diff. scalar)
  LossScalar = 0; // remove foil loss contribution
  float pos_high = 1040 * sqrt((epm * pha.mm - LossScalar*de)/ad.HK.getV_hyp())*
    cos((45 + dphi + 3*sig)/180*MPI) - 165.7;

  // force into bounds
  // --- lower
  if (pos_low < 100) pos_low = 100;
  if (pos_high < 100) pos_high = 100;
  // --- upper
  if (pos_low > 930) pos_low = 930;
  if (pos_high > 930) pos_high = 930;

  if (ph.mm/q > 0.0 && q > 0. && q < mass) {
    return(true);
  }
  else{
    return(false);
  }
}
