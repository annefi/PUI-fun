/*
  File: ElemEffic.cc

  Description:
    Class provides a container for holding efficiency-related items,
    written to be used with UlyssesSwicsEffic and interpolation to
    required energy.

  Author(s): Jim Raines (jmr)

  Method:
    See corresponding header (.h) file for further documentation.  The
    design of this class was made to be compatible with interpolation
    by Numerical Recipes in C.  As such, the data structures are very
    C-like.  This was determined to be the most efficient method.

  Revision controlled by CVS:
  $Id: ElemEffic.cc,v 1.1 2003/11/06 21:48:18 jraines Exp $

  Major Modification History:
    29Oct2003   jmr   initial coding

*/

#include "swindal.h"
#include "swindal_nr.h"

ElemEffic::ElemEffic() : etot(0), prob1(0), prob2(0), prob3(0) {
  ion_name = "";
  element_name = "";
  file = "";

  loaded = false;

}

ElemEffic::~ElemEffic() {
    if (etot) nr::free_vector(etot, 1, nrows);
    if (prob1) nr::free_vector(prob1, 1, nrows);
    if (prob2) nr::free_vector(prob2, 1, nrows);
    if (prob3) nr::free_vector(prob3, 1, nrows);
}
