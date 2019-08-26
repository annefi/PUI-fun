/*
  File: AceSwimsPha.h

  Description:
    Header file for AceSwimsPha class, a class derived from Pha which
    adds SWIMS-specific members.

  Author(s): Jim Raines (jmr)

  Method:

  Revision controlled by CVS:
  $Id: AceSwimsPha.h,v 1.2 2004/06/21 16:06:27 jraines Exp $

  Major Modification History:
    22Mar2004   jmr   initial coding

*/

class AceSwimsPha : public Pha {
 public:

  // start (or is it stop?)  amplitude
  short int stamp;

  // stop k1
  short int stopk1;

  // stop k2
  short int stopk2;

  AceSwimsPha();

  // specialized version of output function
  void dumpHeaders(FILE* F) const;
  void dump(int npha, int ncycle, FILE* F) const;
 private:

};
