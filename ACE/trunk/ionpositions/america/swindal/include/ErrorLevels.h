/*
  File: ErrorLevels.h

  Description:
    Header file for ErrorLevels class, a class containing error level
    cutoffs for derived products, e.g., n and vth.

  Author(s): Jim Raines (jmr)

  Method:
    

  Revision controlled by CVS:
  $Id: ErrorLevels.h,v 1.1 2005/03/24 21:36:34 jraines Exp $

  Major Modification History:
    24Mar2005   jmr   initial coding

*/

class ErrorLevels {
 public:

  float n_yellow;
  float n_red;

  float v_yellow;
  float v_red;

  float vth_yellow;
  float vth_red;
  
  void dump(void);

 private:

};
