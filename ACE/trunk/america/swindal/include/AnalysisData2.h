/*
  File: AnalysisData.h

  Description:
    Containers and data for analysis of data from for TOF plasma
    instruments.  Does not contain info. specific to any one instrument.

  Author: Jim Raines

  Method:
    
  Revision controlled by CVS:
  $Id: AnalysisData2.h,v 1.3 2004/11/11 21:47:40 jraines Exp $
  
  Major Modification History:
    23Feb2004   jmr   Adapted from AnalysisData.h

*/

class AnalysisData2 {
 public:

  AnalysisData2(InstrumentConstants inst_const);

  InstrumentConstants ic;

  double getDutyCycle() const;

  double getEq(int nedb) const;

  double getPav() const;

  // load an ion for analysis
  int loadIon(string name, string element, float mass, float charge);
  int loadIon(string name, float mass, float charge);

  // total number of ions loaded
  int getNumIons() const ;

  // get an ion by index (for looping)
  Ion getIon(int s) const;

  // get an ion by name
  Ion getIon(string name) const;

  double getCycleTime() const;

  float getAccumTime() const;
  void setAccumTime(float time);

  // set/get forward model parameters
  void setFmTof(int s, int nedb, float tof, float stof);
  void setFmTof(string ion, int nedb, float tof, float stof);
  double getFmTof(int s, int nedb) const; 
  double getFmTof(string ion, int nedb) const; 
  double getFmStof(int s, int nedb) const; 
  double getFmStof(string ion, int nedb) const; 
  // write out all FM params to file
  int FMoutput(string file) const ;

  // get index of ion in Ions array
  unsigned int getIonIndex(string ion) const;
 private:

  // this allows InstrumentData and it's specific instrument derivatives
  // to set private members, which is appropriate
  friend class InstrumentData;
  friend class AceSwimsData;
  friend class AceSwicsData;

  // all ions to be used in analysis
  vector<Ion> Ions;

/*   Removed, pending a way to implement a const map */
/*   // alternate ways to access ions */
/*   map<string,int> IonsIndex;           // indexes in Ions vector keyed by  */
/*                                        // ion name  */
/*   map<string,Ion> IonsByName;          // all defined ions, keyed by ion name */
/*   map<string,Ion>::iterator Ibn_iter;  // iterator for above */

  // E/q values (keV/e) indexed by step (EDB) number
  // Note:  This means elements 0 and 1 are -1.0 and not used.
  vector <double> Eqtab;

  // most recent value for duty cycle (unit-less)
  float DutyCycle;

  // most recent value for post-acceleration voltage (kV)
  double PostAccelVolt;

  // cycle time (seconds since 1Jan1970 00:00:00) 
  // read out of first PHA of most recently loaded group
  double CycleTime;

  // accumulation time (s) of most recently loaded MeasurementArray/Vector
  float AccumTime;

};
