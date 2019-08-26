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
  TNT::Matrix<float> EtSlice2Mmq(TNT::Matrix<float>, int nedb); 

  /* Fills measurement matrix from vector of Pha objects.  */
  int fill(vector<Pha> *);

  // Constructor
  MeasurementArray(void);

 private:
  vector<TNT::Matrix<float> > MA;  // the measurement array itself
  vector<TNT::Matrix<float> > MM;  // the masses for measurement array elements
  vector<TNT::Matrix<float> > MQ;  // the m/q for measurement array elements


};

