#include "swindal.h"
#include "axlv2.h"
#include <iomanip>

int main(){
  // variables which will be defined in axlv2
  string thisprog = "axlv2_devel";
  int NumCycAtOnce = 5;
  int NumCycToAccum = 5;
  float StartYdoy = 2001094;
  float StopYdoy  = 2001094;
  double CenterYdoy = 2001094.5979;
  int DbgLvl = 1;
  char LV1DIR[] = "/shrg1/ace/LV1";
  char tmpstring[150];  // tmp, for forming data filename
  bool OnlyOneTimestep = false;

  AnalysisData ad;
  ad.setRange0(1);  // add range 0 ions if incl. in filter
  ad.init(); // initialize ion arrays and other non-file dependent stuff

  /* --- build array of cycle times for center-based running --- */
  gAccumTime = 0.0;     // force to zero
  vector<double> doyfrs;
  vector<long> scets;
  long int CurYdoy = StartYdoy-1; // forces increment 1st time through
  int Year = 0;
  bool DoneLoading = false;
  int NumCycLoaded = 0;
  while (! DoneLoading){
    {
      AceSwicsData swxdata;
	
      if (swxdata.loadNeedsNewFile()){
	if (CurYdoy == StopYdoy) {
	  DoneLoading = true;
	  swxdata.closeFile();
	  break;
	}
	else {
	  CurYdoy = incrementYdoy(CurYdoy);
	  Year = static_cast<int>(CenterYdoy/1000.);
	  cout << "Year=" << Year << " CenterYdoy=" 
	       << std::setprecision(13) << CenterYdoy << endl;
	}
      
	// change filename
	/* form filename, e.g. /home/acedata/LV1/2000/2000158.nc */
	sprintf(tmpstring, "%s/%4d/%d.nc\0",LV1DIR, CurYdoy/1000, CurYdoy);
	gCurLv1File = (string) tmpstring;
	    
	if (DbgLvl) {
	  cout << thisprog << " -I- using file " << gCurLv1File << endl;
	}
      }
      
      // load an AnalysisInterval cycles worth of PHAs
      int NumCycJustLoaded = swxdata.load(1);

      // skip the rest if these are met
      if (swxdata.loadNeedsNewFile() || !(NumCycJustLoaded > 0)) continue;

      if (swxdata.loadFoundError()) {
	break;  // error message below
      }

      NumCycLoaded += NumCycJustLoaded;

      ad.loadInstParam(swxdata);

      Pha pha = swxdata.getPha(0);
      scets.push_back(pha.scet);

      doyfrs.push_back(static_cast<double>(Year)*1e3+ad.Doyfr);

    }
    
  }


  /* ----------------------------------------------------------------------
     determine start, stop and skip
     ---------------------------------------------------------------------- */
  cout << thisprog << " -D- finding CenterYdoy (" << CenterYdoy
       << ") in doyfr array:" << endl;
  int center_cycle = 0;
  for (int idoyfr = 0; idoyfr < doyfrs.size(); idoyfr++){
    cout << "+ checking doyfrs[" << idoyfr << "]=" << std::setprecision(13) 
	 << doyfrs[idoyfr] << endl;
    
    if (doyfrs[idoyfr] > CenterYdoy){
      cout << "+ ++++++++ found it ++++++++" << endl;
      center_cycle = idoyfr;
      break;
    }
  }

  cout << "+ done!" << endl;
  cout << thisprog << " -D- CenterYdoy ("
       << std::setprecision(13) << CenterYdoy 
       << ") is between cycles " << center_cycle-1 << " and " 
       << center_cycle << " in doyfr array:" << endl;

  double start_ydoyfr, stop_ydoyfr;

  int skip_cycle = center_cycle - 1;
  int start_cycle = skip_cycle - NumCycToAccum*2;
  int stop_cycle = skip_cycle + NumCycToAccum*2; 

  long skip_scet = scets[skip_cycle];
  long start_scet = scets[start_cycle];
  long stop_scet = scets[stop_cycle];

  if (start_cycle > 0)
    start_ydoyfr = doyfrs[start_cycle];
  if (stop_cycle < doyfrs.size())
    stop_ydoyfr = doyfrs[stop_cycle];
    
  cout << "axlv2 should be run between " << std::setprecision(13) 
       << start_ydoyfr 
       << "(cycle=" <<  start_cycle << ")"
       << " and " << std::setprecision(13) << stop_ydoyfr
       << "(cycle=" <<  stop_cycle << "), skipping cycle(s) " 
       << skip_cycle << " (scet=" << skip_scet << ")" << endl;

  cout << "start_scet=" << start_scet
       << " stop_scet=" << stop_scet
       << " skip_scet=" << skip_scet << endl;

  /* ----------------------------------------------------------------------
     load for real
     ---------------------------------------------------------------------- */
  /* --- loop over days --- */
  CurYdoy = StartYdoy-1; // forces increment 1st time through
  DoneLoading = false;
  while (! DoneLoading ){

    MeasurementArray MA;  // array of counts/s for each tof,esd (for each edb)
    int NumCycLoaded = 0;
    while( (NumCycLoaded < NumCycToAccum) || OnlyOneTimestep ){

      {
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

	// load an AnalysisInterval cycles worth of PHAs
	int NumCycJustLoaded = swxdata.load(NumCycAtOnce);
	// --- skip the rest if these are met
	if (swxdata.loadNeedsNewFile() || !(NumCycJustLoaded > 0)) continue;
	// --- error found, exit
	if (swxdata.loadFoundError()) {
	  break;  // error message below
	}

	// fast-forward feature (a crude one!)
	Pha pha = swxdata.getPha(0);
	if (pha.scet <= start_scet || pha.scet == skip_scet) {
	  cout << "***skipping scet" << pha.scet << endl;
	  continue;
	}
	if (pha.scet >= stop_scet) {
	  DoneLoading = true; 
	  break;
	}

	// Add to measurement array
	cout << thisprog << " -I- filling MA... " << endl;
	MA.fill(swxdata);

	NumCycLoaded += NumCycJustLoaded;
      }

    }

    //********************rest of timestep work here*************************

  }
 
  //******************rest of main here********************

}
