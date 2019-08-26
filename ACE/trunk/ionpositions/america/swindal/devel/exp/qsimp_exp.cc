// Test out Numerical Recipes function qsimp
// JMR, 18Sep2003

#include "swindal.h"
#include "swindal_nr.h"

float square(float a);

int main(){

  // plain old function (global) called through pointer
  float (*pfunc) (float);
  pfunc = &square;
  printf("%f\n",pfunc(3.0));
  // works

//   // try Numerical Recipes qsimp integration on times function
//   float integral;
//   float (*pfunc4) (float) = square;
//   integral = nr::qsimp( pfunc4, 1.0, 3.0);
//   printf("integral=%f\n",integral);

  // try out AceSwicsDutyCycle
  AceSwicsDutyCycle asdc;
  float duty;
  duty = asdc.calc(100000, 0.001);
  cout << "duty = " << duty << endl;

  return(0);
}

float square(float a){
  return(a*a);
}
