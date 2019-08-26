/*
  File: AceSwicsData.h

  Description:

    Class of functions and containers for groups of Pha words.  This
    class, along with the Pha class contain all instrument-specific
    functions and containers.

  Author(s): Jim Raines (jmr)

  Method:
    
  Revision controlled by CVS:
  $Id: AceSwicsData.h,v 1.9 2005/06/09 04:06:12 jraines Exp $

  Major Modification History:
    01Sep2002   jmr   initial coding

*/

class AceSwicsData {
 public:
  AceSwicsData(void);  // constructor

  int load(int AnalysisInterval,double &swspeed);

  /* force-close cycle file 

     Normally load() takes care of this automatically.  This is only
     used when a file must be pre-processed in some way before.  It is
     then closed with this function and load() is called as normal. */

  int closeFile(void) const;

  Pha getPha(int i) const;
  long getNpha(void) const;   // number of PHA for looping getPha

  double *getFM(double, double, double, double) const;

  double getPav() const;   // get post acceleration voltage
  double getEqtab(int i) const;  // get E/q at step i
  float  ss1970_to_doyfr(double ss1970) const;

  // Returns cycle time (in sec. since 1970) for first PHA in PhaData,
  // set at the end of each load().
  double getCycleTime() const;

  // --- Solar Wind Speed ---
  //  double getswspeed (); 
  // calculates solar wind speed from count-weighed average E/q
  // Used in load() function to set values in indiv. PHA words.
  double calcSwSpeed (vector<double> eoq, vector<double> cnt, 
		      double moq, double cutoff);


  // used only for debugging
  int dumpPha(Pha *pha, int npha, int ncycle) const;
  int dumpPhaFile(Pha *pha, int npha, int ncycle, FILE* F) const;

  // load information functions
  bool loadNeedsNewFile(void);
  bool loadFoundError(void);

  // copy constructor
  AceSwicsData(const AceSwicsData& asd);

  // copy assignment operator -- may not be necessary
  AceSwicsData& operator= (const AceSwicsData& rhs);

 private:
  // create PHA vector
  vector<Pha> PhaData;

  //post-acceleration voltage in kV
  double PapsVolt;

  // eqtab
  vector<double> Eqtab;        // Commanded E/q values

  // Cycle time (in sec. since 1970) for first PHA in PhaData,
  // set at the end of each load().
  double CycleTime;

  // ------load control flags------
  // flag indicating a load error has occurred, T=>error occurred
  bool LoadFoundError;

  /* flag to control switching data files, T=>new file should be used, 
     meaning either EOF was found or no file has yet been opened

     note on static:  ALL instances of this class use this one copy of this 
     variable.  Beware! */
  static bool LoadNeedsNewFile;

};
