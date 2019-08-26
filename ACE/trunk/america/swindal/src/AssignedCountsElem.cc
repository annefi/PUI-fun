/*
  File: AssignedCountsElem.cc

  Description:

    Code for AssignedCountsElem class, a class holding a sum of
    MeasurementArray slices for ions and steps of a specified element.
    Also contains associated meta-data.  This represents counts
    assigned to specified element by the axlv2 method.

  Author(s): Jim Raines (jmr)

  Method:

  Revision controlled by CVS:
  $Id: AssignedCountsElem.cc,v 1.1 2005/01/19 03:20:30 jraines Exp $

  Major Modification History:
    18Jan2005   jmr   Adapted from AssignedCounts class

*/
#include "swindal.h"

AssignedCountsElem::AssignedCountsElem(InstrumentConstants ic, 
				       string input_elem, 
				       int input_index_lo, int input_index_hi, 
				       int input_nedb) {
  string thisprog = "AssignedCountsElem";
  string build_info = __DATE__;
  build_info = build_info + " ";
  build_info = build_info + __TIME__;
  string rcs_id = "$Id: AssignedCountsElem.cc,v 1.1 2005/01/19 03:20:30 jraines Exp $";

  // init slice
  TNT::Matrix<float> tmp(ic.getNumTofCh(), ic.getNumEsdCh(), 0.0);
  slice = tmp;

  elem = input_elem;
  index_lo = input_index_lo;
  index_hi = input_index_hi;
  nedb = input_nedb;

}

