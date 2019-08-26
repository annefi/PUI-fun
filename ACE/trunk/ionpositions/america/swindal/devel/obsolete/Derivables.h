/*
  File: BoxRates.h

  Description:
    BoxRates class.

  Author: Jim Raines, 31Jul2001.

  Method:
    
  Major Modification History:
    Adapted from Derivables class.  JR, 31Jul2001

*/
class BoxRates {
public:
  // constructor -- just initializes
  BoxRates::BoxRates(void);

  // access functions
  long int getBoxrate(string ionName, int nedb);
  int setBoxrate(string ionName, int nedb, int val);
  int incrBoxrate(string ionName, int nedb);

private:
  map<string, vector<long int> > boxrates;

  int initBoxrate(string key);
};


