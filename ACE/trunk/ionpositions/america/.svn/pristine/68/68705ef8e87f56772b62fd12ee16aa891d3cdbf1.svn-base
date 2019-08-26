/*
  File: Pha.h

  Description:
    Pha Class

  Author: Jim Raines, May2001

  Method:
    Right now, all of the data items are public.  In the future, they
    will be private with only loadPha and MeasurementArray.fill accessing them
    directly as friends.  .  

  Major Modification History:
    

*/

class Pha {

public:
  // Data access functions -- not currently used 
  double getScet();
  int    getNedb();
  double getEq();
  double getTof();
  int    getTofch();
  double getEsd();
  int    getEsdch();
  int    getSector();
  int    getDetector();
  int    getRange();
  int    getBr(int i);
  double getTcr();
  double getMmch();
  double getMm();
  double getMqch();
  double getMq();
  
  int    getAsp();
  float  setAsp();

  int setHspeed(float hspeed);
  float getHspeed();

  int setWeight(double weight);
  double getWeight();

  int setIonName(string ionName);
  string getIonName();

  /* data elements -- public for now
     note: some of these are read directly others are
     converted from digital values. 
  */
  double scet;     // spacecraft event time, in seconds since 1Jan1970
  int  nedb;       // number of edb
  double eq;       // energy per charge value in keV/e
  double tof;      // time of flight in nanoseconds
  int tofch;       // time of flight in channel numbers
  double esd;      // energy in keV      
  int esdch;       // energy in channel numbers
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

