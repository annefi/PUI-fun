#include "twodgauss.h"

using namespace std;


bool twodgauss(int x,int y, vector<double> &param, vector<double> &param2, double *value, vector<double> &deriv, int numpar, int numion)
{
  double tmp = 0.;
  double tmp2 = 0.;
  double tmp3 = 0.;
  vector<double> sum;
  vector<double> norm;
  double tmpval;
  vector<double> sum2;
  
  tmpval = 0.;

  for (int k = 0; k < numion; k++){
    sum.push_back(0.);
    norm.push_back(0.);
    sum2.push_back(0.);
    deriv[k] = 0.;
  }
  /*
    for (int k = 0; k < numion; k++){
    //for (int i = 0; i < 256; i++){
    for (int j = 0; j < 1024 ; j++){
    tmp2 = param[((k+1)*5)-3]-double(j);
    tmp2 = tmp2 / param[(k+1)*5-2];
    tmp2 = tmp2*tmp2;
    tmp2 = tmp2 / 2.;
    tmp3 = param[((k+1)*5)-1]-double(i);
    tmp3 = tmp3 / param[(k+1)*5];
    tmp3 = tmp3*tmp3;
    tmp3 = tmp3 / 2.;
    tmp = exp(-tmp2)*exp(-tmp3);
    sum2[k]+= tmp;
    }
    //}
    //    sum2[k] = param2[k] / sum2[k];
    }
  */
  
  
  //  for (int k = 0; k < numion; k++){
  //  norm[k] = sqrt(param[(k+1)*5-2] * param[(k+1)*5]);
  //  norm[k] = norm[k] * 2. * PI;
  //  norm[k] = 1 / norm[k];
  //  sum[k] = norm[k] * param2[k];
  for (int k = 0; k < numion; k++){
    sum2[k] = (1 / normgauss[k]) * param2[k];
  }

  /*
  cout << "normgauss = " << normgauss[0] << endl; 
  cout << "nspill = " << param2[0] << endl;
  cout << "sigmaT = " << param[3] << endl;
  cout << "sigmaE = " << param[5] << endl;
  //cout << "sum = " << sum[0] << endl;
  cout << "sum2 = " << sum2[0] << endl;
  */
  for (int k = 0; k < numion; k++){
    tmp2 = param[((k+1)*5)-3]-double(y);
    //cout << "twodgauss: tmp2 = " << tmp2 << endl;
    tmp2 = tmp2 / param[(k+1)*5-2];
    //cout << "twodgauss: tmp2 = " << tmp2 << endl;
    tmp2 = tmp2*tmp2;
    tmp2 = tmp2 / 2.;
    tmp3 = param[((k+1)*5)-1]-double(x);
    tmp3 = tmp3 / param[(k+1)*5];
    tmp3 = tmp3*tmp3;
    tmp3 = tmp3 / 2.;
    tmp = exp(-tmp2)*exp(-tmp3);
    //  cout << "twodgauss: tmp = " << tmp << endl;
    //cout << endl;
    tmp = tmp * sum2[k];
    deriv[k] = (1 / normgauss[k]) * exp(-tmp2)*exp(-tmp3);  
    tmpval += tmp;
    //cout << x << "  " << y << endl;
    //if (tmp>0.3) cout << "twodgauss:Wert " << k << " = " << tmp << "  " << deriv[k] << endl;
  }

  *value = tmpval;
  // cout << "twodgauss: value = " << tmpval << endl;
  return true;
} 
 
  
