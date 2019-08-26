#include "boxrates.h"

using namespace std;

bool boxrates(mdouble &et_mat, vdouble &param)
{
  string thisprogram="boxrates : ";
  int nrions=param.size()/7;
  double sum;
  int dbglvl=0;
  for (int i=0;i< nrions;i++){
    sum=0.;
    if (dbglvl>=1){
      cout << thisprogram << i << "  " << param[(i*7)+1] << " : " << int(param[(i*7)+1]-param[(i*7)+4]) << " : " << int(param[(i*7)+1]+param[(i*7)+3]) << endl;
      cout << thisprogram << i << "  " << param[(i*7)+2] << " : " << int(param[(i*7)+2]-param[(i*7)+6]) << " : " << int(param[(i*7)+2]+param[(i*7)+5]) << endl;
    }
    for (int x=int(param[(i*7)+1]-param[(i*7)+4]);x<int(param[(i*7)+1]+param[(i*7)+3]);x++){
      for (int y=int(param[(i*7)+2]-param[(i*7)+6]);y<int(param[(i*7)+2]+param[(i*7)+5]);y++){
	if (y < 128 && y > 0 && x < 512 && x > 0){
	  sum+=et_mat[y][x];
	}
      }
    }
    param[i*7]=(sum+0.01)*1.6;
    if (dbglvl>=1){
      cout << thisprogram << "val = " << param[i*7] << endl;
    }
  }
  return true;
}
