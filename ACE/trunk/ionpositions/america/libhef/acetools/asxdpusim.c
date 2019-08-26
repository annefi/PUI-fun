/* ---------------------------------------------------------------------------
   asxdpusim.c --- DPU simulator for ACE/SWICS
   1998 by Hefti, University of Michigan (hefti@umich.edu)
   $Id: asxdpusim.c,v 1.1.1.1 2000/06/02 13:37:19 jraines Exp $
   ------------------------------------------------------------------------ */

static char* rcsid =\
"$Id: asxdpusim.c,v 1.1.1.1 2000/06/02 13:37:19 jraines Exp $";

#include <math.h>
#include <stdio.h>

#include "acetools.h"

#define LUCLAC1 0
#define LUCLAA1 1
#define LUCLAA2 2
#define LUCLAA3 3
#define LUCLAA4 4
#define LUCLAA5 5
#define LUCLAA6 6
#define LUCLATC 7
#define LUCLAEC 8

#define NUCLA   9

static double aducla[NUCLA] = {
   1.9159e-5,
   5.81090,
  -1.50052,
  -3.01352,
   0.471113,
   0.0804588,
   0.0731559,
   5.115,                               /* tof [ns] --> ch */
   0.417498936};                        /* E [keV]  --> ch */

/* ---------------------------------------------------------------------------
   dswxu --- calculate u = ln(t + Toffset) + lnTADC
   -------------------------------------------------------------------------*/
double dswxu(short stau, double dToff, double dTdac)
{
  double dt;

  dt = (double)stau + dToff;
  if( dt < 1.0 ) {
    /* printf("E:dswxu:bad (TOF+OFFSET) %.2f.\n",dt); */
    return(-1.0);
  }

  dt = log(dt) + dTdac;
  return(dt);
}

/* ---------------------------------------------------------------------------
   dswxeoq --- calculate E/q [keV/q]
   low step number gives low E/q. Low index in eqtab is low E/q.
   -------------------------------------------------------------------------*/
double dswxeoq(BYTE bstp, BYTE abeqtab[60],double *adcnq)
{
  return(adcnq[LCNQEOQ0] * pow(adcnq[LCNQEOQ1],(double)abeqtab[bstp]));
}

/* ---------------------------------------------------------------------------
   dswxpal --- calculate PAPS [kV]
   -------------------------------------------------------------------------*/
double dswxpal(BYTE bpaps, BYTE bred, double *adcnq)
{
  if( bred ) {
    return(adcnq[LCNQPOF2] + adcnq[LCNQPSL2] * (double)bpaps);
  } else {
    return(adcnq[LCNQPOF1] + adcnq[LCNQPSL1] * (double)bpaps);
  }
}

/* ---------------------------------------------------------------------------
   dswxlnmq --- calculate ACE/SWICS ln(m/q) in channels, in double precision
   w = ln(E/q + Uacc)
   -------------------------------------------------------------------------*/
double dswxlnmq(double dw, short stau, double *adcnq)
{
  double du   = 0.0;
  double dmq  = 0.0;

  if( stau < adcnq[LCNQTMIN]) return((double)TOFUNDER);
  if( stau > adcnq[LCNQTMAX]) return((double)TOFOVER);

  du   = dswxu(stau,adcnq[LCNQTOFF],adcnq[LCNQTDAC]);

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
double dswxlnm(short stau, BYTE besd, double *adcnm)
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

/* ===========================================================================
** Standard Classification Settings
** ======================================================================== */

/* ---------------------------------------------------------------------------
   adputof --- TOF(E/q,PAPS,m/q) according to DPU algorithm
   -------------------------------------------------------------------------*/
double adputof(double eoq, double paps, double moq)
{
  double etrm = 0.0;
  double dtof;

  etrm = eoq + paps - 1.5;

  if( etrm <= 0.0 ) {
    printf("adputof --- bad energy: %.3f %.3f\n",eoq,paps);
    return(-1.0);
  }

  dtof = moq / aducla[LUCLAC1] / etrm;
  
  dtof = sqrt(dtof) * aducla[LUCLATC];  /* in channels */

  return(dtof);
}

/* ---------------------------------------------------------------------------
   adpuesd --- ESSD(TOF,m) according to DPU algorithm
   -------------------------------------------------------------------------*/
double adpuesd(double tof, double mas)
{
  double y;
  double alf;
  double bet;
  double gam;
  double e1;

  /* -------------------------------------------------------------------------
  ** channel --> ns
  ** ---------------------------------------------------------------------- */

  tof = tof / aducla[LUCLATC];

  y   = log(tof);

  alf = aducla[LUCLAA5];
  bet = aducla[LUCLAA2] + aducla[LUCLAA4] * y;
  gam = aducla[LUCLAA1] + 
    y * (aducla[LUCLAA3] + aducla[LUCLAA6] * y * y) - log(mas);

  if( alf == 0.0 ) {
    printf("adpuesd --- problem. alf = %.3f\n",alf);
    return(-1.0);
  }

  e1  = (-bet + sqrt(bet * bet - 4.0 * alf * gam)) / 2.0 / alf;

  e1  = exp(e1);

  e1  = e1 * aducla[LUCLAEC];

  return(e1);
}
  

/* ---------------------------------------------------------------------------
   adpumoq --- m/q(E/q,PAPS,TOF) according to DPU algorithm
   -------------------------------------------------------------------------*/
double adpumoq(double eoq, double paps, double tof)
{
  double etrm = 0.0;
  double moq;

  etrm = eoq + paps - 1.5;

  if( etrm <= 0.0 ) {
    printf("adpumoq --- bad energy: %.3f %.3f\n",eoq,paps);
    return(-1.0);
  }

  /* -------------------------------------------------------------------------
  ** channel --> ns
  ** ---------------------------------------------------------------------- */

  tof = tof / aducla[LUCLATC];

  moq = aducla[LUCLAC1] * etrm * dsqr(tof);
  
  return(moq);
}

/* ---------------------------------------------------------------------------
   adpumoq_sig --- sigma_moq according to DPU algorithm
   -------------------------------------------------------------------------*/
double adpumoq_sig(double sTOF, double TOF, double moq)
{
  if( TOF <= 0.0 ) {
    printf("adpumoq_sig --- bad TOF: %.1f\n",TOF);
    return(-1.0);
  }
  return(moq * 2.0 * sTOF/TOF);
}

/* ---------------------------------------------------------------------------
   adpumas --- m(ESSD,TOF) according to DPU algorithm
   -------------------------------------------------------------------------*/
double adpumas(double esd, double tof)
{
  double x;
  double y;
  double lnm;

  /* -------------------------------------------------------------------------
  ** channel --> ns/keV
  ** ---------------------------------------------------------------------- */

  y = tof / aducla[LUCLATC];
  x = esd / aducla[LUCLAEC];

  /* -------------------------------------------------------------------------
  ** x,y
  ** ---------------------------------------------------------------------- */

  if( y > 1.0 ) {
    y = log(y);
  } else {
    printf("adpumas --- Cannot deal with TOF = %.1f\n",tof);
    return(-1.0);
  }

  if( x > 1.0 ) {
    x = log(x);
  } else {
    printf("adpumas --- Cannot deal with ESD = %.1f\n",esd);
    return(-1.0);
  }

  /* -------------------------------------------------------------------------
  ** ln(m)
  ** ---------------------------------------------------------------------- */

  lnm = aducla[LUCLAA1] + 
    x * (aducla[LUCLAA2] + x * aducla[LUCLAA5]) + 
    y * (aducla[LUCLAA3] + aducla[LUCLAA4] * x + aducla[LUCLAA6] * y * y);

  return(exp(lnm));
}

/* ---------------------------------------------------------------------------
   adpueoq --- E/q for nominal stepping
   -------------------------------------------------------------------------*/
double adpueoq(int istep)
{
  double adnom[NXEQ] = {
10, 12, 14, 16, 18, 20, 22, 24, 26, 28, 30, 32, 34, 36, 38, 40, 42, 44, 46, 48,
50, 52, 54, 56, 58, 60, 62, 64, 66, 68, 70, 72, 74, 76, 78, 80, 82, 84, 86, 88,
90, 92, 94, 96, 98,100,102,104,108,112,116,120,124,128,132,136,140,144,148,152
  };
  double dres;

  printf("asxdpusim/adpueoq --- usage depreciated. Consider a3gxeqdpu_i.\n");

  if( (istep >= 0) && (istep < NXEQ ) ) {
    dres = 0.4271 * pow(1.036547,adnom[NXEQ - 1 - istep]);
    /* printf("adpueoq --- DBG %.3f\n",dres); */
    return(dres);
  } else {
    printf("adpueoq --- cannot deal with step %d\n",istep);
    return(-1.0);
  }
  return(-1.0);
}
