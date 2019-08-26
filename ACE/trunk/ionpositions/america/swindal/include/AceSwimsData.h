/*
  File: AceSwimsData.h

  Description:
    Header file for AceSwimsData class, a class for loading and
    holding ACE/SWIMS data, including all the necessary specifics for
    that instrument.

  Author(s): Jim Raines (jmr)

  Method:
    References:  (fill out these entries)
    
    1) libhef
    2) instrument paper from ACE book
    3) getdata5 package by Roland Schaerer and Bob Wimmer
    (Note: this one often does not describe methods well.)

  Revision controlled by CVS:
  $Id: AceSwimsData.h,v 1.3 2004/11/03 18:54:33 jraines Exp $

  Major Modification History:
    24Feb2004   jmr   initial coding

*/

class AceSwimsData : public InstrumentData {
 public:
  AceSwimsData(AceSwimsHousekeeping& hk);

  // load specified number of cycles, returns number actually loaded
  int load(AnalysisData2& ad, int NumCyclesToLoad);

  // get forward model (FM) center for specified arguments
  double* getFM(double eoq, double pav, double mass, double charge);

  // get number of PHA currently loaded
  // note: this must be redefined in this derived class because
  // PhaData was redefined to hold AceSwimsPha not Pha.
  virtual long getNumPha() const;
  
  // get ith PHA word (i: 0..getNumPha()-1)
  virtual AceSwimsPha* getPha(int i);

  // load information functions
  bool loadNeedsNewFile(void);
  bool loadFoundError(void);

  // toggle dumping of PHA data to file
  void dumpPha(bool);
  
 private:

  /* Calculate speed from E/q and counts vectors
     This is used in this class to calculate *SWICS* He2+ velocity to
     use for further calculations (later).
  */
  double calcSwSpeed(vector<double> epq,vector<double> cnt,
				   double moq, double cutoff);

  vector<AceSwimsPha> PhaData;

  AceSwimsHousekeeping* HK;

  // ------load control flags------
  // flag indicating a load error has occurred, T=>error occurred
  bool LoadFoundError;

  /* flag to control switching data files, T=>new file should be used, 
     meaning either EOF was found or no file has yet been opened

     note on static:  ALL instances of this class use this one copy of this 
     variable.  Beware! */
  static bool LoadNeedsNewFile;

  // ------------------------------

  // t=>pha info written to static file for debug
  bool dumpPhaFlag; 

};

