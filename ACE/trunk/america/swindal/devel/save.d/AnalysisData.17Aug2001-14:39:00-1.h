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
  map<string,Ion> Ions;        // Ions used for analysis
  map<string,Ion>::iterator Ions_iter;  // iterator for above
  vector<Ion> IonsVec;         // group containing all ions defined

  vector<double> Eqtab;        // Commanded E/q values
  
  AnalysisData(void);          // Constructor

  void dump(void);             // dump contents
 private:

};

