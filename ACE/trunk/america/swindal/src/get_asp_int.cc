#include "get_asp_int.h"

int get_asp_int(float intervall,std::vector<float> &aspint,float aspang){
  for (int i = 0; i < int(15./intervall);i++){
    if (aspang >= aspint[i] && aspang < aspint[i+1]){
      return i;
    }
  }
  return -1;
}
