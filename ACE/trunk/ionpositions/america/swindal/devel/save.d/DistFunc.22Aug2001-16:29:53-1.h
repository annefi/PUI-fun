/*
  File: DistFunc.h

  Description:

    Calculate observed distribution function and moments from
    probabilistic rates.

  Author: Jim Raines, 21Aug2001

  Method:

    
    
  Major Modification History:
    

*/

class DistFunc {
public:
  // constructor, init's arrays (for get functions) to size N
  DistFunc::DistFunc(int N);

  float getDensity(int);
  float getBulkVelocity(int);
  float getThermVelocity(int);

  int calc(const vector<Ion>& group, AnalysisData ad, ProbRates PR);

private:
  vector<float> n;     // density
  vector<float> v0;    // bulk velocity
  vector<float> vth;   // thermal velocity

};
