/*
  File: ProbRates.cc

  Description: 

    Calculates rates using a probabilistic model, in particular eq. 9
    (ref. 1 in swindal.h).

  Author: Jim Raines, 16Aug2001

  Method:
    
    Uses spillover rates and a gaussian function to calculate the
    probability that any particular data point (tof, esd, e/q) comes
    from a particular species.
    
  Major Modification History:
    

*/

#include "swindal.h"
#include <cfloat>

ProbRates::ProbRates(int N){ // N is number of rates (species)
  TNT::Vector<float> tmpv(N, 0.0);
  TNT::Matrix<float> tmpm(N,2,0.0);
  for (int i = 0; i < MAXEDB; i++){
    Nprob.push_back(tmpv);
    NprobCM.push_back(tmpv);
    ProbCenters.push_back(tmpm);
  }

  // set default values
  GCutOff = 3.0;
  PCutOff = FLT_MIN;  // smallest float allowed, from float.h

  DbgLvl = gDbgLvl;  // init. to global val. by default
}

void ProbRates::print(void){
  float sum, sum2;

  for (int s = 0; s < names.size(); s++){
    sum = 0.0;
    sum2 = 0.0;

    for (int nedb = FIRSTEDB; nedb < MAXEDB; nedb++){
      sum += Nprob[nedb][s];
      sum2 += NprobCM[nedb][s];
    }

    cout << names[s] << " " << sum << " " << sum2 << endl;
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
  float ProbRateSum;
  float maelem;

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

	  // write out O7+ box
	  if (DbgLvl >= 2){
	    if (nedb == 41 && grp[s].name == "O7+"){
	      if ( (tofch >= 340) && (tofch <= 348) ){
		if ( (esdch >= 46) && (esdch <= 57) ){
		  cout << thisprog << " -D- "
		       << " " << nedb
		       << " " << tofch
		       << " " << esdch
		       << " sr=" << sr 
		       << " G=" << G[s][tofch][esdch]
		       << " denom=" << denom[tofch][esdch]
		       << " P=" << P[s][tofch][esdch]
		       << endl;
		}
	      }
	    }
	  }



	}
      }

      if (DbgLvl >= 2){
	cout << "sum of P = " << sum << endl;

	cout << thisprog << " -D- Sum of P for " << grp[s].name
	     << " is " << Pspecies << endl;
      }

    } // loop over species

    /* --- calculate probabilistic rates, swindal.h ref. 1, eq. 10  --- */
    /* method:  At each (tofch,esdch), give MA(tofch,esdch) counts to each
       species according to their probability, P(tofch,esdch).  This
       is referred to as the Counts Distributed (CD) method.
    */
    if (DbgLvl) cout << thisprog << " -I- calculating ProbCD rates" << endl;
    sum = 0.0;
    for (int s = 0; s < grp.size(); s++){
      if (DbgLvl >= 2)
	cout << thisprog << " -D- calc. Nprob for " << grp[s].name << ", "; 

      ProbRateSum = 0.0;
      for (int tofch = 0; tofch < MAXTOFCH; tofch++){
	for (int esdch = 0; esdch < MAXESDCH; esdch++){
	  maelem = MA.getElement(nedb,tofch,esdch);

	  Nprob[nedb][s] += maelem * P[s][tofch][esdch];
	  sum += Nprob[nedb][s];

	  // calc. prob. center to compare to forward model
	  ProbCenters[nedb][s][0] += 
	    ((float) tofch) * maelem * P[s][tofch][esdch];
	  ProbCenters[nedb][s][1] += 
	    ((float) esdch) * maelem * P[s][tofch][esdch];
	  ProbRateSum +=  maelem * P[s][tofch][esdch];
	}
      }

      // normalize
      ProbCenters[nedb][s][0] = ProbCenters[nedb][s][0]/ProbRateSum;
      ProbCenters[nedb][s][1] = ProbCenters[nedb][s][1]/ProbRateSum;

      if (DbgLvl >= 2) cout << "sum of Nprob = " << sum << endl;

      
    } // loop over species

    /* -------------- calculate probabilistic rate max --------------- */
    /* method: At each (tofch,esdch), give MA(tofch,esdch) counts to
       species with highest probability.  This is referred to as the
       Counts to Max (CM) method.
    */
    if (DbgLvl) cout << thisprog << " -I- calculating ProbCM rates" << endl;

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
	}

	NprobCM[nedb][smax] += MA.getElement(nedb,tofch,esdch);
	sum += NprobCM[nedb][smax];

      }
    }

    if (DbgLvl >= 2) cout << "sum of NprobCM = " << sum << endl;

  } // loop over EDBs

  if (DbgLvl) cout << thisprog << " -D- returning normally" << endl;

  return(0);
}

TNT::Matrix<float> ProbRates::getProbCenter(int nedb){
  return(ProbCenters[nedb]);
}

vector<float> ProbRates::calcAveProbCenter(const vector<Ion>& grp, int s){
  /*  Description:

        Calculates the probabilistic center of the peak for species s,
        averaged over charge step.  Checks to be sure element s of grp
        is the same as element s from getProbRate().
 
  */
  string thisprog = "ProbRates::calcAveProbCenter";

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
        calcProbCenter for specified s.
 
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

float ProbRates::getProbRateCM(int s){

  float sum = 0.0;
  for (int nedb = FIRSTEDB; nedb < MAXEDB; nedb++){
    sum += NprobCM[nedb][s];
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
    fout << NprobCM[nedb];
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

  ifstream fin;
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
    fin >> NprobCM[nedb];
  }

  for (int nedb = FIRSTEDB; nedb < MAXEDB; nedb++){
    fin >> ProbCenters[nedb];
  }

  fin.close();
  return(0);
}

