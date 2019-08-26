/*
  File: InstrumentHousekeeping.h

  Description:
    Header file for InstrumentHousekeeping class, a base class set up to
    handle all housekeeping values from  TOF plasma spectrometers (with and
    without energy detectors).  Note that this class contains very
    little, and mainly exists to allow generic typing for HK classes
    in AnalysisData2 objects.

  Author(s): Jim Raines (jmr)

  Method:

  Revision controlled by CVS:
  $Id: InstrumentHousekeeping.h,v 1.1 2004/04/27 20:39:31 jraines Exp $

  Major Modification History:
    18Mar2004   jmr   initial coding

*/

class InstrumentHousekeeping {
 public:

  InstrumentHousekeeping();

  // required because of virtual functions
  //virtual ~InstrumentHousekeeping();

 private:

  // this allows InstrumentData and it's specific instrument derivatives
  // to set private members, which is appropriate
  friend class InstrumentData;
  friend class AceSwimsData;
  friend class AceSwicsData;

};
