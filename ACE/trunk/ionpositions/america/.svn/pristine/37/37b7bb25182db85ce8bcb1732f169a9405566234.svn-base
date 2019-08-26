/*
  File: get_ace_angles.cc

  Description:

    Get a bunch of angles for ACE.  (I figured all these out while
    trying to figure out the aspect (Sun-Probe-Earth) angle.

  Author(s): Jim Raines (jmr)

  Method:

    Direction cosines for ACE are read from the ancillary data using
    the acetest/anciltest tools.  


  Revision controlled by CVS:
  $Id: get_ace_angles.cc,v 1.3 2003/10/17 16:01:54 jraines Exp $

  Major Modification History:
    19Sep2003   jmr   initial coding (as get_ace_aspect.cc)
    02Oct2003   jmr   Renamed from get_ace_aspect.cc

*/
#include <cstdio>
#include <iostream>
#include <cmath>
extern "C" {
#include "libace_ancil.h"
#include <cstdlib>
}

int main(int argc, char *argv[]){
  int retval = 0; // return value; 0=>normal, 1=>problem
  long int CycleTime;
  float AspectAngle = 0.0;
  float AttAngle = 0.0;

  using std::cout;
  using std::endl;

    // switch based on args
  switch (argc) {
  case 2:
    CycleTime = atol(argv[1]);
    break;
  default:
    // print usage and exit
    cout << "usage:  " << argv[0] << " cycle_time" << endl;
    return(1);
  }

  a3goa_read("/home/ivar/berger/ace/LV1/ACE_ANCIL.HDF");

  AttAngle = acos(a3goa_att_GSE_x(CycleTime));
    ;

//   AttAngle = 180 - acos(a3goa_pos_GSE_x(CycleTime)) - 
//     acos(a3goa_pos_HSEb_x(CycleTime));

  cout << "GSE x - ACE z Angle = " << AttAngle << " deg." << endl;

  // Sun - Probe - Earth angle
  float r_sun;
  float beta_sun;
  r_sun = sqrt( pow( (double)a3goa_pos_HSEb_x(CycleTime), 2 ) 
		+ pow( (double)a3goa_pos_HSEb_z(CycleTime), 2) );
  beta_sun = acos( a3goa_pos_HSEb_x(CycleTime) / r_sun );

  float r_earth;
  float beta_earth;
  r_earth = sqrt( pow(a3goa_pos_GSE_x(CycleTime),2) + 
		  pow(a3goa_pos_GSE_z(CycleTime),2) );
  beta_earth = acos( a3goa_pos_GSE_x(CycleTime) / r_earth );

  AspectAngle = 180 - beta_sun - beta_earth;

  cout << "Sun - Probe - Earth angle = " << AspectAngle << " deg." << endl;

  // Angle between ACE spin axis and ACE-Sun line (relevant aspect angle)
  AspectAngle = acos(a3goa_att_HSEb_x(CycleTime));
  cout << "acos(a3goa_att_HSEb_x) = " << AspectAngle << endl;

  AspectAngle = acos(a3goa_att_RTN_r(CycleTime));
  cout << "acos(a3goa_att_RTN_r) = " << AspectAngle << endl;

  return(retval);
}
