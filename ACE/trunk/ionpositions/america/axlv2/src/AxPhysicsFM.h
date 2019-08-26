/*
  File: AxPhysicsFM.cc

  Description:
    ACE/SWICS physics-based forward model object.

  Author(s): Jim Raines (jmr)

  Method:
    Right now, this is just a wrapper for xfmexp_phys.c.

  Revision controlled by CVS:
  $Id: AxPhysicsFM.h,v 1.1 2004/10/19 13:56:10 jraines Exp $

  Major Modification History:
    16Sep2004   jmr   initial coding

*/

class AxPhysicsFM {
 public:

  // constructor
  AxPhysicsFM();

  // load FM parameters into AnalysisData ions 
  // at given post-accel. voltage (pav)
  int load(AnalysisData& ad, double pav);

 private:

};
