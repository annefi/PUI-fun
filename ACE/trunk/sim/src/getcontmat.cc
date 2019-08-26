#include "getcontmat.h"
#include <vector>

bool getcontmat(vector<vector<int> > paragauss,vector<vector<vector<double> > > box, vector<vector<double> > *contmat)
{

  double tmp;
  double tmp2;
  double tmp3;
  double sum;

  vector<vector<double> > gauss;
  vector<double> auxgauss;

  for (int i = 0; i < 1024; i++){
    auxgauss.push_back(0.);
  }
  for (int i = 0; i < 256; i++){
    gauss.push_back(auxgauss);
  }


  for (int l = 0; i < 2; l++){
    for (int k = 0; i < 2; k++){
      for (int i = 0; i < 256; i++){
	for (int j = 0; j < 1024 ; j++){
	  tmp2 = paragaus[0][(k*5)-3]-double(j);
	  tmp2 = tmp2 / paragaus[0][(k*5)-2];
	  tmp2 = tmp2*tmp2;
	  tmp2 = tmp2 / 2.;
	  tmp3 = paragaus[0][(k*5)-1]-double(i);
	  tmp3 = tmp3 / paragaus[0][(k*5)];
	  tmp3 = tmp3*tmp3;
	  tmp3 = tmp3 / 2.;
	  //      cout << tmp2 << "   " << tmp3 << endl;
	  tmp = exp(-tmp2)*exp(-tmp3);
	  gauss[i][j] = tmp;
	  sum += tmp;
	}
      }
      sum = 1 / sum; 
      for (int i = 0; i < 256; i++){
	for (int j = 0; j < 1024 ; j++){
	  gauss[i][j] = gauss[i][j] * sum;
	}
      }
      for (int i  = box[k][0][1];i <= box[k][1][1]; i++){
	for (int j = box[k][0][0];j <= box[k][1][0]; j++){
	  contmat[l][k] += gauss[i][j];
	}
      }
    }
  }
}
