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
  void ProbRates::dump(int s); //prints sum and per edb ProbRates for species s
  void ProbRates::dump(void);  // as above for all species


  bool ProbRates::operator<< (ProbRates);

  // calculate probabilistic rates
  int calc(const vector<Ion>& group, const MeasurementArray& MA,
	   SpillRates SR);

  // calculate (tau,esd) center(s) for ions in grp
  // ----- for species s, charge step nedb
  vector<float> calcProbCenter(const vector<Ion>& grp, int s, int nedb);
  // ----- for species s, all charge steps
  vector<vector<float> > calcProbCenter(const vector<Ion>& grp, int s);
  // ----- for species s, averaged over charge steps
  vector<float> calcAveProbCenter(const vector<Ion>& grp, int s);
  // ----- for entire group grp, averaged over charge steps
  vector<vector<float> > calcAveProbCenter(const vector<Ion>& grp);

  // get probabilistic a rate
  float getProbRate(int nedb, int s); //  for nedb species s
  float getProbRate(int s); //  summed over edbs species s
  float ProbRates::getProbRateCM(int s); //  summed over edbs species s

  // get/set parameters for probabilistic rate calculation
  float setGaussCutOff(float);
  float getGaussCutOff(void);
  float setProbCutOff(float);
  float getProbCutOff(void);

  // save and load
  int ProbRates::save(string file);
  int ProbRates::load(string file);

 private:
  vector<string> names;              // ion names
  vector<TNT::Vector<float> > Nprob; // prob rates, MA counts dist. by P (CD)
  vector<TNT::Vector<float> > NprobCM; // prob rates, Counts to Max (P)

  // gaussian, G(tof,esd) from eq. 2
  vector<TNT::Matrix<float> > G;
  // probability of pha (tof,esd, e/q) being species s at edb i from eq. 9
  vector<TNT::Matrix<float> > P; 

  float GCutOff;  // mult. of sigma outside of which to zero G
  float PCutOff;  // P[nedb][ntof][nesd] set to 0.0 if it is below this value.

  int DbgLvl;     // Debugging level for class methods

};
