/*
  File: Invert.cc

  Description:
    Inverts a square matrix using singular value decomposition from ref. 1

  Author: Jim Raines, 14Aug2001 

  Method: 
    This is mostly a wrapper for using the Numerical Recipes (NR) routine,
    svdcmp.  It essentially copies the TNT matrix A into a NR-style
    matrix then calls svdcmp.c.  The results, u, v and w are then
    copied back to TNT matrices(vector).  Finally, S inverse is
    calculated using eq. 2.6.5 in ref. 1.

  References:
  1.  Numerical Recipes in C: The Art of Scientific Computing, 
      W. H. Press, et al., Cambridge Univ. Press, 1992
    
  Revision controlled by CVS:
  $Id: Invert.cc,v 1.3 2003/11/06 21:53:09 jraines Exp $

  Major Modification History:
    

*/

#include "swindal.h"
#include "swindal_nr.h"

TNT::Matrix<float> Invert(TNT::Matrix<float> A){

  const char thisprog[] = "invert";
  int i,j;  // short range loop counters
  int DbgLvl = 0;  // Debugging level

  int N;    // dimension of matrix to be inverted
  N = A.dim(1);
  if (A.dim(2) != N){
    cout << thisprog << " -F- input matrix not square; exiting..." << endl;
    return (A = 0);
  }

  TNT::Matrix<float> U(N,N,0.0),V(N,N,0.0);

  TNT::Vector<float> W(N,0.0);

  TNT::Matrix<float> Wdr(N,N,0.0);     // middle mat in ref 1, eq 2.6.5
  TNT::Matrix<float> Ainv(N,N,0.0);

  /* --- NR-style matrix/vector declarations --- */
  float **u;
  float *w;
  float **v;

  u = nr::matrix(1,N,1,N);
  v = nr::matrix(1,N,1,N);

  w = nr::vector(1,N);

  /* ---  copy TNT-matrix to NR-style matrix --- */
  for (i = 1;i <= N; i++){
    for (j = 1; j <= N; j++){
      u[i][j] = A[i-1][j-1];
    }
  }

  /* --- decompose u using svd --- */
  nr::svdcmp(u,N,N,w,v);  

  /* --- reset small values of w --- */
  float wmax = 0.0;     // max value of w
  for (j = 1; j<= N; j++){
    if (w[j] > wmax) wmax = w[j];
  }

  float wmin;          // minimum allowed value of w
  wmin = wmax * 1.0e-6;

  for (j = 1; j<= N; j++){
    if (w[j] < wmin) w[j] = 0;
  }

  /* --- copy NR-style u, v and w to TNT-style U, V and W --- */
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

  if (DbgLvl > 3){
    cout << thisprog << " -I- A=" << endl;
    cout << A;
    cout << endl;
  }

  /* --- calculate inverse of A, using ref. pg 61, eq 2.6.5 --- */
  if (DbgLvl > 1){
    cout << thisprog << " -I- calculating inverse of A" << endl;
  }

  for (i = 1; i <= N; i++){
    if (w[i] != 0){
      Wdr[i-1][i-1] = 1/W[i-1];
    }
    else {
      Wdr[i-1][i-1] = 0.0;
    }
  }
  
  if (DbgLvl > 3){
    cout << thisprog << " -I- V=" << endl;
    cout << V;
    cout << endl;

    cout << thisprog << " -I- Wdr=" << endl;
    cout << Wdr;
    cout << endl;

    cout << thisprog << " -I- transpose(U)=" << endl;
    cout << transpose(U);
    cout << endl;
  }

  Ainv = V * Wdr * transpose(U);

  if (DbgLvl > 1){
    cout << thisprog << " -I- Ainv=" << endl;
    cout << Ainv;
    cout << endl;
  }

  nr::free_matrix(u, 1, N, 1, N);
  nr::free_matrix(v, 1, N, 1, N);
  nr::free_vector(w, 1, N);
  return(Ainv);
}
  
  
