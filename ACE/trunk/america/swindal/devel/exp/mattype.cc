#include "swindal.h"

class JR {
public:
  int N;
  int M;

  JR::JR(int, int);

  typedef int jint;
  typedef TNT::Matrix<float> (N,M,0.0) JR::JRMat;

private:
  
};

JR::JR(int Nin, int Min){
  N = Nin;
  M = Min;
}

int main(){
  JR jr(2,3);
  jint i;
  //  JR::JRMat j;

  return(0);
}

