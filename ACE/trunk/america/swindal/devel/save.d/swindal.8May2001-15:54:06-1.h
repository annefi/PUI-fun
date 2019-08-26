/* swindal.h -- main header file for swindal
   Jim Raines, 5Apr2001
 */

#include <stl.h>
#include <iostream>
#include <string>
#include <cstdlib>
#include <cmath>
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
  
/* ------------------
   AnalysisData Class
   ------------------
*/
class AnalysisData {
 public:
  map<string,Ion> Ions;        // Ions used for analysis
  map<string,Ion>::iterator Ions_iter;  // iterator for above

  vector<double> Eqtab;        // Commanded E/q values
  
  AnalysisData(void);          // Constructor
 private:

};

/* ---------
   Pha Class
   ---------
*/

class Pha {

public:
  /* data elements -- note: some of these are read directly others are
     converted from digital values. 
  */
  double scet;     // spacecraft event time, in seconds since 1Jan1970
  int  nedb;       // number of edb
  double epq;      // Energy Per charge value in keV/e
  double tof;      // time of flight in nanoseconds
  double esd;      // energy in keV      
  int sector;      // sector of PHA (1/8 of circle)
  int detector;    // detector of PHA
  int range;       // range of PHA (goes with BR, 0-2)
  int br[3];       // basic rates
  double tcr;      // triple coincidence rate
  double mmch;     // mass in channel units
  double mm;       // mass in amu
  double mqch;     // m/q in channel units
  double mq;       // m/q in amu/C
  float asp;       // aspect angle - FIX: read in, do not hardcode

  /* quantities calculated by this packages */
  float hspeed;    // H+ speed
  double weight;   // pha weights
  string ionName;  // ion name assigned to this PHA word

private:
};

/* ---------------- 
   Derivables class
   ----------------
*/
class Derivables {
public:
  map<string,int> boxrates;
  map<string,int> boxrates_it;

  // constructor -- just initializes
  Derivables::Derivables(void);
};


/* ----------------------------------------------------------------------------
			   Global Functions
   ----------------------------------------------------------------------------
*/

int loadPha(vector<Pha> *pha, int);
int boxClassify(vector<Pha> *pha, vector<Ion> *grp, Derivables *deriv);

extern "C" double swspeed (double [], int [], float, float);

/* ----------------------------------------------------------------------------
			   Global Variables
   ----------------------------------------------------------------------------
*/

namespace Global {
  /* Global debugging level: 
     0 -> almost zero message
     1 -> few messages but enough to see data flow
     2 ->
     3 ->
     4 -> dump even minute details
  */

  extern int gDbgLvl;

  /* Starting year and day of year in yyyydoy format */
  extern long StartYdoy;

  /* Stop year and day of year in yyyydoy format */
  extern long StopYdoy;

  /* Current LV1 filename, including path */
  //extern string CurLv1File;
  // Why is extern not needed?
  extern string CurLv1File;

};
