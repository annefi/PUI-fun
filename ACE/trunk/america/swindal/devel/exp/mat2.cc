#include "tnt/tnt.h"
#include "tnt/cmat.h"
#include <stl.h>
#include <iostream>
#include <fstream>


int main(){
  int i,j,k;
  const int N = 10;
  TNT::Matrix<int> A(N, N,
		     " 0   0   0   0   0   0   0   3   5   6 "
		     " 0   0   0   0   0   0   0   3   5   5 "
		     " 0   0   0   0   0   0   0   3   3   3 "
		     " 0   0   0   0   0   0   0   0   0   0 "
		     " 0   0   0   0   0   0   0   0   0   0 "
		     " 1   1   1   1   1   0   0   3   3   0 "
		     " 1   3   3   3   1   0   0   1   3   0 "
		     " 1   3   5   3   1   0   0   2   2   0 "
		     " 1   3   3   3   1   0   0   2   0   0 "
		     " 1   1   1   1   1   0   0   0   0   0 "
		     );

  TNT::Matrix<int> B(N, N, 1000);

  // write small value matrix
  ofstream fout;
  fout.open("../tst.xboxrates");
  fout << "2000158" << endl;
  fout << "0 " << N - 1 << " 0 " << N - 1  << endl;
  fout << A; 
  fout.close();

  // write large value matrix
  fout.open("../tst2.xboxrates");
  fout << "2000158" << endl;
  fout << "0 " << N - 1 << " 0 " << N - 1  << endl;
  fout << A*B; 
  fout.close();

  return 0;
}
  
