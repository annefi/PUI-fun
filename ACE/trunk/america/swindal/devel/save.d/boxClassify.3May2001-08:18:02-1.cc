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

  // -- pointers to data items; used to make notation managable --
  Pha    *lpha;          // current Pha object
  Ion ion;               // current Ion

  bool fMatch;   // flag indicating that a PHA is in a range/box

  // -- Loop over PHAs then Ions --
  for (i = 0; i < pha->size(); i++){

    // pointer to ith Pha object in *pha vector
    lpha = &((*pha)[i]);
    
    for (j = 0; j < grp->size(); j++){
      ion = (*grp)[j];


      // see if tof is in forward model range for this ion
      if ( 
	  (lpha->tof >= (ion.tof[lpha->nedb] - sqrt(ion.stof[lpha->nedb]) )) &&
	  (lpha->tof <= (ion.tof[lpha->nedb] + sqrt(ion.stof[lpha->nedb]) )) ){

	fMatch = true;
      }
      else {
	fMatch = false;
      }

      // see if esd is forward model range box for this ion
      if ( 
	  (lpha->esd >= (ion.esd[lpha->nedb] - sqrt(ion.sesd[lpha->nedb]) )) &&
	  (lpha->esd <= (ion.esd[lpha->nedb] + sqrt(ion.sesd[lpha->nedb]) )) ){

	fMatch = true;
      }
      else {
	fMatch = false;
      }

      // classify if ion matched both (ie, is in box)
      if (fMatch) {
	// increment rate corresponding to this ion
	deriv->boxrates[ion.name]++;

	// save name 
	lpha->ionName = ion.name;
      }	

    }
    
  }

  return (0);
}

