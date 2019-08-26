/*
  File: Ion.h

  Description:
    Ion Class

  Author: Jim Raines, 

  Method:
    
  Revision controlled by CVS:
  $Id: Ion.h,v 1.6 2005/03/24 21:34:14 jraines Exp $

  Major Modification History:
    

*/

class Ion {

 public:

  string name;             // name of ion, includes charge (e.g. He2+)
  string element;          // short name of element
  float mass;              // mass (in amu) of ion
  float charge;            // charge (in units of elem. charge) of ion

  /* forward model variables, one set per E/q step */
  vector<double> esd;       // Energy measured by solid state detector
  vector<double> tof;       // time of flight 
  vector<double> sesd;      // variance of esd
  vector<double> stof;      // variance of tof

  /* method control values */
  float PrGaussCutoff;      /* Multiples of FM sigma (both TOF and ESD).
			       Prob. rates are zeroed beyond
			       PrGaussCutoff * FM sigma (TOF and ESD) */

  /* Contains error cutoffs for this ion */
  ErrorLevels errlvl;

  void print(void);         // print Ion
  void dump(void);          // dump *all* data from selected ion

  // zero constructor -- sets name to "" and zeros mass and charge
  Ion(void);                 

  // initializing constructor -- sets values based on args
  Ion(const string i_name, const string i_element, 
      float i_mass, float i_charge); 

  // define equality operator
  bool operator== (const Ion& right) const;  

  // copy constructor
  Ion(const Ion& ion);

  // copy assignment operator
  Ion& operator= (const Ion& ion);

 private:

};
  
