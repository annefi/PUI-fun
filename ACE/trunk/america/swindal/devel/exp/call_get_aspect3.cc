// Test out calling of get_ace_aspect from C++
// JMR, 14Oct2003

#include "swindal.h"
#include "swindal_nr.h"
#include <cmath>
#include <cstdlib>
#include <sstream>

int main(){
  string thisprog = "call_get_aspect3";

  float CycleTime = 1018310400;
  float AspectAngle = -1.0;

  ostringstream cmdout;
  cmdout << "/home/jraines/ace/libace_ancil/get_ace_aspect "
	 << static_cast<long>(CycleTime);

  //char cmd[] = "/home/jraines/ace/libace_ancil/get_ace_aspect 1018310400";
  cout << thisprog << " -D- cmd=" << cmdout.str() << endl;

  FILE *PIPE;
  PIPE = popen(cmdout.str().c_str(), "r");
  char aspect_str[8];
  int retval;
  retval = fscanf(PIPE, "%s", aspect_str);
  if (retval >= 0){
    cout << thisprog << " -D- string returned by ext. aspect command: " 
	 << aspect_str << endl;

    AspectAngle = atof(aspect_str);
    cout << "AspectAngle = " << AspectAngle << endl;
  }
  else {
    cout << "-E- fscanf returned " << retval << endl;
  }
  fclose(PIPE);

  return(0);
}
