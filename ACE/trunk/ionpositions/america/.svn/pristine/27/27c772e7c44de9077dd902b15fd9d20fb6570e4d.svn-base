/*
  File: correctFeFM.cc

  Description:
    Correct Iron Forward Model with deltas from offline peak pick and fit.

  Author(s): Jim Raines (jmr)

  Method:
    Uses data produced by fmpick_cfe.pro from picking Fe peaks and calculating
    the difference between these and the forward model.

  Revision controlled by CVS:
  $Id: setPrGaussCutoff.cc,v 1.5 2005/02/08 21:40:35 jraines Exp $

  Major Modification History:
    26Nov2003   jmr   initial coding

*/
#include "swindal.h"

int setPrGaussCutoff(float PRGaussCutoff, int FirstHSFe, 
		     float PRGaussCutoffHSFe, AnalysisData& ad){
  const string thisprog = "setPrGaussCutoff";

  vector<string> hsfe_ions;
  for (int s = 0; s < ad.Ions.size(); s++){
    // set them all
    ad.Ions[s].PrGaussCutoff = PRGaussCutoff;

    // reset selected ions to another values
    float chg = ad.Ions[s].charge;
    if (ad.Ions[s].element == "Fe"){
      if (chg >= FirstHSFe) {
	ad.Ions[s].PrGaussCutoff = PRGaussCutoffHSFe;
	hsfe_ions.push_back(ad.Ions[s].name);
      }
    }
  }

  if (gDbgLvl >= 1){
    cout << thisprog << " -I- assigned high-state Fe prob. rates"
	 << " Gauss cutoff (" << PRGaussCutoffHSFe 
	 << ") to the following ions:";
    for (int i = 0; i < hsfe_ions.size(); i++) cout << " " << hsfe_ions[i];
    cout << endl;
    cout << thisprog << " -I- remaining ions assigned PRGCO = " 
	 << PRGaussCutoff << endl;
  }

  return(0);
}
