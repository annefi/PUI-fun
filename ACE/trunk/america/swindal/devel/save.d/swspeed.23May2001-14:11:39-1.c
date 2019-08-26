/*
C  File: swspeed.c
C
C  Description: 
C     Calculates solar wind speed using a count-weighted average of E/q
c     for all E/q >= cutoff*maximum.  
C
C  Author: Jim Raines, 30Nov2000
C          (Algorithm concept by Thomas Zurbuchen, Oct2000)
C
C  Method: 
C
C  Requires: read(-->) written(<--)
C  <called functions and globals read(-->)/written(<--)>

   Argument  list
      EPQ[60]           Energy Per charge value in keV/e
      long npha[60]     number of pha words per E/q step
      float moq         mass / charge to use in speed calc.
      float cutoff      % of max counts to qualify for inclusion

C
C  See libh2n.doc for further documentation.
C
C  This file is controlled by the Concurent Version System (CVS):
C  $Id:$
C
C  Major Modification History: (keep this last section)
C    Translated to C.  JR, 29Jan2001.
*/
#include <stdio.h>
#include <math.h>

#define LDEBUG 0

double swspeed(double epq[],int npha[],float moq, float cutoff){
  /* constants */
  const int NEDBMIN=1;  /* minimum EDB from Hefti */

  /* Local variables */
  int i,j;               // short range loop counters
  float sumepq = 0.0;       // sum of E/q for average
  float sumpha = 0;        // number of pha used for weighting
  int hi;                // maximum number of pha words
  float energy;             // count-weighted average energy
  double swspeed;        // speed

  /* dump args for debugging */
  if (LDEBUG) {
    for(i = NEDBMIN; i< 60; i++){
      printf("swspeed: epq[%02d]=%10.2e npha[%02d]=%05d\n",i,epq[i],i,npha[i]);
    }
    printf("swspeed: moq=%10.2f cutoff=%10.2f\n",moq, cutoff);
  }

  /* find max */
  /* -------- */
  for(i = NEDBMIN; i < 60; i++){
    if (i == 0) hi = npha[i];

    if (npha[i] > hi) hi = npha[i];
  }

  /* calculate count-weighted average energy */
  /* --------------------------------------- */
  for(i = NEDBMIN; i < 60; i++){
    if (npha[i] >= (int)(cutoff*hi + 1)){
      sumepq += epq[i] * npha[i];
      sumpha += (float)npha[i];
    }
  }

  energy = sumepq/sumpha;
  if (LDEBUG) printf("swspeed: sumepq=%10.2f sumpha=%10.2f energy=%10.2f \n",
		     sumepq,sumpha,energy);

  /* compute:  v = sqrt( 2 E/q 9.648E4 / (m/q) ) */
  /*           where 9.648E4 is conversion to C/g units */
  swspeed = sqrt(2*energy*9.648E4/moq);

  //printf("swspeed: swspeed=%10.2f\n",swspeed);

  return(swspeed);
}
