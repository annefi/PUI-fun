/*
  File: prob_range.cc

  Description:
    Simulate probabilistic assignment of swindal MeasurementArray counts to 
    ions via the dice roll (Ruedi von Steiger's) method.

  Author(s): Jim Raines (jmr)

  Method:
    
  Major Modification History:
    12Aug2003   jmr   initial coding

*/

#include "swindal.h"
#include "stdlib.h"

int main(int argc, char *argv[]){

  bool debug = false;

  const int PSIZE = 3;
  float P[PSIZE];
  P[0] = .12;
  P[1] = .65;
  P[2] = .23;

  float dice_roll;
  float lo = 0.0;
  float hi = 0.0; 

  // grab number of iterations from command line
  int niter = 5;
  if (argc >= 2) niter =  atoi(argv[1]);

  // set up data file
  FILE *DATFILE;
  char datfile[] = "prob_range_data.dat";
  if( (DATFILE = fopen( datfile, "w+" )) == NULL ) {
      printf( "Error opening output file %s.\n", datfile ) ;
      return( -1 ) ;
  }
  

  for (int i = 0; i < niter; i++){
    lo = 0.0;
    hi = 0.0;
    dice_roll = (float)random()/(float)RAND_MAX;

    if (debug) printf("iteration=%d dice_roll=%f\n",i, dice_roll);

    for (int s = 0; s < PSIZE; s++){
      if(s == 0){
	lo = 0.0;
      }
      else {
	lo = lo + P[s-1];
      }
      hi = hi + P[s];
      
      if (debug) printf(" lo=%6.2f hi=%6.2f\n",lo,hi);

      if (dice_roll >= lo && dice_roll < hi) {
	if (debug) printf("  counts go to s = %d\n", s);
	fprintf(DATFILE, "%4i %10.7f %10.7f %10.7f\t%i\n",
		i,dice_roll,lo,hi,s);
      }
					 
    }
  }

  fclose(DATFILE);
  return(0);
}
