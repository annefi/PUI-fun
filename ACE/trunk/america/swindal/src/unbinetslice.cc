/*
 Function unbins et-slice in x and y direction, transpones it and gives the result back leaving the original unchanged!!!
*/
#include "swindal.h"

TNT::Matrix<float> unbinetslice(TNT::Matrix<float> et_mat){

  string thisprog = "unbinetslices : ";

  int xdim = 1024;
  int ydim = 256;
  int xdimbin = 512;
  int ydimbin = 128;
  TNT::Matrix<float> et_mat_unbin_tmp(ydim,xdim,0.0);
  TNT::Matrix<float> et_mat_unbin(xdim,ydim,0.0);
  
  // unbin inner matrix
  for (int i=1; i<ydimbin;i++){
    for (int j=1;j< xdimbin;j++){
      et_mat_unbin_tmp[i*2][j*2]=et_mat[i][j];
    }
  }
  // unbin 0 channels
  for (int i=1;i<xdimbin;i++){
    et_mat_unbin_tmp[0][i*2]=et_mat[0][i];
  }
  for (int i=1;i<ydimbin;i++){
    et_mat_unbin_tmp[i*2][0]=et_mat[i][0];
  }
  // unbin 0 point
  et_mat_unbin_tmp[0][0]=et_mat[0][0];

  for (int i = 0;i < xdim;i++){
    for (int j = 0;j < ydim;j++){
      et_mat_unbin[i][j]=et_mat_unbin_tmp[j][i];
    }
  }
  return et_mat_unbin;
}
