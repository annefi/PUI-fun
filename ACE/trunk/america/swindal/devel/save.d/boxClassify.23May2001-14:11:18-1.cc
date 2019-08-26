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

  /* --  local copies of or pointers to data items --
         Used to make notation manageable.
  */
  Pha    *lpha;          // current Pha object (pointer)
  Ion ion;               // current Ion
  int nedb;              // current EDB number

  bool fMatch;   // flag indicating that a PHA is in a range/box
  
  // -- Loop over PHAs --
  for (i = 0; i < pha->size(); i++){

    // pointer to ith Pha object in *pha vector
    lpha = &((*pha)[i]);
    
    // -- Loop over ions in analysis group --
    for (j = 0; j < grp->size(); j++){
      // define these to simplify notation
      ion = (*grp)[j];
      nedb = lpha->nedb;
      //cout << "boxClassify -D- nedb=" << nedb << endl;

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
	deriv->incrBoxrate(ion.name,nedb);

	// save name 
	lpha->ionName = ion.name;
      }	

    }
    
  }

  // copy local derivables into argument
  //*deriv = lderiv;

  return (0);
}

