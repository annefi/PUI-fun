/*  
  Filename: SpillRates.cc

  Description:
    This class contains spillover matrices and routines needed to perform
    spillover correction of box rates.

  Author:  Jim Raines, 31Jul2001

  Method:

  Major Modification History:

*/

#include "swindal.h"

extern "C" {
  // NOTE: NR select conflicts with the system call; work around
  //#include "nr.h"
  float erff(float x);
}

SpillRates::SpillRates(int N){
  TNT::Matrix<float> tmpm(N, N, 0.0);
  TNT::Vector<float> tmpv(N, 0.0);

  for (int i = 0; i < MAXEDB; i++){
    S.push_back(tmpm);
    Sinv.push_back(tmpm);
    
    Nspill.push_back(tmpv);
    Btil.push_back(tmpv);
    Nspilltil.push_back(tmpv);
  }
}

float SpillRates::getCorSpillRate(int nedb, int s){
  return(Nspilltil[nedb][s]);
}  

float SpillRates::getCorSpillRate(int s){

  float sum = 0.0;
  for (int nedb = FIRSTEDB; nedb < MAXEDB; nedb++){
    sum += Nspilltil[nedb][s];
  }

  return(sum);
}  

void SpillRates::print(void){
  float sum;

  for (int s = 0; s < names.size(); s++){
    sum = 0.0;

    for (int nedb = FIRSTEDB; nedb < MAXEDB; nedb++){
      sum += Nspilltil[nedb][s];
    }

    cout << names[s] << " " << sum << endl;
  }

  return;
}

void SpillRates::dump(int s){
  float sum;

  sum = 0.0;

  for (int nedb = FIRSTEDB; nedb < MAXEDB; nedb++){
    sum += Nspill[nedb][s];
  }

  cout << names[s] << " " << sum << "(";

  for (int nedb = FIRSTEDB; nedb < MAXEDB; nedb++){
    cout << " " << Nspill[nedb][s];
  }

  cout << " )" << endl;

  return;
}
void SpillRates::dump(void){
  float sum;

  for (int s = 0; s < names.size(); s++){
    dump(s);
  }

  return;
}

void SpillRates::printRaw(void){
  float sum;

  for (int s = 0; s < names.size(); s++){
    sum = 0.0;

    for (int nedb = FIRSTEDB; nedb < MAXEDB; nedb++){
      sum += Nspill[nedb][s];
    }

    cout << names[s] << " " << sum << endl;
  }

  return;
}

int SpillRates::calc(vector<Ion>& grp, BoxRates BR){
  string thisprog = "SpillRates::calc";
  int result = 0;
  vector<int> badspecies; // indexes of species to be removed from analysis

  // badspecies must be a vector of iterator positions (can I do that?)
  result = calc2(grp,BR,badspecies);

  if (result != 0){
    // get rid of duplicates in badspecies
    sort(badspecies.begin(),badspecies.end());
    vector<int>::iterator pos;
    pos = unique(badspecies.begin(),badspecies.end()); // resizes too
    badspecies.erase(pos, badspecies.end());

    // remove misbehaving ions from group
    vector<Ion> newgrp;
    //newgrp.reserve(grp.size());
    bool DoCopy;
    for (int s = 0; s < grp.size(); s++){
      for (int i = 0; i < badspecies.size(); i++){
	if (s == badspecies[i]){
	  DoCopy = false;

	  cout << thisprog << " -I- " 
	       << grp[s].name << " has been removed from analysis." << endl;

	  break; // stop looking through badspecies, we found s
	}
	else{
	  DoCopy = true;
	}
      }

      if (DoCopy){
	//newgrp[s] = grp[s];
	newgrp.push_back(grp[s]);
      }
    }

    // copy new to old
    grp.clear();
    grp.reserve(newgrp.size());
    grp = newgrp;

    // re-init the names
    names.clear();

    // re-run calc2
    result = calc2(grp,BR, badspecies);
  }

  return(0);
}

int SpillRates::calc2(const vector<Ion>& grp, BoxRates BR, 
		      vector<int>& badspecies){
  string thisprog = "SpillRates::calc2";
  int DbgLvl = gDbgLvl;
  int retval = 0;  // return value of this routine
                   // 0 -> no bad species; 1 -> bad species exist

  // grab ion names for printing and stuff
  for (int s = 0; s < grp.size(); s++){
    names.push_back(grp[s].name);
  }
  
  /* Calculate S by elements, ref. 1, eq. 3 */
  double Stofp,Stofm, Sesdp, Sesdm;  // args to the erf in eq.
  for (int nedb = FIRSTEDB; nedb < MAXEDB; nedb++){
    for (int s = 0; s < grp.size(); s++){
      for (int t = 0; t < grp.size(); t++){
	// tof + sigma
	Stofp = (1.0/(sqrt(2.0)*grp[t].stof[nedb])) *
		 (grp[s].tof[nedb] + 
		  grp[s].stof[nedb] - 
		  grp[t].tof[nedb]);

	// tof - sigma
	Stofm = (1.0/(sqrt(2.0)*grp[t].stof[nedb])) *
		  (grp[s].tof[nedb] - 
		   grp[s].stof[nedb] - 
		   grp[t].tof[nedb]);

	// esd + sigma
	Sesdp = (1.0/(sqrt(2.0)*grp[t].sesd[nedb])) *
		 (grp[s].esd[nedb] +
		  grp[s].sesd[nedb] -
		  grp[t].esd[nedb]);

	// esd - sigma
	Sesdm = (1.0/(sqrt(2.0)*grp[t].sesd[nedb])) *
		   (grp[s].esd[nedb] - 
		    grp[s].sesd[nedb] - 
		    grp[t].esd[nedb]);

	S[nedb][s][t] = (1.0/2.0)*( erff(Stofp) - erff(Stofm) ) *
	  (1.0/2.0)*( erff(Sesdp) - erff(Sesdm) );
	
// 	if (S[nedb][s][t] != 0.0) {
// 	  cout << thisprog << " -D- S[" 
// 	       << nedb << "]["
// 	       << s << "]["
// 	       << t << "]="
// 	       << S[nedb][s][t] << endl;
// 	}

      } // loop over species t
    } // loop over species s
    
    Sinv[nedb] = Invert(S[nedb]);

    if (nedb == 48 && DbgLvl >= 3) {
      cout << thisprog << " -D- testing inversion..." << endl;
      TNT::Matrix<float> I(S[nedb].dim(1),S[nedb].dim(1), 1.0E-5);
      TNT::Matrix<float> P(S[nedb].dim(1),S[nedb].dim(1), 0.0);

      P = S[nedb] * Sinv[nedb];
      // make identity matrix
      for (int i = 0; i < I.dim(1); i++){
	I[i][i] = 1.0;
      }
      
//       //if (I == 1.0) cout << thisprog << " -D- I == 1.0" << endl;

      if ( P > I){
	cout << thisprog << " -D- S*Sinv > I" << endl;
      }

      if (0){
	ofstream fout;
	fout.open("invprod.axlv2");
	fout << P;
	fout.close();
      }
    }

  } // loop over edbs

  // --- calculate spillover rates
  vector<TNT::Vector<float> > B;  
  B = BR.getBoxrates();
  for (int nedb = FIRSTEDB; nedb < MAXEDB; nedb++){
    Nspill[nedb] = Sinv[nedb] * B[nedb];
  } // loop over edbs

  
  // --- calculate ghost-count-corrected box rates
  for (int nedb = FIRSTEDB; nedb < MAXEDB; nedb++){
    for (int s = 0; s < grp.size(); s++){
      for (int t = 0; t < grp.size(); t++){
	if (t != s){
	  // derived from equation 7
	  Btil[nedb][s] += - Sinv[nedb][s][t] * B[nedb][t]
	    / Sinv[nedb][s][s];
	}
      } // loop over species t
    } // loop over species s
  } // loop over edbs

  /* --- calculate ghost-count-correct spillover rates (eq 8) --- */
  
  // Bcorr are boxrates from B and Btil, depending on sign of Nspill
  TNT::Vector<float> Bcorr(Btil[FIRSTEDB].size(),0.0);
  for (int nedb = FIRSTEDB; nedb < MAXEDB; nedb++){

    for (int s = 0; s < grp.size(); s++){
      if (nedb == 41){
	cout << thisprog << " -D- Nspill["
	     << s << "]=" << Nspill[nedb][s] << endl;
      }

      // if block replaces Heaviside step function, theta, in eq 8
      if (Nspill[nedb][s] >= 0.0){
	Bcorr[s] = B[nedb][s];
      }
      else if (Nspill[nedb][s] < 0.0){
	Bcorr[s] = Btil[nedb][s];
	
	badspecies.push_back(s);
	retval = 1;

	cout << thisprog << " -D- nedb=" << nedb << " s=" << s
	     << " adding " << grp[s].name << " to removal list" << endl; 
      }
    }

    // equation 8
    Nspilltil[nedb] = Sinv[nedb] * Bcorr;
  } // loop over edbs

  return(retval);
}


/* -----------------
   PRIVATE FUNCTIONS
   -----------------
*/
