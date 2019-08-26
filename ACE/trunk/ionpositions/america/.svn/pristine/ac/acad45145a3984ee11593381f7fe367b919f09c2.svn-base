// Try out Numerical Recipes integration (and the pointer passing)
// JMR, 18Sep2003

#include "swindal.h"
#include "swindal_nr.h"

float square(float a);

int main(){

  // plain old function (global) called through pointer
  float (*pfunc) (float);
  pfunc = &square;
  printf("square(3.0)=%f\n",pfunc(3.0));
  // works

  float integral;
  integral = nr::qtrap( pfunc, 1.0, 3.0);
  printf("integral(square,1.0,3.0)=%f\n",integral);
  // Works; Answer should be 8.666687

  return(0);
}

float square(float a){
  return(a*a);
}
