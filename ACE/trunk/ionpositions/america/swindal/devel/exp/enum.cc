// try out enumerations and such
// J. Raines, 28Oct2003

#include <iostream>
#include <stl.h>

int main(){

  enum Element {H, He, C, N, O, Ne, Mg, Si, S, Ar, Fe, Kr};

  Element current_element;

  current_element = He;
  cout << "current_element = " << current_element << endl;

  vector<int> a;
  a.push_back(He);
  a.push_back(Ne);
  a.push_back(Ar);
  a.push_back(Kr);

  for (int i = 0; i < a.size(); i++){
    cout << "a[" << i << "]=" << a[i] << endl;
  }
  
  return(0);
}
