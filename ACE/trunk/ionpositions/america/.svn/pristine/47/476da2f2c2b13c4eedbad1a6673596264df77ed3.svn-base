/*
  File: AssignedCounts.cc

  Description:
    Code for AssignedCounts class, a class holding a MeasurementArray
    slice and associated meta-data representing counts assigned by
    some method, e.g. axlv2.

  Author(s): Jim Raines (jmr)

  Method:

  Revision controlled by CVS:
  $Id: AssignedCounts.cc,v 1.1 2004/04/27 20:39:44 jraines Exp $

  Major Modification History:
    12Mar2004   jmr   initial coding

*/
#include "swindal.h"

AssignedCounts::AssignedCounts(InstrumentConstants ic, string input_ion, 
			       int input_index, int input_nedb) {
  string thisprog = "AssignedCounts";
  string build_info = __DATE__;
  build_info = build_info + " ";
  build_info = build_info + __TIME__;
  string rcs_id = "$Id: AssignedCounts.cc,v 1.1 2004/04/27 20:39:44 jraines Exp $";

  // init slice
  TNT::Matrix<float> tmp(ic.getNumTofCh(), ic.getNumEsdCh(), 0.0);
  slice = tmp;

  ion = input_ion;
  nedb = input_nedb;
  index = input_index;

//   se_index = index*100 + nedb;
}

