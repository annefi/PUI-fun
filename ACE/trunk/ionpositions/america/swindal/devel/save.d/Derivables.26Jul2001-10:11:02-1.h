/*
  File: Derivables.h

  Description:
    Derivables class.

  Author: Jim Raines, May2001 

  Method:
    
  Major Modification History:
    

*/
class Derivables {
public:
  //map<string,int[60] > boxrates;
  //map<string,vector<int> >::iterator boxrates_it;

  // constructor -- just initializes
  Derivables::Derivables(void);

  // access functions
  long int getBoxrate(string ionName, int nedb);
  int setBoxrate(string ionName, int nedb, int val);
  int incrBoxrate(string ionName, int nedb);

private:
  map<string, vector<long int> > boxrates;

  int initBoxrate(string key);
};


