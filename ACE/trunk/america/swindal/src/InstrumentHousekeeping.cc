/*
  File: InstrumentHousekeeping.cc

  Description:
    Code for InstrumentHousekeeping class, a base class set up to
    handle all housekeeping values from  TOF plasma spectrometers (with and
    without energy detectors).  However, actual constants are intended
    to be hardcoded into derived classes of this class, 
    e.g. AceSwimsHousekeeping, and will be a superset of those within.

  Author(s): Jim Raines (jmr)

  Method:

  Revision controlled by CVS:
  $Id: InstrumentHousekeeping.cc,v 1.1 2004/04/27 20:39:47 jraines Exp $

  Major Modification History:
    18Mar2004   jmr   initial coding

*/
#include "swindal.h"

InstrumentHousekeeping::InstrumentHousekeeping(){

}
