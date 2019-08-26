/*
  File: MeasurementArray.cc

  Description:
    Code for MeasurementArray class

  Author: Jim Raines, 6Jun2001

  Method:
    
  Revision controlled by CVS:
  $Id: MeasurementArray.cc,v 1.12 2005/02/11 15:59:42 jraines Exp $

  Major Modification History:
    

*/

#include "swindal.h"
#include <iomanip>

// Constructor 
MeasurementArray::MeasurementArray(void){
  TNT::Matrix<float> A(MAXTOFCH,MAXESDCH, 0.0);
  
  /* --- fill vector with (tofch,esdch) matrices --- */
  
  MA.reserve(MAXEDB);
  for (int i = 0; i < MAXEDB; i++){
    MA.push_back(A);
  }
  
  /* set default PHA range(s) to keep, see header for details */
  filter = 2;  // 2 -> keep range 1 only

  /* set default value for basic rate weighting flag, see header for details */
  doBRW = 1;   // 1 => T
}

int MeasurementArray::fill(const AceSwicsData& swxdata, bool& Rates){
/*
  Description:

    Make measurement array.  This routine builds and returns the
    measurement array (tof, esd, nedb). Rates = true -> The elements
    of the array are in counts per second. Rates = false -> The elements
    of the array are in counts.The tof and esd indices are in
    channels.  Inclusion of the nedb dimension makes a cube of
    (tof,esd) matrices, where the nedb index is the number of the EDB
    in which the (tof,esd) values were collected (which corresponds to
    the E/q value).


  Author: Jim Raines, 

  Method:
    
  Major Modification History:
  28.07.05 Lars Berger :
  changed Rates from local variable to input parameter. Now one is able
  to choose method from outside (via axlv2.in)
    

*/
  string thisprog = "MeasurementArray::fill";  // name of this routine
  int DbgLvl = gDbgLvl;  // debugging level, init. to global value

  bool dumpPhaFlag = false;  // t=>pha info written to static file for debug

  Pha pha;  // container for holding each successive pha word as returned
            // from swxdata.getPha(i)

  if (DbgLvl >= 1) {
    cout << thisprog << " -I- filling MeasurementArray..." << endl;
  }

  /* --- change elements of MA from rates to counts --- */
  /* -------------------------------------------------- */
  
  if (Rates){
    for (int nedb = FIRSTEDB; nedb < MAXEDB; nedb++){
      for (int ntof = 0; ntof < MAXTOFCH; ntof++){
	for (int nesd = 0; nesd < MAXESDCH; nesd++){
	  MA[nedb][ntof][nesd] = MA[nedb][ntof][nesd] * gAccumTime;
	}
      }
    }
  }
  

  /* --- count PHA words with tof (channels), esd (channels) and nedb --- 
     -------------------------------------------------------------------- */
  int npha_tot  = 0;  // number of pha read from swxdata object
  int npha_used = 0;  // number of pha in analyzed for filling into MA

  if (DbgLvl >= 2) dumpPhaFlag = true; // temporary

  FILE *DUMP_USED;
  FILE *DUMP_DISC;
  if (dumpPhaFlag) {
    DUMP_USED = fopen("mafill_used_pha.dat", "a");
    DUMP_DISC = fopen("mafill_discarded_pha.dat", "a");
  }    

  for (int npha = 0; npha < swxdata.getNpha(); npha++){ // loop over PHAs

    pha = swxdata.getPha(npha);
    npha_tot++;

    // select PHAs to used based on several criteria
    bool pha_ok = false;
    if (pha.nedb < MAXEDB && 
	passRange(pha.range) &&
	passVelFilter(pha.speed, pha.swspeed) ){ // PHA used

      pha_ok = true;
      npha_used++;

      if (dumpPhaFlag)
	swxdata.dumpPhaFile(&pha, npha, -1, DUMP_USED);
    }
    else {
      pha_ok = false;

      if (dumpPhaFlag)
	swxdata.dumpPhaFile(&pha, npha, -1, DUMP_DISC);
    }

    // if PHA passes selection criteria, put it into MA
    if (pha_ok){

      // this should be up in selection criteria
      if ( pha.tofch > (MAXTOFCH - 1) ) {  // -1 b/c ch starts at 0
	cout << thisprog << " -W- tofch out of range (" 
	     << MAXTOFCH - 1 << " max):" 
	     << " nedb=" << pha.nedb 
	     << " tofch=" << pha.tofch 
	     << " esdch=" << pha.esdch 
	     << endl;
      }

      // so should this
      if ( pha.esdch > (MAXESDCH - 1) ) {
	cout << thisprog << " -W- esdch out of range (" 
	     << MAXESDCH -1 << " max):"
	     << " nedb=" << pha.nedb 
	     << " tofch=" << pha.tofch 
	     << " esdch=" << pha.esdch 
	     << endl;
      }

      if (DbgLvl >= 3) {
	cout << thisprog << " -D- dumping meas. array coord.: "
	     << " nedb=" << pha.nedb 
	     << " tofch=" << pha.tofch 
	     << " esdch=" << pha.esdch 
	     << endl;
      }

      if (DbgLvl >= 4) {
	cout << thisprog << "-D- before add MA[" << pha.nedb << "," 
	     << pha.tofch << "," 
	     << pha.esdch << "]=" 
	     << MA[pha.nedb][pha.tofch][pha.esdch] << endl;
      }

      /* ------------------------------ */
      /* increment counts in E-T matrix */
      /* ------------------------------ */
      if (doBRW){
 	MA[pha.nedb][pha.tofch][pha.esdch] += pha.weight;
      }
      else{
	MA[pha.nedb][pha.tofch][pha.esdch] += 1.0;
      }

      if (DbgLvl >= 4) {
	cout << thisprog << "-D- after add MA[" << pha.nedb << "," 
	     << pha.tofch << "," 
	     << pha.esdch << "]=" 
	     << MA[pha.nedb][pha.tofch][pha.esdch] 
	     << endl << endl;
      }

    }
  }

  if (DbgLvl >= 1){
    float used_percent = 100.0 * static_cast<float>(npha_used) / 
      static_cast<float>(npha_tot);
    cout << thisprog << " -I- " << npha_used << " of " << npha_tot
	 << " pha used to fill array ("
	 << used_percent << "%)"  << endl;
  }

  /* --- determine accumulation time for PHAs just added ---
     ------------------------------------------------------- */
  double timeInterval;  // seconds between first and last PHA

  pha = swxdata.getPha(swxdata.getNpha() - 1);
  timeInterval = pha.scet;
  if (DbgLvl >= 3) {
    cout.precision(12);
    cout << thisprog << "-D- end_time=" << pha.scet << endl;
    cout.precision(6);
  }

  pha = swxdata.getPha(0);
  if (DbgLvl >= 3) {
    cout.precision(12);
    cout << thisprog << "-D- start_time=" << pha.scet << endl;
    cout.precision(6);
  }

  timeInterval = timeInterval - pha.scet;

  /* Differences between cycle times will not include time for the last
     cycle read.  Therefore, add a typical cycle time to the calc. interval.
     FIX:  Should this be 58?
  */
  timeInterval += 12.*60.;

  gAccumTime += (float)timeInterval;

  if (DbgLvl >= 2) {
    cout << thisprog << " -D-"
	 << " timeInterval=" << timeInterval 
	 << " gAccumTime=" << gAccumTime 
	 << endl;
  }

  /* --- transform elements of MA back from counts to rates --- 
     ---------------------------------------------------------- */
  float ma_sum = 0.0;
  if (Rates){
    for (int nedb = FIRSTEDB; nedb < MAXEDB; nedb++){
      for (int ntof = 0; ntof < MAXTOFCH; ntof++){
	for (int nesd = 0; nesd < MAXESDCH; nesd++){
	  
	  if (DbgLvl >= 4 && MA[nedb][ntof][nesd] > 0.0){
	    cout << thisprog << "-D- before norm MA[" << nedb 
		 << "," << ntof << "," << nesd
		 << "]=" << MA[nedb][ntof][nesd] << endl;
	  }

	  MA[nedb][ntof][nesd] = MA[nedb][ntof][nesd] / (float)gAccumTime;
	  
	  // for debugging
	  ma_sum += MA[nedb][ntof][nesd];
	  
	  if (DbgLvl >= 4 && MA[nedb][ntof][nesd] > 0.0){
	    cout << thisprog << "-D- after norm MA[" << nedb << "," << ntof 
		 << "," << nesd
		 << "]=" << MA[nedb][ntof][nesd] << endl;
	  }

	} // loop over nesd
      } // loop over ntof
    } // loop over EDBs
  } // endif

  if (DbgLvl >= 2){
    cout << thisprog << " -D- sum of all elements of MA = " << ma_sum << endl;;
  }

  if (dumpPhaFlag) {
    fclose(DUMP_USED);
    fclose(DUMP_DISC);
  }
return 0;
}

TNT::Matrix<float> MeasurementArray::getSlice(int nedb){
  return(MA[nedb]);
}

TNT::Matrix<float> MeasurementArray::EtSlice2Mmq(TNT::Matrix<float> slice, 
  int nedb, const AnalysisData& ad){

  // call with default MMQ limits
  EtSlice2Mmq(slice, nedb, ad, 1.2, 70.0, 1.15, 10.0);
}

TNT::Matrix<float> MeasurementArray::EtSlice2Mmq
  (TNT::Matrix<float> slice, int nedb, const AnalysisData& ad,
   double mm0, double mm1, double mq0, double mq1){
  // mass range of (mm0,mm1) and m/q range of (mq0,mq1)

  string thisprog = "EtSlice2Mmq";
  int DbgLvl = gDbgLvl; // init local debugging level to global one
  static bool FirstTime = true; 

  TNT::Matrix<float> mmq(NQCH, NMCH, 0.0);

  int nmm = 0;
  int nmmzero = 0;
  int nmq = 0;
  int nmqzero = 0;

  if (DbgLvl >= 1 && FirstTime){
    cout << thisprog << " -I- MMQ output using following limits" 
	 << " mm0=" << mm0
	 << " mm1=" << mm1
	 << " mq0=" << mq0
	 << " mq1=" << mq1
	 << endl;
    FirstTime = false;
  }


  double mm;   // mass for current E-T coordinate
  double mq;   // m/q for current E-T coordinate
  int   im;   // mass bin
  int   iq;   // m/q bin

  for (int ntof = 0; ntof < MAXTOFCH; ntof++){
    for (int nesd = 0; nesd < MAXESDCH; nesd++){

      eqte2mmq(ad.Eqtab[nedb], ad.PapsVolt, ntof, nesd, mm, mq);

      if ( (DbgLvl >= 3) && (mm > 0.0 && mq > 0.0) ){
	cout << thisprog << " -D- " 
	     << " nedb=" << nedb
	     << " ntof=" << ntof
	     << " nesd=" << nesd
	     << " mm=" << mm
	     << " mq=" << mq
	     << endl;
      }
      
      /* collect some stats on zero and nonzero mass and m/q */
      if (mm > 0.0){
	nmm++;
      }
      else{
	nmmzero++;
      }

      if (mq > 0.0){
	nmq++;
      }
      else{
	nmqzero++;
      }

      im =  int ( (NMCH - 1) * log(mm/mm0)/log(mm1/mm0) );

      iq =  int ( (NQCH - 1) * log(mq/mq0)/log(mq1/mq0) );

      if ( (DbgLvl >= 3) && (im > 0.0 && iq > 0.0) ){
	cout << thisprog << " -D- " 
	     << " nedb=" << nedb
	     << " ntof=" << ntof
	     << " nesd=" << nesd
	     << " im=" << im
	     << " iq=" << iq
	     << endl;
      }
      
      // assign if within mmq dimensions
      if ( ((im >= 0) && (iq >= 0)) &&  ((im < NMCH) && (iq < NQCH)) ){
	mmq[iq][im] += slice[ntof][nesd];

	if (DbgLvl >= 3){
	  cout << thisprog << " -D- " 
	       << "mmq=" << mmq[iq][im] << endl;
	}
      }
    }
  }

  /* some stats calculations and output */
  if (DbgLvl >= 3){
    float nmmfrac, nmqfrac;
    nmmfrac = (float) nmm / (float) (nmm + nmmzero);
    nmqfrac = (float) nmq / (float) (nmq + nmqzero);
    cout << thisprog << " -D- Non-zero:" 
	 << " nmmfrac=" << nmmfrac
	 << " nmqfrac=" << nmqfrac
	 << endl;
  }

  return mmq;
}

int MeasurementArray::outputMMQ
 (string outfile,long int StartYdoy, long int StopYdoy,const AnalysisData& ad){

  outputMMQ(outfile, StartYdoy, StopYdoy, ad, 1.2, 70.0, 1.15, 10.0);
}

int MeasurementArray::outputMMQ
  (string outfile,long int StartYdoy, long int StopYdoy,const AnalysisData& ad,
   double mm0, double mm1,double mq0, double mq1) {
  /* Description: Output several tof-esd and mmq matrices to files. */

  string thisprog = "outputMMQ";

  std::ofstream fout;
  fout.precision(3);

  TNT::Matrix<float> a(MAXTOFCH,MAXESDCH, 0.0);
  TNT::Matrix<float> sum(MAXTOFCH,MAXESDCH, 0.0);

  /* --- write mmq matrices to file ---
     ----------------------------------
  */
  TNT::Matrix<float> mmq(NQCH,NMCH, 0.0);
  TNT::Matrix<float> mmqsum(NQCH,NMCH, 0.0);
  TNT::Matrix<float> zero(NQCH,NMCH, 0.0);

  fout.open(outfile.c_str());

  fout << "ACE/SWICS m-m/q in counts/second for day(s) " << StartYdoy <<
    " - " << StopYdoy << endl;
  fout << "m/q_(amu/e) mass_(amu)" << endl;
  fout << mq0 << " " << mq1 << " " << mm0 << " " << mm1 << endl;
  //fout << "1 " << NQCH << " 1 " << NMCH << endl;
  
  mmqsum = 0.0;
  for(int nedb = FIRSTEDB; nedb < MAXEDB ; nedb++){
    a = getSlice(nedb);
    mmq = EtSlice2Mmq(a,nedb,ad, mm0, mm1, mq0, mq1);
    mmqsum = mmqsum + mmq;
  }

  fout << mmqsum;
  fout.close();

  return(0);
}


int MeasurementArray::outputMMQfmc(string outfile,const AnalysisData& ad){
  /* Description: Write out FMC centers in M-M/Q.
     Copied from AnalysisData::outputFM.  */

  FILE *FMCF; // Forward Model Comparison File (pointer)
  FMCF = fopen(outfile.c_str(), "w+");

  // keep fields the same total width!
  char hdrfmt[] ="# %3s %6s %6s %6s %6s %6s %6s\n";
  char datafmt[]=
  "  %3d %6.2f %6s %6.2f %6.2f %6.2f %6.2f \n";

  // --- print file header ---
  fprintf(FMCF,"# Forward Model parameters from ACE Level II data processor (v2.0)\n");

  // get and format calendar time for header
  time_t now;
  char timestr[19];
  time(&now);
  strftime(timestr, 19, "%d%b%Y %H:%M:%S", localtime(&now));
  fprintf(FMCF,"# Created: %s\n", timestr);

  // print column headings
  fprintf(FMCF,hdrfmt,"EDB","E/q","ion","moq","moqsig","mass","massig");

  // --- write output line for each EDB for each species ---
  int itof,iesd;  // integer versions
  for (int nedb = FIRSTEDB; nedb < MAXEDB; nedb++){
    for (int s = 0; s < ad.Ions.size(); s++){
      double mq = 0.0;
      double mqsig = 0.0;
      double mm = 0.0;
      double mmsig = 0.0;

      // --- get mass (mm) and m/q (mq) ---
      itof = static_cast<int> (ad.Ions[s].tof[nedb]);
      iesd = static_cast<int> (ad.Ions[s].esd[nedb]);
      eqte2mmq(ad.Eqtab[nedb], ad.PapsVolt, itof, iesd, mm, mq);      
      
      // --- get sigmas for mass (mmsig) and m/q (mqsig) ---
      // must add to tof/esd to get into range
      itof = static_cast<int> (ad.Ions[s].tof[nedb]+ad.Ions[s].stof[nedb]);
      iesd = static_cast<int> (ad.Ions[s].esd[nedb]+ad.Ions[s].sesd[nedb]);
      eqte2mmq(ad.Eqtab[nedb], ad.PapsVolt, itof, iesd, mmsig, mqsig);      
      // subtract off center to get actual sigma
      if (mmsig > mm) mmsig = mmsig - mm;
      else mmsig = 0.0;
      if (mqsig > mq) mqsig = mqsig - mq;
      else mmsig = 0.0;

      fprintf(FMCF, datafmt, nedb, ad.Eqtab[nedb],ad.Ions[s].name.c_str(),
	      mq,mqsig,mm,mmsig);
    }
  }

  fclose(FMCF);

  return (0);
}


int MeasurementArray::save(string file){

  std::ofstream fout;
  fout.open(file.c_str());
  fout.precision(10);

  if (gDbgLvl) {
    cout << "MeasurementArray::save -I- saving MA to " << file << endl;
  }

  for (int nedb = FIRSTEDB; nedb < MAXEDB; nedb++){
    fout << MA[nedb];
  }
  fout.close();

  return(0);
}

int MeasurementArray::savespeed(string file,int cycles){

  std::ofstream fout;
  fout.open(file.c_str());
  fout.precision(10);

  if (gDbgLvl) {
    cout << "MeasurementArray::save -I- saving MA to " << file << endl;
  }

  fout << "Cycles : " << cycles << std::endl;
  fout << "*****" << std::endl;
  for (int nedb = FIRSTEDB; nedb < MAXEDB; nedb++){
    TNT::Matrix<float> a(MAXTOFCH,MAXESDCH, 0.0);
    TNT::Matrix<float> abin(MAXESDCH/2,MAXTOFCH/2,0.0);
    a = MA[nedb];
    abin = binetslice(a);
    fout << abin;
  }
  fout.close();

  return(0);
}


int MeasurementArray::load(string file){
  string thisprog = "MeasurementArray::load";
  
  std::ifstream fin;
  fin.open(file.c_str());
  if (gDbgLvl) {
    cout << thisprog << " -I- loading MA from " << file << endl;
  }
  for (int nedb = FIRSTEDB; nedb < MAXEDB; nedb++){
    fin >> MA[nedb];
  }
  return(0);
}

int MeasurementArray::loadspeed(string file,int &cycles){
  string thisprog = "MeasurementArray::load";
  
  std::ifstream fin;
  fin.open(file.c_str());
  if (gDbgLvl) {
    cout << thisprog << " -I- loading MA from " << file << endl;
  }
  string tmp;
  fin >> tmp >> tmp >> cycles;
  fin >> tmp;
  for (int nedb = FIRSTEDB; nedb < MAXEDB; nedb++){
    TNT::Matrix<float> a(128,512,0.0);
    TNT::Matrix<float> aunbin(1024,256,0.0);
    fin >> a;
    aunbin = unbinetslice(a);
    MA[nedb]=aunbin;
  }
  return(0);
}

float MeasurementArray::getElement(int nedb, int tofch, int esdch) const {

  /* The nedb is bounds checked because the STL vector is not. */
  if ( (nedb < MAXEDB) ){
    return(MA[nedb][tofch][esdch]);
  }
  else {
    return(-1.0);
  }
}

/*  Output swindal E-T matrices for entire charge step range to a file.
    Adapted from outputMA.cc.
*/
int MeasurementArray::outputETslices
  (string outfile, string StartYdoy, string StopYdoy, 
   const AnalysisData& ad, int cycles, float aspang, double swspeed) {

  string thisprog = "outputETslices";

  std::ofstream fout;
  fout.precision(3);

  TNT::Matrix<float> a(MAXTOFCH,MAXESDCH, 0.0);
  TNT::Matrix<float> abin(MAXESDCH/2,MAXTOFCH/2,0.0);
 
  /* --- output all E-T (MA) slices (into one file) ---
     --------------------------------------------------
  */
  cout << thisprog << " -I- writing E-T slice for each charge step..." << endl;
  fout.open(outfile.c_str());
  fout << "ACE/SWICS counts for day(s) " << StartYdoy << " - " << StopYdoy <<endl;
  fout << "Cycles  : " << cycles << std::endl;
  fout << "Aspang  : " << aspang << std::endl;
  fout.precision(5);
  fout << "SWSpeed : " << swspeed << std::endl;
  fout.precision(3);
  fout << "*****" << std::endl;
  for(int i = FIRSTEDB; i < MAXEDB ; i++){
    a = getSlice(i);
    abin = binetslice(a);
    fout << abin; 
  }

  fout.close();


  return (0);
}


int MeasurementArray::setFilter(int newfilter){
  if ( (newfilter >= 0) && (newfilter <= 15) ){
    filter = newfilter;
    return(0);
  }
  else{
    if (gDbgLvl >= 2) {
      cout << "MeasurementArray::setFiler -E- filter="
	   << newfilter << " not allowed" << endl;
    }
    return(1);
  }
}

int MeasurementArray::getFilter(void){
  return(filter);
}

bool MeasurementArray::passRange(int range){
  
  /* array of flags with the bit corresponding to the range (index) set */
  const int RANGE[4] = {1,2,4,8};

  if (range >= 0 && range <= 3){
    return(RANGE[range] & filter);
  }
  else {
    if (gDbgLvl >= 2) {
      cout << "MeasurementArray::passRange -E- range="
	   << range << " not allowed" << endl;
    }
    return false;
  }
}

int MeasurementArray::setDoBRW(bool val){
  doBRW = val;
  if (gDbgLvl >= 1) {
    cout << "MeasurementArray::setDoBRW -I- basic rate weighting is ";
    if (doBRW){
      cout <<"on" << endl;
    }
    else{
      cout <<"off" << endl;
    }
  }
  return(0);
}

bool MeasurementArray::getDoBRW(void){
  return(doBRW);
}

void MeasurementArray::setVelFilterFrac(double val){
  velFilterFrac = val;
  return;
}

double MeasurementArray::getVelFilterFrac(){
   return(velFilterFrac);
}

bool MeasurementArray::passVelFilter(double ion_speed, double sw_speed){
  bool retval = false;
  if (velFilterFrac > 0.0){
    if ( (ion_speed >= sw_speed*(1.0-velFilterFrac)) && 
	 (ion_speed <= sw_speed*(1.0+velFilterFrac)) ){
      retval = true;
    }
  }
  else{ // 0.0 => filter off, i.e. all speeds pass
    retval = true;
  }

  return(retval);
}

bool MeasurementArray::add(MeasurementArray b){
  for (int i = 0;i < MAXEDB; i++){
    for (int j = 0;j < MAXTOFCH; j++){
      for (int k = 0;k < MAXESDCH; k++){
	MA[i][j][k] = MA[i][j][k] + b.MA[i][j][k];
      }
    }
  }
  return true;
}
