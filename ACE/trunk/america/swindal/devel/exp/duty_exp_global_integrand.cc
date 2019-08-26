// Test out Numerical Recipes function qsimp
// JMR, 18Sep2003

#include "swindal.h"
#include "swindal_nr.h"
#include <cmath>

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

  int max_i = 10;
  float phi;
  float sum = 0.0;
  float ig;
  float dphi;
  dphi = 2*M_PI/(float)max_i;
  for (int i = 0; i <= max_i; i++){
    phi = dphi * (float)i;
    ig = integrand(phi);
    cout << "integrand(" << phi << ") = " << ig << endl;
    sum += ig;
  }
  cout << "poor man's integral: (" << sum << ")*(" << dphi
       << ")/2*Pi = " << sum*dphi/(2.0*M_PI) << endl;

  // try out AceSwicsDutyCycle
  if (sum > 0.0) { 
    AceSwicsDutyCycle asdc;
    float duty = -1.0;
    duty = asdc.calc(100000, 0.001);
    cout << "duty = " << duty << endl;
  }
  else {
    cout << "Sum = " << sum << "; not integrating." << endl;
  }


  return(0);
}

float square(float a){
  return(a*a);
}
