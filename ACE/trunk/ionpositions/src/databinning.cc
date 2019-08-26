#include "databinning.h"


bool databinning(mdouble &et_mat, mdouble &et_mat_binned)
{
  string thisprogram="databinning : ";
  int bin=2;
  int xdim=et_mat.size(1);
  int ydim=et_mat.size(0);
  int xdimbin=et_mat_binned.size(1);
  int ydimbin=et_mat_binned.size(0);

  if ((xdim!=xdimbin*bin)||(ydim!=ydimbin*bin)){
    std::cout << thisprogram << "Matrix sizes not compatable!!!" << std::endl;
    return false;
  }
  mdouble et_mat_tmpbin(ydim,xdimbin);

  for (int l=0;l<ydim;l++){
    et_mat_tmpbin[l][0]=et_mat[l][0];
    for (int m=1;m<(xdimbin-1);m++){
      for (int k=0;k<bin;k++){ 
	et_mat_tmpbin[l][m]+=et_mat[l][(m*bin)-k];
      }
    }
  }

  for (int l=0;l<xdimbin;l++){
    et_mat_binned[0][l]=et_mat_tmpbin[0][l];
    for (int m=1;m<(ydimbin-1);m++){
      for (int k=0;k<bin;k++){
	et_mat_binned[m][l]+=et_mat_tmpbin[(m*bin)-k][l];
      }
    }
  }
  return true;
}
