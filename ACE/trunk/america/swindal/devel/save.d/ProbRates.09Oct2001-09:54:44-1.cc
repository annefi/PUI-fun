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

ProbRates::ProbRates(int N){
  TNT::Vector<float> tmpv(N, 0.0);

  for (int i = 0; i < MAXEDB; i++){
    Nprob.push_back(tmpv);
  }

  // set default values
  GCutOff = 3.0;
  PCutOff = 0.7; 

  DbgLvl = gDbgLvl;  // init. to global val. by default
}

void ProbRates::print(void){
  float sum;

  for (int s = 0; s < names.size(); s++){
    sum = 0.0;

    for (int nedb = FIRSTEDB; nedb < MAXEDB; nedb++){
      sum += Nprob[nedb][s];
    }

    cout << names[s] << " " << sum << endl;
  }

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

int ProbRates::calc(const vector<Ion>& grp, SpillRates SR){
  // init some variables
  string thisprog = "ProbRates::calc";
  DbgLvl = 2;

  // gaussian, G(tof,esd) from eq. 2
  vector<TNT::Matrix<float> > G;
  // probability of pha (tof,esd, e/q) being species s at edb i from eq. 9
  vector<TNT::Matrix<float> > P; 

  // fill with 0.0 matrices
  TNT::Matrix<float> tmpm(MAXTOFCH,MAXESDCH, 0.0);
  for (int s = 0; s < grp.size(); s++){
    G.push_back(tmpm);
    P.push_back(tmpm);
    names.push_back(grp[s].name);  // store names
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

  for (int nedb = FIRSTEDB; nedb < MAXEDB; nedb++){
  //for (int nedb = FIRSTEDB; nedb < 4; nedb++){
    if (DbgLvl >= 2) 
      cout << thisprog << " -D- Doing all calc. for nedb=" << nedb << endl;

    /* Calculate G by elements, swindal.h ref. 1, eq. 2 */
    
    for (int s = 0; s < grp.size(); s++){
      if (DbgLvl >= 2) 
	cout << thisprog << " -D- calc. G for " << grp[s].name << ", ";

      /* grab forward model values for this ion and edb */
      fmtof  = grp[s].tof[nedb];   // tof
      fmstof = grp[s].stof[nedb];  // sigma tof
      fmesd  = grp[s].esd[nedb];   // esd
      fmsesd = grp[s].sesd[nedb];  // sigma esd

      for (int ntof = 0; ntof < MAXTOFCH; ntof++){
	for (int nesd = 0; nesd < MAXESDCH; nesd++){
	  tof = (float) ntof;
	  esd = (float) nesd;

	  // distances from centers
	  delta_tof = abs(tof - fmtof); 
	  delta_esd = abs(esd - fmesd);

	  /* probability from eq. 2
	     Note: G outside of GCutOff*sigma in each dim. to 0.0
	  */
	  if ( (delta_tof < GCutOff*fmstof) && (delta_esd < GCutOff*fmsesd) ){
	    G[s][ntof][nesd] = 
	      1.0/(2.0*M_PI*sqrt(fmstof*fmsesd)) *  // M_PI is pi from math.h
	      exp(-pow(tof - fmtof,2)/(2.0*pow(fmstof,2)) 
		  -pow(esd - fmesd,2)/(2.0*pow(fmsesd,2)));
	  }
	  else{
	    G[s][ntof][nesd] = 0.0;
	  }
	  
	  // denominator in eq. 9
	  sr =  SR.getCorSpillRate(nedb,s); // to see in the debugger

	  if (DbgLvl >= 3){
	    if ( (sr > 0.0) && (G[s][ntof][nesd] > 0.0) ){
	      cout << thisprog << " -D- getCorSpillRate(" << nedb
		   << "," << s << ")=" << sr << endl;
	      cout << thisprog << " -D- G[" << s << "][" << ntof << " ]["
		   << nesd << "]=" << G[s][ntof][nesd] << endl;
	    }
	  }

	  denom[ntof][nesd] += sr * G[s][ntof][nesd];

	  // keep a running total for debugging
	  sum += G[s][ntof][nesd];
	}
      }
      
      if (DbgLvl >= 2) cout << "sum of G = " << sum << endl;

    } // loop over species

    //cout << thisprog << " -D- dumping denom to stdout..." << endl;
    //cout << denom << endl;

    /* Calculate P by elements, swindal.h ref. 1, eq. 9 */
    sum = 0.0;
    for (int s = 0; s < grp.size(); s++){
      if (DbgLvl)
	cout << thisprog << " -D- calc. P for " << grp[s].name << ", ";
      
      for (int ntof = 0; ntof < MAXTOFCH; ntof++){
	for (int nesd = 0; nesd < MAXESDCH; nesd++){
	  sr =  SR.getCorSpillRate(nedb,s); // to see in the debugger
	  P[s][ntof][nesd] = sr * G[s][ntof][nesd]/denom[ntof][nesd];

	  sum += P[s][ntof][nesd];
	}
      }

      if (DbgLvl >= 2) cout << "sum of P = " << sum << endl;

    } // loop over species

    /* --- calculate probabilistic rates, swindal.h ref. 1, eq. 10  --- */
    sum = 0.0;
    for (int s = 0; s < grp.size(); s++){
      if (DbgLvl)
	cout << thisprog << " -D- calc. Nprob for " << grp[s].name << ", "; 

      for (int ntof = 0; ntof < MAXTOFCH; ntof++){
	for (int nesd = 0; nesd < MAXESDCH; nesd++){
	  if (P[s][ntof][nesd] > PCutOff){
	    Nprob[nedb][s] += 1.0;
	  }
	  sum += Nprob[nedb][s];
	}
      }

      if (DbgLvl >= 2) cout << "sum of Nprob = " << sum << endl;

    } // loop over species

  } // loop over EDBs

  if (DbgLvl) cout << thisprog << " -D- returning normally" << endl;

  return(0);
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
