/* swindal.h -- main header file for swindal
   Jim Raines, 5Apr2001
 */

#include <stl.h>
#include <iostream>
#include <string>
#include <cstdlib>
#include <stdio.h>

/* Range-checked vector template 
   From: The C++ Programming Language, Special E., Bjarne Stroustrup,
   Addison-Wesley, New York 2000 p53

   NOTE: Not used.  Currently DNW!  The at() member function does not
   seem to exist in my STL implementation (or the one on the CAEN
   machines, or the SGI website).  */

template<class T> class Vec : public vector<T> {
 public:
  Vec() : vector<T>() { }
  Vec(int s) : vector<T>(s) { }

  T& operator[] (int i) { return at(i); }             // range-checked
  const T& operator[] (int i) const { return at(i); } // range-checked
};

/* ---------
   Ion Class
   ---------
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

  void print(void);            // print Ion
  Ion(const string i_name, float i_mass, float i_charge); // Constructor
  bool operator== (const Ion& right) const;  // define equality operator

  // Load SWICS Forward Model ouput
  //void Ion::lxfm(double, double, double, double);

 private:
};
  
/* ------------------
   AnalysisData Class
   ------------------
*/
class AnalysisData {
 public:
  map<string,Ion> Ions;        // Ions used for analysis
  vector<double> Eqtab;        // Commanded E/q values
  
  AnalysisData(void);          // Constructor
 private:

};
