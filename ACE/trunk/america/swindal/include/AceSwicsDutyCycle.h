/*
  File: AceSwicsDutyCycle.h

  Description:
    Duty cycle combines the angular integrations performed by a
    SWICS-type instrument into one number. This module contains
    functions which calculate the duty cycle and handle associated tasks.

  Author(s): Jim Raines (jmr)

  Method:

  References:
    1.  SWICS Specific Instrument Interface Specification, SWICS_SIIS-01.pdf
    2.  von Steiger, R., et. al., "Composition of quasi-stationary
    solar wind flows from Ulysses/Solar Wind Ion Composition
    Spectrometer", JGR 105(A12), p27,217-27,238 (2000)

  Revison controlled by CVS:
  $Id: AceSwicsDutyCycle.h,v 1.4 2004/09/24 15:24:45 jraines Exp $

  Major Modification History:
    11Sep2003   jmr   initial coding

*/
 
/* -------------------------------------------------------------------------
   Define constants for ACE/SWICS
   -------------------------------------------------------------------------
   See ref. 1 for more details.
   -------------------------------------------------------------------------
*/
// Sensor Viewing Angle, SVA
//const float GAMMA = (34.5/360.0)*(2.0*M_PI);
const double GAMMA = (57.0/360.0)*(2.0*M_PI); // ULYSSES

// Sensor opening angle about SVA in elevation (SOE) 
//const float DEL_PHI_C = (70.0/360.0)*(2.0*M_PI);  // SOE Sunward +
                                                  //SOE Earthward

const double DEL_PHI_C = (69.0/360.0)*(2.0*M_PI);  // SOE Sunward + SOE
						  // Earthward

// Sensor opening angle about SVA in azimuth (SOA)
//const float DEL_THETA_C = (4.2/360.0)*(2.0*M_PI); // SOA1 + SOA2
const double DEL_THETA_C = (4.0/360.0)*(2.0*M_PI); // SOA1 + SOA2
  
// number of points over which to do interpolation (in calcByInterpolation)
const int NPOINT_INTERPOL = 4;
  

class AceSwicsDutyCycle {

  /* Note on static members: 

     (1) The integrand member function had to be made static so that
     calls to _Numerical Recipes in C_ integration routines would work
     properly.  For example, the qtrap functions expect a pointer to
     the function to be integrated, of type

     float (*) (float)

     Pointers to static member functions can be of this type (if they
     have a float return type and one float arg. of course).

     However, pointers to non-static member functions would be of type

     float (AceSwicsDutyCycle::*) (float)

     The former CANNOT be cast into the latter.  If it happens to work
     -- it did not as of this writing (gcc 2.96), it is non-portable,
     possibly undefined and definitely to be avoided at all costs.
     See the following URL for details.

     http://www.parashift.com/c++-faq-lite/pointers-to-members.html

     (2) The data members MachAngle and AspectAngle had to be made
     static so that the (static) integrand function could access them.
  */


 public:
  AceSwicsDutyCycle(void);  // constructor

  /* set/get angle between ion velocity and solar wind bulk velocity
     -------------------------------------------------------------------------
     Value determined by external empirical knowledge of solar wind
     velocity distribution.  Values from 0.0 to 0.25 are reasonable.
  */
  void setMachAngle(float value);
  float getMachAngle(void);

  // get current aspect angle stored in class variable
  float getAspectAngle();

  /* set/get external command to be used for retrieving ACE aspect
     angle.  Command should take one argument, cycle time in seconds
     since 1970, and print one value to stout, angle (in deg.) between
     ACE spin (z) axis and Sun-ACE radial vector.  Default is 
     /shrg1/ace/sw/bin/get_ace_aspect.
   */ 
  void setExtAspectCommand(string cmd);
  string getExtAspectCommand();

  /* Toggle method of aspect angle retrieval.  Setting 'true' causes
     use of external command (see setExtAspectCommand()).  Setting
     'false' causes use of functions from libace_ancil internally
     (currently does not work).
  */
  void useExtAspectCommand(bool val);
  bool useExtAspectCommand();

  // set/get filename for reading ACE ancillary (orbit/attitude) data
  void setAncillaryFilename(string filename);
  string getAncillaryFilename();

  /* calcByIntegration
     Calculate duty cycle on the fly by integration.  This currently
     does not give good results.
  */
  float calcByIntegration(double CycleTime);

  /* calcByInterpolation
     Calculate by interpolation of pre-calculated values.  Filename
     should be pre-specified
  */
  float calcByInterpolation(double CycleTime, float MachAngle);

  /* set/get filename from which to read table for interpolation */
  void setInterpolFilename(string name);
  string getInterpolFilename();

  /* Set/get acceptable accuracy of duty cycle interpolation.

     The absolute value of interpolation accuracy divided by the
     interpolated value (the duty cycle) must be less than this value
     or calcByInterpolation returns duty = -1.0.  According to
     Numerical Recipes, this accuracy is the last adjustment to the
     interpolated value.

     This value can be set to whatever fractional uncertainty is
     allowable in the duty cycle.  At the time of this writing, 0.02,
     implying an error of less than 2%, seems to work reliably.

  */
  void setInterpolAccurCutoff(float cutoff);
  float getInterpolAccurCutoff() const;
  // get a new aspect angle
  int getNewAspectAngle(double CycleTime);

 private:

  // Filename for ancillary data
  string AncillaryFilename;

  // toggle for using external 
  bool UseExtAspectCommand;

  string ExtAspectCommand;

  // Sun-probe-earth angle in radians
  static float AspectAngle;

  // Angle between ion velocity and solar wind bulk velocity in radians(?)
  static float MachAngle;

  // integrand of duty cycle equation for use by numerical integrator
  static float integrand(float phi);

  // Integer minimum/maximum functions, used in calcByInterpolation
  // Translated from pre-processor macros in nrutil.h, part of
  // Numerical Recipes in C.
  int imin(int a, int b);
  int imax(int a, int b);

  // filename from which to read duty cycle info for interpolation
  string InterpolFilename;

  // interpolation accuracy cutoff
  float InterpolAccurCutoff;

};
