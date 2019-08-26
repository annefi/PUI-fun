#include "heavyside.h"

using namespace std;


double heavyside(double x)
{
  if (x >= 0.) {
    return 0.;
  }
  else{
    return 1.;
  }
}
