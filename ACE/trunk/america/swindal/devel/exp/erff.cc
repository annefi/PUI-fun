#include "swindal.h"

#include <cmath>

extern "C" {
  // NOTE: NR select conflicts with the system call; work around
  //#include "nr.h"
  float erff(float x);
}

int main(int argc, char* argv[]){
  
  float x;
  cout << "Calculates erff(x) from input value; use ctrl-c to exit." << endl;
  while (1){
    cout << "x: ";
    cin >> x;
    cout << "Numerical Reciples: erff(" << x << ")=" << erff(x)   << endl;
    cout << "C math: erf(" << x << ")=" << erf(x)   << endl;
  }
}
