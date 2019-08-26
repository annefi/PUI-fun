/*
  File: InstrumentConstants.h

  Description:
    Header file for InstrumentConstants class, a base class set up to
    handle all fixed constants from TOF plasma spectrometers (with and
    without energy detectors).  However, actual constants are intended
    to be hardcoded into derived classes of this class,
    e.g. AceSwimsConstants.

  Author(s): Jim Raines (jmr)

  Method:

  Revision controlled by CVS:
  $Id: InstrumentConstants.h,v 1.1 2004/04/27 20:39:29 jraines Exp $

  Major Modification History:
    20Feb2004   jmr   initial coding

*/

class InstrumentConstants {

 public:

  InstrumentConstants(); // constructor

  // required because of virtual functions
  virtual ~InstrumentConstants();

  double getGeomFactor() const;
  double getEqAcceptFac() const;
  int getNumEdb() const;
  int getFirstEdb() const;
  float getTofDistance() const;
  int getNumTofCh() const;
  int getNumEsdCh() const;
  int getNumMassCh() const;
  int getNumMqCh() const;
  float get_Tof_Ns_Per_Ch() const;  
  float get_Esd_Kev_Per_Ch() const;

  // nominal cycle time in seconds
  float getNomCycleTime() const;

  // get foil thickness
  float getFoilThickness() const;

  void dump() const;

 private:

  // initialize all values to safe values; this is not in the constructor
  // because that function is replaced in the derived classes
  void initialize();

  // list derived classes that will contain actual values as friends below
  friend class AceSwimsConstants;
  friend class AceSwicsConstants;

  double GeomFactor;

  // width of E/q window at step i = EqAcceptFac * Eqtab(i)
  double EqAcceptFac ;

  // number of EDBs in cycle
  int NumEdb;

  // first EDB to process 
  int FirstEdb;

  // flight distance in time of flight region
  float TofDistance;

  // number of tof channels
  int NumTofCh;

  // number of solid state energy detector (esd) channels
  int NumEsdCh;

  // number of mass channels
  int NumMassCh;

  // number of m/q channels
  int NumMqCh;

  // TOF conversion factor between channels and nanoseconds
  float Tof_Ns_Per_Ch;

  // ESD conversion factor between channels and keV
  float Esd_Kev_Per_Ch;

  // nominal cycle time in seconds
  float NomCycleTime;

  // carbon foil thickness in ug/??
  float FoilThickness;

};
