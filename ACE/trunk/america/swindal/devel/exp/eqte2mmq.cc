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
double dswxusw(short stau, double dToff, double dTdac);
double dswxlnmqsw(double dw, short stau, double *adcnq);
double dswxlnmsw(short stau, BYTE besd, double *adcnm);
}

int eqte2mmq(float eq, float pav, int tofch, int esdch,  // input param.
	       double& mm, double& mq){                    // output values

  static bool FirstTime = true; // T on first time through only

  // conversion constants for eqte2mmq from libhef
  double adcnq[NCNQ];  // m/q conversion constants
  double adcnm[NCNM];  // mass conversion constants

  if (FirstTime){
    double *padcnq, *padcnm;
    padcnq = a3gcnq();
    padcnm = a3gcnm();

    for(int i = 0; i < NCNQ; i++){
//       adcnq[i] = padcnq[i];
//       adcnm[i] = padcnm[i];
      adcnq[i] = aget(padcnq,i);
      adcnm[i] = aget(padcnm,i);
     }

    FirstTime = false;
  }


  double lnmq, lnm, w;   

  w = log(eq + pav);
  lnmq = dswxlnmqsw(w, tofch, adcnq);  // adcnq?
  cout << "lnmq=" << lnmq << endl;
  mq = exp(lnmq); // M_E is e (as in ln(e)=1) from math.h

  lnm = dswxlnmsw(tofch, esdch, adcnm);
  mm = exp(lnm);

  return(0);
}

