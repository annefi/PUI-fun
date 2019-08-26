#include "read_et_mat.h"

bool read_et_mat(ifstream &datastream,int loadstep,mdouble &et_mat){

  string thisprogram="read_et_mat : ";
  int dbglvl=0;
  int xdim=et_mat.size(1);
  int ydim=et_mat.size(0);
  int tmp=0;
  int tmp1=0;
  string tmp2="";
  double tmp3=0.;

  if (dbglvl>=1){
    std::cout << thisprogram << "xdim = " << xdim << std::endl;
    std::cout << thisprogram << "ydim = " << ydim << std::endl;
    std::cout << thisprogram << "step = " << loadstep << std::endl;
  }
  for (int step=0;step<loadstep;step++){
    if (dbglvl>=1){
      std::cout << thisprogram << "mainloop step " << step << std::endl;
    }
    if (xdim==1024){
      datastream >> tmp2 >> tmp2 >> tmp2 >> tmp2 >> tmp2 >> tmp2 >> tmp2;
      datastream >> tmp2 >> tmp2;
      datastream >> tmp >> tmp >> tmp >> tmp;
      datastream >> tmp >> tmp1;
      if ((tmp!=ydim)||(tmp1!=xdim)){
	std::cerr << thisprogram << "Matrix has wrong size for datafile" << std::endl;
	return false;
      }
      for (int i = 0; i < xdim; i++){
	for (int k = 0; k < ydim; k++){
	  datastream >> tmp3;
	  et_mat[k][i] = double(tmp3);
	}
      }
      for (int i = 0; i < xdim; i++){
	et_mat[0][i] = 0.;
      }
    }

    if (xdim==512){
      if (dbglvl>=1){
	std::cout << thisprogram << "reading binned data" << std::endl;
      }
      datastream >> tmp >> tmp1 ;
      if ((tmp!=ydim)||(tmp1!=xdim)){
	std::cerr << thisprogram << "Matrix has wrong size for datafile" << std::endl;
	return false;
      }

      for (int i = 0; i < ydim; i++){
	for (int k = 0; k < xdim; k++){
	  datastream >> tmp3;
	  et_mat[i][k] = double(tmp3);
	}
      }
      for (int i = 0; i < xdim; i++){
	et_mat[0][i] = 0.;
      }
    }
  }
  return true; 
}
