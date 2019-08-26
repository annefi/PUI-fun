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
  PCutOff = 1.0e-20;  // arb. small number

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
  DbgLvl = 1;

  // gaussian, G(tof,esd) from eq. 2
  vector<TNT::Matrix<float> > G;
  // probability of pha (tof,esd, e/q) being species s at edb i from eq. 9
  vector<TNT::Matrix<float> > P; 

  // fill with 0.0 matrices
  TNT::Matrix<float> zero(MAXTOFCH,MAXESDCH, 0.0);
  for (int s = 0; s < grp.size(); s++){
    G.push_back(zero);
    P.push_back(zero);
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

  //for (int nedb = FIRSTEDB; nedb < MAXEDB; nedb++){
  for (int nedb = 41; nedb < 42; nedb++){
    if (DbgLvl >= 1) {
      cout << thisprog << " -D- Doing all calc. for nedb=" << nedb << endl;
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
      
      for (int ntof = 0; ntof < MAXTOFCH; ntof++){
	for (int nesd = 0; nesd < MAXESDCH; nesd++){
	  sr =  SR.getCorSpillRate(nedb,s); // to see in the debugger
	  P[s][ntof][nesd] = sr * G[s][ntof][nesd]/denom[ntof][nesd];

	  // this avoids 'nan' results which mask valid values when summed
	  // note: a less than test will not work (reason unknown)
	  if (! (P[s][ntof][nesd] > PCutOff)){
	    P[s][ntof][nesd] = 0.0;
	  }

	  sum += P[s][ntof][nesd];
	  Pspecies += P[s][ntof][nesd];

	  // write out O7+ box
	  if (nedb == 41 && grp[s].name == "O7+"){
	    if ( (ntof >= 340) && (ntof <= 348) ){
	      if ( (nesd >= 46) && (nesd <= 57) ){
		cout << thisprog << " -D- "
		     << " " << nedb
		     << " " << ntof
		     << " " << nesd
		     << " sr=" << sr 
		     << " G=" << G[s][ntof][nesd]
		     << " denom=" << denom[ntof][nesd]
		     << " P=" << P[s][ntof][nesd]
		     << endl;
	      }
	    }
	  }

	}
      }

      if (DbgLvl >= 2) cout << "sum of P = " << sum << endl;

      cout << thisprog << " -D- Sum of P for " << grp[s].name
         << " is " << Pspecies << endl;

    } // loop over species

    /* --- calculate probabilistic rates, swindal.h ref. 1, eq. 10  --- */
    sum = 0.0;
    for (int s = 0; s < grp.size(); s++){
      if (DbgLvl >= 2)
	cout << thisprog << " -D- calc. Nprob for " << grp[s].name << ", "; 

      for (int ntof = 0; ntof < MAXTOFCH; ntof++){
	for (int nesd = 0; nesd < MAXESDCH; nesd++){
	  Nprob[nedb][s] += MA.getElement(nedb,ntof,nesd)*P[s][ntof][nesd];
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
