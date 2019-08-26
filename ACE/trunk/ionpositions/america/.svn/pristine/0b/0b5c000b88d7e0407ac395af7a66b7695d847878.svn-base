/*
  File: Pha.cc

  Description:
    Code for Pha class, which contains data for individual PHA words.

  Author: Jim Raines, 31Jul2001

  Method: 
    Functions supporting the Pha class.

  Revision controlled by CVS:
  $Id: Pha.cc,v 1.5 2005/06/09 04:06:12 jraines Exp $

  Major Modification History:
    

*/

#include "swindal.h"

Pha::Pha(){
  scet = -1.0;
  nedb = -1;
  eq = -1.0;
  tof = -1.0;
  tofch = -1;
  esd = -1.0;
  esdch = -1;
  sector = -1;
  detector = -1;
  range = -1;
  for (int  i = 0; i < 3; i++) br[i] = -1;
  tcr = -1.0;
  mmch = -1.0;
  mm = -1.0;
  mqch = -1.0;
  mq = -1.0;
  speed = -1.0;
  swspeed = -1.0;
  weight = -1.0;
}

void Pha::dump(int npha, int ncycle, FILE* F) const {
  /* scet, nedb, npha, eq */
  fprintf(F,"%010.0f %02d %03d %6.2f",scet, nedb,npha,eq);

  /* tof, esd, sector */
  fprintf(F," %10.2f %10.2f %02d",tof,esd,sector);

  /* range, br0, br1, br2, wt */
  fprintf(F," %01d %05ld %05ld %05ld %10.2f",range,
	  br[0],br[1],br[2], weight);
  
  /* vi, vw, mm, mq, ncycle*/
  fprintf(F," %10.2f %10.2f %10.2f %10.2f %03d\n",speed,swspeed,mm,mq,
	 ncycle);
}

// copy constructor, required because vectors do not default copy
Pha::Pha(const Pha& pha){
  scet = pha.scet;
  nedb = pha.nedb;
  eq = pha.eq;
  tof = pha.tof;
  tofch = pha.tofch;
  esd = pha.esd;
  esdch = pha.esdch;
  sector = pha.sector;
  detector = pha.detector;
  range = pha.range;
  for (int  i = 0; i < 3; i++) br[i] = pha.br[i];
  tcr = pha.tcr;
  mmch = pha.mmch;
  mm = pha.mm;
  mqch = pha.mqch;
  mq = pha.mq;
  speed = pha.speed;
  swspeed = pha.swspeed;
  weight = pha.weight;  
}

// assignment copy constructor
Pha& Pha::operator= (const Pha& rhs){
  if (this != &rhs){  // guard against self assignment
    scet = rhs.scet;
    nedb = rhs.nedb;
    eq = rhs.eq;
    tof = rhs.tof;
    tofch = rhs.tofch;
    esd = rhs.esd;
    esdch = rhs.esdch;
    sector = rhs.sector;
    detector = rhs.detector;
    range = rhs.range;
    for (int  i = 0; i < 3; i++) br[i] = rhs.br[i];
    tcr = rhs.tcr;
    mmch = rhs.mmch;
    mm = rhs.mm;
    mqch = rhs.mqch;
    mq = rhs.mq;
    speed = rhs.speed;
    swspeed = rhs.swspeed;
    weight = rhs.weight;  
  }

  return *this;
}

