#include "tnt/cmat.h"
#include "tnt/vec.h"
#include "tnt/region1d.h"

int main(){
  const int N = 2;  // row dimension of matrix
  const int M = 3;  // column dimension of matrix 

  TNT::Matrix<float> A(N,M,
		       " 1 2 3"
		       "-1 1 4");

  cout << "A has size " << A.size() << endl;
  cout << "A is " << A.dim(1) << " rows by " << A.dim(2) << " columns" << endl;
  cout << "A:" << endl;
  cout << A;
}
