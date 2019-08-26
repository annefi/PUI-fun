/*
  File:  TofMeasurementArray.h

  Description:
    Header file for TofMeasurementArray class. This purpose of this
    class is to provide an intelligent container for time of flight
    (TOF) spectra.  It has facilities for specifying filters on the
    input PHA data, extracting parts of the data and file I/O.  It
    automatically handles merging multiple adjacent channels to create arrays
    of reduced resolution.

  Author(s): Jim Raines (jmr)

  Method:

  Revision controlled by CVS:
  $Id: TofMeasurementArray.cc,v 1.4 2004/07/28 13:28:35 jraines Exp $

  Major Modification History:
    01Mar2004   jmr   initial coding

*/
#include "swindal.h"

TofMeasurementArray::TofMeasurementArray(InstrumentConstants& ic,
					      int size=0){
  if (size == 0) size = ic.getNumTofCh();

  // initialize array
  TNT::Vector<float> tmp(size, 0.0);
  for (int i = 0; i < ic.getNumEdb(); i++){
    TMA.push_back(tmp);
  }
  ResolScalar = ic.getNumTofCh()/size;

  // set up defaults
  doBRW = false;
  useRates = false;
  dumpPhaFlag = false;

  // save this for later
  IC = ic;
}

// Weird results when this constructor called the other one.
// TofMeasurementArray::TofMeasurementArray(InstrumentConstants& ic){
//   TofMeasurementArray(ic, ic.getNumTofCh());
// }

bool TofMeasurementArray::goodNedb(int nedb) const {
  if (nedb < static_cast<int>(TMA.size())){
    return(true);
  }
  else {
    if (gDbgLvl >= 1){
      cout << "TofMeasurementArray::goodNedb -E- nedb (" << nedb
	   << ") out of range (0.." << TMA.size() << ")" << endl;
    }
    return(false);
  }    
}

bool TofMeasurementArray::goodTofch(int tofch) const {
    if (tofch < static_cast<int>(TMA[0].size())){
      return(true);  // return good value
    }
    else {
      if (gDbgLvl >= 1){
	cout << "TofMeasurementArray::goodTofch -E- tofch (" << tofch
	     << ") out of range (0.." << TMA[0].size() << ")" << endl;
      }
      return(false);
    }
}

int TofMeasurementArray::fill(AnalysisData2& ad, AceSwimsData& id){
  const string thisprog = "TofMeasurementArray::fill";

  // current PHA word
  AceSwimsPha* pha;

  if (gDbgLvl >= 1) {
    cout << thisprog << " -I- filling..." << endl;
  }

  /* --- change elements of TMA from rates to counts --- */
  /* -------------------------------------------------- */
  bool useRates = false; // temporary
  if (useRates){
    for (int nedb = ad.ic.getFirstEdb(); nedb < ad.ic.getNumEdb(); nedb++){
      for (int tofch = 0; tofch < ad.ic.getNumTofCh(); tofch++){
	TMA[nedb][tofch] = TMA[nedb][tofch] * ad.getAccumTime();
      }
    }
  }

  /* --- count PHA words with tof (channels) and nedb --- 
     ---------------------------------------------------- */
  int npha_tot  = 0;  // number of pha read from InstrumentData object
  int npha_used = 0;  // number of pha in analyzed for filling into MA

  // set up PHA dump output files
  FILE *DUMP_USED;
  FILE *DUMP_DISC;
  if (dumpPhaFlag) {
    AceSwimsPha pha;
    string file = DumpPhaFile + "_pha_used.dat";
    DUMP_USED = fopen(file.c_str(), "a");
    pha.dumpHeaders(DUMP_USED);
    file = DumpPhaFile + "_pha_discarded.dat";
    DUMP_DISC = fopen(file.c_str(), "a");
    pha.dumpHeaders(DUMP_DISC);
  }    

  for (int npha = 0; npha < id.getNumPha(); npha++){ // loop over PHA
    pha = id.getPha(npha);
    npha_tot++;

    /* Check to see if pha should be added to TMA.  All these tests must
       return true for this to happen. */
    // --- filters
    bool pha_ok = true;
    for (unsigned int nfilter = 0; nfilter < Filters.size(); nfilter++){
      pha_ok = (pha_ok & Filters[nfilter]->passFilter(*pha));
    }
    // --- bounds
    pha_ok = (pha_ok & goodNedb(pha->nedb));
    pha_ok = (pha_ok & goodTofch(pha->tofch/ResolScalar));

    if (pha_ok){

      // actually increments counts
      if (doBRW){
	TMA[pha->nedb][pha->tofch/ResolScalar] += pha->weight;
      }
      else{
	TMA[pha->nedb][pha->tofch/ResolScalar] += 1.0;
      }

      npha_used++;
      if (dumpPhaFlag)
	pha->dump(npha, -1, DUMP_USED);
    }
    else{
      if (dumpPhaFlag)
	pha->dump(npha, -1, DUMP_DISC);
    }      
  }

  if (gDbgLvl >= 1){
    float used_percent = 100.0 * static_cast<float>(npha_used) / 
      static_cast<float>(npha_tot);
    cout << thisprog << " -I- " << npha_used << " of " << npha_tot
	 << " pha used to fill array ("
	 << used_percent << "%)"  << endl;
  }


  /* --- determine accumulation time for PHAs just added ---
     ------------------------------------------------------- */
  pha = id.getPha(id.getNumPha() - 1);
  double timeInterval;  // seconds between first and last PHA
  timeInterval = pha->scet;
  if (gDbgLvl >= 3) {
    cout.precision(12);
    cout << thisprog << "-D- end_time=" << pha->scet << endl;
    cout.precision(6);
  }

  pha = id.getPha(0);
  if (gDbgLvl >= 3) {
    cout.precision(12);
    cout << thisprog << "-D- start_time=" << pha->scet << endl;
    cout.precision(6);
  }

  timeInterval = timeInterval - pha->scet;

  /* Differences between cycle times will not include time for the last
     cycle read.  Therefore, add a typical cycle time to the calc. interval.
  */
  timeInterval += ad.ic.getNomCycleTime();

  ad.setAccumTime(ad.getAccumTime() + static_cast<float>(timeInterval));

  if (gDbgLvl >= 2) {
    cout << thisprog << " -D-"
	 << " timeInterval=" << timeInterval 
	 << " AccumTime=" << ad.getAccumTime()
	 << endl;
  }

  /* --- transform elements of MA back from counts to rates --- 
     ---------------------------------------------------------- */
  if (useRates){
    for (int nedb = ad.ic.getFirstEdb(); nedb < ad.ic.getNumEdb(); nedb++){
      for (int tofch = 0; tofch < ad.ic.getNumTofCh(); tofch++){
	TMA[nedb][tofch] = TMA[nedb][tofch] / ad.getAccumTime();
      } // loop over tofch
    } // loop over EDBs
  }

  if (dumpPhaFlag) {
    fclose(DUMP_USED);
    fclose(DUMP_DISC);
  }

  return(npha_used);
}

// int TofMeasurementArray::registerPhaFilter( const PhaFilter& f){
//   Filters.push_back(f);
//   return(Filters.size());
// }
//int TofMeasurementArray::registerPhaFilter( const VelocityPhaFilter& f){
int TofMeasurementArray::registerPhaFilter( AmPhaFilter& f){
  Filters.push_back(&f);
  return(Filters.size());
}

void TofMeasurementArray::setDoBRW(bool flag){
  doBRW = flag;
}

bool TofMeasurementArray::getDoBRW(){
  return(doBRW);
}

int TofMeasurementArray::save(string file){

  return(-1);
}

int TofMeasurementArray::load(string file){

  return(-1);
}

float TofMeasurementArray::sumInSlice(int nedb, int start_ch, int stop_ch) const{
  float sum = 0.0;
  float tmp_sum = 0.0;
  for (int tofch = start_ch/ResolScalar; 
       tofch <= stop_ch/ResolScalar; tofch++){
    tmp_sum = getElement(nedb, tofch);
    if (tmp_sum >= 0.0) sum += tmp_sum;
    else {
      if (gDbgLvl >= 1){
	cout << "TofMeasurementArray::sumInSlice -E- bad element" << endl;
      }
      return(-1.0); // bad nedb or bad channel
    }
  }

  return(sum);
}

float TofMeasurementArray::getElement(int nedb, int tofch) const{
  if (goodNedb(nedb) && goodTofch(tofch)){
      return(TMA[nedb][tofch]);  // return good value
  }
  else {
    return(-1.0);
  }
}

TNT::Vector<float> TofMeasurementArray::getSlice(int nedb){
  if (goodNedb(nedb))
    return(TMA[nedb]);
  else{
    TNT::Vector<float> tmp(TMA[0].size(), -1.0);
    return(tmp);
  }
  
}

void TofMeasurementArray::dumpPha( string file_base ){
  dumpPhaFlag = true;
  DumpPhaFile = file_base;
}

void TofMeasurementArray::outputSlices(std::ofstream& fout){
  // put in number of slices to follow
  fout << IC.getNumEdb() - IC.getFirstEdb() << endl;

  // ===> FIX: get out hardcoded 2
  for (int nedb = IC.getFirstEdb(); nedb < IC.getNumEdb(); nedb++){
    fout << getSlice(nedb);
  }
}


