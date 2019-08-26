/* ionlist.cc -- test using ion objects with STL list and iterators
   Jim Raines, 28Mar2001
*/

#include <list.h>
#include <algo.h>
#include <iostream.h>
#include <stdlib.h>
#include <string.h>

#include "ion.h"

int main(){
  int i,j;
  /* declarations */
  list<Ion> IonList;
  list<Ion>::iterator IonList_iter;

  list<Ion> Oxygen;
  list<Ion>::iterator Oxygen_iter;
  Ion tmp("O6+",16.0,6.0);

  /* Using a list object as a container */
  /* ---------------------------------- */
  cout << "\nUsing STL list objects as containers...\n";

  /* store some ions in list */
  IonList.push_back(Ion("H+",1.0,1.0));
  IonList.push_back(Ion("He2+",4.0,2.0));
  IonList.push_back(Ion("O6+",16.0,6.0));
  IonList.push_back(Ion("Fe9+",55.847,9.0));
  IonList.push_back(Ion("O7+",16.0,7.0));

  /* print out ions */
  cout << "Printing ions:\n";
  for(IonList_iter = IonList.begin(); IonList_iter != IonList.end();
      IonList_iter++){
      (*IonList_iter).print();
      cout << "\n";
  }

  /* -- put in oxygen list if mass is 16.0 -- */

  /* init iterator to beginning */
  IonList_iter = IonList.begin(); 
  
  while(IonList_iter != IonList.end()){
  
    /* find next oxygen starting from last one found */
    IonList_iter = find(IonList_iter,IonList.end(),tmp);

    /* put oxygen into list */
    Oxygen.push_back(*IonList_iter);

    /* point iterator at next item in IonList */
    IonList_iter++;
  }

  /* print all ions with mass of 16.0 */
  Oxygen_iter = Oxygen.begin();
  cout << "\nOxygen ions found: \n";
  while(Oxygen_iter != Oxygen.end()){
    (*Oxygen_iter).print();
    cout << "\n";

    Oxygen_iter++;
  }
   
  return(0);
}
