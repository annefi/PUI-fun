/* swindal.h -- main header file for swindal
   Jim Raines, 5Apr2001
 */

#include <stl.h>
#include <iostream.h>
#include <string.h>
#include <stdio.h>

/* Ion Class */
class Ion {
 public:
  char name[4];            // name of ion, includes charge (e.g. He2+)
  float mass;              // mass (in amu) of ion
  float charge;            // charge (in units of elem. charge) of ion

  /* forward model variables, one set per E/q step */
  double esd[60];       // Energy measured by solid state detector
  double tof[60];       // time of flight 
  double sesd[60];      // variance of esd
  double stof[60];      // variance of tof

/*   vector<double> esd;       // Energy measured by solid state detector */
/*   vector<double> tof;       // time of flight  */
/*   vector<double> sesd;      // variance of esd */
/*   vector<double> stof;      // variance of tof */

  void print(void);            // print Ion
  Ion(const char i_name[], float i_mass, float i_charge); // Constructor
  bool operator== (const Ion& right) const;  // define equality operator

  // Load SWICS Forward Model ouput
  void Ion::lxfm(double, double, double, double);

 private:
};
  
/* AnalysisData Class */
class AnalysisData {
 public:
  vector<Ion> Ions;        // Ions used for analysis
  vector<float> Eqtab;       // Commanded E/q values
  
  AnalysisData(void);       // Constructor
 private:
  //  void InitIons(void);     // Load values into ion objects
};
