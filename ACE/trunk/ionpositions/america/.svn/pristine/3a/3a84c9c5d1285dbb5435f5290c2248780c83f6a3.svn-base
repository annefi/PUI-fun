/*
  File: AceSwimsHousekeeping.h

  Description:
    Header file for AceSwimsHousekeeping class, a derived class set up to
    handle all housekeeping values from  TOF plasma spectrometers (with and
    without energy detectors).  Actual constants are  hardcoded into
    this class.

  Author(s): Jim Raines (jmr)

  Method:
    Calibration curves for level -> voltage conversion are from ACE
    S3DPU Command and Data Document, Technical University of Braunschweig.

  Revision controlled by CVS:
  $Id: AceSwimsHousekeeping.h,v 1.2 2004/07/28 13:28:34 jraines Exp $

  Major Modification History:
    18Mar2004   jmr   initial coding

*/

class AceSwimsHousekeeping : public InstrumentHousekeeping {
 public:

  AceSwimsHousekeeping();

  // --- Power supplies ---
  // Note: Setting the level (setHypLev) causes auto conv. and allows getV_hyp.
  // --- Hyperbola power supply
  void setHypLev(int value);
  int getHypLev() const;
  float getV_hyp() const;
  // --- Accel/Decel. PS, Vf
  void setVfLev(int value);
  int getVfLev() const;
  float getV_f() const;

 private:

  friend class AceSwimsData;

  bool goodByte(int byte, string caller) const;

  // hyperbolic power supply 
  // --- level
  int HypLev;
  // --- voltage
  float V_hyp;

  // acceleration/deceleration power supply, Vf
  // --- level
  int VfLev;
  // --- voltage
  float V_f;
};
