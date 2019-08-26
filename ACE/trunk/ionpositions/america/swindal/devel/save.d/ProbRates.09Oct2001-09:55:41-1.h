/*
  File: ProbRates.h

  Description: 
    This class contains the code and containers required to calculate
    probabilistically assigned rates.

  Author: Jim Raines, 13Aug2001

  Method:
    Perform calculations according to eq. 2, 9 and 10 from ref(1) in swindal.h.
    
  Major Modification History:
    

*/

class ProbRates {
 public:
  ProbRates::ProbRates(int);

  void ProbRates::print(void);

  bool ProbRates::operator<< (ProbRates);

  int calc(const vector<Ion>& group, SpillRates SR);

  // get probabilistic a rate
  float getProbRate(int nedb, int s); //  for nedb species s
  float getProbRate(int s); //  summed over edbs species s

  // get/set parameters for probabilistic rate calculation
  float setGaussCutOff(float);
  float getGaussCutOff(void);
  float setProbCutOff(float);
  float getProbCutOff(void);

 private:
  vector<string> names;              // ion names
  vector<TNT::Vector<float> > Nprob; // probabilistic rates, from eq. 10

  float GCutOff;  // mult. of sigma outside of which to zero G
  float PCutOff;  // Prob. threshold above which to count in Nprob

  int DbgLvl;     // Debugging level for class methods
};
