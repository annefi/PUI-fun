#include <stdio.h>
#include "nr.h"
#include "nrutil.h"

int nrsvd(int N, float wmax, float wmin, float **a, float **u, float *w, 
	  float **v, float *b, float *x){

  const char thisprog[] = "nrsvd";
  int i,j;  // short range loop counters

/*   a = matrix(1,N,1,N); */
/*   u = matrix(1,N,1,N); */
/*   v = matrix(1,N,1,N); */

/*   w = vector(1,N); */
/*   b = vector(1,N); */
/*   x = vector(1,N); */
  

/*   a[1][1] = 1; */
/*   a[1][2] = 2; */
/*   a[2][1] = -1; */
/*   a[2][2] = 1; */

/*   b[1] = 1; */
/*   b[2] = -1; */

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

  return(0);
}

