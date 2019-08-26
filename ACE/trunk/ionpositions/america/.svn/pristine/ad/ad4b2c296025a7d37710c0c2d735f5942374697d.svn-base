/*
  File: ProbRates.cc

  Description: 

    Calculates rates using a probabilistic model, in particular eq. 9
    (ref. 1 in swindal.h).

  Author: Jim Raines (jmr)

  Method:
    
    Uses spillover rates and a gaussian function to calculate the
    probability that any particular data point (tof, esd, e/q) comes
    from a particular species.
    
  Revision controlled by CVS:
  $Id: ProbRates.cc,v 1.13 2005/06/07 00:06:40 jraines Exp $

  Major Modification History:
    16Aug2001   jmr   Initial coding
    12Aug2003   jmr   Adding Ruedi von Steiger-style count assignment

*/

#include "swindal.h"
#include <cfloat>

// include files for creation time and mod. time
#include <sys/types.h>   // for FM mod. time (open)
#include <sys/stat.h>    // for FM mod. time (fstat)
#include <fcntl.h>       // for FM mod. time (open)
#include <unistd.h>      // for FM mod. time (fstat)

#include <time.h>        // for creation time in header

using std::ofstream;

ProbRates::ProbRates(InstrumentConstants ic, int N){ 
  TNT::Vector<float> tmpv(N, 0.0);
  TNT::Matrix<float> tmpm(N,2,0.0);
  for (int i = 0; i < MAXEDB; i++){
    Nprob.push_back(tmpv);
    ProbCenters.push_back(tmpm);
  }

  // set default values
  GCutOff = 3.0;
  PCutOff = FLT_MIN;  // smallest float allowed, from float.h

  DbgLvl = gDbgLvl;  // init. to global val. by default

  Method = 1;  // set method default

  outputPslices = false;

  IC = ic;
}

void ProbRates::print(void){
  float sum, sum2;

  for (int s = 0; s < names.size(); s++){
    sum = 0.0;
    sum2 = 0.0;

    for (int nedb = FIRSTEDB; nedb < MAXEDB; nedb++){
      sum += Nprob[nedb][s];
    }

    cout << names[s] << " " << sum << endl;
  }

  return;
}

void ProbRates::dump(void){
  float sum;

  for (int s = 0; s < names.size(); s++){
    dump(s);
  }

  return;
}

void ProbRates::dump(int s){
  float sum;

  sum = 0.0;

  for (int nedb = FIRSTEDB; nedb < MAXEDB; nedb++){
    sum += Nprob[nedb][s];
  }

  cout << names[s] << " " << sum << "(";

  for (int nedb = FIRSTEDB; nedb < MAXEDB; nedb++){
    cout << " " << Nprob[nedb][s];
  }

  cout << " )" << endl;

  return;
}

bool ProbRates::operator<< (ProbRates) {
  float sum;

  for (int s = 0; s < names.size(); s++){
    sum = 0.0;

    for (int nedb = FIRSTEDB; nedb < MAXEDB; nedb++){
      sum += Nprob[nedb][s];
    }

    cout << names[s] << " " << sum;
  }

  return(true);
}

int ProbRates::calc(const vector<Ion>& grp, const MeasurementArray& MA, 
		    SpillRates SR){
  // init some variables
  string thisprog = "ProbRates::calc";
  //DbgLvl = 2;

  // a correctly dimensioned matrix of zeros
  const TNT::Matrix<float> zero(MAXTOFCH,MAXESDCH, 0.0);

  // init some variables for each species
  for (int s = 0; s < grp.size(); s++){
    G.push_back(zero);
    P.push_back(zero);

    // while we are here, store names to be sure we do not get confused later
    names.push_back(grp[s].name); 
  }

  // denominator in swindal.h ref. 1, eq. 9
  TNT::Matrix<float> denom(MAXTOFCH,MAXESDCH, 0.0);

  float tof, esd;  // float versions of the position in the
		   // measurement array slice 

  float sum = 0.0; // sum of G for current ion, for debugging

  // tmp. var. for forward model values of current species and edb
  float fmtof, fmstof; //  tof and sigma tof
  float fmesd, fmsesd; //  esd and sigma esd

  // distances from forward model center for current tof,esd
  float delta_tof, delta_esd;

  // variables for to ease debugging with DDD
  float sr; // current corrected spill rate

  // tmp variables for probabilistic centers
  vector<float> center;  // (tof,esd)
  center.assign(2, 0.0);
  vector<float> ProbRateSum;
  ProbRateSum.assign(grp.size(), 0.0);
  float maelem;

  // set up output file for P matrices if necessary
  string bname = "axlv2";  //FIX: this should be passed in from top level
  ofstream fout;
  int maxedb[grp.size()];
  
  if (outputPslices){
    cout << thisprog << " -I- writing P slice for each charge step..." << endl;
    string outfile = bname + "_p_slices.dat";
    fout.open(outfile.c_str());

    for (int s = 0; s < grp.size(); s++){
      float max = 0.0;
      float sr = 0.0;
      float srsum = 0.0;
      // form spill rate weighted sum of s
      for (int nedb = FIRSTEDB; nedb < MAXEDB; nedb++){
	sr =  SR.getCorSpillRate(nedb,s); // to see in the debugger
	max += nedb*sr;
	srsum += sr;
      }
      max = max/srsum; // normalize

      maxedb[s] = (int)(max + 0.5);  // round and make into an integer

      // note:  bounds checking unecessary; out of range elements will 
      // never satisfy P slice output logic

      if (DbgLvl >= 3) {
	cout << thisprog << " -I- P slice for " << grp[s].name
	     << " will be output for EDB=" << maxedb[s] << endl;
      }
    }
  }

  for (int nedb = FIRSTEDB; nedb < MAXEDB; nedb++){
    //for (int nedb = 41; nedb < 42; nedb++){  // few edbs for debugging
    if (DbgLvl >= 1) {
      cout << thisprog << " -I- Doing all calc. for nedb=" << nedb << endl;
    }

    denom = zero;

    /* Calculate G by elements, swindal.h ref. 1, eq. 2 */
    for (int s = 0; s < grp.size(); s++){
      if (DbgLvl >= 2) 
	cout << thisprog << " -D- calc. G for " << grp[s].name << ", ";

      /* grab forward model values for this ion and edb */
      fmtof  = grp[s].tof[nedb];   // tof
      fmstof = grp[s].stof[nedb];  // sigma tof
      fmesd  = grp[s].esd[nedb];   // esd
      fmsesd = grp[s].sesd[nedb];  // sigma esd
      GCutOff = grp[s].PrGaussCutoff; // see below

      for (int tofch = 0; tofch < MAXTOFCH; tofch++){
	for (int esdch = 0; esdch < MAXESDCH; esdch++){
	  tof = (float) tofch;
	  esd = (float) esdch;

	  // distances from centers
	  delta_tof = abs(tof - fmtof); 
	  delta_esd = abs(esd - fmesd);

	  /* probability from eq. 2
	     Note: G outside of GCutOff*sigma in each dim. to 0.0
	  */
	  if ( (delta_tof < GCutOff*fmstof) && (delta_esd < GCutOff*fmsesd) ){
	    G[s][tofch][esdch] = 
	      1.0/(2.0*M_PI*sqrt(fmstof*fmsesd)) *  // M_PI is pi from math.h
	      exp(-pow(tof - fmtof,2)/(2.0*pow(fmstof,2)) 
		  -pow(esd - fmesd,2)/(2.0*pow(fmsesd,2)));
	  }
	  else{
	    G[s][tofch][esdch] = 0.0;
	  }
	  
	  // denominator in eq. 9
	  sr =  SR.getCorSpillRate(nedb,s); // to see in the debugger

	  if (DbgLvl >= 3){
	    if ( (sr > 0.0) && (G[s][tofch][esdch] > 0.0) ){
	      cout << thisprog << " -D- getCorSpillRate(" << nedb
		   << "," << s << ")=" << sr << endl;
	      cout << thisprog << " -D- G[" << s << "][" << tofch << " ]["
		   << esdch << "]=" << G[s][tofch][esdch] << endl;
	    }
	  }

	  denom[tofch][esdch] += sr * G[s][tofch][esdch];

	  // keep a running total for debugging
	  sum += G[s][tofch][esdch];
	}
      }
      
      if (DbgLvl >= 2) cout << "sum of G = " << sum << endl;

    } // loop over species

    // careful! this is a matrix
    //cout << thisprog << " -D- denom=" << denom << endl;

    /* Calculate P by elements, swindal.h ref. 1, eq. 9 */
    sum = 0.0;
    float Pspecies = 0.0;
    for (int s = 0; s < grp.size(); s++){
      if (DbgLvl >= 2){
	cout << thisprog << " -D- calc. P for " << grp[s].name << ", ";
      }

      Pspecies = 0.0;
      
      for (int tofch = 0; tofch < MAXTOFCH; tofch++){
	for (int esdch = 0; esdch < MAXESDCH; esdch++){
	  sr =  SR.getCorSpillRate(nedb,s); // to see in the debugger
	  P[s][tofch][esdch] = sr * G[s][tofch][esdch]/denom[tofch][esdch];

	  // this avoids 'nan' results which mask valid values when summed
	  // note: a less than test will not work (reason unknown)
	  if (! (P[s][tofch][esdch] > PCutOff)){
	    P[s][tofch][esdch] = 0.0;
	  }

	  sum += P[s][tofch][esdch];
	  Pspecies += P[s][tofch][esdch];


	}
      }

      if (DbgLvl >= 2){
	cout << "sum of P = " << sum << endl;

	cout << thisprog << " -D- Sum of P for " << grp[s].name
	     << " is " << Pspecies << endl;
      }
      
      
      if (outputPslices){
	if (maxedb[s] == nedb){
	  string title = "AXLV2 Probability Matrix for " + grp[s].name;
	  outputSlice(fout, P[s], nedb, title);
	}
      }

    } // loop over species

    /* -------------------------------------------------------------------- */
    /* -------------- Calculate Probabilisic Rates ------------------------ */
    /* -------------------------------------------------------------------- */
    switch (Method){
    case 1:
      /* --- calculate probabilistic rates, swindal.h ref. 1, eq. 10  --- */
      /* method:  At each (tofch,esdch), give MA(tofch,esdch) counts to each
	 species according to their probability, P(tofch,esdch).  This
	 is referred to as the Counts Distributed (CD) method.
      */
      if (DbgLvl) 
	cout << thisprog << " -I- calculating prob. rates via Counts Distributed (CD) method" << endl;

      sum = 0.0;
      for (int s = 0; s < grp.size(); s++){
	if (DbgLvl >= 2)
	  cout << thisprog << " -D- calc. Nprob for " << grp[s].name << ", "; 

	for (int tofch = 0; tofch < MAXTOFCH; tofch++){
	  for (int esdch = 0; esdch < MAXESDCH; esdch++){
	    maelem = MA.getElement(nedb,tofch,esdch);

	    Nprob[nedb][s] += maelem * P[s][tofch][esdch];
	    sum += Nprob[nedb][s];  // for debugging

	    // calc. prob. center to compare to forward model
	    ProbCenters[nedb][s][0] += 
	      ((float) tofch) * maelem * P[s][tofch][esdch];
	    ProbCenters[nedb][s][1] += 
	      ((float) esdch) * maelem * P[s][tofch][esdch];
	    ProbRateSum[s] +=  maelem * P[s][tofch][esdch];
	  }
	}

	// normalize probabilistic centers
	ProbCenters[nedb][s][0] = ProbCenters[nedb][s][0]/ProbRateSum[s];
	ProbCenters[nedb][s][1] = ProbCenters[nedb][s][1]/ProbRateSum[s];
	
	// re-init. for next time
	ProbRateSum[s] = 0.0;

	if (DbgLvl >= 2) cout << "sum of Nprob = " << sum << endl;

      
      } // loop over species
      break;

    case 2:
      /* -------------- calculate probabilistic rate max --------------- */
      /* method: At each (tofch,esdch), give MA(tofch,esdch) counts to
	 species with highest probability.  This is referred to as the
	 Counts to Max (CM) method.
      */
      if (DbgLvl) cout << thisprog << " -I- calculating prob. rates via Counts to Max. (CM) method" << endl;

      sum = 0.0;
      for (int tofch = 0; tofch < MAXTOFCH; tofch++){
	for (int esdch = 0; esdch < MAXESDCH; esdch++){

	  float max = 0.0;
	  int smax  = 0;
	  for (int s = 0; s < grp.size(); s++){
	    if (P[s][tofch][esdch] > max){
	      max = P[s][tofch][esdch];
	      smax = s;
	    } // note: same smax could come up twice or an s may not come up

	    // calc. prob. center to compare to forward model
	    ProbCenters[nedb][s][0] += 
	      ((float) tofch) * maelem * P[s][tofch][esdch];
	    ProbCenters[nedb][s][1] += 
	      ((float) esdch) * maelem * P[s][tofch][esdch];
	    ProbRateSum[s] +=  maelem * P[s][tofch][esdch];
	  }

	  Nprob[nedb][smax] += MA.getElement(nedb,tofch,esdch);
	  sum += Nprob[nedb][smax];

	}
      }

      // normalize probabilistic centers
      for (int s = 0; s < grp.size(); s++){
	ProbCenters[nedb][s][0] = ProbCenters[nedb][s][0]/ProbRateSum[s];
	ProbCenters[nedb][s][1] = ProbCenters[nedb][s][1]/ProbRateSum[s];
	
	// re-init. for next time
	ProbRateSum[s] = 0.0;
      }

      if (DbgLvl >= 2) cout << "sum of Nprob = " << sum << endl;

      break;
    case 3:
      /* ---------- calculate probabilistic rates via dice method ---------- */
      /* method:  At each (tofch,esdch), use the probabilities for each
	 species to set up ranges of values assigned to each species.
	 Then, generate a random number (dice roll).  Assign all counts
	 to the species whose range the random number falls within.
      */

      if (DbgLvl) cout << thisprog << " -I- calculating prob. rates via Dice Roll (DR) method" << endl;
    
      float lo,hi,dice_roll;
      sum = 0.0;
      for (int tofch = 0; tofch < MAXTOFCH; tofch++){
	for (int esdch = 0; esdch < MAXESDCH; esdch++){
	  maelem = MA.getElement(nedb,tofch,esdch);

	  lo = 0.0;
	  hi = 0.0;
	  dice_roll = (float)random()/(float)RAND_MAX;

	  for (int s = 0; s < grp.size(); s++){
	    // set up interval for this species (s)
	    if(s == 0){
	      lo = 0.0;
	    }
	    else {
	      lo = lo + P[s-1][tofch][esdch];
	    }
	    hi = hi + P[s][tofch][esdch];

	    // if dice_roll falls in interval for this species,
	    // assign counts at this (tofch,esdch) to that species
	    if (dice_roll >= lo && dice_roll < hi){
	      Nprob[nedb][s] += maelem;

	      // save assigned counts information for selected ion/nedb pairs
	      for (int i = 0; i < AC.size(); i++){
		if (AC[i].index == s && AC[i].nedb == nedb){
		  AC[i].slice[tofch][esdch] =  maelem;
		}
	      }

	      // save assigned counts for a particular element
	      for (int i = 0; i < ACElem.size(); i++){
		if ( ((s >= ACElem[i].index_lo) && 
		      (s <= ACElem[i].index_hi)) &&
		     (nedb == ACElem[i].nedb)){
		  ACElem[i].slice[tofch][esdch] += maelem;
		}
	      }

	      // save assigned counts into sum for single MMQ output
	      // (summed over ion)
	      if (ACSum.size() > 0){
		ACSum[nedb-IC.getFirstEdb()].slice[tofch][esdch] = maelem;
	      }

	      // for debugging
	      sum += Nprob[nedb][s];
	    }

	    // calc. prob. center to compare to forward model
	    ProbCenters[nedb][s][0] += 
	      ((float) tofch) * maelem * P[s][tofch][esdch];
	    ProbCenters[nedb][s][1] += 
	      ((float) esdch) * maelem * P[s][tofch][esdch];
	    ProbRateSum[s] +=  maelem * P[s][tofch][esdch];
	  }
	
	
	}
      }

      // normalize probabilistic centers
      for (int s = 0; s < grp.size(); s++){
	ProbCenters[nedb][s][0] = ProbCenters[nedb][s][0]/ProbRateSum[s];
	ProbCenters[nedb][s][1] = ProbCenters[nedb][s][1]/ProbRateSum[s];
	
	// re-init. for next time
	ProbRateSum[s] = 0.0;
      }

      if (DbgLvl >= 2) cout << "sum of Nprob = " << sum << endl;

      break;
    } // end switch for prob rate method
  } // loop over EDBs



  if (outputPslices) fout.close();

  if (DbgLvl) cout << thisprog << " -D- returning normally" << endl;

  return(0);
}

TNT::Matrix<float> ProbRates::getProbCenter(int nedb){
  return(ProbCenters[nedb]);
}

// Note: this is a meaningless quantity.  JMR, 21Nov2003
vector<float> ProbRates::calcAveProbCenter(const vector<Ion>& grp, int s){
  /*  Description:

        Calculates the probabilistic center of the peak for species s,
        averaged over charge step.  Checks to be sure element s of grp
        is the same as element s from getProbRate().
 
  */
  string thisprog = "ProbRates::calcAveProbCenter";
  using std::cerr;

  vector<float> center;  // (tau,esd)
  center.assign(2, 0.);

  // double check that argument s refers to same ion as in ProbRates
  if (grp[s].name != names[s]){
    cerr << thisprog << " -E- ions do not match.  ProbRates refers to "
	 << names[s] << " while argument group[s] refers to "
	 << grp[s].name << endl;
    cerr << "+ Re-calculate ProbRates with argument group." << endl;
    return(center);
  }

  float ProbRateSum = 0.0;  // sum over all ProbRates for normalization
  for (int nedb = FIRSTEDB; nedb < MAXEDB; nedb++){
    ProbRateSum += getProbRate(nedb,s);
  }

  for (int nedb = FIRSTEDB; nedb < MAXEDB; nedb++){
    center[0] += getProbRate(nedb,s) * grp[s].tof[nedb];
    center[1] += getProbRate(nedb,s) * grp[s].esd[nedb];
  }

  center[0] = center[0]/ProbRateSum;
  center[1] = center[1]/ProbRateSum;

  return center;
}  

vector<vector<float> > ProbRates::calcAveProbCenter(const vector<Ion>& grp){
  /*  Description:

        Calculates the probabilistic center of the peak, averaged over
        charge step (nedb), for all species in grp, using
        calcAveProbCenter for specified s.
 
  */
  vector<vector<float> > centers;
  
  for (int s = 0; s < grp.size(); s++){
    centers.push_back(calcAveProbCenter(grp, s));
  }

  return centers;
}

float ProbRates::getProbRate(int nedb, int s){
  return(Nprob[nedb][s]);
}

float ProbRates::getProbRate(int s){

  float sum = 0.0;
  for (int nedb = FIRSTEDB; nedb < MAXEDB; nedb++){
    sum += Nprob[nedb][s];
  }

  return(sum);
}  

/* --- get/set parameters for probabilistic rate calculation --- */

float ProbRates::setGaussCutOff(float val){
  GCutOff = val;
  return(GCutOff);
}

float ProbRates::getGaussCutOff(void){
  return(GCutOff);
}

float ProbRates::setProbCutOff(float val){
  PCutOff = val;
  return(PCutOff);
}

float ProbRates::getProbCutOff(void){
  return(PCutOff);
};

void ProbRates::setMethod(int method){
  Method = method;
  return;
}

int ProbRates::getMethod(void){
  return(Method);
}
/* --- save/load --- */

int ProbRates::save(string file){

  ofstream fout;
  fout.open(file.c_str());
  fout.precision(10);

  if (gDbgLvl) {
    cout << "ProbRates::save -I- saving ProbRates to " << file << endl;
  }

  fout << names.size() << endl;
  for (int s = 0; s < names.size(); s++){
    fout << names[s] << " ";
  }
  fout << endl;
  
  for (int nedb = FIRSTEDB; nedb < MAXEDB; nedb++){
    fout << Nprob[nedb];
  }

  for (int nedb = FIRSTEDB; nedb < MAXEDB; nedb++){
    fout << ProbCenters[nedb];
  }

  fout.close();

  return(0);
}


int ProbRates::load(string file){
  string thisprog = "ProbRates::load";
  string name;
  int nspecies = 0;

  std::ifstream fin;
  fin.open(file.c_str());

  if (gDbgLvl) {
    cout << thisprog << " -I- loading ProbRates from " << file << endl;
  }

  fin >> nspecies;
  cout << thisprog << " -D- loading rates for " 
       << nspecies << " species" << endl;
  for (int s = 0; s < nspecies; s++){ // 
    //fin >> names[s];
    fin >> name;
    names.push_back(name);
  }

  for (int nedb = FIRSTEDB; nedb < MAXEDB; nedb++){
    fin >> Nprob[nedb];
  }

  for (int nedb = FIRSTEDB; nedb < MAXEDB; nedb++){
    fin >> ProbCenters[nedb];
  }

  fin.close();
  return(0);
}

/*
  Routine: outputSlice

  Description: 

    Output E-T matrix to file.

  Author: Jim Raines (jmr)

  Method:
    
  Major Modification History:
    22Aug2003   jmr   Adapted from outputMA.cc and outputPR.cc
    15Mar2004   jmr   Generalized to work with AssignedCounts slices too

*/

int ProbRates::outputSlice(ofstream &fout, TNT::Matrix<float> slice, 
			    int nedb, string title){

  string thisprog = "ProbRates::outputSlice";

  fout.precision(3);

  fout << title << endl;
  fout << "TOF_CH_STEP_" << nedb << " ESD_CH" << endl;
  fout << "0 1023 0 255" << endl;
  fout << slice; 
    
  return (0);
}

void ProbRates::setOutputPslices(bool value){
  outputPslices = value;
}

void ProbRates::outputProbCenters(string outfile,const AnalysisData& ad){

  FILE *PCF; // Prob. Center Comparison File (pointer)
  PCF = fopen(outfile.c_str(), "w+");

  // keep fields the same total width!
  char hdrfmt[] ="# %3s %6s %6s %6s %6s %6s %6s %8s\n";
  char datafmt[]=
  "  %3d %6.2f %6s %6.2f %6.2f %6.2f %6.2f %8.2e\n";

  // ----------------------- print file header --------------------------------
  fprintf(PCF,"# Probabilistic Centers from ACE Level II data processor (v2.0)\n");

  // get and format calendar time for header
  time_t now;
  char timestr[19];
  time(&now);
  strftime(timestr, 19, "%d%b%Y %H:%M:%S", localtime(&now));
  fprintf(PCF,"# Created: %s\n", timestr);

  // print column headings
  fprintf(PCF,hdrfmt,"EDB","E/q","ion","tof","tofsig","esd","esdsig","Prate");

  // ------------------------- output data -----------------------------------
  // temporary variables for inside loop
  // ----- probabilistic centers
  TNT::Matrix<float> pcmat;  // centers for all s at this nedb
  float pctof, pcesd;        // centers for current s at this nedb
  // ----- forward model sigmas for current nedb, s
  float stof, sesd;

  //  write output line for each EDB for each species
  for (int nedb = FIRSTEDB; nedb < MAXEDB; nedb++){
  //for (int nedb = 41; nedb < 42; nedb++){ // for debugging
    pcmat = getProbCenter(nedb);

    for (int s = 0; s < ad.Ions.size(); s++){
      pctof = pcmat[s][0];
      pcesd = pcmat[s][1];

      stof = ad.Ions[s].stof[nedb];
      sesd = ad.Ions[s].sesd[nedb];

      fprintf(PCF, datafmt,nedb,ad.Eqtab[nedb],ad.Ions[s].name.c_str(),
	      pctof,stof,pcesd,sesd,getProbRate(nedb,s));
    }
  }

  fclose(PCF);


  return;
}

int ProbRates::registerACSlice(string ion, int nedb, 
			       AnalysisData ad){
  if (nedb < IC.getNumEdb()){
    AssignedCounts ac(IC, ion, ad.getIonIndex(ion), nedb);
    AC.push_back(ac);
  }
  else if (gDbgLvl >= 1) {
    cout << "ProbRates::registerACSlice -E- nedb (" << nedb 
	 << ") out of range (" << IC.getFirstEdb() << ".."
	 << IC.getNumEdb()-1 << ")" << endl;
  }
}

int ProbRates::registerACElem(string elem, int nedb_lo, int nedb_hi,
			       AnalysisData ad){

  if ( nedb_lo < IC.getFirstEdb() || nedb_hi > IC.getNumEdb()){
    if (gDbgLvl >= 1) {
      cout << "ProbRates::registerACElem -E- invalid edb range (" << nedb_lo 
	   << " - " << nedb_hi << "), only " << IC.getFirstEdb() << ".."
	   << IC.getNumEdb()-1 << ") allowed" << endl;
    }
  }

  // find lo/hi index for specified element
  int index_lo = ad.Ions.size()-1;
  int index_hi = 0;
  for (int s = 0; s < ad.Ions.size(); s++){
    if (ad.Ions[s].element == elem){
      string ion = ad.Ions[s].name;

      if (ad.getIonIndex(ion) > index_hi) 
	index_hi = ad.getIonIndex(ion);
      if (ad.getIonIndex(ion) < index_lo) 
	index_lo = ad.getIonIndex(ion);
    }
  }

  if (gDbgLvl >= 1) {
    cout << "ProbRates::registerACElem -I- registering element " << elem
	 << " (s:" << index_lo << ".." << index_hi << ") for nedb = "
	 << nedb_lo << ".." << nedb_hi << endl;
  }

  for (int i = 0; i < nedb_hi - nedb_lo + 1; i++){
    AssignedCountsElem ac(IC, elem, index_lo, index_hi, nedb_lo+i);
    ACElem.push_back(ac);    
  }
}

int ProbRates::registerACSum(void){
  if (AC.size() > 0){
    if (gDbgLvl >= 1){
      cout << "ProbRates::registerACSum "
	   << "-E- attempting to re-register ACSum" << endl;
    }
    return(1);
  }

  for (int nedb = IC.getFirstEdb(); nedb < IC.getNumEdb(); nedb++){
    // only slice member and EDB are used for sum; rest initialized to null
    AssignedCounts ac(IC, "", -1, nedb);
    ACSum.push_back(ac);
  }

  return(0);
}

void ProbRates::outputACSlices(string file){
  // output AssignedCounts slices if there are any
  if (AC.size() > 0){
    if (gDbgLvl >= 1){
      cout << "ProbRates::outputACSlices "
	   << "-I- writing selected AssignedCount slices..." << endl;
    }

    ofstream ac_fout;
    ac_fout.open(file.c_str());

    for (int i = 0; i < AC.size(); i++){
      string title = "AXLV2 Assigned Counts for " + AC[i].ion;
      outputSlice(ac_fout, AC[i].slice, AC[i].nedb, title);
    }

    ac_fout.close();
  }
}

int ProbRates::outputACSumMMQ
  (string file, const AnalysisData& ad,
   MeasurementArray& MA,
   double mm0, double mm1,double mq0, double mq1) {

  if (ACSum.size() <= 0) return(-1);

  if (gDbgLvl >= 1){
    cout << "ProbRates::outputACSumMMQ "
	   << "-I- writing selected AssignedCount array in MMQ..." << endl;
  }

  // set up file
  ofstream fout;
  fout.open(file.c_str());

  TNT::Matrix<float> mmq(IC.getNumMqCh(),IC.getNumMassCh(), 0.0);
  TNT::Matrix<float> mmqsum(IC.getNumMqCh(),IC.getNumMassCh(), 0.0);

  string ions;
  for (int i = 0; i < ACSum.size(); i++){
    ions = ions + " " + ACSum[i].ion;
    mmq = MA.EtSlice2Mmq(ACSum[i].slice,ACSum[i].nedb,ad, mm0, mm1, mq0, mq1);
    mmqsum = mmqsum + mmq;
  }

  // "ACE/SWICS m-m/q in counts/second for day(s) "
  fout << "ACE/SWICS Level II Assigned Counts for " << ions << endl;
  fout << "m/q_(amu/e) mass_(amu)" << endl;
  fout << mq0 << " " << mq1 << " " << mm0 << " " << mm1 << endl;
  fout << mmqsum;

  fout.close();

  return(0);
}

int ProbRates::outputACElemMMQ
  (string file, const AnalysisData& ad,
   MeasurementArray& MA,
   double mm0, double mm1,double mq0, double mq1) {

  if (ACElem.size() <= 0) return(-1);

  if (gDbgLvl >= 1){
    cout << "ProbRates::outputACElemMMQ "
	   << "-I- writing selected AssignedCount array in MMQ..." << endl;
  }

  // set up file
  ofstream fout;
  fout.open(file.c_str());

  TNT::Matrix<float> mmq(IC.getNumMqCh(),IC.getNumMassCh(), 0.0);
  TNT::Matrix<float> mmqsum(IC.getNumMqCh(),IC.getNumMassCh(), 0.0);

  for (int i = 0; i < ACElem.size(); i++){
    mmq = MA.EtSlice2Mmq(ACElem[i].slice,ACElem[i].nedb,ad, 
			 mm0, mm1, mq0, mq1);
    mmqsum = mmqsum + mmq;
  }

  // "ACE/SWICS m-m/q in counts/second for day(s) "
  fout << "ACE/SWICS Level II Assigned Counts for element " 
       << ACElem[0].elem << endl;
  fout << "m/q_(amu/e) mass_(amu)" << endl;
  fout << mq0 << " " << mq1 << " " << mm0 << " " << mm1 << endl;
  fout << mmqsum;

  fout.close();

  return(0);
}


int ProbRates::output(FILE *PRF, float doyfr, const AnalysisData& ad){

  static bool FirstTime = true;

  // keep fields the same total width!
  char hdrfmt[] ="# %7s %3s %8s %6s %10s %10s\n";
  char datafmt[]=
  "  %7.3f %3d %8.2f %6s %10.2e %10.2e\n";

  if (FirstTime) {  // print header first time through 
    fprintf(PRF,"# Probabilistic rates from ACE Level II data processor (v2.0)\n");

    // get and format calendar time for header
    time_t now;
    char timestr[19];
    time(&now);
    strftime(timestr, 19, "%d%b%Y %H:%M:%S", localtime(&now));
    fprintf(PRF,"# Created: %s\n", timestr);

    fprintf(PRF,"# ProbRates: %s\n", "$Id: ProbRates.cc,v 1.13 2005/06/07 00:06:40 jraines Exp $");

    // column headings
    fprintf(PRF,hdrfmt,"doyfr", "EDB", "E/q","ion","probrate",
	    "probcnt");

    FirstTime = false;
  }

  float pr;
  for (int s = 0; s < ad.Ions.size(); s++){
    for (int nedb = FIRSTEDB; nedb < MAXEDB; nedb++){
      pr = getProbRate(nedb, s);
      fprintf(PRF, datafmt, doyfr, nedb, ad.Eqtab[nedb], 
	      ad.Ions[s].name.c_str(),
	      getProbRate(nedb, s), gAccumTime*getProbRate(nedb,s));
      // Note: last item is approx. counts
    }
  }

  return(0);
}


  
