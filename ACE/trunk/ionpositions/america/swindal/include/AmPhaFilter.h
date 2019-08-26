/*
  File: AmPhaFilter.h

  Description:
    Header file for the ACE/SWIMS PHA Filter class, a class for
    defining filters which removed certain PHA words from
    consideration.  This is an abstract base class only; it should
    never be instantiated.  Rather, all filter-specific details are to
    be encapsulated in derived classes, e.g., AceSwimsSsdFilter.

  Author(s): Jim Raines (jmr)

  Method:

  Revision controlled by CVS:
  $Id: AmPhaFilter.h,v 1.1 2004/04/27 20:39:25 jraines Exp $

  Major Modification History:
    01Mar2004   jmr   initial coding

*/

class AmPhaFilter {

 public:

  // required because of virtual functions
  virtual ~AmPhaFilter();

  virtual bool passFilter(const AceSwimsPha& pha) const = 0;

 private:

};
