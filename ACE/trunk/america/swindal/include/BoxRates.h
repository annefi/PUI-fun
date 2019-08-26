/*
  File: BoxRates.h

  Description:
    BoxRates class.

  Author: Jim Raines, 31Jul2001.

  Method:
    
  Revision controlled by CVS:
  $Id: BoxRates.h,v 1.4 2005/03/10 20:02:49 jraines Exp $

  Major Modification History:
    Adapted from Derivables class.  JR, 31Jul2001

*/
#include <iostream>

class BoxRates {
public:
  // constructor
  BoxRates(int);

  // from Stroustrup, p 612
  // decl. as friend from "C++ How to Program", Deitel and Deitel, 3rd Ed.
  friend std::ostream& operator<<(std::ostream& out_file, const BoxRates& BR);
  void print(void);
  void print(int, const AnalysisData&); // print by species

  // calculate box rates
  int calc( MeasurementArray* MA , const vector<Ion>& grp);

  // access function, returns array b/c SpillRates does a mat. mult.
  vector<TNT::Vector<float> > getBoxrates(void);

  // access function for specific rate
  float getBoxrate(int nedb, int s);  
  float getBoxrate(int s); // summed over edb 
  
  // write box rates to open file handle (BRF)
  int output(FILE *BRF, float doyfr, const AnalysisData& ad);

private:
  vector<TNT::Vector<float> > B;    // box rates
  vector<string> names;             // names of ions that go with the rates
};


