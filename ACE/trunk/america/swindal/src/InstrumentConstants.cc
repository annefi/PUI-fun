/*
  File: InstrumentConstants.cc

  Description:
    Code for InstrumentConstants class, a base class set up to
    handle all fixed constants from TOF plasma spectrometers (with and
    without energy detectors).  However, actual constants are intended
    to be hardcoded into derived classes of this class,
    e.g. AceSwimsConstants.

  Author(s): Jim Raines (jmr)

  Method:

  Revision controlled by CVS:
  $Id: InstrumentConstants.cc,v 1.2 2004/07/28 13:28:35 jraines Exp $

  Major Modification History:
    20Feb2004   jmr   initial coding

*/
#include "InstrumentConstants.h"
#include <iostream>

using std::cout;
using std::endl;

InstrumentConstants::InstrumentConstants(){
}

InstrumentConstants::~InstrumentConstants() {}

void InstrumentConstants::initialize(){
  GeomFactor = -1.0;
  EqAcceptFac = -1.0;
  NumEdb = -1;
  FirstEdb = 0;
  TofDistance = -1.0;
  NumTofCh = 0;
  NumEsdCh = 0;
  NumMassCh = 0;
  NumMqCh = 0;
  Tof_Ns_Per_Ch = -1.0;
  Esd_Kev_Per_Ch = -1.0;
  NomCycleTime = -1.0;
  FoilThickness = -1.0;
}

double InstrumentConstants::getGeomFactor() const {
  return(GeomFactor);
}

double InstrumentConstants::getEqAcceptFac() const {
  return(EqAcceptFac);
}

int InstrumentConstants::getNumEdb() const {
  return(NumEdb);
}

int InstrumentConstants::getFirstEdb() const {
  return(FirstEdb);
}

float InstrumentConstants::getTofDistance() const {
  return(TofDistance);
}

int InstrumentConstants::getNumTofCh() const {
  return(NumTofCh);
}

int InstrumentConstants::getNumEsdCh() const {
  return(NumEsdCh);
}

int InstrumentConstants::getNumMassCh() const {
  return(NumMassCh);
}

int InstrumentConstants::getNumMqCh() const {
  return(NumMqCh);
}

float InstrumentConstants::get_Tof_Ns_Per_Ch() const {
  return(Tof_Ns_Per_Ch);
}
  
float InstrumentConstants::get_Esd_Kev_Per_Ch() const {
  return(Esd_Kev_Per_Ch);
}

void InstrumentConstants::dump() const {
  cout << "InstrumentConstants::dump -I- Dumping constants:" << endl;

  cout << "+ GeomFactor = " << GeomFactor << endl;
  cout << "+ EqAcceptFac = "  << EqAcceptFac  << endl; 
  cout << "+ NumEdb = "  << NumEdb  << endl; 
  cout << "+ FirstEdb = "  << FirstEdb  << endl; 
  cout << "+ TofDistance = "  << TofDistance  << endl; 
  cout << "+ NumTofCh = "  << NumTofCh  << endl; 
  cout << "+ NumEsdCh = "  << NumEsdCh  << endl; 
  cout << "+ NumMassCh = "  << NumMassCh  << endl; 
  cout << "+ Tof_Ns_Per_Ch = " << Tof_Ns_Per_Ch  << endl; 
  cout << "+ Esd_Kev_Per_Ch = " << Esd_Kev_Per_Ch  << endl; 
  cout << "+ NomCycleTime = " << NomCycleTime << endl;

  // copy following line to add new
  //cout << "+ = " <<   << endl; 
  return;
}

float InstrumentConstants::getNomCycleTime() const {
  return(NomCycleTime);
}

float InstrumentConstants::getFoilThickness() const {
  return(FoilThickness);
}
