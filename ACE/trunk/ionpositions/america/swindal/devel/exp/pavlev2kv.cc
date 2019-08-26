#include "swindal.h"

extern "C" {
#include "libhef.h"
}

int main(){
  int DbgLvl = 4;
  string thisprog = "pavlev2kv";
  int pavlevs[] = {127, 171, 141};
  float PapsVolt;

  map<int,float> pavlev2kv;
  pavlev2kv[127] = 22.8;
  pavlev2kv[171] = 26.1;

  for (int i = 0; i < 3; i++){
    PapsVolt = pavlev2kv[pavlevs[i]];
    if (DbgLvl > 3) printf("%s -D- PAPS = %f kV\n",thisprog.c_str(),PapsVolt);
  }

 
}
