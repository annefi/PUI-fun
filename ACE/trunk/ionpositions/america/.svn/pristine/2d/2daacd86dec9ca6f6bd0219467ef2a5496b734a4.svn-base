/* axlv2.cc -- test the AnalysisData class
   Jim Raines 4Apr2001
*/

#include "swindal.h"

int outputMats(string bname, MeasurementArray *MA, 
	       long int StartYdoy, long int StopYdoy,
	       const AnalysisData& ad);

int main(int argc, char* argv[]){
  char thisprog[] = "axlv2";
  int i,j;
  char tmpstring[150];
  
  int result;     // returned value from a function call, used local to call
  int lpresult;   // returned value from loadPha
  
  initSwindal();

  /* ===> adjustable parameters */

  /* -- run start/stop days -- */
  long int StartYdoy = 2000158;
  long int StopYdoy  = 2000158;
  
  // base name of file for saving measurement array
  string mabase = "axlv2_ma";
  bool LoadMA = false; // true means load instead of fill from LV1 data
  //dnw bool SaveMA = false; // true means save MA after filling

  /* Number of cycles to analyze at a time */
  int AnalysisInterval = 10; // 5-10 cycles is reasonable
  bool OneAnInt = false;  // run just one analysis interval (for testing)

  gDbgLvl = 1;
  int DbgLvl = gDbgLvl; // init local debugging level to global one
  //DbgLvl = 0;

  char LV1DIR[] = "/home/acedata/LV1";
  
  /* end of adjustable parameters */

  /* --- init variables --- */
  char cdaterange[17];
  sprintf(cdaterange, "_%07d_%07d", StartYdoy, StopYdoy);
  string mafile = mabase + cdaterange + ".dat";

  /* --- Process command-line arguments --- */
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

  AnalysisData ad;

  if (DbgLvl > 1) ad.dump();

  BoxRates BR(ad.Ions.size());
  { // block for MA (it is destroyed after this block)
    /* --- loop over days --- */
    MeasurementArray MA;  // array of counts/s for each tof,esd (for each edb)
    if (LoadMA) {  // read MeasurementArray from file
      MA.load(mafile);
    }
    else { // accumulate data into MeasurementArray
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

	lpresult = 0;
	/* --- loop over analysis intervals to get through whole day --- */
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

	    // force exit after one Analysis Interval for testing
	    if (OneAnInt) {
	      lpresult = 1;
	      cout << thisprog << " -I- accumulating from only "
		   << AnalysisInterval << " cycles." << endl;

	    }

	  }
	}

      }
      if (! OneAnInt) MA.save(mafile);

      if (lpresult != 0 && lpresult != 2){
	cout << thisprog << " -E- loadPha returned " << lpresult << "\n";
      }

    }

    BR.calc(&MA, ad.Ions);
    //outputMats(thisprog, &MA, StartYdoy, StopYdoy, ad);


    if (0){
      string file;
      
      file = thisprog;
      file = file + "_MM.dat";
      MA.dumpMM(file, StartYdoy, StopYdoy);

      file = thisprog;
      file = file + "_MQ.dat";
      MA.dumpMQ(file, StartYdoy, StopYdoy);
    }
  }

  cout << thisprog << " -I- printing boxrates" << endl;
  cout << BR;
  //cout << thisprog << " -I- dumping boxrates..." << endl;
  BR.print(ad.IonsIndex["O6+"], ad);
  BR.print(ad.IonsIndex["O7+"], ad);

  // calculate O7+/O6+
  float o7o6 = BR.getBoxrate(ad.IonsIndex["O7+"])/
    BR.getBoxrate(ad.IonsIndex["O6+"]);
  cout << thisprog << " -I- BoxRates O7+/O6+ = " << o7o6 << endl << endl;

  SpillRates SR(ad.Ions.size());
  if (1){
    SR.calc(ad.Ions, BR);

    cout << thisprog << " -I- dumping spillrates..." << endl;
    SR.print();

    // calculate O7+/O6+
    o7o6 = SR.getCorSpillRate(ad.IonsIndex["O7+"])/
      SR.getCorSpillRate(ad.IonsIndex["O6+"]);
    cout << thisprog << " -I- SpillRates O7+/O6+ = " << o7o6 << endl << endl;
  }

  ProbRates  PR(ad.Ions.size());
  if (1){
    cout << thisprog << " -I- starting probrates calculation..." << endl;  

    PR.calc(ad.Ions, SR);

    cout << thisprog << " -I- dumping probrates..." << endl;
    PR.print();

    // calculate O7+/O6+
    o7o6 = PR.getProbRate(ad.IonsIndex["O7+"])/
      PR.getProbRate(ad.IonsIndex["O6+"]);
    cout << thisprog << " -I- ProbRates O7+/O6+ = " << o7o6 << endl << endl;
  }

  DistFunc  DF(ad.Ions.size());
  if (0){
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

