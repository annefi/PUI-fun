# ---------------------------------------------------------------------------
#   Adapted from asxdpusim.c by Lars Berger (berger@physik.uni-kiel.de)
#   asxdpusim.c --- DPU simulator for ACE/SWICS
#   1998 by Hefti, University of Michigan (hefti@umich.edu)
#   $Id: asxdpusim.c,v 1.1.1.1 2000/06/02 13:37:19 jraines Exp $
# ---------------------------------------------------------------------------

from numpy import *
from datatypes import *
from decoded import *

S3DPULNQ = 34.59577
S3DPULNM = 25.50089

# --- DPU software hard-coded values ---

MUNDER  =   0                # Output this code if M is too small   
MOVER   = 123                # Output this code if M is too big     
EUNDER  = 124                # Output this code if E is too small   
EOVER   = 125                # Output this code if E is too big     


MQUNDER =   0                # Output this code if M/Q is too small 
MQOVER  = 125                # Output this code if M/Q is too big   
TOFUNDER= 126                # Output this code if TOF is too small 
TOFOVER = 127                # Output this code if TOF is too big   

S3XNMMAX=  122.0             # min/max channel used 
S3XNMMIN=    1.0
S3XM_MAX=  115.0             # min/max mass classified 
S3XM_MIN=    1.0

S3XNQMAX=  124.0             # min/max channel used 
S3XNQMIN=    1.0
S3XQ_MAX=   35.0             # min/max m/q classified 
S3XQ_MIN=    1.0

LUCLAC1 =0
LUCLAA1 =1
LUCLAA2 =2
LUCLAA3 =3
LUCLAA4 =4
LUCLAA5 =5
LUCLAA6 =6
LUCLATC =7
LUCLAEC =8

NUCLA   =9
aducla=array([1.9159e-5, 5.81090, -1.50052, -3.01352, 0.471113, 0.0804588, 0.0731559, 5.115, 0.417498936])                        # E [keV]  --> ch 
#                                                                                            ^            ^          
#                                                                                        tof[ns]->ch  E[keV]->ch                  
# ---------------------------------------------------------------------------
#   dswxu --- calculate u = ln(t + Toffset) + lnTADC
# ---------------------------------------------------------------------------
def dswxu(stau,dToff,dTdac):
  dt = float64(stau) + dToff
  if (dt < 1.0):
    print "E:dswxu:bad (TOF+OFFSET) %.2f"%(dt) 
    return -1.0
  
  dt = log(dt) + dTdac
  return dt


# ---------------------------------------------------------------------------
#   dswxeoq --- calculate E/q [keV/q]
#   low step number gives low E/q. Low index in eqtab is low E/q.
# --------------------------------------------------------------------------
def dswxeoq(bstp,abeqtab,adcnq):
    return adcnq[LCNQEOQ0] * pow(adcnq[LCNQEOQ1],float64(abeqtab[bstp]))

# ---------------------------------------------------------------------------
#   dswxpal --- calculate PAPS [kV]
# ---------------------------------------------------------------------------
def dswxpal(bpaps,bred,adcnq):
    if (bred):
        return adcnq[LCNQPOF2] + adcnq[LCNQPSL2] * float64(bpaps)
    else:
        return adcnq[LCNQPOF1] + adcnq[LCNQPSL1] * float64(bpaps)

# ---------------------------------------------------------------------------
#   dswxlnmq --- calculate ACE/SWICS ln(m/q) in channels, in double precision
#   w = ln(E/q + Uacc)
# ---------------------------------------------------------------------------
def dswxlnmq(dw,stau,adcnq):
    du   = 0.0
    dmq  = 0.0

    if (stau < adcnq[LCNQTMIN]):
        return float64(TOFUNDER)
    if (stau > adcnq[LCNQTMAX]):
        return float64(TOFOVER)

    du   = dswxu(stau,adcnq[LCNQTOFF],adcnq[LCNQTDAC])

    dmq  = adcnq[LCNQCLA0] + adcnq[LCNQCLA1] * dw + adcnq[LCNQCLA2] * du

    if (dmq < adcnq[LCNQCMIN]):
        return float64(MQUNDER)
    if (dmq > adcnq[LCNQCMAX]):
        return float64(MQOVER)
    return dmq

# ---------------------------------------------------------------------------
#   dswxlnm --- calculate ACE/SWICS ln(m) in channels, double precision
# ---------------------------------------------------------------------------
def dswxlnm(stau,besd,adcnm):
    dv = 0.0
    du = 0.0
    dm = 0.0

    if (stau < adcnm[LCNMTMIN]):
        return float64(TOFUNDER)
    if (stau > adcnm[LCNMTMAX]):
        return float64(TOFOVER)

    if (int32(besd) < adcnm[LCNMEMIN]):
        return float(EUNDER)
    if (int32(besd) > adcnm[LCNMEMAX]):
        return float64(EOVER)

    du = dswxu(stau,adcnm[LCNMTOFF],adcnm[LCNMTDAC])
    dv = dswxu(int32(besd),adcnm[LCNMEOFF],adcnm[LCNMEDAC])
    # dswxu calculates ln(1st + 2nd) + 3rd 

    dm = adcnm[LCNMCLA0] + dv * (adcnm[LCNMCLA1] + adcnm[LCNMCLA3] * du + adcnm[LCNMCLA4] * dv) + du * (adcnm[LCNMCLA2] + adcnm[LCNMCLA5] * du * du)

    if (dm < adcnm[LCNMCMIN]):
        return float64(MUNDER)
    if (dm > adcnm[LCNMCMAX]):
        return float64(MOVER)

    return dm

# ===========================================================================
# Standard Classification Settings
# ======================================================================== 

# ---------------------------------------------------------------------------
#   adputof --- TOF(E/q,PAPS,m/q) according to DPU algorithm
# ---------------------------------------------------------------------------
def adputof(eoq,paps,moq):
    etrm = 0.0
    

    etrm = eoq + paps - 1.5

    if (etrm <= 0.0):
        print "adputof --- bad energy: %.3f %.3f\n"%(eoq,paps)
        return -1.0

    dtof = moq / aducla[LUCLAC1] / etrm
    
    dtof = sqrt(dtof) * aducla[LUCLATC]  # in channels 

    return dtof 

# ---------------------------------------------------------------------------
#   adpuesd --- ESSD(TOF,m) according to DPU algorithm
# ---------------------------------------------------------------------------
def adpuesd(tof,mas):

    # -------------------------------------------------------------------------
    # channel --> ns
    # ---------------------------------------------------------------------- 

    tof = tof / aducla[LUCLATC]

    y   = log(tof)

    alf = aducla[LUCLAA5]
    bet = aducla[LUCLAA2] + aducla[LUCLAA4] * y
    gam = aducla[LUCLAA1] + y * (aducla[LUCLAA3] + aducla[LUCLAA6] * y * y) - log(mas)

    if (alf == 0.0):
        print "adpuesd --- problem. alf = %.3f\n"%(alf)
        return -1.0
  
    e1  = (-bet + sqrt(bet * bet - 4.0 * alf * gam)) / 2.0 / alf

    e1  = exp(e1)

    e1  = e1 * aducla[LUCLAEC]

    return e1

  

# ---------------------------------------------------------------------------
#   adpumoq --- m/q(E/q,PAPS,TOF) according to DPU algorithm
# ---------------------------------------------------------------------------
def adpumoq(eoq,paps,tof):
    etrm = 0.0
        
    etrm = eoq + paps - 1.5

    if (etrm <= 0.0):
        print "adpumoq --- bad energy: %.3f %.3f\n"%(eoq,paps)
        return -1.0
  

    # -------------------------------------------------------------------------
    # channel --> ns
    # ---------------------------------------------------------------------- 

    tof = tof / aducla[LUCLATC];

    moq = aducla[LUCLAC1] * etrm * sqrt(tof)  # FIXME sqrt==dsqr?????
  
    return moq


# ---------------------------------------------------------------------------
#   adpumoq_sig --- sigma_moq according to DPU algorithm
# ---------------------------------------------------------------------------
def adpumoq_sig(sTOF,TOF,moq):
    if (TOF <= 0.0):
        print "adpumoq_sig --- bad TOF: %.1f\n"%(TOF)
        return -1.0
    
    return moq * 2.0 * sTOF/TOF


# ---------------------------------------------------------------------------
#   adpumas --- m(ESSD,TOF) according to DPU algorithm
# ---------------------------------------------------------------------------
def adpumas(esd,tof):

    # -------------------------------------------------------------------------
    # channel --> ns/keV
    # ------------------------------------------------------------------------- 

    y = tof / aducla[LUCLATC]
    x = esd / aducla[LUCLAEC]

    # -------------------------------------------------------------------------
    # x,y
    # ---------------------------------------------------------------------- 

    if (y > 1.0):
        y = log(y)
    else:
        print "adpumas --- Cannot deal with TOF = %.1f\n"%(tof)
        return -1.0
  

    if (x > 1.0):
        x = log(x)
    else:
        print "adpumas --- Cannot deal with ESD = %.1f\n"%(esd)
        return -1.0
  

    # -------------------------------------------------------------------------
    # ln(m)
    # ---------------------------------------------------------------------- 

    lnm = aducla[LUCLAA1] + x * (aducla[LUCLAA2] + x * aducla[LUCLAA5]) + y * (aducla[LUCLAA3] + aducla[LUCLAA4] * x + aducla[LUCLAA6] * y * y)

    return exp(lnm)


# ---------------------------------------------------------------------------
#   adpueoq --- E/q for nominal stepping
# ---------------------------------------------------------------------------
def adpueoq(istep):
    adnom = array([10, 12, 14, 16, 18, 20, 22, 24, 26, 28, 30, 32, 34, 36, 38, 40, 42, 44, 46, 48,50, 52, 54, 56, 58, 60, 62, 64, 66, 68, 70, 72, 74, 76, 78, 80, 82, 84, 86, 88,90, 92, 94, 96, 98,100,102,104,108,112,116,120,124,128,132,136,140,144,148,152],float)

    print "asxdpusim/adpueoq --- usage depreciated. Consider a3gxeqdpu_i.\n"

    if ((istep >= 0) and (istep < NXEQ)):
        dres = 0.4271 * pow(1.036547,adnom[NXEQ - 1 - istep])
        # printf("adpueoq --- DBG %.3f\n",dres); 
        return dres
    else:
        print "adpueoq --- cannot deal with step %d\n"%(istep)
        return -1.0
  
    return -1.0

