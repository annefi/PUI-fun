/*
  File: AceSwimsEffic.h

  Description:

  Header file for ACE/SWIMS Efficiency class returns flux-weighted
  efficiencies for input element.

  Author(s): Jim Raines (jmr)

  Method:
  Class reads  pre-calculated efficiencies and SWICS fluxes from disk
  files.  Efficiencies are then weighted by fluxes according to
  following formula (in pseudo-code):

  eff(m, v) = eff(m,v)*swxflux(m,step)/sum(sxwflux(m,step),step)

  Efficiencies are calculated in constructor and stored in class
  member variables.

  Note: Missing efficiencies are set to 0.0 to avoid erroneous
  results.  Care should be taken in division.

  Revision controlled by CVS:
  $Id: AceSwimsEffic.h,v 1.2 2004/08/16 19:02:25 jraines Exp $

  Major Modification History:
    04May2004   jmr   Adapted from getdata5_angie.cpp.

*/

class AceSwimsEffic {
 public:
  // file is fully qualified filename containing efficiencies
  AceSwimsEffic(const string file);
  
  // get efficiency for specified speed and mass
  float getEffic(float speed, float mass) const;

  // register an ion (by name string, e.g. Mg10+) for flux weighting in
  // efficiency calculation
  int registerFluxWgtIon(string ion);

  // trigger flux weighting -- using registered ions -- of efficiencies
  void fluxWgtEffic(AceSwicsFlux axflux, float start_doyfr, float stop_doyfr);

  // get flux-weighted average efficiency for ion s
  float getFluxWgtAveEffic(int s) const;

 private:
  // fully-qualified efficiency file name
  string EffFile;

  // fully-qualified axlv2 boxrates filename
  string FluxFile;

  // size in km/s of speed bins in eff. file
  int SpeedBinSize;

  vector<vector<float> > Effic;
  vector<string> Headers;

  // (class internal) read eff. file
  int readEffic();

  /* constants 
     note: must be static allow init in header file. */
  // --- number of header lines
  static const int NUM_HEADERS = 3;
  // --- number of columns in the file
  static const int NUM_COLUMNS = 3;

  // Maximum speed and mass for which efficiencies are loaded
  float MaxSpeed;
  float MaxMass;

  // calculate velocity bin (matches binning of eff. file)
  int speedBin(float velocity) const;

  // ions to use in flux-weighting eff.
  vector<string> FluxWgtIons;
  
  // flux-weighted efficiencies, separate for each weighting ion
  vector<float> FluxWgtAveEffic; 

  // KE-based speed, for flux-weighting
  float eoqSpeed(float eoq, float mass, float charge) const; 
  
  // get flux-weighted average efficiency
  float getFluxWgtAveEffic(int s);
};
