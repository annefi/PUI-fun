#include <iostream>
#include "tnt/tnt.h"
#include "tnt/vec.h"
#include "tnt/cmat.h"

using namespace std;
using namespace TNT;

int main()
{
    const int N=6;
    Vector<double> x(N), y(N);
    Matrix<double> A(N,N);

    A[0][0] = 0.1;
    x[1] = 1.1;
    y[2] = 3.2;

    A[0][1] =  x[1] * A[0][0] + y[2];
    
    cout << A[0][1] << "\n";


        return 0;
}

