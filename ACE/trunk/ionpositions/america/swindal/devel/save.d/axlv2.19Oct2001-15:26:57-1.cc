/*
  File: axlv2.cc

  Description:
    Produce ACE/SWICS LV2 data, version 2.0.
    This code is not finished and CURRENTLY UNDER DEVELOPMENT.

  Author: Jim Raines, Aug2001 

  Method:
    
  Major Modification History:
    

*/

#include "swindal.h"

int outputMA(string bname, MeasurementArray *MA, 
	       long int StartYdoy, long int StopYdoy,
	       const AnalysisData& ad);
int outputMMQ(string bname, MeasurementArray *MA, 
	       long int StartYdoy, long int StopYdoy,
	       const AnalysisData& ad);

int main(int argc, char* argv[]){
  char thisprog[] = "axlv2";
  
  initSwindal();  // initializes global variables

  /* ----------------------------------------------------------------------- */
  /*                     ===> adjustable parameters <===                     */
  /* ----------------------------------------------------------------------- */

  /* -- run start/stop days -- */
  long int StartYdoy = 2000158;
  long int StopYdoy  = 2000158;
  
  // base name for saving files (i.e. ma, ma output, mmq output)
  string filebase = "axlv2";
  bool LoadMA = true; // true means load instead of fill from LV1 data
  bool SaveMA = false;// true means save MA after filling

  /* Number of cycles to analyze at a time */
  int AnalysisInterval = 5; // 5-10 cycles is reasonable
  int MaxAnInt = 0;  // max. number of analysis intervals (0 => no limit)

  gDbgLvl = 1;
  int DbgLvl = gDbgLvl; // init local debugging level to global one
  //DbgLvl = 0;

  char LV1DIR[] = "/home/acedata/LV1";
  
  /* ----------------------------------------------------------------------- */
  /* -------------------------- init variables ----------------------------- */
  /* ----------------------------------------------------------------------- */
  char cdaterange[17];
  sprintf(cdaterange, "_%07d_%07d", StartYdoy, StopYdoy);
  string mafile = filebase + "_ma" + cdaterange + ".dat";

  /* ----------------------------------------------------------------------- */
  /* -------------------- Process command-line arguments ------------------- */
  /* ----------------------------------------------------------------------- */
  if (DbgLvl > 2){
    cout << thisprog << " -D- dumping args:" << endl;
    for (int i = 0; i < argc; i++){
      cout << "argv[" << i << "]=" << argv[i] << endl;
    }
  }

  switch (argc) {
  case 1:
    break;
  case 2:
    break;
  case 3:
    break;
  default:
    ;
  }

  /* ----------------------------------------------------------------------- */
  /* ------------------------ Load/Accumulate Data ------------------------- */
  /* ----------------------------------------------------------------------- */
  int lpresult;         // returned value from loadPha
  char tmpstring[150];  // tmp, for forming data filename

  AnalysisData ad;      // contains ion info, Eq table, foward model, PAV
  if (DbgLvl >= 2) ad.dump();

  MeasurementArray MA;  // array of counts/s for each tof,esd (for each edb)
  if (LoadMA) {         // read MeasurementArray from file
    MA.load(mafile);
  }
  else {                // accumulate data into MeasurementArray
    /* --- loop over days --- */
    for (long int CurYdoy = StartYdoy; 
	 CurYdoy <= StopYdoy; 
	 CurYdoy = incrementYdoy(CurYdoy)) {

      cout << thisprog << " -I- accumulating PHAs from ydoy " 
	   << CurYdoy << endl;

      /* form filename, e.g. /home/acedata/LV1/2000/2000158.nc */
      sprintf(tmpstring, "%s/%4d/%d.nc\0",LV1DIR, CurYdoy/1000, CurYdoy);
      gCurLv1File = (string) tmpstring;

      if (DbgLvl) {
	cout << thisprog << " -I- using file " << gCurLv1File << endl;
      }

      /* --- loop over analysis intervals to get through whole day --- */
      lpresult = 0;
      int nAnInt = 0; // number of completed analysis intervals
      while ( lpresult == 0 ){

	/* -- load PHAs in block so PHA vector is destroyed each time -- */ 
	{
	  // create PHA vector
	  vector<Pha> pha;
	
	  // load an AnalysisInterval cycles worth of PHAs
	  lpresult = loadPha(&pha, AnalysisInterval);
	  if (lpresult != 0) {
	    break;
	  }

	  // Add to measurement array
	  MA.fill(&pha);

	  nAnInt++;  
	  // force exit after fixed number of analysis intervals for testing
	  if ( (MaxAnInt != 0) && (nAnInt == MaxAnInt) ) {
	    lpresult = 1;
	    cout << thisprog << " -I- accumulating from only "
		 << MaxAnInt << " analysis intervals, each of "
		 << AnalysisInterval << " cycles." << endl;

	  }

	} // PHA vector block


      } // end of loop over analysis intervals

    } // end of loop over days
    if (SaveMA) MA.save(mafile);

    if (lpresult != 0 && lpresult != 2){
      cout << thisprog << " -E- loadPha returned " << lpresult << "\n";
    }

  } // end of load/accumulate block  

  //outputMA(filebase, &MA, StartYdoy, StopYdoy, ad);
  //outputMMQ(filebase, &MA, StartYdoy, StopYdoy, ad);

  /* ----------------------------------------------------------------------- */
  /* ------------------------ Calculate Rates ------------------------------ */
  /* ----------------------------------------------------------------------- */
  BoxRates BR(ad.Ions.size());
  BR.calc(&MA, ad.Ions);

  cout << thisprog << " -I- printing boxrates" << endl;
  cout << BR;

  // for debugging
  cout << thisprog << " -I- dumping boxrates..." << endl;
  //BR.print(ad.IonsIndex["O6+"], ad);
  //BR.print(ad.IonsIndex["O7+"], ad);

  // calculate O7+/O6+
  float o7o6 = BR.getBoxrate(ad.IonsIndex["O7+"])/
    BR.getBoxrate(ad.IonsIndex["O6+"]);
  cout << thisprog << " -I- BoxRates O7+/O6+ = " << o7o6 << endl << endl;

  SpillRates SR(ad.Ions.size());
  if (1){
    SR.calc(ad.Ions, BR);

    cout << thisprog << " -I- dumping spillrates..." << endl;
    SR.print();

    //SR.dump(ad.IonsIndex["O6+"]);
    //SR.dump(ad.IonsIndex["O7+"]);

    // calculate O7+/O6+
    o7o6 = SR.getCorSpillRate(ad.IonsIndex["O7+"])/
      SR.getCorSpillRate(ad.IonsIndex["O6+"]);
    cout << thisprog << " -I- SpillRates O7+/O6+ = " << o7o6 << endl << endl;
  }

  ProbRates  PR(ad.Ions.size());
  if (1){
    cout << thisprog << " -I- starting probrates calculation..." << endl;  

    string prfile = filebase + "_pr" + cdaterange + ".dat";
    if (1){
      PR.load(prfile); 
    }
    else{
      PR.calc(ad.Ions, MA, SR);
      PR.save(prfile);
    }

    cout << thisprog << " -I- printing probrates..." << endl;
    PR.print();

    //PR.dump(ad.IonsIndex["O6+"]);
    //PR.dump(ad.IonsIndex["O7+"]);

    // calculate O7+/O6+
    o7o6 = PR.getProbRate(ad.IonsIndex["O7+"])/
      PR.getProbRate(ad.IonsIndex["O6+"]);
    cout << thisprog << " -I- ProbRates O7+/O6+ = " << o7o6 << endl << endl;

    o7o6 = PR.getProbRateCM(ad.IonsIndex["O7+"])/
      PR.getProbRateCM(ad.IonsIndex["O6+"]);
    cout << thisprog << " -I- ProbRatesCM O7+/O6+ = " << o7o6 << endl << endl;
  }

  /* ----------------------------------------------------------------------- */
  /* -------- Calculate distribution function and state variables ---------- */
  /* ----------------------------------------------------------------------- */
  DistFunc  DF(ad.Ions.size());
  if (1){
    cout << thisprog << " -I- starting distribution function calculation..." 
	 << endl;  

    DF.calc(ad.Ions, ad, PR);

    cout << thisprog << " -I- dumping state variables..." << endl;
    for(int nedb=FIRSTEDB; nedb < MAXEDB; nedb++){
      cout << "+ nedb=" << nedb
	   << " n=" << DF.getDensity(nedb)
	   << " v(bulk)=" << DF.getBulkVelocity(nedb)
	   << " v(therm)=" << DF.getThermVelocity(nedb)
	   << endl;
    }

  }

  return(0);
}  
