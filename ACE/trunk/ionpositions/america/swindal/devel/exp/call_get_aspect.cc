// Test out calling of get_ace_aspect from C++
// JMR, 04Oct2003

#include "swindal.h"
#include "swindal_nr.h"
#include <cmath>
#include <cstdlib>

int main(){
  float CycleTime = 1018310400;

  char cmd[255];
  

  system("/home/jraines/ace/libace_ancil/get_ace_aspect 1018310400");

  FILE *PIPE;
  PIPE = popen("/home/jraines/ace/libace_ancil/get_ace_aspect 1018310400", "r");
  float aspect = -1.0;
  char aspect_str[8];

  int retval;
  retval = fread(&aspect_str, sizeof(aspect_str), sizeof(aspect_str), PIPE);
  if (retval >= 0){
    printf("aspect_str=%s\n",aspect_str);
    aspect = atof(aspect_str);
    cout << "-I- fread returned " << retval << endl;
    cout << "aspect = " << aspect << endl;
  }
  else {
    cout << "-E- fread returned " << retval << endl;
  }

  fclose(PIPE);

  return(0);
}
