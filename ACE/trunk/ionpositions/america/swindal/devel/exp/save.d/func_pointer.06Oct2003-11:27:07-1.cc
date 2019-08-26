// Try out various ways of making/using a pointer to a function
// JMR, 18Sep2003

#include <stl.h>
#include <cstdlib>
#include <cstdio>

#include "swindal.h"
#include "swindal_nr.h"

class ExpClass {
public:
  static float ExpClass::times2(float);
  float ExpClass::integrand(float value);

private:
  
};

 float ExpClass::times2(float value){
  return(value*2.0);
}

// f(x) = x
float ExpClass::integrand(float value){
  return(value*value*value);
}

// global (non-member) function
float times(float a, float b);

float square(float a);

int main(){

  // plain old function (global) called through pointer
  float (*pfunc) (float,float);
  pfunc = &times;
  printf("times(3.0,4.0)=%f\n",pfunc(3.0,4.0));
  // works

  // member function called as member function
  ExpClass c;
  printf("times2(4.0)=%f\n",c.times2(4.0));
  // works

  // member function called through pointer
  // Note:  pfunc2 is a pointer to a float(float) of class ExpClass only!
//   float (ExpClass::*pfunc2) (float) = &ExpClass::times2;
//   ExpClass c2;
//   printf("ExpClass::times2(3.0)=%f\n",(c2.*pfunc2)(3.0));
  // works

  // try Numerical Recipes qsimp integration on times function
  float integral;
  float (*pfunc4) (float) = square;
  integral = nr::qtrap( pfunc4, 1.0, 3.0);
  printf("integral(square,1.0,3.0)=%f\n",integral);


  // try Numerical Recipes qsimp integration on times2 member function
  // cast pointer to float (ExpClass::*) float as float (*) float
  //float (*pfunc5) (float) = (float (*) (float))pfunc2;
  float (*pfunc5) (float) = &ExpClass::times2;
  integral = nr::qtrap( pfunc5, 1.0, 3.0);
  printf("integral(times2,1.0,3.0)=%f\n",integral);

  return(0);

}

float times(float a, float b){
  return(a*b);
}

float square(float a){
  return(a*a);
}
