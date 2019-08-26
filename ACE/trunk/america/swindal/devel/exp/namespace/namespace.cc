#include <iostream>

#include "namespace.h"

int main(){

  extern int Common::dbg;
  
  Common::dbg = 1;

  cout << "Common::dbg = " << Common::dbg << endl;
}
