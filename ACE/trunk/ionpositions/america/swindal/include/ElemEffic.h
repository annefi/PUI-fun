/*
  File: ElemEffic.h

  Description:
    Class provides a container for holding efficiency-related items,
    written to be used with UlyssesSwicsEffic and interpolation to
    required energy.

  Author(s): Jim Raines (jmr)

  Method:
    The design of this class was made to be compatible with
    interpolation by Numerical Recipes in C.  As such, the data
    structures are very C-like.  This was determined to be the most
    efficient method.

  Revision controlled by CVS:
  $Id: ElemEffic.h,v 1.1 2003/11/06 21:48:18 jraines Exp $

  Major Modification History:
    29Oct2003   jmr   initial coding

*/

class ElemEffic {
 public:

  ElemEffic();

  // full ion name
  string ion_name;
  
  // ion name parsed into just element
  string element_name;

  // efficiency data filename
  string file;

  // T => eff. table loaded from disk
  bool loaded;

  // total energy in keV
  float *etot;

  // probability 1, FSR/I
  float *prob1;
  
  // probability 2, DCR/FSR
  float *prob2;

  // probability 3, TCR/DCR
  float *prob3;

  //! vector sizes for the vectors above
  size_t nrows;
  
  ~ElemEffic();
};

