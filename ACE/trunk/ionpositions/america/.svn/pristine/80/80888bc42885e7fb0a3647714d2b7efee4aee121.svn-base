/*  
  Filename: boxClassify.cc

  Description:
  Classify PHA words into forward model-predicted boxes.

  Author:  Jim Raines, 1May2001

  Method:

  Major Modification History:

*/

#include "swindal.h"

int boxClassify(vector<Pha> *pha, vector<Ion> *grp, Derivables *deriv ){
  int i,j;      // loop counters

  // 
  AnalysisData ad;

  // pointers to data items; used to make notation managable
  Pha    *lpha;
  
  double ltof;
  double lstof;

  double lesd;
  double lsesd;

  bool fMatch;   // flag indicating that a PHA is in a range/box

  map<string,Ion>::iterator lIons_iter;

  // Loop over PHAs then Ions
  for (i = 0; i < pha->size(); i++){

    // pointer to ith Pha object in *pha vector
    lpha = &((*pha)[i]);
    
    for (ad.Ions_iter = ad.Ions.begin(); 
	 ad.Ions_iter != ad.Ions.end();
	 ad.Ions_iter++){

      lIons_iter = ad.Ions_iter;

      // check tof
      //      ltof = (*ad.Ions_iter).second.tof;      // makes notation managable
      ltof = lIons_iter->second.tof;      // makes notation managable
      lstof = ad.Ions_iter->second.stof;
      if ( ( lpha->tof >= ( ltof - sqrt(lstof) ) ) &&
	   ( lpha->tof <= ( ltof + sqrt(lstof) ) ) ){

	fMatch = true;
      }
      else {
	fMatch = false;
      }

      // check esd
      iesd = &(ad.Ions_iter->second.esd);     // makes notation managable
      isesd = &(ad.Ions_iter->second.sesd);
      if ( ( lpha->esd >= ( lesd - sqrt(lsesd) ) ) &&
	   ( lpha->esd <= ( lesd + sqrt(lsesd) ) ) ){

	fMatch = true;
      }
      else {
	fMatch = false;
      }

      // classify if ion matched both (ie, is in box)
      if (fMatch) {
	// increment rate corresponding to this ion
	deriv->boxrates[ad.Ions_iter->first]++;

	// save name 
	lpha->ionName = ad.Ions_iter->first;
      }	

    }
    
  }

}

