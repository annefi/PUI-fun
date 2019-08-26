/*
  File: MeasurementArray.h

  Description:
    Header for MeasurementArray Class

  Author: Jim Raines, 

  Method:
    
  Major Modification History:
    

*/

class MeasurementArray {
 public:
  TNT::Matrix<float> getSlice(int); // get a tof/esd matrix at edb=nedb
  TNT::Matrix<float> putSlice(int);// put a tof/esd matrix at edb=nedb into MA

  float MeasurementArray::getElement (int nedb, int tofch, int esdch) const;

  // Convert an esdch-tofch matrix (slice) to mass-mass/charge
  TNT::Matrix<float> 
    MeasurementArray::EtSlice2Mmq(TNT::Matrix<float> slice,int nedb, 
				  const AnalysisData& ad);

  /* Fills measurement matrix from vector of Pha objects.  */
  int fill(vector<Pha> *);

  /* filter - bit field decsribing from which Range(s) to keep PHAs
     If the bit corresponding to a particular range is on (1), then
     PHAs from that range will be loaded into MA.
     
     filter    use range(s)
     ------    ---------------
     0         none (not used)
     1         0
     2         1
     3         0 and 1
     4         2
     5         0 and 2
     6         1 and 2
     7         0, 1, and 2

  */
  int filter; 
  int setFilter(int filter); // returns what filter was before set
  int getFilter();           // returns current value of filter
  bool passRange(int range);// returns true if range passes through filter

  int save(string file);
  int load(string file);

  // Constructor
  MeasurementArray(void);

 private:
  vector<TNT::Matrix<float> > MA;  // the measurement array itself (cnts/s)
};

