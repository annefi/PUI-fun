/*
  File: AssignedCounts.h

  Description:

    Header file for AssignedCountsElem class, a class holding a sum of
    MeasurementArray slices for ions and steps of a specified element.
    Also contains associated meta-data.  This represents counts
    assigned to specified element by the axlv2 method.  Note, this
    class is effectively just a data structure, since members are
    accessed directly.

  Author(s): Jim Raines (jmr)

  Method:

  Revision controlled by CVS:
  $Id: AssignedCountsElem.h,v 1.1 2005/01/19 03:20:30 jraines Exp $

  Major Modification History:
    18Jan2005   jmr   Adapted from AssignedCounts class

*/

class AssignedCountsElem {
 public:
  // TOF-ESD slice
  TNT::Matrix<float> slice; 

  // element name
  string elem; 

  // EDB (step) number
  int nedb;

  // index range in AnalysisData::Ions array
  int index_lo;
  int index_hi;

  AssignedCountsElem(InstrumentConstants ic, 
					 string input_elem, 
					 int input_index_lo, 
					 int input_index_hi, 
					 int input_nedb);

 private:

};
