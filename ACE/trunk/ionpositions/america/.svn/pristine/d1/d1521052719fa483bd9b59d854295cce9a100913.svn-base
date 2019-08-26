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
  int setHspeed(float hspeed);
  int getHspeed(float hspeed);

  int setWeight(float weight);
  int getWeight(float weight);

  int setIonName(string ionName);
  int getIonName(string ionName);

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
  //map<string,int[60] > boxrates;
  //map<string,vector<int> >::iterator boxrates_it;

  // constructor -- just initializes
  Derivables::Derivables(void);

  // access functions
  long int getBoxrate(string ionName, int nedb);
  int setBoxrate(string ionName, int nedb, int val);
  int incrBoxrate(string ionName, int nedb);

private:
  map<string, vector<long int> > boxrates;

  int initBoxrate(string key);
};


/* ----------------------------------------------------------------------------
			   Global Functions
   ----------------------------------------------------------------------------
*/

int initSwindal(void);
int loadPha(vector<Pha> *pha, int);
int boxClassify(vector<Pha> *pha, vector<Ion> *grp, Derivables *deriv);

// calculates solar wind speed from count-weighed average E/q
extern "C" double swspeed (double [], int [], float, float);

/* ----------------------------------------------------------------------------
			   Global Variables
   ----------------------------------------------------------------------------
*/


/* Global debugging level: 
     0 -> almost zero message
     1 -> few messages but enough to see data flow
     2 ->
     3 ->
     4 -> dump even minute details
  */
extern int gDbgLvl;

/* Starting year and day of year in yyyydoy format */
extern long gStartYdoy;

/* Stop year and day of year in yyyydoy format */
extern long gStopYdoy;

/* Current LV1 filename, including path */
extern string gCurLv1File;

/* maximum number of EDBs for array dim. and looping */
const int MAXEDB = 60;   

/* first EDB to read
   According to Simon Hefti: 
   EDB 0 is from last cycle 
   EDB 1 is voltage ramp up 
   EDB 2 should be first good one (still need to
         shift them back on (i.e., use nedb - 1 for
	 e/q function.
*/
const int FIRSTEDB = 2;  


