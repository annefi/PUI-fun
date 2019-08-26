/*
  File: get_ace_aspect.cc

  Description:
    Get ACE aspect (Sun - ACE spin axis (z)) angle in degrees.

  Author(s): Jim Raines (jmr)

  Method:

    Direction cosines for ACE are read from the ancillary data using
    the acetest/anciltest tools.  

  Revision controlled by CVS:
  $Id: get_ace_aspect.cc,v 1.4 2003/10/21 15:49:20 jraines Exp $

  Major Modification History:
    19Sep2003   jmr   initial coding
    02Oct2003   jmr   cleaned up

*/
#include <cstdio>
#include <iostream>
#include <cmath>
extern "C" {
#include "libace_ancil.h"
#include <cstdlib>
}

using namespace std;

int main(int argc, char *argv[]){
  int retval = 0; // return value; 0=>normal, 1=>problem
  long int CycleTime;
  float AspectAngle = 0.0;
  float AttAngle = 0.0;

    // switch based on args
  switch (argc) {
  case 3:
    CycleTime = atol(argv[1]);
    break;
  default:
    // print usage and exit
    cerr << "usage:  " << argv[0] << " cycle_time  'position of ACE_ANCIL.HDF'" << endl;
    cerr << "Prints angle between ACE spin (z) axis and ACE-Sun radial vector in degrees." << endl;
    return(1);
  }

  cerr << "get_ace_aspect :: " << argv[2] << std::endl;
  //a3goa_read("/data/asterix/ace/data/LV1/ACE_ANCIL.HDF");
  a3goa_read(argv[2]);

  // Angle between ACE spin axis and ACE-Sun line (relevant aspect angle)
  AspectAngle = acos(a3goa_att_RTN_r(CycleTime));
  cout << AspectAngle << endl;

  return(retval);
}
