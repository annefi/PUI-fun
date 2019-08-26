/*
  File: PhaFilter.h

  Description:
    Code for the PHA Filter class, a class for defining filters
    which removed certain PHA words from consideration.  This is an
    abstract base class only; it should never be instantiated.
    Rather, all filter-specific details are to be encapsulated in
    derived classes, e.g., AceSwimsSsdFilter.

  Author(s): Jim Raines (jmr)

  Method:

  Revision controlled by CVS:
  $Id: PhaFilter.cc,v 1.1 2004/04/27 20:39:48 jraines Exp $

  Major Modification History:
    01Mar2004   jmr   initial coding

*/
#include "swindal.h"

PhaFilter::~PhaFilter() {}
