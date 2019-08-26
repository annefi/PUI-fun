/*
  File: Invert.cc

  Description:
    Inverts a square matrix using singular value decomposition from ref. 1

  Author: Jim Raines, 14Aug2001 

  Method:
    This is mostly a wrapper for using the Numerical Recipes routine,
    svdcmp.  It essentially copies the TNT matrix A into a NR-style
    matrix then calls another wrapper which calls svdcmp.c.  The
    results, u, v and w are then copied back to TNT matrices(vector).
    Finally, S inverse is calculated using eq. 2.6.5 in ref. 1.

  References:
  1.  Numerical Recipes in C: The Art of Scientific Computing, 
      W. H. Press, et al., Cambridge Univ. Press, 1992
    
  Major Modification History:
    

*/

// standard library
#include <iostream>
#include <string>
#include <cstdlib>
#include <stdio.h>

// Numerical Recipes
extern "C"{
#include "nrutil.h"
  //#include "nr.h"
}

// Template Numerical Toolkit (TNT)
#include "tnt/tnt.h"
#include "tnt/cmat.h"
#include "tnt/vec.h"
#include "tnt/region1d.h"

extern "C" {
int nrsvd(int N, float wmax, float wmin, float **a, float **u, float *w, 
	  float **v, float *b, float *x);
void svdcmp(float **a, int m, int n, float w[], float **v);
}



TNT::Matrix<float> Invert(TNT::Matrix<float> A){

  const char thisprog[] = "invert";
  int i,j;  // short range loop counters

  const int N = 2;  // dimension of matrix 

  TNT::Vector<float> X(N,
		       "1 0");

  TNT::Vector<float> B(N,
		       "1 -1");

  TNT::Matrix<float> U(N,N,0.0),V(N,N,0.0);

  TNT::Vector<float> W(N,0.0);

  TNT::Matrix<float> Wdr(N,N,0.0);     // middle mat in ref 1, eq 2.6.5
  TNT::Matrix<float> Ainv(N,N,0.0);

  float wmax;
  float wmin;
  float **a;
  float **u;
  float *w;
  float **v;
  float *b;
  float *x;

  a = matrix(1,N,1,N);
  u = matrix(1,N,1,N);
  v = matrix(1,N,1,N);

  w = vector(1,N);
  b = vector(1,N);
  x = vector(1,N);

  // copy in

  for (i = 1;i <= N; i++){
    for (j = 1; j <= N; j++){
      a[i][j] = A[i-1][j-1];
    }
  }

  for (j = 1; j <= N; j++){
    b[j] = B[j-1];
  }
  
  // run svd
  nrsvd( N, wmax,  wmin, a,  u,  w, v, b, x);
  //svdcmp(a,N,N,w,v);  

  // copy out

  for (i = 1;i <= N; i++){
    for (j = 1; j <= N; j++){
      A[i-1][j-1] = a[i][j];
    }
  }

  for (j = 1; j <= N; j++){
    X[j-1] = x[j];
  }
  
  for (i = 1;i <= N; i++){
    for (j = 1; j <= N; j++){
      V[i-1][j-1] = v[i][j];
    }
  }

  for (j = 1; j <= N; j++){
    W[j-1] = w[j];
  }
  
  for (i = 1;i <= N; i++){
    for (j = 1; j <= N; j++){
      U[i-1][j-1] = u[i][j];
    }
  }

//   ofstream fout;
//   fout.precision(3);

//   fout.open("ma.longrun");
//   fout << "ACE/SWICS counts/second for day(s) " << StartYdoy <<
//     " - " << StopYdoy << endl;
//   fout << "TOF_CH ESD_CH" << endl;
//   fout << "0 1023 0 255" << endl;
//   fout << sum; 
//   fout.close();

  cout << thisprog << " -I- A=" << endl;
  cout << A;

  cout << thisprog << " -I- X=" << endl;
  cout << X;

  cout << thisprog << " -I- B=" << endl;
  cout << B;

  // calculate inverse of A
  cout << thisprog << " -I- calculating inverse of A" << endl;
  for (i = 1; i <= N; i++){
    if (w[i] != 0){
      Wdr[i-1][i-1] = 1/W[i-1];
    }
    else {
      Wdr[i-1][i-1] = 0.0;
    }
  }
  
  cout << thisprog << " -I- V=" << endl;
  cout << V;

  cout << thisprog << " -I- Wdr=" << endl;
  cout << Wdr;

  cout << thisprog << " -I- transpose(U)=" << endl;
  cout << transpose(U);

  Ainv = V * Wdr * transpose(U);

  cout << thisprog << " -I- Ainv=" << endl;
  cout << Ainv;


  return(Ainv);
}
  
  
