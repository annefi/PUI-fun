/*
  File: Invert.cc

  Description:
    Performs singular value decomposition on input matrix a, returning
    the decomposition (u, v and w) for later use.

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

#include <stdio.h>
#include "nr.h"
#include "nrutil.h"

int nrsvd(int N, float wmax, float wmin, float **a, float **u, float *w, 
	  float **v, float *b, float *x){

  const char thisprog[] = "nrsvd";
  int i,j;  // short range loop counters
  int DbgLvl = 0;

  for (i = 1;i <= N; i++){
    for (j = 1; j <= N; j++){
      u[i][j] = a[i][j];
    }
  }

  svdcmp(u,N,N,w,v);
  
  wmax = 0.0;
  for (j = 1; j<= N; j++){
    if (w[j] > wmax) wmax = w[j];
  }

  wmin = wmax * 1.0e-6;

  for (j = 1; j<= N; j++){
    if (w[j] < wmin) w[j] = 0;
  }
      
  svbksb(u,w,v,N,N,b,x);

  if (DbgLvl > 3) {
    printf("%s -I- printing matrices/vectors: \n", thisprog);
    for (i = 1; i<= N; i++){
      for (j = 1; j<= N; j++){
	printf(" a[%1d][%1d]=%6.2f",i,j,a[i][j]);
      }
      printf("\n");
    }
    
    for (j = 1; j<= N; j++){
      printf(" x[%1d]=%6.2e",j,x[j]);
    }
    printf("\n");
    
    for (j = 1; j<= N; j++){
      printf(" b[%1d]=%6.2f",j,b[j]);
    }
    printf("\n");
  }

  return(0);
}

