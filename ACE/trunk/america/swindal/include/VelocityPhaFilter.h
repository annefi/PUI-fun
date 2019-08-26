/*
  File: PhaFilter.h

  Description:
    Code for the PHA Filter class, a class which defines a PHA
    velocity filter.  The class is derived from PhaFilter.

  Author(s): Jim Raines (jmr)

  Method:

  Revision controlled by CVS:
  $Id: VelocityPhaFilter.h,v 1.1 2004/04/27 20:39:35 jraines Exp $

  Major Modification History:
    01Mar2004   jmr   initial coding

*/

class VelocityPhaFilter : public AmPhaFilter {

 public:

  VelocityPhaFilter();

  virtual bool passFilter(const AceSwimsPha& pha) const;

  void setVelFraction(float frac);

 private:

  float VelFraction;
};
