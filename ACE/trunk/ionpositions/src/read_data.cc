#include "read_data.h"

bool read_data(ifstream &datastream,int step,mdouble &et_mat,int dobin){

  string thisprogram="read_data : ";
  int dbglvl=0;
  
  if (dbglvl>=1){
    std::cout << thisprogram << "reading 1 step" << std::endl;
    std::cout << thisprogram << "working with binned data" << std::endl;
  }
  read_et_mat(datastream,step,et_mat);

  return true;

}
  
  
  
