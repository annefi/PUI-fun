#include "swindal.h"
#include "swindal_nr.h"

int main(int argc, char* argv[]){
  float lo, hi, incr;

  cout << "Calculates erff(x) and erf(x) from cmd. line range/incr.." << endl;

  // switch based on args
  switch (argc) {
  case 4:
    lo = atof(argv[1]);
    hi = atof(argv[2]);
    incr = atof(argv[3]);
    break;
  default:
    cout << "usage: " << argv[0] << " lo hi increment" << endl;
  }

  
  float x = lo;
  printf("%6s %6s %6s\n", "x", "erf(x)", "erff(x)");
  while (x <= hi){
    printf("%6.2f %6.2f %6.2f\n",x, erf(x), nr::erff(x));
    x += incr;
  }
}
