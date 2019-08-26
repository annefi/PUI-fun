/*
  File: Pha.h

  Description:
    Class containing data for individual PHA words.
  
  Author: Jim Raines, May2001

  Method:
    This is functioning as a data structure, hence the public members.

  Revision controlled by CVS:
  $Id: Pha.h,v 1.6 2005/06/09 04:06:12 jraines Exp $

  Major Modification History:
    

*/

class Pha {

 public:
  Pha();

  /* dump PHA word data in one line to previously open file
     The npha and ncycle arguments are to be used by the invoking code
     as counters.
  */
  void dump(int npha, int ncycle, FILE* F) const;
  
  /* data elements
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
  long br[3];       // basic rates
  double tcr;      // triple coincidence rate
  double mmch;     // mass in channel units
  double mm;       // mass in amu
  double mqch;     // m/q in channel units
  double mq;       // m/q in amu/C

  double speed;     // speed of this PHA (from d/TOF)
  double swspeed;   // solar wind speed
  double weight;   // pha weights

  // copy constructor
  Pha(const Pha& pha);

  // assignment copy constructor
  Pha& operator= (const Pha& rhs);

private:

};

