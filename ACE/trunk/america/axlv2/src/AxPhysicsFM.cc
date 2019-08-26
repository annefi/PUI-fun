/*
  File: AxPhysicsFM.cc

  Description:
    ACE/SWICS physics-based forward model object.

  Author(s): Jim Raines (jmr)

  Method:
    Right now, this is just a wrapper for xfmexp_phys.c.

  Revision controlled by CVS:
  $Id: AxPhysicsFM.cc,v 1.1 2004/10/19 13:56:10 jraines Exp $

  Major Modification History:
    16Sep2004   jmr   initial coding

*/

#include "swindal.h"
#include "axlv2.h"

AxPhysicsFM::AxPhysicsFM() {
  // make routine and build info available to code and 
  // from binary file via 'strings' program
  const string thisprog = "AxPhysicsFM::AxPhysicsFM";
  string build_info = __DATE__;
  build_info = build_info + " ";
  build_info = build_info + __TIME__;
  const string rcs_id = "$Id: AxPhysicsFM.cc,v 1.1 2004/10/19 13:56:10 jraines Exp $";

}

int AxPhysicsFM::load(AnalysisData& ad, double pav){
  double *xfm;
  for(int s = 0; s < ad.Ions.size(); s++){
    for (int nedb = FIRSTEDB; nedb < MAXEDB; nedb++){
      xfm = xfmexp_phys(ad.Eqtab[nedb], pav, 
			ad.Ions[s].mass, ad.Ions[s].charge);

      ad.Ions[s].tof[nedb] = xfm[0];
      ad.Ions[s].stof[nedb] = xfm[1];
      ad.Ions[s].esd[nedb] = 0.88*xfm[2];
      ad.Ions[s].sesd[nedb] = xfm[3];
    }
  }
  
}
