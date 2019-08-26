/*
  File: setErrorLevels

  Description:
    Set error levels for all ions in the analysis.  The levels control
    which data is thrown out or marked with quality flags later in the
    DistFunc object.

  Author(s): Jim Raines (jmr)

  Method:

    Right now, there are only two sets of levels, one for high charge
    species and one for the rest.  The high charge species have counts
    spread over a wider range of states and thus tend to have a higher
    error.

  Revision controlled by CVS:
  $Id: setErrorLevels.cc,v 1.1 2005/03/24 21:41:06 jraines Exp $

  Major Modification History:
    24Mar2005   jmr   Adapted from setPrGaussCutoff.cc

*/
#include "swindal.h"

int setErrorLevels(AnalysisData& ad){
  const string thisprog = "setErrorLevels";

  vector <string> hs_elements;

  // ===> configure <===

  // elements considered high state (hs) for error purposes
  hs_elements.push_back("Si");
  hs_elements.push_back("S");
  hs_elements.push_back("Fe");

  // levels for elements not specified in hs_elements array
  const float N_ERR_YELLOW = 0.35;
  const float N_ERR_RED    = 0.50;

  const float V_ERR_YELLOW  = -1.0;
  const float V_ERR_RED     = -1.0;

  const float VTH_ERR_YELLOW  = -1.0;
  const float VTH_ERR_RED     = 2.0;

  // levels for elements specified in hs_elements array
  const float N_ERR_YELLOW_HS = 0.50;
  const float N_ERR_RED_HS    = 1.00;

  // ===> end configure <===

  vector<string> hs_ions; // holds all ions set to h.s. levels
  for (int s = 0; s < ad.Ions.size(); s++){
    // set them all
    ad.Ions[s].errlvl.n_yellow = N_ERR_YELLOW;
    ad.Ions[s].errlvl.n_red = N_ERR_RED;

    ad.Ions[s].errlvl.v_yellow = V_ERR_YELLOW;
    ad.Ions[s].errlvl.v_red = V_ERR_RED;

    ad.Ions[s].errlvl.vth_yellow = VTH_ERR_YELLOW;
    ad.Ions[s].errlvl.vth_red = VTH_ERR_RED;

    // reset ions of selected elements to other values
    for (int ielem = 0; ielem < hs_elements.size(); ielem++){
      if (ad.Ions[s].element == hs_elements[ielem]){

	ad.Ions[s].errlvl.n_yellow = N_ERR_YELLOW_HS;
	ad.Ions[s].errlvl.n_red = N_ERR_RED_HS;

	hs_ions.push_back(ad.Ions[s].name);
      }
    }
  }

  if (gDbgLvl >= 1){
    cout << thisprog << " -I- assigned high-state error levels of ("
	 << N_ERR_YELLOW_HS << ", " << N_ERR_RED_HS
	 << ") to the following ions:";
    for (int i = 0; i < hs_ions.size(); i++) cout << " " << hs_ions[i];
    cout << endl;
    cout << thisprog << " -I- remaining ions assigned error levels of (" 
	 << N_ERR_YELLOW << ", " << N_ERR_RED
	 << ") " << endl;
  }

  return(0);
}
