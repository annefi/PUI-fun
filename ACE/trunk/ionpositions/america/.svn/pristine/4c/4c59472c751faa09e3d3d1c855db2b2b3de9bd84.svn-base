/*
  File: AnalysisData.h

  Description:
    Containers and data for data analysis without regard to specific
    (SWICS-style) instrument.

  Author: Jim Raines

  Method:
    
  Revision controlled by CVS:
  $Id: AnalysisData.h,v 1.11 2005/03/24 21:34:14 jraines Exp $
  
  Major Modification History:
      May2001   jmr   initial coding
    10Oct2003   jmr   Inserted duty cycle code.

*/

class AnalysisData {
 public:

  vector<Ion> Ions;                    // vector containing all ions defined

  // get ion index from name of ion
  int getIonIndex(string ion); 

  // get Ion object from name of ion
  Ion getIon(string ion); 

  std::map<string,Ion>::iterator Ibn_iter;  // iterator for above


  vector<double> Eqtab;        // Commanded E/q values

  /* E/q acceptance range factor, delta E / q, unitless
     Eqtab[nedb]*EqAcceptFac give width of E/q accepted at nedb
  */
  double EqAcceptFac;

  /* Post. Acceleration Voltage in kV */
  double PapsVolt;


  /* Geometric Factor, an area in cm^2 */
  double GeomFactor;

  /* Current cycle time in seconds since 1970 */
  double CycleTime;

  /* Current cycle time converted into day of year fraction */
  float Doyfr;

  // constructor
  AnalysisData(void);

  // build ion table
  int init(void);
  // read in various instrument parameters, such as E/q table
  int loadInstParam(const AceSwicsData&);

  void loadIon(string name, string element,float mass, float charge);

  void outputFM();

  // load Forward Model params
  // --- post accel. volt (pav) read from data
  int loadFM(const AceSwicsData&);
  // --- user specified pav
  int loadFM(const AceSwicsData&, double pav);

  // load *EXPERIMENTAL* Forward Model params
  // --- post accel. volt (pav) read from data
  int loadFMexp(const AceSwicsData&);
  // --- user specified pav
  int loadFMexp(const AceSwicsData&, double pav);

  // output forward model parameters for overlay on E-T slices by IDL code
  void outputFM(string outfile);
  
  // print ion names and scalar values
  void print(void);

  // dump contents, including E/q table and per Ion FM
  // *generates many lines per ion*
  void dump(void);             // dump contents

 private:

  std::map<string,int> IonsIndex;      // indexes in Ions vector keyed by 
                                       // ion name 
  std::map<string,Ion> IonsByName;     // all defined ions, keyed by ion name
};

