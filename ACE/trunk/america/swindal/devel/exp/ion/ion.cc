/* ion.cc -- ion class functions
   Jim Raines, 28Mar2001
 */

#include "ion.h"
#include <iostream.h>
#include <string.h>
#include <stdio.h>

// Prints values
void Ion::print(void){
  printf ("name=%4s mass=%6.2f charge=%6.2f",name,mass,charge);
}

// Constructor -- initialized values
Ion::Ion(const char i_name[], float i_mass, float i_charge){
  strcpy(name, i_name);
  mass = i_mass;
  charge = i_charge;
}

// Equality operator for Ion class
bool Ion::operator== (const Ion &right) const {
  int result;
  
//   cout << "Ion::operator== testing: " << 
//     mass << " right mass = " << right.mass ;
//   cout << "\n";

  if (mass == right.mass) result = 1;
  else result = 0;

  return(result);
  //  return(mass == right.mass);
}
