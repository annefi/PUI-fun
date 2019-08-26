// Test out duty cycle calculation
// JMR, 27Oct2003

#include "swindal.h"
#include "swindal_nr.h"

int main(){

  AceSwicsDutyCycle asdc;

  gDbgLvl = 2;

  cout << "by integration:" << endl;
  float duty = -1.0;
  asdc.setMachAngle((0.1/360.0)*(2.0*M_PI));
  asdc.setMachAngle(0.1);

  duty = asdc.calcByIntegration(1018310400); // cycle time from doy 2002099
  cout << "duty = " << duty << endl;
  cout << "aspect = " << asdc.getAspectAngle() << endl;
  cout << "mach = " << asdc.getMachAngle() << endl;

  cout << "by interpolation:" << endl;
  duty = asdc.calcByInterpolation(1018310400); // cycle time from doy 2002099
  cout << "duty = " << duty << endl;
  cout << "aspect = " << asdc.getAspectAngle() << endl;
  cout << "mach = " << asdc.getMachAngle() << endl;

  return(0);
}
