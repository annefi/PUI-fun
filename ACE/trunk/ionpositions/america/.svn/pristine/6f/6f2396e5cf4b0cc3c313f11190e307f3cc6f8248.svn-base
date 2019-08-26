// Trying out string interpolation the C++ way
// JMR, 13Oct2003

#include "swindal.h"
#include "swindal_nr.h"
#include <cmath>
#include <cstdlib>
#include <sstream>
#include <iomanip>

int main(){
  
  ostringstream cmdout;
  string cmd = "/home/jraines/ace/libace_ancil/get_ace_aspect ";

  float CycleTime = 1018310400;
  long lCycleTime = static_cast<long>(CycleTime);

  cmdout << cmd  << static_cast<long>(CycleTime);

  cout << cmdout.str() << endl;

  cout << "CycleTime = " << static_cast<long>(CycleTime) << endl;

  return(0);
}
