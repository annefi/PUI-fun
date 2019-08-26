/* axlv2.cc -- test the AnalysisData class
   Jim Raines 4Apr2001
*/

#include "swindal.h"

int outputMA(string bname, MeasurementArray *MA, 
	       long int StartYdoy, long int StopYdoy,
	       const AnalysisData& ad);
int outputMMQ(string bname, MeasurementArray *MA, 
	       long int StartYdoy, long int StopYdoy,
	       const AnalysisData& ad);

void o7boxmmq(MeasurementArray *MA, const AnalysisData& ad);

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
  int AnalysisInterval = 5; // 5-10 cycles is reasonable
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
    //outputMA(thisprog, &MA, StartYdoy, StopYdoy, ad);
    outputMMQ(thisprog, &MA, StartYdoy, StopYdoy, ad);
    
    // calculate MMQ for EDB 41 O7+ box for debugging
    //o7boxmmq(&MA, ad);

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
  //BR.print(ad.IonsIndex["O6+"], ad);
  //BR.print(ad.IonsIndex["O7+"], ad);

  // calculate O7+/O6+
  float o7o6 = BR.getBoxrate(ad.IonsIndex["O7+"])/
    BR.getBoxrate(ad.IonsIndex["O6+"]);
  cout << thisprog << " -I- BoxRates O7+/O6+ = " << o7o6 << endl << endl;

  SpillRates SR(ad.Ions.size());
  if (0){
    SR.calc(ad.Ions, BR);

    cout << thisprog << " -I- dumping spillrates..." << endl;
    SR.print();

    // calculate O7+/O6+
    o7o6 = SR.getCorSpillRate(ad.IonsIndex["O7+"])/
      SR.getCorSpillRate(ad.IonsIndex["O6+"]);
    cout << thisprog << " -I- SpillRates O7+/O6+ = " << o7o6 << endl << endl;
  }

  ProbRates  PR(ad.Ions.size());
  if (0){
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

void o7boxmmq(MeasurementArray *MA, const AnalysisData& ad){
  TNT::Matrix<float> mmq(NQCH,NMCH, 0.0);

  float pav = ad.PapsVolt;
  float eq;
  //pav = 24.9; // from a3gxpavdpu()

  cout << "o7boxmmq -D- pav=" << pav << endl;

  //mmq = MA->EtSlice2Mmq(MA->getSlice(nedb),nedb,0,ad);

  cout << "o7boxmmq -D- dumping conversions..." << endl;
  double mm, mq;

  //  for (int nedb = FIRSTEDB; nedb < MAXEDB; nedb++){
  for (int nedb = 41; nedb <= 41; nedb++){
    for (int ntof = 340; ntof <= 348; ntof++){ // box is 340 to 348
      for (int nesd = 46; nesd <= 57; nesd++){ // box is 46 to 57
      
	eq = ad.Eqtab[nedb];
	pav = ad.PapsVolt;

//	mmqbyhand(eq,pav, ntof, nesd, &mm, &mq);

//       Pha pha;
//       double tof, esd;
//       tof = pha.tofch2tof(ntof);
//       esd = pha.esdch2esd(nesd);
//       mmqbyhand(eq, pav, (int)tof, (int)esd, &mm, &mq);
      
// 	cout << "+ mmqbyhand eq=" << eq
// 	     << " ntof=" << ntof
// 	     << " nesd=" << nesd 
// 	     << " mm=" << mm
// 	     << " (" << MA->getMM(fxnedb,ntof,nesd) << ")"
// 	     << " mq=" << mq
// 	     << " (" << MA->getMQ(fxnedb,ntof,nesd) << ")"
// 	     << endl;

	eqte2mmq(eq, pav, ntof, nesd, mm, mq);

	cout << "+ eqte2mmq eq=" << eq
	     << " ntof=" << ntof
	     << " nesd=" << nesd 
	     << " mm=" << mm
	     << " (" << MA->getMM(nedb,ntof,nesd) << ")"
	     << " mq=" << mq
	     << " (" << MA->getMQ(nedb,ntof,nesd) << ")"
	     << endl;

	cout << endl;
      }
    } 
  }
  
}
