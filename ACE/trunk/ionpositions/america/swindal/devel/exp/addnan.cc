// I was trying to show that adding a nan to a float results in a nan,
// but c comes out a 0 when the float size is exceeded.
#include "swindal.h"

int main(){
  float a,b,c;

  a = 1.0e-15;
  b = 1.0e-25;

  c = a*(a*b + a*b);

  cout << " a=" << a
       << " b=" << b
       << " c=" << c 
       << endl;

  return(0);
}
