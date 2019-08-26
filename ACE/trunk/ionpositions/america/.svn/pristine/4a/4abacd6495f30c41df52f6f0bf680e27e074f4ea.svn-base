/*
  File:  eqte2mmq.cc

  Description:
    Converts (E/q,tofch,esdch) to (mass, m/q).

  Author: Jim Raines, 13Sep2001

  Method:
    Uses libhef's functions dswxlnm and dswxlnmq and constants from libhef.

  Major Modification History:
    

*/
#include "swindal.h"

extern "C" {
#include "libhef.h"
}

int eqte2mmq(float eq, float pav, int tofch, int esdch,  // input param.
	       double& mm, double& mq){                    // output values

  static bool FirstTime = true; // T on first time through only

  // conversion constants for eqte2mmq from libhef
  static double adcnq[NCNQ];  // m/q conversion constants
  static double adcnm[NCNM];  // mass conversion constants

  // build the constants arrays, I do not know why just passing the pointer
  // does not work -- but it does not.
  if (FirstTime){
    double *padcnq, *padcnm;
    padcnq = a3gcnq();
    padcnm = a3gcnm();

    for(int i = 0; i < NCNM; i++){
      adcnm[i] = aget(padcnm,i);
     }

    for(int i = 0; i < NCNQ; i++){
      adcnq[i] = aget(padcnq,i);
     }

    FirstTime = false;
  }


  double lnmq, lnm, w;
  short shtof;  // to match libhef prototypes
  unsigned char besd;  // to match libhef prototypes

  shtof = (short) tofch;
  besd = (unsigned char) esdch;
  

  w = log(eq + pav);
  lnmq = dswxlnmq(w, tofch, adcnq);  // adcnq?

  if ( (lnmq >= 1.0) && (lnmq <= 124.0) ){
    mq = a3cxmoq(lnmq);
  }
  else{
    mq = 0.0;
  }

  lnm = dswxlnm(tofch, esdch, adcnm);

  if ( (lnm >= 1.0) && (lnm <= 122.0) ){
    mm = a3cxmas(lnm);
  }
  else{
    mm = 0.0;
  }

  return(0);
}
