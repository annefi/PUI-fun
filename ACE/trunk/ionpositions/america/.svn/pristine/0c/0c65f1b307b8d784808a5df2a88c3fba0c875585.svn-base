/*
  File: correctFM_phys.cc

  Description:
    Correct Forward Model for specified elements with physics forward model.

  Author(s): Jim Raines (jmr)

  Method:
    Uses xfmexp_phys, a physics-based forward forward model, adapted from 
    work at Univ. of Maryland and Bob Lundgren.

  Revision controlled by CVS:
  $Id: correctFM_phys.cc,v 1.1 2005/03/18 21:27:10 jraines Exp $

  Major Modification History:
    18Mar2005   jmr   Adapted from correctFeFM_phys.cc and setPrGaussCutoff.cc

*/
#include "swindal.h"
#include "axlv2.h"

int correctFM_phys(AnalysisData& ad, const vector<string>& elements, 
		   double pav){
  const string thisprog = "correctFM_phys";

  int DbgLvl=0;
  string fmfile;
  if (gDbgLvl >= 2) {
    cout << thisprog << " -I- dumping before modification:" << endl;
    fmfile = thisprog + "_before.dat";
    ad.outputFM(fmfile);
  }

  double *xfm;
   for (int s = 0; s < ad.Ions.size(); s++){
    for (int ielem = 0; ielem < elements.size(); ielem++){
      if (ad.Ions[s].element == elements[ielem]){
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
  }


   if (DbgLvl>=1){
     cout << thisprog 
       << " -I- replaced FM values with physics FM output for elements:";
     for (int ielem = 0; ielem < elements.size(); ielem++){
       cout << " " << elements[ielem];
     }
     cout << endl;
   }
  if (gDbgLvl >= 2) {
    cout << thisprog << " -I- dumping after modification:" << endl;
    fmfile = thisprog + "_after.dat";
    ad.outputFM(fmfile);
  }

  return(0);
}
