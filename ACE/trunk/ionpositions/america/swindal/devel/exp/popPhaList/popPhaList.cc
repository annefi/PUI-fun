#include <list>
#include <iostream>
#include "../../swindal.h"

int main(){

  int i;
  list<Pha> l;
  list<Pha>::iterator l_it;
  Pha lpha;

  for (i = 0; i < 10; i++){
    lpha.nedb = i;
    l.push_back(lpha);
  }

  cout << "Dumping l:\n";
  for (l_it = l.begin(); l_it != l.end(); l_it++){
    cout << (*l_it).nedb << " ";
  }
  cout << "\n";

  cout << "Popping off l:\n";
  l_it = l.begin();
  while (l_it != l.end()){
    for (; l_it != l.end(); l_it++){
      cout << (*l_it).nedb << " ";
    }
    cout << "\n";
    l.pop_front();
    l_it = l.begin();
  }
  cout << "\n";


}
