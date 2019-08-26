/*
  File:  TofMeasurementArray.h

  Description:
    Header file for TofMeasurementArray class. This purpose of this
    class is to provide an intelligent container for time of flight
    (TOF) spectra.  It has facilities for specifying filters on the
    input PHA data, extracting parts of the data and file I/O.  It
    automatically handles merging multiple adjacent channels to create arrays
    of reduced resolution.

  Author(s): Jim Raines (jmr)

  Method:

  Revision controlled by CVS:
  $Id: TofMeasurementArray.h,v 1.3 2004/07/28 13:28:35 jraines Exp $

  Major Modification History:
    01Mar2004   jmr   initial coding

*/

class TofMeasurementArray{

 public:
  // Construct a reduced-resolution array of 'size', automatically
  // handling filling with TOF into correct reduced-size bin
  // If size is ommitted it is set equal to ic.NumTofCh.
  TofMeasurementArray(InstrumentConstants& ic, int size);

  // Fill measurement array with counts from Pha
  int fill(AnalysisData2& ad, AceSwimsData& id);

  /* Register AmPhaFilter-derived class, so it is used with next fill().
     Returns number of PhaFilters registed (incl. this one). */
  //  int registerPhaFilter( const PhaFilter& f);
  //  int registerPhaFilter( const VelocityPhaFilter& f);
  int registerPhaFilter( AmPhaFilter& f);

  // turn on/off basic rate weighting
  void setDoBRW(bool flag);
  bool getDoBRW();  // report current state

  // file I/O of entire array
  int save(string file);
  int load(string file);

  // perform sum over start_ch though stop_ch channels (inclusive)
  float sumInSlice(int nedb, int start_ch, int stop_ch) const;

  // get an individual element
  float getElement(int nedb, int tofch) const;

  // get tof vector for one EDB
  TNT::Vector<float> getSlice(int nedb);

  // dump PHA used and not used into file with specified base
  void dumpPha(string file_base);

  // write out TMA to file
  void outputSlices(std::ofstream& fout);

 private:

  vector<TNT::Vector<float> > TMA;
  bool doBRW;
  bool useRates;

  bool dumpPhaFlag;
  string DumpPhaFile;

  // number by which to divide TOF when filling a reduced-resolution array
  int ResolScalar;

  // range checking, for class-internal use only
  bool goodNedb(int nedb) const;
  bool goodTofch(int tofch) const;

  // array of PhaFilters for pha checking fill()
  vector<AmPhaFilter *> Filters;
  //vector<VelocityPhaFilter> Filters;

  // store instrument constants for later
  InstrumentConstants IC;
};

