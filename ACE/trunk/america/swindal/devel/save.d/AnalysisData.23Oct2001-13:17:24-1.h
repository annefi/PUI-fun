/*
  File: AnalysisData.h

  Description:
    AnalysisData Class

  Author: Jim Raines, May2001

  Method:
    
  Major Modification History:
    

*/

class AnalysisData {
 public:
  vector<Ion> Ions;                    // vector containing all ions defined
  map<string,int> IonsIndex;           // indexes in Ions vector keyed by 
                                       // ion name 
  map<string,Ion> IonsByName;          // all defined ions, keyed by ion name
  map<string,Ion>::iterator Ibn_iter;  // iterator for above


  vector<double> Eqtab;        // Commanded E/q values

  /* E/q acceptance range factor, delta E / q, unitless
     Eqtab[nedb]*EqAcceptFac give width of E/q accepted at nedb
  */
  double EqAcceptFac;

  /* Post. Acceleration Voltage in kV */
  double PapsVolt;


  /* Geometric Factor, an area in cm^2 */
  double GeomFactor;

  AnalysisData(void);          // Constructor

  void dump(void);             // dump contents
 private:

};

