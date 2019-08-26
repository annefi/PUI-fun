#include "filter_data.h"

bool filter_data(int &step,mdouble &et_mat){

  string thisprogram="filter_data : ";
  
  int filter_arr[]={300,300,300,300,300,300,300,300,300,300,310,320,320,295,300,305,310,315,320,290,295,300,300,305,310,310,315,320,320,320,300,305,305,305,305,305,305,305,305,305,290,280,260,255,240,240,240,240,240,240,220,220,220,220,220,220,220,220};
  
  int xdim=et_mat.size(1);
  int ydim=et_mat.size(0);
  
  
  // set DCR=0.
  for (int i = 0; i < xdim; i++){
    et_mat[0][i] = 0.;
  }

  // set Dirtbox=0.
  for (int i = 220; i < xdim; i++){
    for (int j = 0;j <12; j++){
      et_mat[j][i] = 0.;
    }
  }
  
  // set Dirt=0. dynamically 
  for (int i = filter_arr[step];i < xdim;i++){
    for (int j = 0;j < ydim;j++){
      et_mat[j][i]=0.;
    }
  }

  return true;

}
