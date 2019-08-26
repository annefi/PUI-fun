/*
  File: axlv2.cc

  Description:
    Produce ACE/SWICS LV2 data, version 2.0.
    This code is not finished and CURRENTLY UNDER DEVELOPMENT.

    This variant is a first stab at getting hourly (or sub-daily)
    resolution for the entire product, by starting with the hourly
    boxrates.  This data will be used for rudimentary science studies
    in order to provide independent verification of the method (FM
    then box rates) thus far.

  Author: Jim Raines (jmr) 

  Method:
    
  Revision controlled by SVN:
  $Id: axlv2.cc 4882 2007-08-25 14:48:09Z berger $
  
  Major Modification History:
    12Jun2003   jmr   Adapted from axlv2.cc

*/

#include "swindal.h"
#include "axlv2.h"
#include <iomanip>
#include <cstdlib>
#include <stdexcept>

int main(int argc, char* argv[]){

  char thisprog[] = "axlv2";
  string rcs_id = "$Id: axlv2.cc 4882 2007-08-25 14:48:09Z berger $";
  int cyclesspeed=0;
  double swspeed=0.;
  int cycles=0;

  try {

  char thisprog[] = "axlv2";

  using std::cin;

  // print banner
  printf("%s -I- This is the ACE/SWICS Level 2 Data Processor,\n",thisprog);
  printf("          built %s %s\n\n",__DATE__,__TIME__);
  
  initSwindal();  // initializes global variables
  cout << endl;

  /* ----------------------------------------------------------------------- */
  /*                     ===> adjustable parameters <===                     */
  /* ----------------------------------------------------------------------- */

  // local debugging level
  int DbgLvl = 1;  // set to gDbgLvl later

  // toggle production of filtered NVT file for quality debugging
  bool DbgQualFilter = false;

  // Elements for which to produce charge distribution files
  vector<string> QDIST_ELEMENTS;
  QDIST_ELEMENTS.push_back("Fe");
  QDIST_ELEMENTS.push_back("O");
  QDIST_ELEMENTS.push_back("C");
  QDIST_ELEMENTS.push_back("Si");
  QDIST_ELEMENTS.push_back("Ne");
  QDIST_ELEMENTS.push_back("Mg");
  
  /* ----------------------------------------------------------------------- */
  /* -------------------- Process command-line arguments ------------------- */
  /* ----------------------------------------------------------------------- */
  string usage = "usage: axlv2 start_ydoy stop_ydoy accum_minutes";

  if (DbgLvl > 2){
    cout << thisprog << " -D- dumping args:" << endl;
    for (int i = 0; i < argc; i++){
      cout << "argv[" << i << "]=" << argv[i] << endl;
    }
  }


  long int StartYdoy;
  long int StopYdoy;
  int NumMinToAccum;
  // FIX: someday put in sophisticated argument processing
  switch (argc) {
  case 2:
    if ( strcmp(argv[1],"--versions") == 0) {
      showVersions();
      exit(0);
    }
    else {
      cout << thisprog << " -F- wrong number of arguments" << endl;
      cout << "+ " << usage << endl;
      exit(1);
    }
    break;
  case 4:
    StartYdoy = atol(argv[1]);
    StopYdoy = atol(argv[2]);
    NumMinToAccum = atoi(argv[3]);

    cout << thisprog << " -I- running from " << StartYdoy << " to "
	 << StopYdoy << ", accumulating for " << NumMinToAccum 
	 << " min. in each timestep" << endl << endl;

    break;
  default:
    cout << thisprog << " -F- wrong number of arguments" << endl;
    cout << "+ " << usage << endl;
    exit(1);
  }

  /* ----------------------------------------------------------------------- */
  /* ------------------------ Get Input Parameters ------------------------- */
  /* ----------------------------------------------------------------------- */
  // ===> Change this whenever the sequence of inputs (below) is changed! <===
  float InputSeqVersion = 9.0;
  
  string input;  // generic holder for input

  cout << "***** Begin program control parameter input *****" << endl << endl;

  cout << "All prompts ending with a question mark require 1 (true) or "
       << "0 (false) response."  << endl;
  cout << "Inputs are not validated; be CAREFUL!" 
       << endl << endl;

  float InputSeqVersion_read = 0.0;
  cout << "Enter input sequence version number: ";
  cin >> InputSeqVersion_read;
  getline(cin,input);  // reads through the comments
  cout << InputSeqVersion_read << endl;

  // avoid cryptic input sequence errors by checking explicit version
  if (InputSeqVersion_read != InputSeqVersion){
    cout << thisprog << " -F- wrong input sequence version number" << endl;
    cout << "+ Get the latest version of the input script." << endl;
    exit(1);
  }

  bool dosumspeed = false;//false means no summation
  cout << "Sum up E-T slice over whole timeframe, sorted for aspect angle (true or false)? ";
  cin >> dosumspeed;
  getline(cin,input); //reads through the comments 
  cout << dosumspeed << endl;

  float lowspeed = 0.; // lower range for speed summation
  cout << "Enter Aspect angle interval range : ";
  cin >> lowspeed ;
  getline(cin,input); //read through the comments
  cout << lowspeed << endl;

  float highspeed = 0.; // upper range for speed summation
  cout << "Enter Aspect angle interval range : ";
  cin >> highspeed ;
  getline(cin,input); //read through the comments
  cout << highspeed << endl;

  bool dosumwhole = false;//false means no summation
  cout << "Sum up E-T slice over whole timeframe, sorted for aspect angle (true or false)? ";
  cin >> dosumwhole;
  getline(cin,input); //reads through the comments 
  cout << dosumwhole << endl;

  float aspint = 0.; // Aspect angle interval range for upper summation
  cout << "Enter Aspect angle interval range : ";
  cin >> aspint ;
  getline(cin,input); //read through the comments
  cout << aspint << endl;

  bool ratesorcounts = false; // false means do counts
  cout << "Do Rates or Counts (true or false)? ";
  cin >> ratesorcounts;
  getline(cin,input);  // reads through the comments
  cout << ratesorcounts << endl;

  int  MAFilter = 2;  // bit field telling from which Ranges to keep PHAs
                      // See MeasurementArrray.h for details
  cout << "Enter PHA filter flag: ";
  cin >> MAFilter;
  getline(cin,input);
  cout << MAFilter << endl;

  double VelFilter = 0.0; // PHA velocity filter as frac of sw speed
  cout << "Enter velocity filter value (0.0 for none): ";
  cin >> VelFilter;
  getline(cin,input);
  cout << VelFilter << endl;

  int FMType = 2; // default
  cout << "FM choices: -1->none, 0->libhef, 1->libhef-like xfmexp, "
       <<"2->libhef+physics, 3->physics, 4->xfmexp+physics" << endl;
  cout << "Use which FM (-1..4, 2 is standard): ";
  cin >> FMType;
  getline(cin,input);
  cout << FMType << endl;

  bool OutputET = true;  // true means output E-T slices file
  cout << "Output E-T slices? ";
  cin >> OutputET;
  getline(cin,input);  // reads through the comments
  cout << OutputET << endl;

  bool OutputMMQ = true; // true means output MMQ file (summed over step)
  cout << "Output MMQ data for MA? ";
  cin >> OutputMMQ;
  getline(cin,input);  // reads through the comments
  cout << OutputMMQ << endl;

  double mm0,mm1,mq0,mq1; // mass (mm0,mm1) and m/q (mm0,mm1) ranges 
                          // for MMQ output 
  cout << "Enter MMQ data mass *lower* limit: ";
  cin >> mm0;
  getline(cin,input);  // reads through the comments
  cout << mm0 << endl;

  cout << "Enter MMQ data mass *upper* limit: ";
  cin >> mm1;
  getline(cin,input);  // reads through the comments
  cout << mm1 << endl;

  cout << "Enter MMQ data m/q *lower* limit: ";
  cin >> mq0;
  getline(cin,input);  // reads through the comments
  cout << mq0 << endl;

  cout << "Enter MMQ data m/q *upper* limit: ";
  cin >> mq1;
  getline(cin,input);  // reads through the comments
  cout << mq1 << endl;

  // base name for saving files (i.e. ma, ma output, mmq output)
  string filebase = "axlv2";
  cout << "Enter filename base (for all files): ";
  cin >> filebase;
  getline(cin,input);
  cout << filebase << endl;

  // NOTE: StartYdoy, StopYdoy, NumMinToAccum moved into arguments
//   long int StartYdoy = 2000158;
//   cout << "Enter start date (yyyydoy): ";
//   cin  >> StartYdoy;
//   getline(cin,input);
//   cout << StartYdoy << endl;

//   long int StopYdoy  = 2000158;
//   cout << "Enter stop date (yyyydoy): ";
//   cin  >> StopYdoy;
//   getline(cin,input);
//   cout << StopYdoy << endl;

//   int NumMinToAccum; // 120 -> 2hr resolution
//   cout << "Enter number of minutes to accumulate per timestep (-1 => inf): ";
//   cin >> NumMinToAccum;
//   getline(cin,input);
//   cout << NumMinToAccum << endl;

  cout << "Enter global debugging level (0-5): ";
  cin >> gDbgLvl;
  getline(cin,input);
  cout << gDbgLvl << endl;

  // FIX:  The length of this is fixed; it should not be.
  //char LV1DIR[256] = //"/shrg1/ace/LV1";
  string LV1DIR;
  cout << "Enter directory containing LV1 data organized into yearly subdirectories: ";
  cin >> input;
  //strcpy(LV1DIR, input.c_str());
  LV1DIR = input;
  cout << endl << LV1DIR  << endl;
  getline(cin,input);
  string ace_ancil_name;
  ace_ancil_name = LV1DIR + "/ACE_ANCIL.HDF";
  cout << "ace_ancil_name = " << ace_ancil_name << endl;

  // Directory containing efficiency files
  string EFF_DIR;
  cout << "Enter efficiency directory: ";
  cin >> input;
  EFF_DIR = input;
  cout << endl << EFF_DIR  << "[end]" << endl;
  getline(cin,input);

  // fully qualified external aspect command
  string ExtAspectCommand;
  cout << "Enter external aspect command (full path):";
  cin >> input;
  ExtAspectCommand = input;
  cout << endl << ExtAspectCommand << "[end]" << endl;
  getline(cin, input);

  // fully-qualified duty cycle filename
  string InterpolFilename = "/xhome/jraines/ace/axlv2/DUTYCYCL.DAT";
  cout << "Enter duty cycle filename (full path):";
  cin >> input;
  InterpolFilename = input;
  cout << endl << InterpolFilename << "[end]" << endl;
  getline(cin, input);

  bool DoBoxrates   = true;
  cout << "Do boxrates calculation? ";
  cin >> DoBoxrates;
  getline(cin,input);
  cout << DoBoxrates << endl;

  bool DoSpillrates = true;
  cout << "Do spillrates calculation? ";
  cin >> DoSpillrates;
  getline(cin,input);
  cout << DoSpillrates << endl;

  float SRcutoff    = 0.03;
  cout << "SpillRates cutoff: ";
  cin >> SRcutoff;
  getline(cin,input);
  cout << SRcutoff << endl;

  int   SRmaxiter   = 5;
  cout << "SpillRates max. iterations: ";
  cin >> SRmaxiter;
  getline(cin,input);
  cout << SRmaxiter << endl;

  bool DoProbrates  = true;
  cout << "Do probrates calculation? ";
  cin >> DoProbrates;
  getline(cin,input);
  cout << DoProbrates << endl;

  bool OutputPslices = true;
  cout << "Output P slices? ";
  cin >> OutputPslices;
  getline(cin,input);
  cout << OutputPslices << endl;

  bool LoadPR       = false;
  cout << "Load probrates? ";
  cin >> LoadPR;
  getline(cin,input);
  cout << LoadPR << endl;

  bool SavePR       = true;
  cout << "Save probrates? ";
  cin >> SavePR;
  getline(cin,input);
  cout << SavePR << endl;

  float PRGaussCutoff = 3.0;
  cout << "Enter PR gauss cutoff: ";
  cin >> PRGaussCutoff;
  getline(cin,input);
  cout << PRGaussCutoff << endl;

  int FirstHSFe = 16;
  cout << "Enter state of first high-state Fe: ";
  cin >> FirstHSFe;
  getline(cin,input);
  cout << FirstHSFe << endl;

  float PRGaussCutoffHSFe = 3.0;
  cout << "Enter PR gauss cutoff for high-state Fe: ";
  cin >> PRGaussCutoffHSFe;
  getline(cin,input);
  cout << PRGaussCutoffHSFe << endl;

  bool DoDistfunc   = false;
  cout << "Do distribution function calculations? ";
  cin >> DoDistfunc;
  getline(cin,input);
  cout << DoDistfunc << endl;

  cout << endl << "***** End program control parameter input *****" << endl 
       << endl;
  /* ----------------------------------------------------------------------- */
  /* -------------------------- init variables ----------------------------- */
  /* ----------------------------------------------------------------------- */
  cout << thisprog << " -I- efficiencies will be read from " << EFF_DIR
       << "/" << endl;

  DbgLvl = gDbgLvl; // set local debugging level to global one

  AceSwicsConstants ASC;

  AnalysisData ad;
  ad.init(); // initialize ion arrays and other non-file dependent stuff
  loadIons(ad);

  setErrorLevels(ad);

  setPrGaussCutoff(PRGaussCutoff, FirstHSFe, PRGaussCutoffHSFe, ad);

  // dbg
  if (DbgLvl>=1){
    ad.print();
  }  

  char cdaterange[17];
  sprintf(cdaterange, "_%07d_%07d", StartYdoy, StopYdoy);
  string mafile = filebase + "_ma" + cdaterange + ".dat";

  vector<float> avewgt;
  avewgt.reserve(MAXEDB);
  avewgt.assign(MAXEDB, 0.0);

  vector<long> nwgt;
  nwgt.reserve(MAXEDB);
  nwgt.assign(MAXEDB, 0);

  // change date range to just start ydoy since prob. will not run over days
  sprintf(cdaterange, "_%07d", StartYdoy);

  // set flag if all-in-one timestep accumulation requested
  bool OnlyOneTimestep = false;
  if (NumMinToAccum == -1) OnlyOneTimestep = true;

  // open and initialize files

  FILE *BRF;
  if (DoBoxrates){
    string brfile = filebase + "_br" + cdaterange + ".dat";
    BRF = fopen(brfile.c_str(), "w+");
  }
  
  FILE *SRF;
  if (DoSpillrates){
    string srfile = filebase + "_sr" + cdaterange + ".dat";
    SRF = fopen(srfile.c_str(), "w+");
  }

  FILE *PRF;
  if (DoProbrates){
    string prfile = filebase + "_pr" + cdaterange + ".dat";
    PRF = fopen(prfile.c_str(), "w+");
  }

  FILE *DFF;
  FILE *NVTF;
  FILE *FILTERED_NVTF;
  FILE *D_NVTF;
  FILE *D_ELEMF;
  FILE *D_ELEMLAF;
  FILE *D_QRATF;
  FILE *QDISTF_TMP; 
  vector<FILE*> D_QDISTF;  // array of filehandles, one for each element
  if (DoDistfunc){
    string file;

    file = filebase + "_distfunc" + cdaterange + ".dat";
    DFF = fopen(file.c_str(), "w+");

    file = filebase + "_nvt" + cdaterange + ".dat";
    NVTF = fopen(file.c_str(), "w+");

    file = filebase + "_nvt_qf" + cdaterange + ".dat";
    if (DbgQualFilter) FILTERED_NVTF = fopen(file.c_str(), "w+");

    file = filebase + "_deliv_nvt" + cdaterange + ".dat";
    D_NVTF = fopen(file.c_str(), "w+");

    file = filebase + "_deliv_elem" + cdaterange + ".dat";
    D_ELEMF = fopen(file.c_str(), "w+");

    file = filebase + "_deliv_elem_la" + cdaterange + ".dat";
    D_ELEMLAF = fopen(file.c_str(), "w+");

    file = filebase + "_deliv_qratio" + cdaterange + ".dat";
    D_QRATF = fopen(file.c_str(), "w+");

    for (unsigned int i = 0; i < QDIST_ELEMENTS.size(); i++){
      file = filebase + "_deliv_" + QDIST_ELEMENTS[i] + 
	"_qdist" + cdaterange + ".dat";
      QDISTF_TMP = fopen(file.c_str(), "w+");
      D_QDISTF.push_back(QDISTF_TMP);
    }
  }

  // if dosumwhole is set Aspect Angle intervalls are determined and the corresponding 
  // files are created if not already existing. (should be put into function!) 
  if (dosumwhole){
    if (aspint){
      int tmp = int(15./aspint) + 1;
      cout << "tmp = " << tmp << endl;
      
      vector<float> asparr(tmp,0.);
      int tmp_aspangint;
      float tmp_aspang;
      set_asp_int(aspint,asparr);      
      if (1) {
	cout << "axlv2 : -D- " << endl;
	for (int i = 0; i < int(15./aspint) + 1; i++){
	  cout << "asparr[" << i << "] = " << asparr[i] << endl;
	}
      }

      char testexist[10];
      sprintf(testexist, "%04.1f-%04.1f", asparr[0], asparr[1]);
      string testexist_name;
      testexist_name = filebase + "_sumwhol_asp_" + testexist + ".dat";
      if (std::ifstream(testexist_name.c_str()).fail()){
	for (int i = 0; i < tmp-1; i++){
	  MeasurementArray data_asp_int;
	  string aspint_name;
	  char borders[10];
	  sprintf(borders, "%04.1f-%04.1f", asparr[i], asparr[i+1]);
	  cout << "borders = " << borders << endl;
	  aspint_name = filebase + "_sumwhol_asp_" + borders + ".dat";
	  data_asp_int.save(aspint_name);
	}
      }
    }
  }

  if (dosumspeed){
    MeasurementArray data_speedsum_int;
    string sumspeed_name; 
    char borders[10];
    sprintf(borders, "%04.0f-%04.0f", lowspeed, highspeed);	      
    sumspeed_name = filebase + "_sumspeed_" + borders + ".dat";
    if (std::ifstream(sumspeed_name.c_str()).fail()){
      data_speedsum_int.savespeed(sumspeed_name,0);
    }
  }


  /* ----------------------------------------------------------------------- */
  /* -------------------------- Accumulate Data ---------------------------- */
  /* ----------------------------------------------------------------------- */
  char tmpstring[256];  // tmp, for forming data filename
  bool FirstTimestep=true;  // true on first timestep only

  /* --- loop over days --- */
  long int CurYdoy = StartYdoy-1; // forces increment 1st time through
  bool DoneLoading = false;
  bool CycleWaiting = false;
  AceSwicsData swxdata_for_next_ts;

  // if dosumwhole is set true -> 
  
  double EndAccumCycleTime2 = 0;
  double StartAccumCycleTime = 0;

  while (! DoneLoading ){ // loop over timesteps

    cout << thisprog << " -I- accumulating PHAs from ydoy " 
	 << CurYdoy << endl;

    { // ensure MA goes out of scope with each timestep
    /* --- loop over accumulation period --- */
    using std::cerr; using std::flush;
    cerr << "Allocating MA..." << flush;
    MeasurementArray MA;  // array of counts/s for each tof,esd (for each edb)
    vector<MeasurementArray> MA_asp(2,MeasurementArray()); // arrays of counts for dosumwhole!
    vector<int> MA_aspint(2,-10); // intervalls correspond to MA_asp
    MeasurementArray MA_speedint;

    cerr << "ready." << endl;
    MA.setFilter(MAFilter);
    MA.setDoBRW(1);     // turn on basic rate weighting explicitly
    MA.setVelFilterFrac(VelFilter);

    // if dosumwhole -> initialize MA_asp;
    if (dosumwhole){
      for (int i = 0; i < 2; i++){
	MA_asp[i].setFilter(MAFilter);
	MA_asp[i].setDoBRW(0);     // turn on basic rate weighting explicitly
	MA_asp[i].setVelFilterFrac(VelFilter);
      }
    }

    if (dosumspeed){
      MA_speedint.setFilter(MAFilter);
      MA_speedint.setDoBRW(1);     // turn on basic rate weighting explicitly
      MA_speedint.setVelFilterFrac(VelFilter);
    }



    gAccumTime = 0.0;     // force to zero
    
    // set variables to load MA and run through PHA load once, if specified
    // NOTE: this ability is crucial for forward model modifications

    int NumCycLoaded = 0;
    float aspang =0.;
    double meanswspeed =0.;
    bool FirstLoadOfAccum = true;
    double CurrentCycleTime,EndAccumCycleTime = 0;
    StartAccumCycleTime = 0;

    //    while( (NumCycLoaded < NumMinToAccum) || OnlyOneTimestep){ // loop to spec.
    vector<double> aspang_cycle_time(120,0.);
    int numbercycle = -1;
    while( 1 || OnlyOneTimestep){ // loop to spec. cyc/timestep
      
      /* -- load PHAs and fill MA in block to save memory by destroying --
	 -- PHA vector and MA each time                                 -- */
      { // swxdata scope
	AceSwicsData swxdata;

	if (swxdata.loadNeedsNewFile()){
	  if (CurYdoy == StopYdoy) {
	    DoneLoading = true;
	    break;
	  }
	  else {
	    CurYdoy = incrementYdoy(CurYdoy);
	  }
      
	  // change filename
	  /* form filename, e.g. /home/acedata/LV1/2000/2000158.nc */
	  sprintf(tmpstring, "%s/%4d/%d.nc\0",LV1DIR.c_str(), 
		  CurYdoy/1000, CurYdoy);
	  gCurLv1File = (string) tmpstring;
	    
	  if (DbgLvl) {
	      cout << thisprog << " -I- using file " << gCurLv1File << endl;
	  }
	}

	// load an 1 cycles worth of PHAs if there are 
	// no cycles waiting
	int NumCycJustLoaded;
	if (CycleWaiting){
	  swxdata = swxdata_for_next_ts;
	  CycleWaiting = false;
	  NumCycJustLoaded = 1;
	  cout << thisprog << " -D- restored saved cycle (time="
	       << std::setprecision(12) << swxdata.getCycleTime()
	       << ")" << endl;
	}
	else {
	  swspeed=0.;
	  NumCycJustLoaded = swxdata.load(1,swspeed);
	}

	// skip the rest if these are met
	//if (swxdata.loadNeedsNewFile() || !(NumCycJustLoaded > 0)) continue;
	if (swxdata.loadNeedsNewFile()) continue;

	if (swxdata.loadFoundError()) {
	  break;  // error message below
	}
	numbercycle++;
	aspang_cycle_time[numbercycle] = swxdata.getCycleTime(); // store cycletimes to get aspangangles for dosumwhole
	// dbg only
	CurrentCycleTime = swxdata.getCycleTime();
	if (DbgLvl>=1){
	  cout << thisprog << " -D- current cycle time is "
	     << std::setprecision(12) << CurrentCycleTime << endl;
	}
	if (FirstLoadOfAccum){ // FIX: merge with others?
	  // N min. * 60 s/min = M seconds to accumulate
	  EndAccumCycleTime = CurrentCycleTime + NumMinToAccum * 60.;
	  EndAccumCycleTime2= CurrentCycleTime + (NumMinToAccum+1) * 60.;
	  StartAccumCycleTime = CurrentCycleTime;
	  // dbg only
	  if (DbgLvl>=1){
	    cout << thisprog << " -D- accumulating from " 
	       << std::setprecision(12) 
	       << CurrentCycleTime << " to " << std::setprecision(12) 
	       << EndAccumCycleTime << " in ss1970" << endl;
	  }
	}

	// check to see if within time period for this accumulation
	// if NOT within time period continue
	if (! OnlyOneTimestep) {
	  if (CurrentCycleTime > EndAccumCycleTime) {
	    cout << thisprog << " -D- saving cycle (src time=" 
		 << std::setprecision(12) << swxdata.getCycleTime()
		 << ", tgt time="
		 << std::setprecision(12) << swxdata_for_next_ts.getCycleTime()
		 << ")" << endl;
	    swxdata_for_next_ts = swxdata;

	    CycleWaiting = true;
	    break;
	  }
	}
	cout << thisprog << " -D- INCLUDED cycle with time "
	     << std::setprecision(12) << swxdata.getCycleTime() << endl;

	// Add to measurement array
	MA.fill(swxdata,ratesorcounts);
	if (1){
	    AceSwicsDutyCycle tmp_duty; // cycle time is in aspang_cycle_time
	    float tmp_aspang=0.;
	    tmp_duty.setExtAspectCommand(ExtAspectCommand);
	    tmp_duty.setAncillaryFilename(ace_ancil_name);      
	    tmp_duty.getNewAspectAngle(swxdata.getCycleTime());
	    tmp_aspang = tmp_duty.getAspectAngle();
	    aspang += 180. - ((tmp_aspang / (2. * 3.14159265)) * 360.);
	    meanswspeed +=swspeed;
	    if (DbgLvl>=0){
	      cout << "aspang_deg = " << aspang << endl;
	      cout << "swspeed    = " << meanswspeed << endl;
	    }
	}

	/* 
	   If dosumwhole is true -> determine aspect angle intervall of current cycle
	   and add cycle to corresponding MA_asp[*] (not if aspect angle is default 
	   value 3.06 rad == 4.66 deg.). First usable cycle determines first intervall
	   MA_aspint[0]. If during the day the aspect angle enters a new intervall, a 
	   second intervall MA_aspint[1] is set and the data is sortet to its corresponding
	   MA_asp[*]. If the for any reason the aspect angle enters a third or even more
	   intervalls for a single day the corresponding data is not summed up.(This case is
	   very unlikely to happen!)
	*/

	if (dosumwhole){
	  if (aspint){
	    
	    AceSwicsDutyCycle tmp_duty; // cycle time is in aspang_cycle_time
	    int tmp = int(15./aspint)+1;
	    vector<float> asparr(tmp,0.);
	    int tmp_aspangint;
	    float tmp_aspang;
	    
	    set_asp_int(aspint,asparr);
	    tmp_duty.setExtAspectCommand(ExtAspectCommand);
	    tmp_duty.setAncillaryFilename(ace_ancil_name);      
	    
	    tmp_duty.getNewAspectAngle(swxdata.getCycleTime());
	    tmp_aspang = tmp_duty.getAspectAngle();
	    tmp_aspang = 180. - ((tmp_aspang / (2. * 3.14159265)) * 360.);
	    if (DbgLvl>=1){
	      cout << "aspang_deg = " << tmp_aspang << endl;
	    }
	    tmp_aspangint = get_asp_int(aspint,asparr,tmp_aspang);
	    if (MA_aspint[0] == -10 && tmp_aspangint >= 0){
	      MA_aspint[0] = tmp_aspangint;
	    }
	    if (MA_aspint[0] != -10 && MA_aspint[1] == -10 && tmp_aspangint != MA_aspint[0] && tmp_aspangint >= 0){
	      MA_aspint[1] = tmp_aspangint;
	    }

	    
	    // fill data into temporary MA_asp[i] if actual cycles aspect angle is equal to MA_aspint[i]
	    for (int i = 0; i < 2 ; i++){
	      if (tmp_aspangint == MA_aspint[i] && (tmp_aspang <= 4.65 || tmp_aspang >= 4.75)) { 
		cout << i << " : MA_aspint[" << i << "] = " << MA_aspint[i] << " ; tmp_aspangint = " << tmp_aspangint << endl;
		MA_asp[i].fill(swxdata,ratesorcounts);
	      }
	    }
	    
	  }
	}

	// End dosumwhole

	// start sumspeedint
	if (dosumspeed){

	  // fill data into temporary MA_speedint if actual cycles swspeed is in defined interval
	  if ((swspeed>=lowspeed) && (swspeed<=highspeed)){
	    MA_speedint.fill(swxdata,ratesorcounts);
	    cyclesspeed++;
	  }
	}
	// end sumspeedint
	
	
	NumCycLoaded += NumCycJustLoaded;
	cout << thisprog << " -D- NumCycLoaded = " << NumCycLoaded << endl;



	// Load FM on first load of accumulation only
	vector<string> elem2correct;
	if (FirstLoadOfAccum){

	  if (FMType != -1){
	    /* All FM except 'none' need this.  This loads E/q table,
	       cycle time, and Doyfr.  Must only run on first load
	       because to keep cycle time at beginning of
	       accumulation.*/
	    ad.loadInstParam(swxdata);
	  }
	 
	  AxPhysicsFM pfm;
	  switch (FMType) {

	  case 6:  // *xfmexp + physics FM correction of Fe and S
	    cout << thisprog << " -I- using (local) *EXPERIMENTAL* FM" << endl;
	    ad.loadFMexp(swxdata);
	    elem2correct.clear();
	    elem2correct.push_back("Fe");
	    elem2correct.push_back("S");
	    correctFM_phys(ad, elem2correct, swxdata.getPav());
	    break;

	  case 5:  // libhef + physics FM correction of Fe and S
	    ad.loadFM(swxdata);
	    cout << thisprog << " -I- using libhef FM" << endl;
	    elem2correct.clear();
	    elem2correct.push_back("Fe");
	    elem2correct.push_back("S");
	    correctFM_phys(ad, elem2correct, swxdata.getPav());
	    break;

	  case 4:  // *xfmexp + physics FM correction of Fe*
	    cout << thisprog << " -I- using (local) *EXPERIMENTAL* FM" << endl;
	    ad.loadFMexp(swxdata);
	    elem2correct.clear();
	    elem2correct.push_back("Fe");
	    correctFM_phys(ad, elem2correct, swxdata.getPav());
	    break;

	  case 3:  // *only* physics FM
	    cout << thisprog << " -I- using physics FM" << endl;
	    pfm.load(ad, swxdata.getPav());
	    break;

	  case 2:  // libhef + physics FM correction of Fe
	    ad.loadFM(swxdata);
	    cout << thisprog << " -I- using libhef FM" << endl;
	    elem2correct.clear();
	    elem2correct.push_back("Fe");
	    correctFM_phys(ad, elem2correct, swxdata.getPav());
	    break;

	  case 1: // local (axlv2) copy of the libhef-like xfm
	    cout << thisprog << " -I- using (local) *EXPERIMENTAL* FM" << endl;
	    ad.loadFMexp(swxdata);

	  case 0: // *only* libhef FM
	    ad.loadFM(swxdata);
	    cout << thisprog << " -I- using libhef FM" << endl;
	    break;

	  case -1:// no FM (for creating new ions in FM)
	    cout << thisprog << " -W- no FM loaded (adding ions)" << endl;
	    break;

	  default:
	    cout << thisprog << " -F- invalid FM (" << FMType 
		 << ") selected" << endl;
	    break;
	  }

	}

	if (DbgLvl >= 2){
	  ad.print();
	}
	else if (DbgLvl >=3){
	  ad.dump();
	}
	

      } // swxdata passes out of scope
      
      FirstLoadOfAccum = false;
    } // end of loop to specified cycles/timestep 

    /* 
       If dosumwhole is true -> load file(s) that corresponds to MA_aspint[*]
       and add MA_asp[*]. Afterwards save file(s). Then the temporaly created
       Array data_asp_int is destroyed. Loading and saving takes a lot time.
       In order to save time only the data of whole day is added.
       USER SHOULD TAKE CARE THAT THE POSTACCELERATION VOLTAGE IS CONSTANT 
       DURING TIMEFRAME!!!
       (should be put into function)
    */

    if (dosumwhole){
      if (aspint){
	
	AceSwicsDutyCycle tmp_duty; // cycle time is in aspang_cycle_time
	int tmp = int(15./aspint)+1;
	vector<float> asparr(tmp,0.);

	set_asp_int(aspint,asparr);

	for (int i = 0; i < 2 ; i++){
	  if (MA_aspint[i] != -10){ 
	    MeasurementArray data_asp_int;
	    string aspint_name; 
	    char borders[10];
	    sprintf(borders, "%04.1f-%04.1f", asparr[MA_aspint[i]], asparr[MA_aspint[i]+1]);	      
	    aspint_name = filebase + "_sumwhol_asp_" + borders + ".dat";
	    data_asp_int.load(aspint_name);
	    data_asp_int.add(MA_asp[i]);
	    data_asp_int.save(aspint_name);
	  }
	  else if (i == 0){
	    cout << "Aspect Angle is default 3.06 rad for whole day -> Day is not added to sum!" << endl;
	  }
	  else{
	    cout << "Whole day falls into one intervall" << endl; 
	  }
	}
      }
    }

    // dosumwhole ends here

    if (dosumspeed){
      MeasurementArray data_asp_int;
      string sumspeed_name; 
      char borders[10];
      int tmp_cycles;
      sprintf(borders, "%04.0f-%04.0f", lowspeed, highspeed);	      
      sumspeed_name = filebase + "_sumspeed_" + borders + ".dat";
      data_asp_int.loadspeed(sumspeed_name,tmp_cycles);
      data_asp_int.add(MA_speedint);
      cyclesspeed=tmp_cycles+cyclesspeed;
      data_asp_int.savespeed(sumspeed_name,cyclesspeed);
    }


    // switch to loaded MA if specifed

    // do not continue processing if no cycles were loaded into MA
    /* note: This occurs at end of file under certain conditions
       because libhef reports EOF only after trying to read *past*
       it */
    if (NumCycLoaded <= 0) break;

    /* ----------------------------------------------------------------- */
    /* ------------------------ Calculate Rates ------------------------ */
    /* ----------------------------------------------------------------- */
    // separate integer and fraction part in doyfr for use in 
    // output file names
    // FIX: doyfr on multiple day run should be first or last one?
    string doy_fr = doyfr2doy_fr_str(ad.Doyfr);

    BoxRates BR(ad.Ions.size());
    if (DoBoxrates){
      if (DbgLvl >= 1)
	cout << thisprog << " -I- calc. box rates for " << doy_fr << endl;
      BR.calc(&MA, ad.Ions);
    }
    SpillRates SR(ad.Ions.size());
    if (DoSpillrates){
      if (DbgLvl >= 1)
	cout << thisprog << " -I- calc. spill. rates for " << doy_fr << endl;
      SR.setNegRateCutoff(SRcutoff);
      SR.setMaxIterations(SRmaxiter);
      SR.calc(ad.Ions, BR);
    }
    ProbRates  PR(ASC, ad.Ions.size());
    if (DoProbrates){
      if (DbgLvl >= 1)
	cout << thisprog << " -I- calc. prob. rates for " << doy_fr << endl;

      PR.setMethod(3);
      PR.setOutputPslices(OutputPslices);
      //PR.setGaussCutOff(PRGaussCutoff);

      PR.registerACSum();
      //PR.registerACSlice("O2+",20, ad);
      //PR.registerACSlice("O6+",24, ad);
      PR.registerACElem("O",10,48,ad);
      //PR.registerACElem("C",10,50,ad);
      //PR.registerACElem("He",10,50,ad);
	  
      PR.calc(ad.Ions, MA, SR);
    }
    /* ----------------------------------------------------------------- */
    /* ------ Calculate distribution function and state variables ------ */
    /* ----------------------------------------------------------------- */
    DistFunc  DF(ad.Ions.size());
    if (DoDistfunc){
      if (DbgLvl >= 1)
	cout << thisprog << " -I- calc. dist. func. for " << doy_fr << endl;
      AceSwicsDutyCycle duty; // cycle time is in ad
      duty.setExtAspectCommand(ExtAspectCommand);
      duty.setInterpolFilename(InterpolFilename);
      duty.setAncillaryFilename(ace_ancil_name);      
      cout << "ancil_name = " << duty.getAncillaryFilename() << endl;

      UlyssesSwicsEffic eff;
      eff.setEfficDirectory(EFF_DIR);

      DF.calc(ad.Ions, ad, PR, duty, eff);
    }

    /* ----------------------------------------------------------------- */
    /* ----------------------- output results -------------------------- */
    /* ----------------------------------------------------------------- */
    if (OutputET) {
      string start=cycletimetodate(StartAccumCycleTime);
      string end=cycletimetodate(EndAccumCycleTime2);
      string file = filebase+"_et_slices_"+start+"_"+end+".dat";
      MA.outputETslices(file, start, end, ad, NumCycLoaded, aspang/float(NumCycLoaded), double(meanswspeed/double(NumCycLoaded)));
    }
    // output fmc info regardless; it is small and used by other things
    /* FIX:  This file will be repeatedly overwritten at each
       doyfr step.  This is not very time eff. and should be
       corrected. */
    string file = filebase + "_fmcomp.dat";
    ad.outputFM(file);

    if (OutputMMQ) {
      string file = filebase + "_mmq_" + doy_fr + ".dat";
      MA.outputMMQ(file, StartYdoy, StopYdoy, ad,
		   mm0, mm1, mq0, mq1);

    }
    // output fmc info regardless; it is small and used by other things
    /* FIX:  This file will be repeatedly overwritten at each
       doyfr step.  This is not very time eff. and should be
       corrected. */
    file = filebase + "_mmq_fmc.dat";
    MA.outputMMQfmc(file, ad);

    /* --- append to boxrates/edb/hour --- */
    if (DoBoxrates) {
      BR.output(BRF, ad.Doyfr, ad);
    }

    // append to spillrates/edb/hour
    if (DoSpillrates){
      SR.output(SRF, ad.Doyfr, ad);
    }
	
    // write out some ProbRates items for this timestep
    if (DoProbrates){
      // append to probrates/edb/hour
      PR.output(PRF, ad.Doyfr, ad);

      // write out centers to file
      string file = filebase + "_pccomp_" + doy_fr + ".dat";
      PR.outputProbCenters(file, ad);

      // output selected assigned counts slices to file
      file = filebase + "_ac_" + doy_fr + ".dat";
      PR.outputACSlices(file);

      // output selected assigned counts slices to file (MMQ units, summed)
      file = filebase + "_acmmq_elem_" + doy_fr + ".dat";
      PR.outputACElemMMQ(file, ad, MA, mm0, mm1, mq0, mq1);

      // output selected assigned counts slices to file (MMQ units, summed)
      file = filebase + "_acmmq_" + doy_fr + ".dat";
      PR.outputACSumMMQ(file, ad, MA, mm0, mm1, mq0, mq1);
    }
	
    // append to LV2 output file
    if (DoDistfunc){
      DF.outputDF(DFF, ad.Doyfr, ad);
      DF.outputNVT(NVTF, ad.Doyfr, ad);

      // WARNING:  Class-wide NVT values are now filtered (set to fill) 
      // by quality
      DF.filterNvtByQuality(ad);

      // output NVT again, this time filtered
      if (DbgQualFilter) DF.outputNVT(FILTERED_NVTF, ad.Doyfr, ad);

      /* Remove (by setting to FILL) ions with extended charge states
	 (beyond that which is delivered to ASC) to make
	 autoproduction safer. */
      DF.keepOnlyDeliv(ad, "C",4.0,6.0);
      DF.keepOnlyDeliv(ad, "N",5.0,7.0);
      DF.keepOnlyDeliv(ad, "O",5.0,8.0);
      DF.keepOnlyDeliv(ad, "Ne",6.0,9.0);
      DF.keepOnlyDeliv(ad, "Mg",6.0,12.0);
      DF.keepOnlyDeliv(ad, "Si",6.0,12.0);
      DF.keepOnlyDeliv(ad, "S",6.0,14.0);
      DF.keepOnlyDeliv(ad, "Fe",6.0,20.0);

      DF.outputDelivNVT(D_NVTF, ad.Doyfr, ad);
      DF.outputDelivElemAbun(D_ELEMF, ad.Doyfr, ad);
      DF.outputDelivElemAbunLA(D_ELEMLAF, ad.Doyfr, ad);
      DF.outputDelivQRatio(D_QRATF, ad.Doyfr, ad);
      for (unsigned int i = 0; i < QDIST_ELEMENTS.size(); i++){
	DF.outputDelivQDist(D_QDISTF[i], ad.Doyfr, ad, QDIST_ELEMENTS[i]);
      }
    }
	
    FirstTimestep = false;  // first timestep is finished

    } // MA scope block

    // force quit for debug
    //    DoneLoading = true;
    //cout << thisprog << " -D- hardcoded forced quit after 1 timestep" <<endl;

  } // end of loop over timesteps

  //ad.outputFM();



  if (DoBoxrates) fclose(BRF);
  if (DoSpillrates) fclose(SRF);
  if (DoProbrates) fclose(PRF);
  if (DoDistfunc) {
    fclose(DFF); 
    fclose(NVTF);
    if (DbgQualFilter) fclose(FILTERED_NVTF);
 
    fclose(D_NVTF);
    fclose(D_ELEMF);
    fclose(D_ELEMLAF);
    fclose(D_QRATF);
    for (unsigned int i = 0; i < QDIST_ELEMENTS.size(); i++){
      fclose(D_QDISTF[i]);
    }
  }

  cout << "axlv2 -I- successfully completed processing" << endl;
  
  }
  catch(std::exception &e){
    cout << thisprog << " -F- " << e.what() << endl;
  }

  return(0);
}  
