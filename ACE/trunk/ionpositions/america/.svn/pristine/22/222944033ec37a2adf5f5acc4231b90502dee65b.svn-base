/*
  File: Ion.h

  Description:
    Ion Class

  Author: Jim Raines, 

  Method:
    
  Major Modification History:
    

*/

class Ion {
 public:
  string name;             // name of ion, includes charge (e.g. He2+)
  float mass;              // mass (in amu) of ion
  float charge;            // charge (in units of elem. charge) of ion

  /* forward model variables, one set per E/q step */
  vector<double> esd;       // Energy measured by solid state detector
  vector<double> tof;       // time of flight 
  vector<double> sesd;      // variance of esd
  vector<double> stof;      // variance of tof

  void print(void);         // print Ion

  // zero constructor -- sets name to "" and zeros mass and charge
  Ion(void);                 

  // initializing constructor -- sets values based on args
  Ion(const string i_name, float i_mass, float i_charge); 

  // define equality operator
  bool operator== (const Ion& right) const;  

  // Load SWICS Forward Model ouput
  //void Ion::lxfm(double, double, double, double);

 private:
};
  
