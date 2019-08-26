#include <iostream>
#include "matrix.hh"
#include "matrixio.hh"

using namespace std;

int main() {
    Matrix<double> m(3,3);
    m[0][0]=1;
    m[0][1]=-2;
    m[0][2]=3;
    m[1][0]=4;
    m[1][1]=5;
    m[1][2]=6;
    m[2][0]=3;
    m[2][1]=-1;
    m[2][2]=2;
    cerr << m << endl;
    m.sort(2);
    cerr << m << endl;

    vector_compare<double> my_compare(0);

    vector<double> a(2), b(2);
    a[0]=1; a[1]=2;
    b[0]=-1; b[1]=3;
    
    cerr << my_compare(a, b) << endl;
}
