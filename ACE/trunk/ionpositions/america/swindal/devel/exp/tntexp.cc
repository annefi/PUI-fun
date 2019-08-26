#include "tnt/tnt.h"
#include "tnt/cmat.h"
#include <stl.h>

int main(){
  int i,j,k;
  const int N = 5;
  TNT::Matrix<int> A(N,N),B(N,N),C;
  vector<TNT::Matrix<int> > cube;
  

  for(i = 0; i < N; i++){
    for(j = 0; j < N; j++){
      
      A[i][j] = i + j;
      B[i][j] = i * j;
    }
  }
  
  cout << "Outputing simple matrices and operations:" << endl;
  cout << A << endl;
  cout << B << endl;
  cout << A + B << endl;
  cout << A * B << endl;

  C = A * B;
  cout << " C[0,2]=" << C[0][2];
  cout << " C[2,3]=" << C[2][3];
  cout << " C[4,3]=" << C[4][3];
  cout << endl;

  cout << "Building cube..." << endl;
  cube.push_back(A);
  cube.push_back(B);

  cout << "Outputting slices of cube:" << endl;
  for(i = 0; i < cube.size(); i++){
    cout << cube[i] << endl;
  }

  cout << "Outputting elements of cube:" << endl;

  i = 3;
  j = 2;
  k = 1;
  cout << "cube(" << i << "," << j << "," << k << ")=" 
       << cube[k][i][j] << endl;

}
