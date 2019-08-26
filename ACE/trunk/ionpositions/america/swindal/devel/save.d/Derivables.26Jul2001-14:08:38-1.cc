/*  
  Filename: Derivables.cc

  Description:
  Class of derivable quantities for swindal.  Consists largely of containers.

  Author:  Jim Raines, 1May2001

  Method:

  Major Modification History:

*/

#include "swindal.h"

/* ----------------
   PUBLIC FUNCTIONS
   ----------------
*/

// Constructor
Derivables::Derivables(void){
  //initSwindal();
}

/* --- Access Functions --- */

long int Derivables::getBoxrate(string ionName, int nedb){
  initBoxrate(ionName);
  return boxrates[ionName][nedb];
}

int Derivables::setBoxrate(string ionName, int nedb, int val){
  initBoxrate(ionName);
  boxrates[ionName][nedb] = val;
  return(0);
}
  
int Derivables::incrBoxrate(string ionName, int nedb){
  initBoxrate(ionName);
  boxrates[ionName][nedb]++;
  return(0);
}
  
/* -----------------
   PRIVATE FUNCTIONS
   -----------------
*/

int Derivables::initBoxrate(string key){
  map<string, vector<long int> >::iterator br_it;

  br_it = boxrates.find(key);  // returns end if not found

  // grow vector to req. elements if key is new
  if (br_it == boxrates.end()){
    // initialize vector (MAXEDB is used for dimensioning
    for (int i = 0; i < MAXEDB; i++){
      boxrates[key].push_back(0);
    }
  }

  return(0);
}
