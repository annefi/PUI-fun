// Pointer to a member function
// JMR, 06Oct2003

#include <stl.h>
#include <cstdlib>
#include <cstdio>

#include "swindal.h"
#include "swindal_nr.h"

class ExpClass {
public:
  static float ExpClass::times2(float);
  float ExpClass::cube(float value);

private:
  
};

 float ExpClass::times2(float value){
  return(value*2.0);
}

// f(x) = x
float ExpClass::cube(float value){
  return(value*value*value);
}

int main(){

  // member function called as member function
  ExpClass c;
  printf("times2(4.0)=%f\n",c.times2(4.0));
  // works

  // static member function called through pointer
  // Note:  pfunc2 is a pointer to a float(float) of class ExpClass only!
  float (*pfunc) (float) = &ExpClass::times2;
  ExpClass c2;
  printf("ExpClass::times2(3.0)=%f\n",(*pfunc)(3.0));
  // works

  // try Numerical Recipes integration on times2 member function
  float integral;
  integral = nr::qtrap( pfunc, 1.0, 3.0);
  printf("integral(times2,1.0,3.0)=%f\n",integral);
  // works; answer is 8.0

  // use pointer to non-static member function
  float (ExpClass::*pfunc2) (float) = &ExpClass::cube;
  printf("ExpClass::cube(3.0)=%f\n",(c2.*pfunc2)(3.0));
  // works; answer is 9.0

  /* Note:  Cannot try Numerical Recipes integration on cube
     function.  Because it is non-static, a pointer to the function
     has type 

     float (ExpClass::*) (float)

     while nr::qtrap requires

     float (*) (float)

     The former CANNOT be cast into the latter.  If it happens to work
     -- it did not as of this writing (gcc 2.96), it is non-portable,
     possibly undefined and definitely to be avoided at all costs.
     See the following URL for details.

     http://www.parashift.com/c++-faq-lite/pointers-to-members.html

  */

  return(0);

}
