/*
  File: cycletimetodate.cc

  Revision controlled by SVN:
  $Id$
*/
#include <string>
#include <sstream>
#include <iomanip>
namespace libhef {
  extern "C" {
#include "libhef.h"
  }
}

std::string cycletimetodate(double cycletime){
  long alltime[14];
  long ss1970l = (long) cycletime;
  
  // use converter from libhef
  // alltime = 
  // 0     1      2    3   4   5     6    7  8   9   10
  // sec70 julian secs DOY day month year hr min sec week-day (0 for sunday)
  libhef::sec70_time(alltime, &ss1970l);

  using std::setw;
  using std::setfill;

  // format string
  std::ostringstream doy_str;
  doy_str << setfill('0') << setw(4) << alltime[6] << "_" << setw(3) << alltime[3] << "_" << setw(2) << alltime[7] << "." << setw(2) << alltime[8] << "." << setw(2) << alltime[9];
    
  return(doy_str.str());
}
