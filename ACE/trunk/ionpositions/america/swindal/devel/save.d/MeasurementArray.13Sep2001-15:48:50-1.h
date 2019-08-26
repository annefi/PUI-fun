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

  // Convert an esdch-tofch matrix (slice) to mass-mass/charge
  TNT::Matrix<float> 
    MeasurementArray::EtSlice2Mmq(TNT::Matrix<float> slice,int nedb, 
				  int method, const AnalysisData& ad);

  /* Fills measurement matrix from vector of Pha objects.  */
  int fill(vector<Pha> *);

  int save(string file);
  int load(string file);

  // Constructor
  MeasurementArray(void);

  // dumping (for debugging)
  int dumpMM(string file, long StartYdoy, long StopYdoy);
  int dumpMQ(string file, long StartYdoy, long StopYdoy);

 private:
  vector<TNT::Matrix<float> > MA;  // the measurement array itself (cnts/s)
  vector<TNT::Matrix<float> > MAcounts;  // the measurement array itself (cnts)
  vector<TNT::Matrix<float> > MM;  // the masses for measurement array elements
  vector<TNT::Matrix<float> > MQ;  // the m/q for measurement array elements


};

