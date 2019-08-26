/*
  File: AssignedCounts.h

  Description:
    Header file for AssignedCounts class, a class holding a
    MeasurementArray slice and associated meta-data representing
    counts assigned by some method, e.g. the axlv2 method.  Note, this
    class is effectively just a data structure, since members are
    accessed directly.

  Author(s): Jim Raines (jmr)

  Method:

  Revision controlled by CVS:
  $Id: AssignedCounts.h,v 1.1 2004/04/27 20:39:28 jraines Exp $

  Major Modification History:
    12Mar2004   jmr   initial coding

*/

class AssignedCounts {
 public:
  // TOF-ESD slice
  TNT::Matrix<float> slice; 

  // ion name
  string ion; 

  // EDB (step) number
  int nedb;

  // index in AnalysisData::Ions array
  int index;

/*   // species/edb combined index (for rapid searching) */
/*   int se_index; */

    AssignedCounts(InstrumentConstants ic, string input_ion, 
		   int input_index, int input_nedb);
 private:

};
