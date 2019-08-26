// Test of NR interpolation in known circumstance
// Jim Raines, 24Oct2003

#include "math.h"
#include "nr.h"
#include "nrutil.h"

int main(){
  unsigned long i,j,k;

  const int N = 10;
  const int M = 3;

  float x,y,dy;

  float *xa;

  float *ya;

  xa = vector(1,N);
  ya = vector(1,N);  
  for ( i = 0; i <= N; i++){
    xa[i] = i;   // just index
    ya[i] = i*i; // index squared
  }

  while (1){
    printf("Enter x: ");
    scanf("%f",&x);

    locate(xa, N, x, &j);
    printf("xa[%d] <-> xa[%d]\n",j,j+1);

    k = IMIN(IMAX(j-(M-1)/2,1),N+1-M);
    printf("k=%d\n",k);

    polint(&xa[k-1],&ya[k-1],M, x, &y, &dy);
    printf("y[%f]=%f\n",x,y);
  }

  
  return(0);
}
