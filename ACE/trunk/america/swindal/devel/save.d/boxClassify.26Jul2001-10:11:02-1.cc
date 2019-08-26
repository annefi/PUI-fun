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
  float tof;                     // tof for current PHA
  float esd;                     // esd for current PHA
  int nedb;                      // nedb for current PHA
  vector<Pha>::iterator pha_it;
  vector<Ion>::iterator grp_it;

  bool fMatch;   // flag indicating that a PHA is in a range/box
  
  // -- Loop over PHAs --
  for (pha_it = pha->begin(); pha_it != pha->end(); pha_it++){

    // -- Loop over ions in analysis group --
    for (grp_it = grp->begin(); grp_it != grp->end(); grp_it++){
      // define these to simplify notation
      tof = pha_it->tof;
      esd = pha_it->esd;
      nedb = pha_it->nedb;

      //cout << "boxClassify -D- grp_it->name=" << grp_it->name << endl;

      // see if tof is in forward model range for this ion
      if ( 
	  (tof >= (grp_it->tof[nedb] - sqrt(grp_it->stof[nedb]) )) &&
	  (tof <= (grp_it->tof[nedb] + sqrt(grp_it->stof[nedb]) )) ){

	fMatch = true;
      }
      else {
	fMatch = false;
      }

      // see if esd is forward model range box for this ion
      if ( 
	  (esd >= (grp_it->esd[nedb] - sqrt(grp_it->sesd[nedb]) )) &&
	  (esd <= (grp_it->esd[nedb] + sqrt(grp_it->sesd[nedb]) )) ){

	fMatch = true;
      }
      else {
	fMatch = false;
      }

      // classify if ion matched both (ie, is in box)
      if (fMatch) {
	// increment rate corresponding to this ion
	deriv->incrBoxrate(grp_it->name , nedb);

	// save name 
	pha_it->ionName = grp_it->name;
      }	

    }
    
  }

  return (0);
}

