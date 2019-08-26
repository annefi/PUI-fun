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
}

// Constructor -- initialized values
Ion::Ion(const string i_name, float i_mass, float i_charge){
  name = i_name;
  mass = i_mass;
  charge = i_charge;
}

// Equality operator for Ion class
bool Ion::operator== (const Ion &right) const {
  return( name == right.name);
}

