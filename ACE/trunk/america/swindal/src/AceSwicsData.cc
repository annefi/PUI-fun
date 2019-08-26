/*
  File: AceSwicsData.cc

  Description:

    Class of functions and containers for groups of Pha words.  This
    class, along with the Pha class contain all instrument-specific
    functions and containers.

  Author(s): Jim Raines (jmr)

  Revision controlled by CVS:
  $Id: AceSwicsData.cc,v 1.12 2005/06/09 04:06:12 jraines Exp $

  Method:
    
  Major Modification History:
    01Sep2002   jmr   initial coding
    02Jul2003   jmr   Changed scet in load() to ss1970 and 
                      added ss1970_to_doyfr 

*/

#include "swindal.h"

namespace libhef {
  extern "C" {
#include "libhef.h"
  }
}

// one-time initialization of *static* member (shared by all instances)
bool AceSwicsData::LoadNeedsNewFile = true;

AceSwicsData::AceSwicsData(void){
  Eqtab.reserve(MAXEDB);
  Eqtab.assign(MAXEDB, 0.0); // init to 0.0;

  CycleTime = -1.0;
  //LoadNeedsNewFile = true;
  LoadFoundError = false;
}

/*
  Routine: AceSwicsData::load

  Description:  
  Loads vector of Pha objects by reading data from Level 1 files. 

  Created by : Jim Raines (jmr)

  Major Modification History
    1Sep2002   jmr   Adapted from loadPha.cc
    1May2002   jmr   Adapted from al2c.c

*/

int AceSwicsData::load(int AnalysisInterval,double &swspeed){
  /* parameters */
  const int iPrintInterval=1;  // printing interval for per cycle stdout info.

  using namespace libhef;

  /* local software housekeeping variables */
  string thisprog = "AceSwicsData::load";
  //const char thisprog[]="loadPha";  // name of this program
  int i,j,k;             // short range loop counters

  int result;            // return value from libhef function
  int a3rcresult=0;      // return value from a3readcycle

  char infile[150];      // input data filename
  FILE *pInfile;         // input file stream

  int nedb;              // counter for looping over EDBs
  int npha;              // counter for looping over PHAs
  int irange;            // counter for counter for looping over ranges

  // get rid of this if LoadNeedsNewFile works
  //static bool fNewFile = true;  // true => open new file

  int DbgLvl= gDbgLvl;   // init local debugging level to global one
  bool dumpPhaFlag = false;  // t=>pha info written to static file for debug

  bool fKeep = true;     // T => store PHA in big vector; F => discard

  /* data variables */
  Pha lpha;              // local pha object, put into vector at end
  std::list<Pha> cycpha;      // PHA words from current cycle
  std::list<Pha>::iterator cycpha_it;

  /* -- stats variables -- */
  
  vector<double> xmr(MAXEDB);  // set of matrix rate values for 
                               // solar wind speed calc
  int nphaedb[MAXEDB];   // number of pha words per EDB
  static long int nphatot = 0;      // total number of PHA words read thus far
  //  double swspeed;          // H+ speed for current cycle
  swspeed=0.;
  // for weights
  long br[MAXEDB][4];     // basic rates for this cycle
  int npharng[MAXEDB][4]; // npha with a range of second index
  float weight[MAXEDB][4]; // factor to scale nphaedb to actual if all
                         // PHAs had been transmitted

  // misc. counters
  int NumCycLoadedTC=0;  // number of cycles successfully loaded this call (TC)

  static int ncycle_file = 1; // number of cycles successfully
			     // processed this file
  int ncyclemax;         // number of cycles to analyze
  long nlines=0;         // number of lines written to outfile
  long nto=0;            // number of PHAs thrown out
  float topercent;       // thrown-out % for PHAs

  /* ------------------------------------
     initialize arrays -- just to be safe
     ------------------------------------*/
  for (nedb = 0; nedb < MAXEDB; nedb++){
    for( i = 0; i < 4; i++){
      br[nedb][i] = 0;
      npharng[nedb][i] = 0;
      weight[nedb][i] = 0.0;
    }

  }

  /* ---------
     open file
     ---------
  */

  if (LoadNeedsNewFile){
    strcpy(infile,gCurLv1File.c_str());
    printf("%s -D- %s\n",thisprog.c_str(),infile);

    result = a3opencyclefile(infile);
    if (result != 0) {
      printf("%s -F- error (%d) opening %s\n",thisprog.c_str(),result,infile);
      return(1);
    }

    LoadNeedsNewFile = false;
  }

  // for debugging dump only
  if (gDbgLvl >= 2) dumpPhaFlag = true; // not permanent
  FILE *DUMP; // Forward Model Comparison File (pointer)
  if (dumpPhaFlag) DUMP = fopen("pha_dump.dat", "a");

  /* ---------------- */
  /* Loop over cycles */
  /* ---------------- */

  ncyclemax = AnalysisInterval;
  if (DbgLvl > 0){
    printf("%s -I- reading %d cycles maximum\n",thisprog.c_str(), ncyclemax);
  }

  while (a3rcresult == 0 && NumCycLoadedTC < ncyclemax){

    /* re-init. some counters */
    for (nedb = FIRSTEDB; nedb < MAXEDB; nedb++)
      for (i = 0; i < 4; i++)
	npharng[nedb][i] = 0;

    /* Get ACE cycle and expand */
    /* ------------------------ */
    a3rcresult = a3readcycle();
    if (result > 0){
	printf("%s -E- a3readcycle returned %d\n",thisprog.c_str(), result);
    }
    else{
      result = a3expand();
      if (result > 0)
	printf("%s -E- a3readcycle returned %d\n",thisprog.c_str(), result);
    }
 
    /* set level of output messages from libhef */
    result = perr_setlevel(1);

    /* cycle time */
    if (! (NumCycLoadedTC % iPrintInterval))
      printf("%s -I- Cycle: %s\n",thisprog.c_str(),a3zrecid());

    /* check to see if everything is nominal before we continue */
    if (a3cycx_nominal(0)){  // 0 specifies E/q tab 0 is nominal
      printf("%s -I- cycle not considered nominal; skipping...\n",
	     thisprog.c_str());
      continue;
    }

    /* scet -- spacecraft event time in seconds since 1Jan1970 00:00:00*/
    lpha.scet = a3gtime();

    /* THIS USED TO BE:

       This is reported in seconds since 1Jan1950 to work with Nathan's 
       code.  The offset of seconds since 1Jan1970 to 1Jan1950 is:

       offset = 86400 sec/day * ( 20 year * 365 day/year + 5 days (leap))

    //lpha.scet = a3gtime() + (double)(86400*(20*365 + 5));
    */

    /* set PAPS voltage to be used for post-accel. voltage throughout */
    PapsVolt = a3gxpavdpu();

    if (DbgLvl >= 1) 
      printf("%s -D- read PAPS = %f kV (level %d)\n",
	     thisprog.c_str(),PapsVolt, a3xpavlev());

    if (PapsVolt == 0.0) {
      cout << thisprog.c_str() << " -F- post-accel. voltage out of range (" 
	   << PapsVolt << ").  This will cause foward model to fail." << endl;
      return(1);
    }

    /* Get everything else */
    /* ------------------- */
    for (nedb=FIRSTEDB; nedb < MAXEDB; nedb++){
      
      /* get number of pha words */
      nphaedb[nedb] = a3xnpha(nedb);
      if (DbgLvl >= 3){
	cout << thisprog.c_str() << " -D- nphaedb[" <<nedb << "]=" 
	     << nphaedb[nedb] <<endl;
      }

      /* store edb number */
      lpha.nedb = nedb;

      /* get eq */
      /* The -1 comes from the fact that PHA words are put into the TM
	 one EDB after they are actually read.  This re-aligns them
	 with the E/q at which they were measured.
	 See libhef docs for details. */
      lpha.eq = a3gxeqdpu_i(nedb - 1);
      Eqtab[nedb] = a3gxeqdpu_i(nedb - 1);

      /* make BR table for calculating weights later */
      for( i = 0; i < 4; i++){
	br[nedb][i] = a3gxbr(nedb, i, 8);
      }

      /* get matrix rate for sw speed calc */
      xmr[nedb] = a3gxmr(1,nedb, 8);

      /* get items for each PHA */
      for (npha = 0; npha < nphaedb[nedb]; npha++){
	
	/* assign tof
	   tch is converted to ns by 0.1955 ns/ch (from Simon Hefti) */
	lpha.tofch = a3gxtof_i(nedb,npha);
	lpha.tof = lpha.tofch * TOF_NS_PER_CH;

	/* assign energy */
	/* ech (digital energy) conv. to keV by 2.395 keV/ch (from S. Hefti)*/
	lpha.esdch = a3gxesd_i(nedb,npha);
	lpha.esd = lpha.esdch * ESD_KEV_PER_CH;
	
	/*assign sector */
        lpha.sector = a3gxsec_i(nedb,npha);

	/* assign detector*/
	lpha.detector = a3gxdid_i(nedb,npha); // right func.?

	/* assign range and count number in each range */
	lpha.range = a3gxrng_i(nedb,npha);
	
	// keep track of number of pha in each range for weighting (later)
	if (lpha.range >= 0 && lpha.range <= 3){
	  npharng[nedb][lpha.range]++;
	}
	else{
	  printf("%s -W- range out of limits",thisprog.c_str());
	}

	/* assign br0-3 */
	for( i = 0; i < 4; i++){
	  lpha.br[i] = br[nedb][i];
	}

	/* assign TCR */
	lpha.tcr = a3gxtcr_i(nedb,8);
	
	/* assign mass */
	lpha.mmch = a3gxmas_i(nedb,npha);
	if (lpha.mmch == 0){    // handle special channels, see libhef docs
	  /* signify mass zero events as zero */
	  lpha.mm = 0.0;
	}
	else if (lpha.mmch >= 123){
	  // just pass on the channel; beware in further processing
	  lpha.mm = lpha.mmch * 10.0;
	}
	else {
	  // not a special channel, convert normally
	  lpha.mm = a3cxmas(lpha.mmch);
	  if (lpha.mm == -1.0){ 
	    printf("%s -W- a3cxmas returned error (-1.0) ", thisprog.c_str());
	    printf("for non-special channel.  Discarding pha.\n");
	    printf("+ lpha.mmch = %d lpha.mm = %f\n",lpha.mmch,lpha.mm);
	    fKeep = false;
	  }
	}
	
	/* assign m/q */
	lpha.mqch = a3gxmoq_i(nedb,npha) ;
        /* handle special channels, see libhef docs */
	if (lpha.mqch == 0){
	  /* just pass on the channel; beware in further
	     processing */
	  lpha.mq = 0.0;
	}
	else if (lpha.mqch < 1){ // should never occur
	  printf("%s -W- 0 < mqch < 1 not handled correctly\n",thisprog.c_str());
	  lpha.mq = lpha.mqch / 10.0;
	}	      
	else if (lpha.mqch > 124){
	  /* just pass on the channel; beware in further
	     processing */
	  lpha.mq = lpha.mqch * 10.0;
	}
	else {
	  /* not a special channel, convert normally */
	  lpha.mq = a3cxmoq(lpha.mqch);
	  if (lpha.mq == -1.0){
	    printf("%s -W- a3cxmoq returned error (-1.0) ", thisprog.c_str());
	    printf("for non-special channel.  Discarding pha.\n");
	    printf("+ lpha.mmch = %d lpha.mm = %f\n",lpha.mqch,lpha.mq);
	    fKeep = false;
	  }
	}

	/* calculate ion speed in km/s from kinetic energy, 

	   E/q=1/2 m/q v^2

	   which, when solved for v and unit conversions are applied
	   results in the formula used.

	   The constant 439.0 km/s is just the product of unit
	   conversion factors when E/q is in keV/e and m/q is in amu/e.

	   note: speed = TOF_DISTANCE * 1.0E-5 km/cm * 1.0E9 ns/s / TOF
	   DOES NOT work because it includes post-acceleration.

	   note2:  Speeds are only calculated for valid mq; Values outside 
	   range below are OVER/UNDERFLOW channels and cannot be used to 
	   calculated speed.
	*/	
	if (lpha.mq > 0.0 && lpha.mq <= 124.0){
	  lpha.speed = 439.0*sqrt(lpha.eq/lpha.mq);
	}
	else {
	  lpha.speed = -1.0;
	}

	/* Add to this cycles PHA list if this is a good one */
	if (fKeep) {
	  cycpha.push_back(lpha);
	}
	else {
	  nto++;  // one more pha thrown out

	  if (DbgLvl > 1) {
	    cout << "thisprog.c_str() -I- discarded current PHA\n";
	  }
	}
			   

      } /* loop over phas */
    } /* loop over edbs */

    /* calculate solar wind speed for this cycle */
    swspeed = calcSwSpeed(Eqtab,xmr,2.0,0.8); // moq = 2.0, cutoff = 0.8

    if (! (NumCycLoadedTC % iPrintInterval))
      printf("%s -I- SW speed = %10.2f\n",thisprog.c_str(),swspeed);

    /* --- calculate PHA weighting for each EDB --- */
    for (nedb = FIRSTEDB; nedb < MAXEDB; nedb ++){
      /* print number of PHA words by EDB */
      nphatot += nphaedb[nedb];
      /* calculate deadtime correction for given EDB
         deadtimecorr = 1s/(1s-T*(1/12.)*TCR[nedb])
	 T=0.000134s ; from Robert Wimmer for Ulysses/SWICS */
      float deadtimecorr = 1./(1.-0.000134*(a3gxtcr_i(nedb,8)/12.));
      //      cout << thisprog.c_str() << "-I- deadtimecorr[" << nedb << "] = " << deadtimecorr << std::endl;
      for(irange = 0; irange < 4; irange++){
	if( npharng[nedb][irange] > 0 && br[nedb][irange] > 0){
	  weight[nedb][irange] = ((float)br[nedb][irange] /
				  (float)npharng[nedb][irange]) * deadtimecorr;
	}
	else
	  weight[nedb][irange] = 1.0*deadtimecorr;

	npharng[nedb][irange] = 0;
      
      }
      
    }

    if (DbgLvl > 0) {
      if (nphatot > 0) {
	topercent = (float)nto * 100.0 / (float)nphatot ;
      }
      else {
	topercent = 0.0;
      }

      printf("%s -I- read %d PHAs so far, %d thrown out (%03.1f%%)\n",
	     thisprog.c_str(),nphatot, nto, topercent);
    }

    // Store weights and swspeeds into phas from this cycle then
    // add them to big vector
    cycpha_it = cycpha.begin();
    while (cycpha_it != cycpha.end()){

      if (cycpha.front().nedb < MAXEDB){
	cycpha.front().weight = 
	  weight[cycpha.front().nedb][cycpha.front().range];
      }
      else {
	printf("%s -W- nedb=%d (out of range)\n",thisprog.c_str(),cycpha.front().nedb);
      }

      if ( swspeed > 0.0 &&  swspeed < 10000.0 ){
	cycpha.front().swspeed = swspeed;
      }
      else {
	printf("%s -W- swspeed = %6.2f (out of range)\n",
	       thisprog.c_str(),swspeed);
      }
      
      if (dumpPhaFlag) dumpPhaFile(&cycpha.front(), npha, ncycle_file, DUMP);

      // add 
      PhaData.push_back(cycpha.front());

      // pop this element off
      cycpha.pop_front();

      // set iterator to new beginning of vector (pop changed it)
      cycpha_it = cycpha.begin();
    
    }
  
    NumCycLoadedTC++;  // increment counter *after* successfully processing cycle
    ncycle_file++;

  } /* loop over cycles */  

  if (a3rcresult != 0){

    if (a3rcresult == 1) { // EOF found
      a3closecyclefile();
      cout << thisprog.c_str() << " -I- end of file reached (" << a3rcresult 
	   << ")\n";

      LoadNeedsNewFile = true;
      ncycle_file = 0;
    }
    else{ // non-zero return but not EOF
      cout << thisprog.c_str() << " -E- a3readcycle returned an error (" 
	   << a3rcresult << ")\n";
      LoadFoundError = true;
      // FIX: put in return or break here?
    }

  }
  else {
    // Assign class-wide cycle time to cycle time for first PHA
    CycleTime = PhaData[0].scet;
    if (gDbgLvl >= 2) printf("%s -D- CycleTime for PhaData set to %f\n",
			     thisprog.c_str(),CycleTime);
  }

  // for debugging dump only
  if (dumpPhaFlag) fclose(DUMP);

  return NumCycLoadedTC;
}



int AceSwicsData::closeFile(void) const{
  return(libhef::a3closecyclefile());
}

/* print PHA info to stdout for debugging */
int AceSwicsData::dumpPha(Pha *pha, int npha, int ncycle) const{

  /* scet, nedb, npha, eq */
  printf("%010.0f %02d %03d %6.2f",pha->scet, pha->nedb,npha,pha->eq);

  /* tof, esd, sector */
  printf(" %10.2f %10.2f %02d",pha->tof,pha->esd,pha->sector);

  /* range, br0,br1, br2, wt */
  printf(" %01d %05d %05d %05d %10.2f",pha->range,
	  pha->br[0],pha->br[1],pha->br[2], pha->weight);
  
  /* vi, vw, mm, mq, ncycle */
  printf(" %10.2f %10.2f %10.2f %10.2f %03d\n",pha->speed,pha->swspeed,
	 pha->mm,pha->mq,
	 ncycle);

  return(0);
}  

/* print PHA info to stdout for debugging */
int AceSwicsData::dumpPhaFile(Pha *pha, int npha, int ncycle, FILE *F) const{

  /* scet, nedb, npha, eq */
  fprintf(F,"%010.0f %02d %03d %6.2f",pha->scet, pha->nedb,npha,pha->eq);

  /* tof, esd, sector */
  fprintf(F," %10.2f %10.2f %02d",pha->tof,pha->esd,pha->sector);

  /* range, br0, br1, br2, wt */
  fprintf(F," %01d %05d %05d %05d %10.2f",pha->range,
	  pha->br[0],pha->br[1],pha->br[2], pha->weight);
  
  /* vi, vw, mm, mq, ncycle*/
  fprintf(F," %10.2f %10.2f %10.2f %10.2f %03d\n",pha->speed,pha->swspeed,pha->mm,pha->mq,
	 ncycle);

  return(0);
}  

Pha AceSwicsData::getPha(int i) const {
  return(PhaData[i]);
}

long AceSwicsData::getNpha(void) const {
  return(PhaData.size());
}

/* get forward model (FM) data 
   wrapper for libhef::xfm */
double* AceSwicsData::getFM(double eoq, double pav, double mass, 
			    double charge) const {
  static double* tmp;
  tmp = libhef::xfm(eoq, pav, mass, charge);
  return(tmp);
}

double AceSwicsData::getPav() const{
  return(PapsVolt);
}

double AceSwicsData::getEqtab(int nedb) const{
  return(Eqtab[nedb]);
}

float AceSwicsData::ss1970_to_doyfr(double ss1970) const{
  float doyfr;
  long alltime[14];

  long ss1970l = (long) ss1970;

  // use converter from libhef
  // alltime = 
  // 0     1      2    3   4   5     6    7  8   9   10
  // sec70 julian secs DOY day month year hr min sec week-day (0 for sunday)
  libhef::sec70_time(alltime, &ss1970l);

  // doy + (hr*3600 + min*60 + sec)/86400.0
  doyfr = alltime[3] + 
    (float)(alltime[7]*3600 + alltime[8]*60 + alltime[9])/86400.0;

  return(doyfr);
}
  
double AceSwicsData::getCycleTime() const{
  return(CycleTime);
}

/*
   Routine: calcSwSpeed.cc

   Description: 
      Calculates solar wind speed (km/s) using a count-weighted average of E/q
      for all E/q >= cutoff*maximum.  

   Author: Jim Raines, 30Nov2000
           (Algorithm concept by Thomas Zurbuchen, Oct2000)

   Method: 

   Requires: read(-->) written(<--)
   <called functions and globals read(-->)/written(<--)>

   Argument  list
      EPQ[n]            Energy Per charge value in keV/e
      cnt[n]            number of counts per E/q step
      float moq         mass / charge to use in speed calc. (amu / ox. #)
      float cutoff      % of max counts to qualify for inclusion


   See libh2n.doc for further documentation.

   This file is controlled by the Concurent Version System (CVS):
   $Id: AceSwicsData.cc,v 1.12 2005/06/09 04:06:12 jraines Exp $

   Major Modification History: (keep this last section)
     Translated to C++.  JR, 23May2001.

     Translated to C.  JR, 29Jan2001.
*/

/*
double AceSwicsData::getswspeed(){
  double swspeed;
  swspeed=calcSwSpeed(Eqtab,xmr,2.0,0.8);
  return swspeed; // moq = 2.0, cutoff = 0.8
}
*/
double AceSwicsData::calcSwSpeed(vector<double> epq,vector<double> cnt,
				 double moq, double cutoff){
  /* constants */
  const string thisprog = "AceSwicsData::calcSwSpeed";

  /* Local variables */
  int DbgLvl = gDbgLvl; /* init local debugging value to global  */

  /* dump args for debugging */
  if (DbgLvl > 2) {
    for(int i = FIRSTEDB; i < MAXEDB; i++){
      printf("%s -D- epq[%02d]=%10.2e cnt[%02d]=%05d\n",thisprog.c_str()
	     ,i,epq[i],i,cnt[i]);
    }
    printf("%s -D- moq=%10.2f cutoff=%10.2f\n",thisprog.c_str(),moq, cutoff);
  }

  /* find max */
  /* -------- */
  double hi;                // maximum number of cnt words
  for(int i = 0; i < cnt.size(); i++){
    if (i == 0) hi = cnt[i];

    if (cnt[i] > hi) hi = cnt[i];
  }

  /* calculate count-weighted average energy */
  /* --------------------------------------- */
  double sumepq = 0.0;       // sum of E/q for average
  double sumcnt = 0;        // number of cnt used for weighting
  for(int i = 0; i < epq.size(); i++){
    if (cnt[i] >= (cutoff*hi)){
      sumepq += epq[i] * cnt[i];
      sumcnt += cnt[i];
    }
  }

  double energy;             // count-weighted average energy
  energy = sumepq/sumcnt;
  if (DbgLvl >= 3) 
    printf("%s -I- sumepq=%10.2f sumcnt=%10.2f energy=%10.2f \n",
	   thisprog.c_str(),sumepq,sumcnt,energy);

  /* compute:  v = sqrt( 2 E/q 9.648E4 / (m/q) ) */
  /*           where 9.648E4 is conversion to C/g units */
  double swspeed;        // speed
  swspeed = sqrt(2*energy*9.648E4/moq);

  if (DbgLvl >= 3) printf("%s -I-  swspeed=%10.2f\n",swspeed);

  return(swspeed);
}

bool AceSwicsData::loadNeedsNewFile(void){
  return(LoadNeedsNewFile);
}

bool AceSwicsData::loadFoundError(void){
  return(LoadFoundError);
}

// Copy constructor because vectors do not copy with default copy
AceSwicsData::AceSwicsData(const AceSwicsData& asd){
  PhaData.clear();
  for(int i = 0; i < asd.PhaData.size(); i++) 
    PhaData.push_back(asd.PhaData[i]);

  PapsVolt = asd.PapsVolt;

  for(int i = 0; i < asd.Eqtab.size(); i++) 
    Eqtab[i] = asd.Eqtab[i];

  CycleTime = asd.CycleTime;
 
  LoadFoundError = asd.LoadFoundError;

  LoadNeedsNewFile = asd.LoadNeedsNewFile;
}

// Assignment copy constructor
AceSwicsData& AceSwicsData::operator= (const AceSwicsData& rhs){

  if (this != &rhs){  // this guards against self assignment
    cout << "AceSwicsData::operator= -I- assigning..." << endl;

    PhaData.clear();
    for(int i = 0; i < rhs.PhaData.size(); i++) 
      PhaData.push_back(rhs.PhaData[i]);

    PapsVolt = rhs.PapsVolt;

    for(int i = 0; i < rhs.Eqtab.size(); i++) 
      Eqtab[i] = rhs.Eqtab[i];

    CycleTime = rhs.CycleTime;
 
    LoadFoundError = rhs.LoadFoundError;

    LoadNeedsNewFile = rhs.LoadNeedsNewFile;
  }

  return *this;
}
