/*  
  Filename: SpillRates.h

  Description:
    This class contains spillover matrices and routines needed to perform
    spillover correction of box rates.

  Author:  Jim Raines, 31Jul2001

  Method:
    Perform calculations according to eq. 2, 5, 7, and 8 from ref. 1
    in swindal.h.

  Revision controlled by CVS:
  $Id: SpillRates.h,v 1.5 2005/03/10 20:02:49 jraines Exp $

  Major Modification History:

*/

class SpillRates {
 public:
  // constructor
  SpillRates(int);

  // printing functions
  void print(void); // print sum for each species
  void printRaw(void); // print sum of uncorrect. for each spec.
  void dump(int s); // print sum and per edb rate for each species
  void dump(void);  // run dump(int s) over all species

  int calc(vector<Ion>& group, BoxRates BR);

  // get ghost-count corrected spill rate edb=nedb and species=s
  float getCorSpillRate(int nedb, int s);
  float getCorSpillRate(int s);

  /* output spillover rates to open filehandle (SRF) */
  int output(FILE *SRF, float doyfr, const AnalysisData& ad);

  // FIX: Add generic named functions
  // getRate(int nedb, int s), getRateSum(int s)

  /* Set/get negative rate cutoff value
     When a particular spill rate exceeds this fraction of the rate sum, it is
     dropped and the spill rates are calculated again for that EDB.
     Allowed values: 0 < cutoff < 1.0
  */
  void setNegRateCutoff(float);
  float getNegRateCutoff(void);

  /* Set/get maximum number of iterations in ghost-count corrected
     spillover rate calculation.  Be careful setting this very high (>10).
  */
  void setMaxIterations(unsigned int);
  int  getMaxIterations(void);

 private:
  vector<string> names;               // ion names
  vector<TNT::Vector<float> > Nspill; // spillover rates
  vector<TNT::Vector<float> > Nspilltil; // ghost-count-corrected spillover rates
  int calc2(const vector<Ion>& grp, int nedb, 
			TNT::Vector<float>& B, 
			TNT::Vector<float>& NspillC2,
			TNT::Vector<float>& NspilltilC2,
			vector<bool>& badspecies);
  
  float negRateCutoff;

  int maxIterations;
};


