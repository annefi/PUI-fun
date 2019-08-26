/*
  File: MeasurementArray.h

  Description:
    Header for MeasurementArray Class

  Author: Jim Raines, 

  Method:
    
  Revision controlled by CVS:
  $Id: MeasurementArray.h,v 1.9 2004/01/27 21:19:02 jraines Exp $

  Major Modification History:
    

*/

class MeasurementArray {
 public:
  TNT::Matrix<float> getSlice(int); // get a tof/esd matrix at edb=nedb
  TNT::Matrix<float> putSlice(int);// put a tof/esd matrix at edb=nedb into MA

  float getElement (int nedb, int tofch, int esdch) const;

  // Write E-T slices to file specified with outfile.
  // Note:  Start/StopYdoy are for matrix headers.
  int outputETslices(string outfile, string StartYdoy, string StopYdoy, 
		     const AnalysisData& ad, int cycles,float aspang, double swspeed);

  // --- Convert an esdch-tofch matrix (slice) to mass-mass/charge
  // with default mmq limits
  TNT::Matrix<float> EtSlice2Mmq
    (TNT::Matrix<float> slice,int nedb,  const AnalysisData& ad);
  // with mmq limits specified
  // mass range of (mm0,mm1) and m/q range of (mq0,mq1)
  TNT::Matrix<float> EtSlice2Mmq
    (TNT::Matrix<float> slice,int nedb,  const AnalysisData& ad,
     double mm0, double mm1, double mq0, double mq1);

  // --- output mass-mass/charge array to file (uses EtSlice2Mmq)
  // with default mmq limits
  int outputMMQ
    (string outfile,long int StartYdoy, long int StopYdoy, 
     const AnalysisData& ad);
  // with mmq limits specified
  // mass range of (mm0,mm1) and m/q range of (mq0,mq1)
  int outputMMQ
    (string outfile,long int StartYdoy, long int StopYdoy, 
     const AnalysisData& ad, double mm0, double mm1,double mq0, double mq1);

  // Output forward model centers in M-M/Q
  int outputMMQfmc(string outfile,const AnalysisData& ad);

  /* Fills measurement matrix from vector of Pha objects.  */
  int fill(const AceSwicsData& swxdata,bool& Rates);

  /* set/getFilter - set/get bit field decsribing from which Range(s)
     to keep PHAs.  If the bit corresponding to a particular range is
     on (1), then PHAs from that range will be loaded into MA.
     
     filter
     value     bits*       use range(s)
     ------    -----       ------------
     0         0000        none (not used)
     1         0001        0
     2         0010        1
     3         0011        1 and 0
     4         0100        2
     5         0101        2 and 0
     6         0110        2 and 1
     7         0111        2, 1, and 0
     8         1000        3
     9         1001        3 and 0
     10        1010        3 and 1
     11        1011        3, 1 and 0
     12        1100        3 and 2
     13        1101        3, 2 and 0
     14        1110        3, 2 and 1
     15        1111        3, 2, 1 and 0
     
     *other leading 0's omitted
  */
  int setFilter(int filter); // returns 0 if successful
  int getFilter(void);           // returns current value of filter
  bool passRange(int range);// returns true if range passes through filter

  // set/getDoBRW -- toggle use of basic rate weighting
  // true -> do basic rate weighting
  int setDoBRW(bool);       // set flag, 1=>T, 0=>F; returns 0 if successful
  bool getDoBRW(void);      // returns current value of doBRW flag

  /* set/get velocity filter fraction
     When set to positive, non-zero value, only PHA words with speed 
     (from d/TOF) with this fraction of the solar wind speed, calculated from
     matrix rates of the cycle from which the PHA originated.
  */
  void setVelFilterFrac(double);
  double getVelFilterFrac();

  int save(string file);
  int savespeed(string file,int cycles);
  int load(string file);
  int loadspeed(string file,int &cycles);

  bool add(MeasurementArray b); 

  // Constructor
  MeasurementArray(void);

 private:

  vector<TNT::Matrix<float> > MA;  // the measurement array itself (cnts/s)

  // PHA filter value used by set/getFilter
  int filter; 

  // returns true if ion_speed is within velFilterFrac of sw_speed
  bool passVelFilter(double ion_speed, double sw_speed);
  double velFilterFrac;

  bool doBRW;               // T => do basic rate weighting
};

