/*
  Filename: incrementYdoy.cc

  Description:  
  Increments yyyydoy rolling over the years properly (incl. leap years).

  Created by : Jim Raines, 19Jul2001

  Major Modification History

*/

#include "swindal.h"
extern "C" {
#include "libhef.h"
}

long int incrementYdoy(long int CurYdoy){
  int year = CurYdoy/1000;
  int day  = CurYdoy - year*1000;

  if ( day == (365 + is_leap(year) ) ){
    CurYdoy = (year + 1)*1000 + 1; 
  }
  else{
    CurYdoy++;
  }
  
  return CurYdoy;
}

