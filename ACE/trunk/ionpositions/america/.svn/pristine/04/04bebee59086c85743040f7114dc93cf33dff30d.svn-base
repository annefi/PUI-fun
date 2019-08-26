/*
  File: Ion.cc

  Description:
    Ion class functions.

  Author: Jim Raines, April 2001

  Method:
    
  Major Modification History:
    

*/

#include "swindal.h"

/* ------------------- */
/* Ion Class Functions */
/* ------------------- */
// Prints values
void Ion::print(void){
  cout << "name=" << name << " mass=" << mass << " charge=" << charge;
  //printf ("name=%4s mass=%6.2f charge=%6.2f",name,mass,charge);
}

// Prints values
void Ion::dump(void){
  cout << "name=" << name << " mass=" << mass << " charge=" << charge << endl;
  cout << "forward model parameters by EDB:" << endl;

  for (int nedb = 0; nedb < esd.size(); nedb++){
    cout << "+ nedb=" << nedb 
	 << " esd=" << esd[nedb]
	 << " sesd=" << sesd[nedb]
	 << " tof=" << tof[nedb]
	 << " stof=" << stof[nedb]
	 << endl;
  }
}

// Constructor -- zeroed values
// Note: this seems to be req. for storing Ion's in a map
Ion::Ion(void){
  name = "";
  mass = 0.0;
  charge = 0.0;

  tof.reserve(MAXEDB);
  tof.assign(MAXEDB,0.0);

  stof.reserve(MAXEDB);
  stof.assign(MAXEDB,0.0);

  esd.reserve(MAXEDB);
  esd.assign(MAXEDB,0.0);

  sesd.reserve(MAXEDB);
  sesd.assign(MAXEDB,0.0);
}

// Constructor -- initialized values
Ion::Ion(const string i_name, float i_mass, float i_charge){
  name = i_name;
  mass = i_mass;
  charge = i_charge;

  // Note: These are given values in the AnalysisData constructor
  //       It cannot be done here because of I/O overhead of opening a 
  //       data file for each Ion.
  tof.reserve(MAXEDB);
  tof.assign(MAXEDB,0.0);

  stof.reserve(MAXEDB);
  stof.assign(MAXEDB,0.0);

  esd.reserve(MAXEDB);
  esd.assign(MAXEDB,0.0);

  sesd.reserve(MAXEDB);
  sesd.assign(MAXEDB,0.0);
}

// Equality operator for Ion class
bool Ion::operator== (const Ion &right) const {
  return( name == right.name);
}

// Copy constructor because vectors do not copy with default copy
Ion::Ion(const Ion& ion){
  name = ion.name;
  mass = ion.mass;
  charge = ion.charge;

  for(int i = 0; i < ion.esd.size(); i++){
    esd.push_back(ion.esd[i]);
  }

  for(int i = 0; i < ion.tof.size(); i++){
    tof.push_back(ion.tof[i]);
  }

  for(int i = 0; i < ion.sesd.size(); i++){
    sesd.push_back(ion.sesd[i]);
  }

  for(int i = 0; i < ion.stof.size(); i++){
    stof.push_back(ion.stof[i]);
  }

}

// Assignment copy
Ion& Ion::operator= (const Ion& ion){

  if (this != &ion){ // guard against self assignment
    /* --- copy --- 
       note: if I knew how to call the copy constructor
       explicitly, I would do that here instead.  */

    name = ion.name;
    mass = ion.mass;
    charge = ion.charge;

    for(int i = 0; i < ion.esd.size(); i++){
      esd[i] = ion.esd[i];
    }

    for(int i = 0; i < ion.tof.size(); i++){
      tof[i] = ion.tof[i];
    }

    for(int i = 0; i < ion.sesd.size(); i++){
      sesd[i] = ion.sesd[i];
    }

    for(int i = 0; i < ion.stof.size(); i++){
      stof[i] = ion.stof[i];
    }

  }

  return *this;
}
