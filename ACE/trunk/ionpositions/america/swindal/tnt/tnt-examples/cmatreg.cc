

//  demonstrate basic matrix regions

#include <iostream>
#include "tnt/tnt.h"
#include "tnt/vec.h"
#include "tnt/cmat.h"

using namespace TNT;

int main()
{
    Matrix<double> A(5,7, 0.0);

    Matrix<double> B(4, 4, 
                                   " 3  4  8  1 "
                                   " 7  8  5  1 "
                                   " 1  2  6  4 "
                                   " 2  4  9  7 ");

    Index1D I(2,4);
    Index1D J(1,3);
    Index1D K(1,2);

    A(I,J+1) = B(I,J);

    std::cout << A << "\n";

    // upper left 2x2 sublock of B(I,I)

    std::cout << B(I,I)(K,K) << "\n";    

	return 0;
}
    
