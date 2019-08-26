/*
  File: InstrumentData.cc

  Description:
    Code for InstrumentData class, a class for loading and
    holding TOF mass spectrometer data.  This is a base class only;
    all instrument-specific details are to be encapsulated in derived
    classes, e.g. AceSwimsData.

  Author(s): Jim Raines (jmr)

  Method:

  Revision controlled by CVS:
  $Id: InstrumentData.cc,v 1.1 2004/04/27 20:39:46 jraines Exp $

  Major Modification History:
    23Feb2004   jmr   initial coding

*/

#include "swindal.h"

//inline InstrumentData::~InstrumentData() {}
InstrumentData::~InstrumentData() {}

long InstrumentData::getNumPha() const{
  return(PhaData.size());
}

Pha* InstrumentData::getPha(int i) {
  return(&PhaData[i]);
}

