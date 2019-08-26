/*  
  Filename: SpillRates.h

  Description:
    This class contains spillover matrices and routines needed to perform
    spillover correction of box rates.

  Author:  Jim Raines, 31Jul2001

  Method:
    Perform calculations according to eq. 2, 5, 7, and 8 from ref. 1
    in swindal.h.

  Major Modification History:

*/

class SpillRates {
 public:
  // constructor
  SpillRates::SpillRates(int);

  // printing functions
  void SpillRates::print(void); // print sum for each species
  void SpillRates::printRaw(void); // print sum of uncorrect. for each spec.
  void SpillRates::dump(int s); // print sum and per edb rate for each species
  void SpillRates::dump(void);  // run dump(int s) over all species

  int calc(vector<Ion>& group, BoxRates BR);

  // get ghost-count corrected spill rate edb=nedb and species=s
  float getCorSpillRate(int nedb, int s);
  float getCorSpillRate(int s);

 private:
  vector<string> names;               // ion names
  vector<TNT::Matrix<float> > S;      // spillover matrices
  vector<TNT::Matrix<float> > Sinv;   // inverse of spillover matrices
  vector<TNT::Vector<float> > Nspill; // spillover rates
  vector<TNT::Vector<float> > Btil;   // ghost-count-corrected box rates
  vector<TNT::Vector<float> > Nspilltil; // ghost-count-corrected spillover rates
  int calc2(const vector<Ion>& group, BoxRates BR, vector<int>& badspecies);
  
};


