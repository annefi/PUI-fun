/*
   File: swspeed.cc

   Description: 
      Calculates solar wind speed (km/s) using a count-weighted average of E/q
      for all E/q >= cutoff*maximum.  

   Author: Jim Raines, 30Nov2000
           (Algorithm concept by Thomas Zurbuchen, Oct2000)

   Method: 

   Requires: read(-->) written(<--)
   <called functions and globals read(-->)/written(<--)>

   Argument  list
      EPQ[60]           Energy Per charge value in keV/e
      long npha[60]     number of pha words per E/q step
      float moq         mass / charge to use in speed calc. (amu / ox. #)
      float cutoff      % of max counts to qualify for inclusion


   See libh2n.doc for further documentation.

   This file is controlled by the Concurent Version System (CVS):
   $Id:$

   Major Modification History: (keep this last section)
     Translated to C++.  JR, 23May2001.

     Translated to C.  JR, 29Jan2001.
*/
#include <stdio.h>
#include <math.h>
#include "swindal.h"

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
  int DbgLvl = gDbgLvl; /* init local debugging value to global  */

  /* dump args for debugging */
  if (DbgLvl > 2) {
    for(i = FIRSTEDB; i < MAXEDB; i++){
      printf("swspeed: epq[%02d]=%10.2e npha[%02d]=%05d\n",i,epq[i],i,npha[i]);
    }
    printf("swspeed: moq=%10.2f cutoff=%10.2f\n",moq, cutoff);
  }

  /* find max */
  /* -------- */
  for(i = FIRSTEDB; i < MAXEDB; i++){
    if (i == 0) hi = npha[i];

    if (npha[i] > hi) hi = npha[i];
  }

  /* calculate count-weighted average energy */
  /* --------------------------------------- */
  for(i = FIRSTEDB; i < MAXEDB; i++){
    if (npha[i] >= (int)(cutoff*hi + 1)){
      sumepq += epq[i] * npha[i];
      sumpha += (float)npha[i];
    }
  }

  energy = sumepq/sumpha;
  if (DbgLvl > 1) 
    printf("swspeed: sumepq=%10.2f sumpha=%10.2f energy=%10.2f \n",
	   sumepq,sumpha,energy);

  /* compute:  v = sqrt( 2 E/q 9.648E4 / (m/q) ) */
  /*           where 9.648E4 is conversion to C/g units */
  swspeed = sqrt(2*energy*9.648E4/moq);

  //printf("swspeed: swspeed=%10.2f\n",swspeed);

  return(swspeed);
}
