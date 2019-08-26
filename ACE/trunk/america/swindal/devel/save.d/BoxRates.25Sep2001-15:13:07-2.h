/*
  File: BoxRates.h

  Description:
    BoxRates class.

  Author: Jim Raines, 31Jul2001.

  Method:
    
  Major Modification History:
    Adapted from Derivables class.  JR, 31Jul2001

*/
#include <iostream>

class BoxRates {
public:
  // constructor
  BoxRates::BoxRates(int);

  // from Stroustrup, p 612
  // decl. as friend from "C++ How to Program", Deitel and Deitel, 3rd Ed.
  friend ostream& operator<<(ostream& out_file, const BoxRates& BR);
  void print(void);
  void print(int, const AnalysisData&); // print by species

  // calculate box rates
  int calc( MeasurementArray* MA , const vector<Ion>& grp);

  // access function, returns array b/c SpillRates does a mat. mult.
  vector<TNT::Vector<float> > getBoxrates(void);

  // access function for specific rate
  float BoxRates::getBoxrate(int nedb, int s);  
  float BoxRates::getBoxrate(int s); // summed over edb 

private:
  vector<TNT::Vector<float> > B;    // box rates
  vector<string> names;             // names of ions that go with the rates
};


