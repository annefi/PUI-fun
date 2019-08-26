/*
  File: doyfr2doy_fr_str.cc

  Description:
    Convert floating point day of year fraction (doyfr) to string 
    with 3 digit year and 2 digit fraction (0 filled to 3 and 2
    places, resp.) and separated by an underscore, e.g. 001_84, 302_08

  Author(s): Jim Raines (jmr)

  Method:

  Revision controlled by CVS:
  $Id: doyfr2doy_fr_str.cc,v 1.3 2005/06/09 04:06:51 jraines Exp $

  Major Modification History:
    26Jan2004   jmr   initial coding
    06Jun2005   jmr   added a decimal place, now ddd.ddd

*/
#include <string>
#include <sstream>
#include <iomanip>

std::string doyfr2doy_fr_str(float doyfr){
  using std::setw;
  using std::setfill;

  // separate integer part from fraction part
  int idoy, ifr;
  idoy = static_cast<int> (doyfr);
  ifr  = static_cast<int> (doyfr*1000.0 + .5) % 1000;

  // format string
  std::ostringstream doyfr_str;
  doyfr_str << setfill('0') << setw(3) << idoy << "_" << setw(3) << ifr;
    
  return(doyfr_str.str());
}
