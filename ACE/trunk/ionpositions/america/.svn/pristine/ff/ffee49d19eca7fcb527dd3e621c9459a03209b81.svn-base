/*
  File: UlyssesSwicsEffic.cc

  Description:
    Class provides services for reading in ULYSSES/SWICS efficiencies
    and interpolation to required energy.

  Author(s): Jim Raines (jmr)

  Method:

  Revision controlled by CVS:
  $Id: UlyssesSwicsEffic.h,v 1.2 2004/01/02 19:42:22 jraines Exp $

  Major Modification History:
    28Oct2003   jmr   initial coding

*/

// in order of increasing atomic number
// Note: If elements are added here, they must also be added in getEffic().
enum Element {H, He, C, N, O, Ne, Mg, Si, S, Ar, Fe, Kr};
const int NElement = 12;  // number of Elements

class UlyssesSwicsEffic {

 public:

  // constructor
  UlyssesSwicsEffic();

  /* set/get directory from which to read tables for interpolation */
  void setEfficDirectory(string dir);
  string getEfficDirectory();

  /* get efficiency for ion of total energy etot in keV */
  float getEffic(const string ion, const float etot);

 private:
  string EfficDir;

  vector<ElemEffic> data;

  // Integer minimum/maximum functions, used in calcByInterpolation
  // Translated from pre-processor macros in nrutil.h, part of
  // Numerical Recipes in C.
  int imin(int a, int b);
  int imax(int a, int b);

};
