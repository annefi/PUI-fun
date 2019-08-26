/*
 Function bins et-slice in x and y direction, transpones it and gives the result back leaving the original unchanged!!!
*/
#include "swindal.h"

TNT::Matrix<float> binetslice(TNT::Matrix<float> et_mat){

  string thisprog = "binetslices : ";

  int xdim = 1024;
  int ydim = 256;
  int xdimbin = 512;
  int ydimbin = 128;
  TNT::Matrix<float> et_mat_xbin(xdim,ydim,0.0);
  TNT::Matrix<float> et_mat_xybin(xdim,ydim,0.0);
  TNT::Matrix<float> et_mat_xytrbin(ydim,xdim,0.0);
  TNT::Matrix<float> et_mat_bin(ydimbin,xdimbin,0.0);
  
  //  std::cout << "binning data";

  // Do x binning
  for (int i = 0; i < ydim;i++){
    et_mat_xbin[0][i]=et_mat[0][i];
  }
  for (int i = 0; i < ydim;i++){
    for (int j = 1; j < xdimbin;j++){
      for (int k = 0; k < 2;k++){
	et_mat_xbin[j][i]+=et_mat[(j*2)-k][i];
      }
    }
  }
  // Do y binning
  for (int i = 0; i < xdimbin;i++){
    et_mat_xybin[i][0]=et_mat_xbin[i][0];
  }
  for (int i = 0; i < xdimbin;i++){
    for (int j = 1; j < ydimbin;j++){
      for (int k = 0; k < 2;k++){
	et_mat_xybin[i][j]+=et_mat_xbin[i][(j*2)-k];
      }
    }
  }
  for (int i = 0;i < xdimbin;i++){
    for (int j = 0;j < ydimbin;j++){
      et_mat_bin[j][i]=et_mat_xybin[i][j];
    }
  }
  return et_mat_bin;
}
