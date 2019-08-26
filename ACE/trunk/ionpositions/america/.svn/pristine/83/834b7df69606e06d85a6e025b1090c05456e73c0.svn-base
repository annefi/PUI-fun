/*
  File: AceSwimsBackground.h

  Description:
    Header file for ACE/SWIMS background class, a class for handling 
    background channel registration, output and calculation from spectra.
    
  Author(s): Jim Raines (jmr)

  Method:

  Revision controlled by CVS:
  $Id: AceSwimsBackground.h,v 1.2 2004/08/02 17:03:45 jraines Exp $

  Major Modification History:
    06May2004   jmr   initial coding

*/

class AceSwimsBackground {
 public:
  AceSwimsBackground();

  // register range of channels which should be considered background
  int registerRange(int lo, int hi);

  // calculate background for all registered channels
  int calc(const TofMeasurementArray& TMA, int nedb);

  // get average background over all ranges
  float getAve();

  // output ranges and calculated values to specified file
  // format: doyfr edb lo  hi  value
  void initOutput(std::ofstream& fout, string file);
  int output(std::ofstream& fout, float doyfr, int nedb);

 private:

  // internal data structure for background ranges
  // all public because is used as a only slightly smart data structure
  class range {
  public:
    // constructor
    range(int lo,int hi);
    // lowest channel to include
    int Lo;
    // highest channel to include
    int Hi;
    // number of channels in range (inclusive of end points)
    int NumCh;
    // sum over channels in range
    float Sum;
    // average over channels in range
    float Ave;

    // set the sum and automatically calculate the average
    void setSum(float);
  };

  vector<range> Ranges;

  float Average;
};
