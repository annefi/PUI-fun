/*
  File: Pha.cc

  Description:
    Pha Class

  Author: Jim Raines, 31Jul2001

  Method: 
    Functions supporting the Pha class.  loadPha should be included
    here but is not yet.

  Major Modification History:
    

*/

#include "swindal.h"

extern "C" {
#include "libhef.h"
}

double Pha::tofch2tof(int tofch){
  return (double) (tofch * 0.1955);
}

int Pha::tof2tofch(double tof){
  return (int) (tof / 0.1955);
}

double Pha::esdch2esd(int esdch){
  return (double) (esdch * 2.395);
}

int Pha::esd2esdch(double esd){
  return (int) (esd / 2.395);
}

