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
  void SpillRates::print(void);
  void SpillRates::printRaw(void);

  int calc(const vector<Ion>& group, BoxRates BR);

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
  
};


