// Calculate duty cycle by approximate integral (for debugging)
// JMR, 17Oct2003

#include "swindal.h"
#include "swindal_nr.h"
#include <cmath>


int main(){

  gDbgLvl = 3;

  AceSwicsDutyCycle duty;
  duty.setMachAngle(0.1);
  
  // this section first so duty.calc inits AspectAngle
  cout << "From object:" << endl;
  float real_duty;
  real_duty = duty.calc(1018310400); // cycle time from doy 2002099
  cout << "duty = " << real_duty << endl;
  cout << "aspect = " << duty.getAspectAngle() << endl;
  cout << "mach = " << duty.getMachAngle() << endl;

  cout << endl << "Beginning integral approximation..." << endl;
  int max_i = 10;
  float phi;
  float sum = 0.0;
  float ig;
  float dphi;
  dphi = 2*M_PI/(float)max_i;
  for (int i = 0; i <= max_i; i++){
    phi = dphi * (float)i;
    ig = duty.integrand(phi);
    cout << "integrand(" << phi << ") = " << ig << endl;
    sum += ig;
  }
  cout << "poor man's integral: (" << sum << ")*(" << dphi
       << ")/2*Pi = " << sum*dphi/(2.0*M_PI) << endl;

  return(0);
}
