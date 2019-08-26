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

  float getDensity(int s);  // for species s
  float getBulkVelocity(int s);
  float getThermVelocity(int s);

  int calc(const vector<Ion>& group, const AnalysisData& ad, ProbRates PR);

private:
  vector<float> n;     // density
  vector<float> v0;    // bulk velocity
  vector<float> vth;   // thermal velocity

};
