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
    // no arguments, just the program name
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

  // output some matrices
  outputMA(filebase, &MA, StartYdoy, StopYdoy, ad);
  outputMMQ(filebase, &MA, StartYdoy, StopYdoy, ad);

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
  float o7o6br = BR.getBoxrate(ad.IonsIndex["O7+"])/
    BR.getBoxrate(ad.IonsIndex["O6+"]);
  cout << thisprog << " -I- BoxRates O7+/O6+ = " << o7o6br << endl << endl;

  SpillRates SR(ad.Ions.size());
  float o7o6sr; // O7+/O6+ from SpillRates
  if (1){
    SR.calc(ad.Ions, BR);

    cout << thisprog << " -I- dumping spillrates..." << endl;
    SR.print();

    //SR.dump(ad.IonsIndex["O6+"]);
    //SR.dump(ad.IonsIndex["O7+"]);

    // calculate O7+/O6+
    o7o6sr = SR.getCorSpillRate(ad.IonsIndex["O7+"])/
      SR.getCorSpillRate(ad.IonsIndex["O6+"]);
    cout << thisprog << " -I- SpillRates O7+/O6+ = " << o7o6sr << endl << endl;
  }

  ProbRates  PR(ad.Ions.size());
  float o7o6pr, o7o6prcm; // O7+/O6+ from ProbRates and ProbRatesCM
  if (1){
    cout << thisprog << " -I- starting probrates calculation..." << endl;  

    string prfile = filebase + "_pr" + cdaterange + ".dat";
    if (1){
      cout << thisprog << " -I- loading ProbRates data..." << endl;
      PR.load(prfile); 
    }
    else{
      cout << thisprog << " -I- calculating ProbRates data..." << endl;
      PR.calc(ad.Ions, MA, SR);
      cout << thisprog << " -I- saving ProbRates data..." << endl;
      PR.save(prfile);
    }

    cout << thisprog << " -I- printing probrates..." << endl;
    PR.print();

    //PR.dump(ad.IonsIndex["O6+"]);
    //PR.dump(ad.IonsIndex["O7+"]);

    // calculate O7+/O6+
    o7o6pr = PR.getProbRate(ad.IonsIndex["O7+"])/
      PR.getProbRate(ad.IonsIndex["O6+"]);
    cout << thisprog << " -I- ProbRates O7+/O6+ = " << o7o6pr << endl << endl;

    o7o6prcm = PR.getProbRateCM(ad.IonsIndex["O7+"])/
      PR.getProbRateCM(ad.IonsIndex["O6+"]);
    cout << thisprog << " -I- ProbRatesCM O7+/O6+ = " 
	 << o7o6prcm << endl << endl;
  }

  /* ----------------------------------------------------------------------- */
  /* -------- Calculate distribution function and state variables ---------- */
  /* ----------------------------------------------------------------------- */
  DistFunc  DF(ad.Ions.size());
  float o7o6df;  // O7+/O6+ density ratio
  if (1){
    cout << thisprog << " -I- starting distribution function calculation..." 
	 << endl;  

    DF.calc(ad.Ions, ad, PR);

    cout << thisprog << " -I- dumping state variables..." << endl;
    for(int s = 0; s < ad.Ions.size(); s++){
      cout << "+ " << ad.Ions[s].name
	   << " n=" << DF.getDensity(s)
	   << " v(bulk)=" << DF.getBulkVelocity(s)
	   << " v(therm)=" << DF.getThermVelocity(s)
	   << endl;
    }

    o7o6df = DF.getDensity(ad.IonsIndex["O7+"])/
      DF.getDensity(ad.IonsIndex["O6+"]);
    cout << thisprog << " -I- Density O7+/O6+ = " 
	 << o7o6df << endl << endl;

  }

  /* ----------------------------------------------------------------------- */
  /* ---------------------- Output Comparison Tables ----------------------- */
  /* ----------------------------------------------------------------------- */

  vector<string> ctions;

  ctions.push_back("C5+");
  ctions.push_back("N5+");
  ctions.push_back("N6+");
  ctions.push_back("O6+");
  ctions.push_back("O7+");
  ctions.push_back("20Ne8+");

  cout << endl;
  cout << thisprog << " -I- writing comparison table(s):" << endl;

  printf("\n");
  printf("%6s\t%8s\t%8s\t%8s\t%8s\n", "", "Box", "Spill", 
	 "Prob", "Density");
  printf("----------------------------------------------------------------\n");

  char fmt[] = "%6s\t%8.2e\t%8.2e\t%8.2e\t%8.2e\n";

  int s; // index of current species
  float boxsum = 0.0;    
  float spillsum = 0.0;
  float probsum  = 0.0;
  float denssum  = 0.0;
  for (int i = 0; i < ctions.size(); i++){
    s = ad.IonsIndex[ctions[i]];
    printf(fmt, ad.Ions[s].name.c_str(), BR.getBoxrate(s),
	   SR.getCorSpillRate(s), PR.getProbRate(s), DF.getDensity(s));


    boxsum += BR.getBoxrate(s);
    spillsum += SR.getCorSpillRate(s);
    probsum += PR.getProbRate(s);
    denssum += DF.getDensity(s);
    
  }
  printf("----------------------------------------------------------------\n");
  printf(fmt, "^sum^", boxsum, spillsum, probsum, denssum);

  printf("----------------------------------------------------------------\n");
  printf(fmt, "O7/O6", o7o6br, o7o6sr, o7o6pr, o7o6df);

  printf("----------------------------------------------------------------\n");
  vector<float> csums,osums;
  for (int i = 0; i < 4; i++){
    csums.push_back(0.0);
    osums.push_back(0.0);
  }

  vector<string> cnames;
  cnames.push_back("C4+");
  cnames.push_back("C5+");
  cnames.push_back("C6+");
  for (int i = 0; i < cnames.size(); i++){
    s = ad.IonsIndex[cnames[i]];

    csums[0] += BR.getBoxrate(s);
    csums[1] += SR.getCorSpillRate(s);
    csums[2] += PR.getProbRate(s);
    csums[3] += DF.getDensity(s);
  }

  vector<string> onames;
  onames.push_back("O5+");
  onames.push_back("O6+");
  onames.push_back("O7+");
  onames.push_back("O8+");

  for (int i = 0; i < onames.size(); i++){
    s = ad.IonsIndex[onames[i]];

    osums[0] += BR.getBoxrate(s);
    osums[1] += SR.getCorSpillRate(s);
    osums[2] += PR.getProbRate(s);
    osums[3] += DF.getDensity(s);
  }

  printf(fmt, "C/O", csums[0]/osums[0], csums[1]/osums[1],
	 csums[2]/osums[2], csums[3]/osums[3]);
  printf("----------------------------------------------------------------\n");

  cout << endl;

  return(0);
}  
