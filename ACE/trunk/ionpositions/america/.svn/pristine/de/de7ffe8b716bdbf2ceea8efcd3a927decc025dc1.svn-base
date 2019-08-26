/*
  File: ProbRates.h

  Description: 
    This class contains the code and containers required to calculate
    probabilistically assigned rates.

  Author: Jim Raines, 13Aug2001

  Method:
    Perform calculations according to eq. 2, 9 and 10 from ref(1) in swindal.h.
    
  Revision controlled by CVS:
  $Id: ProbRates.h,v 1.10 2005/01/19 03:20:30 jraines Exp $

  Major Modification History:
    

*/

class ProbRates {
 public:
  // primary constructor
  // N is number of rates (species)
  ProbRates(InstrumentConstants IC, int N);

  void print(void);
  void dump(int s); //prints sum and per edb ProbRates for species s
  void dump(void);  // as above for all species


  bool operator<< (ProbRates);

  // calculate probabilistic rates
  int calc(const vector<Ion>& group, const MeasurementArray& MA,
	   SpillRates SR);

  // ----- for species s, averaged over charge steps
  vector<float> calcAveProbCenter(const vector<Ion>& grp, int s);
  // ----- for entire group grp, averaged over charge steps
  vector<vector<float> > calcAveProbCenter(const vector<Ion>& grp);

  // returns matrix of prob centers, first index is species, second is 
  // (tof, esd) as (0,1), resp.
  TNT::Matrix<float> getProbCenter(int nedb);

  // outputs prob. centers for overlay onto E-T slices with ext. IDL code
  void outputProbCenters(string outfile,const AnalysisData& ad);


  // get probabilistic a rate
  float getProbRate(int nedb, int s); //  for nedb species s
  float getProbRate(int s); //  summed over edbs species s

  // ----- get/set parameters for probabilistic rate calculation -----

  // set multiple of sigma outside of which to zero G
  float setGaussCutOff(float);
  float getGaussCutOff(void);

  // set cutoff below which probability matrix is set to 0.0
  float setProbCutOff(float);
  float getProbCutOff(void);

  // Choose probabilistic rates calculation method
  // 1 -- Counts Distributed (CD)
  // 2 -- Counts to Max (CM)
  // 3 -- Dice Roll (DR)
  void  setMethod(int);
  int   getMethod(void);

  // ----- save and load -----
  int save(string file);
  int load(string file);

  // write out rates
  int output(FILE *PRF, float doyfr, const AnalysisData& ad);

  // turn on/off output of P matrix slices
  void setOutputPslices(bool);

  // register a ion/edb pair for E-T assigned counts accumulation
  // increases program dynamic RAM by about 1.2Mb/pair during ProbRates calc.
  int registerACSlice(string ion, int nedb, 
				 AnalysisData ad);

  // output all AC slices (if present)
  void outputACSlices(string file);

  // --- Assigned Counts by element ---
  // --- register element for output, including EDB range (lo to hi)
  int registerACElem(string elem, int nedb_lo, int nedb_hi,
				AnalysisData ad);
  // --- output sum of all these into one file, in MMQ units
  int outputACElemMMQ(string file, const AnalysisData& ad,
				 MeasurementArray& MA,double mm0, double mm1,
				 double mq0, double mq1);

  // turn on calculation of assigned counts, summed over ion
  // increases program dynamic RAM by about 70Mb during ProbRates calc.
  int registerACSum(void);

  // output ACSum (if present) in mass-m/q units, summed over E/q
  int outputACSumMMQ
    (string file, const AnalysisData& ad, MeasurementArray& MA,
     double mm0, double mm1,double mq0, double mq1);

 private:
  // store this to use throughout class functions
  InstrumentConstants IC;

  // ion names, stored during calc() as a failsafe against species misalignment
  vector<string> names;              

  // prob rates, calculated as per Method variable
  vector<TNT::Vector<float> > Nprob;

  // probabilistic (tof,esd) centers to compare with forward model
  // note: TNT::Matrix used for easy file I/O
  vector<TNT::Matrix<float> > ProbCenters;

  // gaussian, G(tof,esd) from eq. 2
  vector<TNT::Matrix<float> > G;

  // probability of pha (tof,esd, e/q) being species s at edb i from eq. 9
  vector<TNT::Matrix<float> > P; 

  // NOT CURRENTLY USED; moved to Ion structure to allow specification per ion
  float GCutOff;  // mult. of sigma outside of which to zero G

  float PCutOff;  // P[nedb][ntof][nesd] set to 0.0 if it is below this value.

  int DbgLvl;     // Debugging level for class methods

  // Choice of prob. method
  // 1 -- Counts Distributed (CD)
  // 2 -- Counts to Max (CM)
  // 3 -- Dice Roll (DR)
  int Method;     

  int outputSlice(std::ofstream& fout, TNT::Matrix<float> Pslice, 
			      int nedb, string title);  


  bool outputPslices;

  // --- Assigned Counts arrays ---

  // holds slices for individual ion/edb pairs
  vector<AssignedCounts> AC;

  // slices summed over specified element
  vector<AssignedCountsElem> ACElem;

  // holds global average (for timestep) over all ions
  vector<AssignedCounts> ACSum;
};
