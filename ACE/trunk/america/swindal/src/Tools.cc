/*
  File: Tools.cc

  Description:
    Code for the Tools class, a class of misc. code of general
    usefulness.

  Author(s): Jim Raines (jmr)

  Method:

  Revision controlled by CVS:
  $Id: Tools.cc,v 1.1 2004/04/27 20:39:51 jraines Exp $

  Major Modification History:
    02Mar2004   jmr   initial coding

*/

#include "swindal.h"

float Tools::ss1970_to_doyfr(double ss1970) const{
  float doyfr;
  long alltime[14];

  long ss1970l = (long) ss1970;

  // use converter from libhef
  // alltime = 
  // 0     1      2    3   4   5     6    7  8   9   10
  // sec70 julian secs DOY day month year hr min sec week-day (0 for sunday)
  sec70_time(alltime, &ss1970l);

  // doy + (hr*3600 + min*60 + sec)/86400.0
  doyfr = alltime[3] + 
    (float)(alltime[7]*3600 + alltime[8]*60 + alltime[9])/86400.0;

  return(doyfr);
}

