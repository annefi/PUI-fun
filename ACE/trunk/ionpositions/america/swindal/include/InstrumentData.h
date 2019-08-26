/*
  File: InstrumentData.h

  Description:

    Header file for InstrumentData class, a class for loading and
    holding TOF mass spectrometer data.  This is an abstract base
    class only; it should never be instantiated.  Rather, all
    instrument-specific details are to be encapsulated in derived
    classes, e.g. AceSwimsData.

  Author(s): Jim Raines (jmr)

  Method:

  Revision controlled by CVS:
  $Id: InstrumentData.h,v 1.2 2004/11/03 18:15:09 jraines Exp $

  Major Modification History:
    23Feb2004   jmr   initial coding

*/

class InstrumentData {
 public:

  // required because of virtual functions
  virtual ~InstrumentData();

  // *pure* virtual functions to be defined in derived classes
  virtual int load(AnalysisData2& ad, int NumCyclesToLoad) = 0;
  virtual double* getFM(double eoq, double pav, double mass, double charge) =0;

  // get number of PHA currently loaded
  virtual long getNumPha() const;

  // get ith PHA word (i: 0...getNumPha()-1)
  virtual Pha* getPha(int i) ;

 private:
  
  // list of derived classes that will actually do the work
  friend class AceSwimsData;
  friend class AceSwicsData;

  vector<Pha> PhaData;


};
