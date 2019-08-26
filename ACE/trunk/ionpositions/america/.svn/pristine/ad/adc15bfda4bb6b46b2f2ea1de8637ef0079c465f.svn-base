// test array initialization in various permutations
// JR, 10Feb2004

#include <stdio.h>

int main(int argc, char* argv[]){
  
  int crg;
  double *xfm;
  double mas = 56.0;

  for(crg=6; crg<25; crg++){
    xfm = xfmexp(20.61, 24.8695, mas, (double) crg);
    printf("m=%f c=%d: tof=%6.2f stof=%6.2f esd=%6.2f sesd=%6.2f\n",
	   mas, crg, xfm[0], xfm[1], xfm[2], xfm[3]);
  }

  return(0);
}
