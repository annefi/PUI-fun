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
    
  Revision controlled by CVS:
  $Id: axlv2_shock.cc,v 1.2 2005/02/21 21:46:33 jraines Exp $
  
  Major Modification History:
    12Jun2003   jmr   Adapted from axlv2.cc

*/

#include "swindal.h"
#include "axlv2.h"
#include <iomanip>

int main(int argc, char* argv[]){
  char thisprog[] = "axlv2_shock";
  string rcs_id = "$Id: axlv2_shock.cc,v 1.2 2005/02/21 21:46:33 jraines Exp $";

  using std::cin;

  // print banner
  printf("%s -I- This is the ACE/SWICS Level 2 Data Processor,\n",thisprog);
  printf("          built %s %s\n\n",__DATE__,__TIME__);
  
  initSwindal();  // initializes global variables

  /* ----------------------------------------------------------------------- */
  /*                     ===> adjustable parameters <===                     */
  /* ----------------------------------------------------------------------- */

  // local debugging level
  int DbgLvl = 1;  // set to gDbgLvl later

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
  if (DbgLvl > 2){
    cout << thisprog << " -D- dumping args:" << endl;
    for (int i = 0; i < argc; i++){
      cout << "argv[" << i << "]=" << argv[i] << endl;
    }
  }

  // FIX: someday put in sophisticated argument processing
  switch (argc) {
  case 1:
    // no arguments, just the program name
    break;
  case 2:
    if ( strcmp(argv[1],"--versions") == 0) {
      showVersions();
      exit(0);
    }
    break;
  case 3:
    break;
  default:
    ;
  }

  /* ----------------------------------------------------------------------- */
  /* ------------------------ Get Input Parameters ------------------------- */
  /* ----------------------------------------------------------------------- */
  // ===> Change this whenever the sequence of inputs (below) is changed! <===
  float InputSeqVersion = 3.5;
  
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

  bool LoadMA = true; // true means load instead of fill from LV1 data
  cout << "Load Measurement Array (true or false)? ";
  cin >> LoadMA;
  getline(cin,input);  // reads through the comments
  cout << LoadMA << endl;

  bool SaveMA = false;// true means save MA after filling
  cout << "Save Measurement Array when finished (true or false)? ";
  cin >> SaveMA;
  getline(cin,input);  // reads through the comments
  cout << SaveMA << endl;

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

  long int StartYdoy = 2000158;
  cout << "Enter start date (yyyydoy): ";
  cin  >> StartYdoy;
  getline(cin,input);
  cout << StartYdoy << endl;

  long int StopYdoy  = 2000158;
  cout << "Enter stop date (yyyydoy): ";
  cin  >> StopYdoy;
  getline(cin,input);
  cout << StopYdoy << endl;

  long int StartScet;
  cout << "Enter start SCET (ss1970): ";
  cin  >> StartScet;
  getline(cin,input);
  cout << StartScet << endl;

  long int StopScet;
  cout << "Enter stop SCET (ss1970): ";
  cin  >> StopScet;
  getline(cin,input);
  cout << StopScet << endl;

  long int SkipScet;
  cout << "Enter SCET (ss1970) to skip: ";
  cin  >> SkipScet;
  getline(cin,input);
  cout << SkipScet << endl;

  /* Number of cycles to analyze at a time */
  int NumCycAtOnce = 5; // 5-10 cycles is reasonable
  cout << "Enter number of cycles to load into RAM at once: ";
  cin >> NumCycAtOnce;
  getline(cin,input);
  cout << NumCycAtOnce << endl;

  int NumCycToAccum; // 10 -> 2hr resolution
  cout << "Enter number of cycles to accumulate per timestep (-1 => inf): ";
  cin >> NumCycToAccum;
  getline(cin,input);
  cout << NumCycToAccum << endl;

  cout << "Enter global debugging level (0-5): ";
  cin >> gDbgLvl;
  getline(cin,input);
  cout << gDbgLvl << endl;

  // FIX:  The length of this is fixed; it should not be.
  char LV1DIR[] = "/shrg1/ace/LV1";
  cout << "Enter directory containing LV1 data organized into yearly subdirectories: ";
  cin >> input;
  strcpy(LV1DIR, input.c_str());
  cout << endl << LV1DIR  << endl;
  getline(cin,input);

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
  DbgLvl = gDbgLvl; // set local debugging level to global one

  AceSwicsConstants ASC;

  AnalysisData ad;
  ad.setRange0(MAFilter & 1);  // add range 0 ions if incl. in filter
  ad.init(); // initialize ion arrays and other non-file dependent stuff

  setPrGaussCutoff(PRGaussCutoff, FirstHSFe, PRGaussCutoffHSFe, ad);

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
  if (NumCycToAccum == -1) OnlyOneTimestep = true;

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
  FILE *D_NVTF;
  FILE *D_ELEMF;
  FILE *D_QRATF;
  FILE *QDISTF_TMP; 
  vector<FILE*> D_QDISTF;  // array of filehandles, one for each element
  if (DoDistfunc){
    string file;

    file = filebase + "_distfunc" + cdaterange + ".dat";
    DFF = fopen(file.c_str(), "w+");

    file = filebase + "_nvt" + cdaterange + ".dat";
    NVTF = fopen(file.c_str(), "w+");

    file = filebase + "_deliv_nvt" + cdaterange + ".dat";
    D_NVTF = fopen(file.c_str(), "w+");

    file = filebase + "_deliv_elem" + cdaterange + ".dat";
    D_ELEMF = fopen(file.c_str(), "w+");

    file = filebase + "_deliv_qratio" + cdaterange + ".dat";
    D_QRATF = fopen(file.c_str(), "w+");

    for (unsigned int i = 0; i < QDIST_ELEMENTS.size(); i++){
      file = filebase + "_deliv_" + QDIST_ELEMENTS[i] + 
	"_qdist" + cdaterange + ".dat";
      QDISTF_TMP = fopen(file.c_str(), "w+");
      D_QDISTF.push_back(QDISTF_TMP);
    }
  }

  /* ----------------------------------------------------------------------- */
  /* -------------------------- Accumulate Data ---------------------------- */
  /* ----------------------------------------------------------------------- */
  char tmpstring[150];  // tmp, for forming data filename
  bool FirstTimestep=true;  // true on first timestep only

  /* --- loop over days --- */
  long int CurYdoy = StartYdoy-1; // forces increment 1st time through
  bool DoneLoading = false;
  while (! DoneLoading ){ // loop over timesteps

    cout << thisprog << " -I- accumulating PHAs from ydoy " 
	 << CurYdoy << endl;

    { // ensure MA goes out of scope with each timestep
    /* --- loop over through accumulation period --- */
    MeasurementArray MA;  // array of counts/s for each tof,esd (for each edb)
    MA.setFilter(MAFilter);
    MA.setDoBRW(1);     // turn on basic rate weighting explicitly
    MA.setVelFilterFrac(VelFilter);
    gAccumTime = 0.0;     // force to zero

    // set variables to load MA and run through PHA load once, if specified
    MeasurementArray loaded_MA;
    if (LoadMA) {
      DoneLoading = true;
      NumCycToAccum = NumCycAtOnce;
      OnlyOneTimestep = false;
      loaded_MA.load(mafile);
    }

    int NumCycLoaded = 0;
    bool FirstLoadOfAccum = true;
    while( (NumCycLoaded < NumCycToAccum) || OnlyOneTimestep){ // loop to spec.
                                                               // cyc/timestep

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
	  sprintf(tmpstring, "%s/%4d/%d.nc\0",LV1DIR, CurYdoy/1000, CurYdoy);
	  gCurLv1File = (string) tmpstring;
	    
	  if (DbgLvl) {
	      cout << thisprog << " -I- using file " << gCurLv1File << endl;
	  }
	}

	// load an NumCycAtOnce cycles worth of PHAs
	int NumCycJustLoaded = swxdata.load(NumCycAtOnce);

	// skip the rest if these are met
	if (swxdata.loadNeedsNewFile() || !(NumCycJustLoaded > 0)) continue;

	if (swxdata.loadFoundError()) {
	  break;  // error message below
	}

	// fast-forward feature (a crude one!)
	Pha pha = swxdata.getPha(0);
	if (pha.scet < StartScet || pha.scet == SkipScet) {
	  cout << thisprog << " -I- skipping scet " << std::setprecision(13)
			<< pha.scet << endl;
	  continue;
	}
	if (pha.scet == StopScet) {
	  // StopScet was last scet to keep so do not keep this one and 
	  // jump out to rest of timestep processing
	  cout << thisprog 
	       << " -I- stopping processing with this cycle (scet=" 
	       << std::setprecision(13) << pha.scet << ")" << endl;
	  DoneLoading = true; 
	  break;  // bypasses MA.fill and gets on with processing 
	          // so this cycle is not included
	}

	// Add to measurement array
	MA.fill(swxdata);

	NumCycLoaded += NumCycJustLoaded;

	if (FirstLoadOfAccum && (FMType != -1)){  
	  /* All FM except 'none' need this.  This loads E/q table,
	     cycle time, and Doyfr.  Must only run on first load
	     because to keep cycle time at beginning of
	     accumulation.*/
	  ad.loadInstParam(swxdata);
	}

	// Load FM on first load of first timestep only
	if (FirstLoadOfAccum && FirstTimestep){

	  AxPhysicsFM pfm;
	  switch (FMType) {

	  case 4:  // *xfmexp + physics FM correction of Fe*
	    cout << thisprog << " -I- using (local) *EXPERIMENTAL* FM" << endl;
	    ad.loadFMexp(swxdata);
	    correctFeFM_phys(ad, swxdata.getPav());
	    cout << thisprog 
		 << " -I- manually correcting Fe with physics FM" << endl;
	    break;
	  case 3:  // *only* physics FM
	    cout << thisprog << " -I- using physics FM" << endl;
	    pfm.load(ad, swxdata.getPav());
	    break;

	  case 2:  // libhef + physics FM correction of Fe
	    ad.loadFM(swxdata);
	    cout << thisprog << " -I- using libhef FM" << endl;
	    correctFeFM_phys(ad, swxdata.getPav());
	    cout << thisprog 
		 << " -I- manually correcting Fe with physics FM" << endl;
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

	  // should not be needed here
	  //FirstTimestep = false;
	}

	if (DbgLvl >= 2) ad.dump();

      } // swxdata passes out of scope
      
      FirstLoadOfAccum = false;
    } // end of loop to specified cycles/timestep 

    // switch to loaded MA if specifed
    if (LoadMA) MA = loaded_MA;

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
      //PR.registerACElem("O",10,48,ad);
      PR.registerACElem("C",10,50,ad);
	  
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
      DF.calc(ad.Ions, ad, PR, duty);
    }

    /* ----------------------------------------------------------------- */
    /* ----------------------- output results -------------------------- */
    /* ----------------------------------------------------------------- */
    if (OutputET) {
      string file = filebase + "_et_slices_" + doy_fr + ".dat";
      MA.outputETslices(file, StartYdoy, StopYdoy, ad);
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
      outputBR(BRF, ad.Doyfr, BR, ad);
    }

    // append to spillrates/edb/hour
    if (DoSpillrates){
      outputSR(SRF, ad.Doyfr, SR, ad);
    }
	
    // write out some ProbRates items for this timestep
    if (DoProbrates){
      // append to probrates/edb/hour
      //	  outputPR(PRF, doyfr, PR, ad);
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

      DF.outputDelivNVT(D_NVTF, ad.Doyfr, ad);
      DF.outputDelivElemAbun(D_ELEMF, ad.Doyfr, ad);
      DF.outputDelivQRatio(D_QRATF, ad.Doyfr, ad);
      for (unsigned int i = 0; i < QDIST_ELEMENTS.size(); i++){
	DF.outputDelivQDist(D_QDISTF[i], ad.Doyfr, ad, QDIST_ELEMENTS[i]);
      }
    }
	
    if (SaveMA) MA.save(mafile);

    FirstTimestep = false;  // first timestep is finished

    } // MA scope block

  } // end of loop over timesteps

  if (DoBoxrates) fclose(BRF);
  if (DoSpillrates) fclose(SRF);
  if (DoProbrates) fclose(PRF);
  if (DoDistfunc) {
    fclose(DFF); 
    fclose(NVTF);
 
    fclose(D_NVTF);
    fclose(D_ELEMF);
    fclose(D_QRATF);
    for (unsigned int i = 0; i < QDIST_ELEMENTS.size(); i++){
      fclose(D_QDISTF[i]);
    }
  }

  return(0);
}  
