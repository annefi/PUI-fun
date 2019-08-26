/*
  File: AceSwixFlux.h

  Description:
    Header file for ACE/SWICS flux class, a class which reads in output from 
    the ACE/SWICS Level II processor (axlv2) and serves it up.

  Author(s): Jim Raines (jmr)

  Method:

  Revision controlled by CVS:
  $Id: AceSwicsFlux.h,v 1.2 2004/07/28 13:28:34 jraines Exp $

  Major Modification History:
    05May2004   jmr   initial coding

*/

class AceSwicsFlux {
 public:
  AceSwicsFlux(string file); 

  // internal data structure for axlv2 rate files
  class RateRecord {
  public:
    // day of year fraction
    float doyfr;
    // EDB number
    int edb;
    // E/q (keV/e)
    float eoq;
    // ion name (e.g. Mg10+)
    string ion;
    // counts/second during accumulation period
    float rate;
    // counts during accumulation period
    float counts;

    RateRecord();

    friend std::istream &operator>>( std::istream &input, RateRecord& rr);
    friend std::ostream &operator<<( std::ostream &output, 
				     const RateRecord& rr);
  };

  // dump all RateRecords to file
  void dump(string file) const;
  void dumpIons(string file) const;

  unsigned int getNumRateRecords(void) const;
  RateRecord getRateRecord(int i) const;

 private:
  vector<RateRecord> Data;
};
