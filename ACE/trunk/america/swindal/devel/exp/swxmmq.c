#include "libhef.h"

double dswxusw(short stau, double dToff, double dTdac)
{
  double dt;

  dt = (double)stau + dToff;
  if( dt < 1.0 ) {
    /* printf("E:dswxusw:bad (TOF+OFFSET) %.2f.\n",dt); */
    return(-1.0);
  }

  dt = log(dt) + dTdac;
  return(dt);
}

/* ---------------------------------------------------------------------------
   dswxlnmq --- calculate ACE/SWICS ln(m/q) in channels, in double precision
   w = ln(E/q + Uacc)
   -------------------------------------------------------------------------*/
double dswxlnmqsw(double dw, short stau, double *adcnq)
{
  double du   = 0.0;
  double dmq  = 0.0;

  printf("here I am!\n");
  if( stau < adcnq[LCNQTMIN]) return((double)TOFUNDER);
  if( stau > adcnq[LCNQTMAX]) return((double)TOFOVER);

  du   = dswxusw(stau,adcnq[LCNQTOFF],adcnq[LCNQTDAC]);

  dmq  = adcnq[LCNQCLA0] +
         adcnq[LCNQCLA1] * dw +
         adcnq[LCNQCLA2] * du;

  if( dmq < adcnq[LCNQCMIN]) return((double)MQUNDER);
  if( dmq > adcnq[LCNQCMAX]) return((double)MQOVER);

  return(dmq);
}

/* ---------------------------------------------------------------------------
   dswxlnm --- calculate ACE/SWICS ln(m) in channels, double precision
   -------------------------------------------------------------------------*/
double dswxlnmsw(short stau, BYTE besd, double *adcnm)
{
  double dv = 0.0;
  double du = 0.0;
  double dm = 0.0;

  if( stau < adcnm[LCNMTMIN]) return((double)TOFUNDER);
  if( stau > adcnm[LCNMTMAX]) return((double)TOFOVER);

  if( (long)besd < adcnm[LCNMEMIN]) return((double)EUNDER);
  if( (long)besd > adcnm[LCNMEMAX]) return((double)EOVER);

  du = dswxu(stau,adcnm[LCNMTOFF],adcnm[LCNMTDAC]);
  dv = dswxu((long)besd,adcnm[LCNMEOFF],adcnm[LCNMEDAC]);
  /* dswxu calculates ln(1st + 2nd) + 3rd */

  dm = adcnm[LCNMCLA0] + 
       dv * (adcnm[LCNMCLA1] + adcnm[LCNMCLA3] * du + adcnm[LCNMCLA4] * dv) +
       du * (adcnm[LCNMCLA2] + adcnm[LCNMCLA5] * du * du);

  if( dm < adcnm[LCNMCMIN]) return((double)MUNDER);
  if( dm > adcnm[LCNMCMAX]) return((double)MOVER);

  return(dm);
}

