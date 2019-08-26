#include "set_asp_int.h"

bool set_asp_int(float intervall, std::vector<float> &aspint){

  std::string thisprogram;

  thisprogram = "set_asp_int";

  for (int i = 0; i < int(15./intervall) + 1; i++){
    aspint[i] = float(i)*intervall;
  }
  if (0) {
    std::cout << thisprogram << " : -D- " << std::endl;
    for (int i = 0; i < int(15./intervall) + 1; i++){
      std::cout << "aspint[" << i << "] = " << aspint[i] << std::endl;
    }
  }
  return true;
}
