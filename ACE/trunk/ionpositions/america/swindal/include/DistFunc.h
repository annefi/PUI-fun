/*
  File: DistFunc.h

  Description:

    Calculate observed distribution function and moments from
    probabilistic rates.

  Author: Jim Raines, 21Aug2001

  Method:

  Revision controlled by CVS:
  $Id: DistFunc.h,v 1.18 2005/04/05 18:48:08 jraines Exp $

    
    
  Major Modification History:
    

*/

class DistFunc {
public:
  // constructor, init's arrays (for get functions) to size N
  DistFunc(int N);

  float getDensity(int s);  // for species s
  float getBulkVelocity(int s);
  float getThermVelocity(int s);

  int calc(const vector<Ion>& group, const AnalysisData& ad, ProbRates PR,
	   AceSwicsDutyCycle duty, UlyssesSwicsEffic eff_obj);

  /* filters all class-wide n, v0 and vth values by quality, setting
     quality flag and replacing values with fill value where
     appropriate */
  void filterNvtByQuality(AnalysisData ad);

  /* keep only deliverables
     filters out ions with extended charge states (beyond that which
     is delivered to ASC ) to make auto-production safer.  Works by
     zeroing n, v, vth (and corresponding fit_ variables) for
     specified element outside of specified charge range, ends inclusive */
  void keepOnlyDeliv(const AnalysisData& ad, string element, 
		     float lo_chg, float hi_chg);

  // Write out distribution function for all ions in ad.Ions
  // to OUT file, with doyfr as the time.
  int outputDF(FILE *OUT, float doyfr, AnalysisData ad);

  // Write density, velocity and thermal velocity for all ions in ad.Ions
  // to OUT file, with doyfr as the time.
  int outputNVT(FILE *OUT, float doyfr, AnalysisData ad);

  /* Write *delivered* (to ACE Science Center (ASC)) version of NVT file to
     OUT file, with doyfr as the time.  Content is a mix of individual
     ions values and ratios. */
  int outputDelivNVT(FILE *OUT, float doyfr, AnalysisData ad);

  /* Write delivered (to ASC) elemental abundances */
  int outputDelivElemAbun(FILE *OUT, float doyfr, AnalysisData ad);

  /* Write delivered (to ASC) elemental abundances (LOW ABUNDANCE IONS ONLY) */
  int outputDelivElemAbunLA(FILE *OUT, float doyfr, AnalysisData ad);

  /* Write delivered (to ASC) charge ratios */
  int outputDelivQRatio(FILE *OUT, float doyfr, AnalysisData ad);

  /* Write delivered (to ASC) charge distribution for specified element */
  int outputDelivQDist(FILE *OUT, float doyfr, AnalysisData ad, string element);

private:
  vector<float> n;     // density
  vector<float> n_err; // error in density
  vector<float> v0;    // bulk velocity
  vector<float> vth;   // thermal velocity

  /* E/q velocity -- ion-specific conversion of E/q values to velocity
     This is *not* the bulk velocity; it is the ordinate for 
     calculation of A moments and plotting. */
  vector< vector<float> > v; 

  // A, phase space density in s^3/km^6
  vector< vector<float> > A;

  // Error in A
  vector< vector<float> > ErrA;  

  // gauss fit A to find n, v, vth
  int GaussFitA(int s);

  // physical parameters from fit rather than moment
  vector<float> fit_n;     // density
  vector<float> fit_v0;    // bulk velocity
  vector<float> fit_vth;   // thermal velocity
  vector<float> fit_err;   // fit-derived errors applicable to fit_nvt
  vector< vector<float> > fit_A;
  vector< vector<float> > Err_fit_A;

  // quality -- more to come
  vector<int> quality;
  int determineQuality();

  // The moment part of the distribution function calculations
  int calc3dMoments(const int& s, 
			    const vector< vector<float> >& Alocal, 
			    const vector<float>& delta_v, 
			    AceSwicsDutyCycle duty, const AnalysisData& ad,
			    float& n_local, float& v0_local, float& vth_local);

  int calc1dMoments(const int& s, 
			    const vector< vector<float> >& Alocal, 
			    const vector<float>& delta_v, 
			    AceSwicsDutyCycle duty, const AnalysisData& ad,
			    float& n_local, float& v0_local, float& vth_local);

  // calculate a density ratio, returning the fill value where appropriate
  float calc_n_ratio(float n, float n_he);

  /* calculate sum over density for given element (skipping fill
     values appropriately) */
  float calc_elem_n_sum(string element, AnalysisData ad,
				  int& quality);

  /* calculate sum over density for given element isotope (skipping fill
     values appropriately) */
  float calc_isotope_n_sum(string element, float mass, 
				     AnalysisData ad,int& quality);

  /* calculate density-weighted sum of charges for given element
     (skipping fill values appropriately) */
  float calc_ave_q(string element, AnalysisData ad, int& quality);

  // internal data structure for keeping track of deliverable element
  // charge ranges; all public because it is intimately tied to DistFunc
  class deliv_element {
  public:
    deliv_element(string name, float lo_chg, float hi_chg);
    string name;
    float lo_chg;
    float hi_chg;
  };

  vector<deliv_element> DeliverableRanges;
 };
