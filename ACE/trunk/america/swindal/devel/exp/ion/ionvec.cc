/* ionvec.cc -- test using ion objects with STL vectors and iterators
   Jim Raines, 28Mar2001
*/


#include <vector.h>
#include <algo.h>
#include <iostream.h>
#include <stdlib.h>
#include <string.h>

#include "ion.h"

int main(){
  int i,j;
  /* declarations */
  vector<Ion> Ions;
  vector<Ion> O;

  /* Using vector object as a container */
  /* ---------------------------------- */
  cout << "\nEntering vector part of code...\n";

  /* store some ions in the vector */
  Ions.push_back(Ion("H+",1.0,1.0));
  Ions.push_back(Ion("He2+",4.0,2.0));
  Ions.push_back(Ion("O6+",16.0,6.0));
  Ions.push_back(Ion("Fe9+",55.847,9.0));
  Ions.push_back(Ion("O7+",16.0,7.0));

  /* print ions */
  for(i = 0; i < Ions.size(); i++){
    cout << "Printing vector element " << i << ": ";
    Ions[i].print();
    cout << "\n";
  }

  /* put in oxygen list if mass is 16.0 */
  for(i = 0; i < Ions.size(); i++){
    if (Ions[i].mass == 16.0){
      O.push_back(Ions[i]);
    }
  }

  /* print oxygen ions */
  for(i = 0; i < O.size(); i++){
    cout << "Oxygen ion #" << i << ": " ;
    O[i].print();
    cout << "\n";
  }

  return(0);
}
