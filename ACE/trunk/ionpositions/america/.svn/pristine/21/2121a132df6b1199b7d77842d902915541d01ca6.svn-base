/*
  File: dump_ace_aosr.cc

  Description:
    Print all orbit/attitude information for given cycle time.

  Author(s): Jim Raines (jmr)

  Method:

    Direction cosines for ACE are read from the ancillary data using
    the acetest/anciltest tools.  


  Revision controlled by CVS:
  $Id: dump_ace_aosr.cc,v 1.2 2003/10/17 16:01:53 jraines Exp $

  Major Modification History:
    02Oct2003   jmr   Adapted from get_ace_aspect.cc

*/
#include <cstdio>
#include <iostream>
#include <cmath>
extern "C" {
#include "libace_ancil.h"
#include <cstdlib>
}

using std::cout;
using std::endl;

int main(int argc, char *argv[]){
  long int CycleTime;

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

  cout << "Dumping all ACE orbit/attitude informatin for cycle time = "
       << CycleTime << " ..." << endl;
  cout << "Note:  Coordinates are given in x, y, z order, except for RTN, "
       << "which are in the indicated (RTN) order." << endl;
  print_aosr(*a3goa(CycleTime));

  return(0);
}
