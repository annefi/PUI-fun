/*
  File: swindal_nr.h

  Description:
    Swindal C++ wrapper for Numerical Recipes header.  

  Author(s): Jim Raines (jmr)

  Method:
    NR are put into their own namespace (nr) to avoid conflicts.
    
  Revision controlled by CVS:
  $Id: swindal_nr.h,v 1.2 2004/11/11 14:46:45 jraines Exp $

  Major Modification History:
    18Sep2003   jmr   initial coding

*/

// Numerical Recipes
namespace nr {
  extern "C" {
#include "nrutil_c.h"
#include "nr_c.h"
  }
}

