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

  TNT::Vector<float> tmpv(N, 0.0);
  for (int i = 0; i < MAXEDB; i++){
    Nspill.push_back(tmpv);
    Nspilltil.push_back(tmpv);
  }

  names.reserve(N);
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
  vector<bool> badspecies(grp.size(), false); // badspecies[s] = true
					      // means species s to be
                                              // removed from analysis

  vector<vector<bool> > Removed; // table of species removed at a give
				 // edb
  
  // allocate/init Removed matrix
  vector<bool> tmpv(grp.size(), false);
  for (int nedb = 0; nedb < MAXEDB; nedb++){ // starts at zero so index=nedb
    Removed.push_back(tmpv);
  }

  // grab ion names for printing and misc
  names.clear();  // get rid of previous names, prob un-needed
  for (int s = 0; s < grp.size(); s++){
    names.push_back(grp[s].name);
    //names[s] = grp[s].name;
  }
  
  vector<TNT::Vector<float> > B;  
  B = BR.getBoxrates();  // FIX: get B for only one edb?



  for (int nedb = FIRSTEDB; nedb < MAXEDB; nedb++){

    // local versions of class arrays; C2 refers to routine name calc2
    TNT::Vector<float> NspillC2(grp.size(),0.0);    // spillover rates
    TNT::Vector<float> NspilltilC2(grp.size(),0.0); // ghost-count-corrected

    result = calc2(grp,nedb,B[nedb],NspillC2,NspilltilC2,badspecies);

    if (result != 0){ // some species are misbehaving, remove them for
		      // this edb

      // figure out number of ions left in group
      int newsize = 0;
      for (int s = 0; s < grp.size(); s++){
	if (badspecies[s]) newsize++;
      }
      newsize = grp.size() - newsize; 

      // remove misbehaving ions from group
      vector<Ion> newgrp;
      //newgrp.reserve(newsize);
      TNT::Vector<float> newB(newsize, 0.0);
      int t = 0;
      for (int s = 0; s < grp.size(); s++){

	if (badspecies[s]){
	  Removed[nedb][s] = true; // FIX: Removed is superflous; use
				   // badspecies

	  cout << thisprog << " -I- " 
	       << grp[s].name 
	       << " has been removed from analysis in edb " 
	       << nedb << endl;

	  if (t < newsize){
	    //newgrp[t]= grp[s];
	    newgrp.push_back(grp[s]);
	    newB[t] = B[nedb][s];
	    t++;
	  }
	  else{
	    cout << thisprog << " -E- tried to write beyond (t=" << t
		 << ") new group size ("
		 << newsize << ")" << endl;
	  }
	}
      }

      // re-run calc2
      // Note: must use 'new' vectors because they are smaller
      TNT::Vector<float> newNspillC2(newsize, 0.0);
      TNT::Vector<float> newNspilltilC2(newsize, 0.0);

      result = calc2(newgrp,nedb,newB,newNspillC2,newNspilltilC2,badspecies);

    }

    // copy results into class-wide vectors, taking missing into account
    int sC2 = 0;
    for(int s = 0; s < grp.size(); s++){
      if (Removed[nedb][s]){
	Nspill[nedb][s] = 0.0;
	Nspilltil[nedb][s] = 0.0;
      }
      else{
	Nspill[nedb][s] = NspillC2[sC2];
	Nspilltil[nedb][s] = NspilltilC2[sC2];
	sC2++;
      }
    }
    
    
  } // loop over edbs

  return(0);
}

int SpillRates::calc2(const vector<Ion>& grp, int nedb,
		      TNT::Vector<float>& B,
		      TNT::Vector<float>& NspillC2,
		      TNT::Vector<float>& NspilltilC2, 		      
		      vector<bool>& badspecies){
  /* Description:
       Does spillover rate calculations (and part of ghost count removal) for
       all species at one charge step.
  */
  
  string thisprog = "SpillRates::calc2";
  int DbgLvl = gDbgLvl;
  int retval = 0;  // return value of this routine
                   // 0 -> no bad species; 1 -> bad species exist

  // local numerical arrays
  TNT::Matrix<float> S(grp.size(),grp.size(),0.0);      // spillover matrix
  TNT::Matrix<float> Sinv(grp.size(),grp.size(),0.0);   // inverse of S
  TNT::Vector<float> Btil(grp.size(),0.0); // ghost-count-corrected box rates
  // Bcorr are boxrates from B and Btil, depending on sign of Nspill
  TNT::Vector<float> Bcorr(grp.size(),0.0);

  /* -----------------------------------------------------------------------
     ----------------------------------------------------------------------- */

  /* ---------------- Calculate S by elements, ref. 1, eq. 3 ---------------
     ----------------------------------------------------------------------- */
  double Stofp,Stofm, Sesdp, Sesdm;  // args to the erf in eq.
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

      S[s][t] = (1.0/2.0)*( erff(Stofp) - erff(Stofm) ) *
	(1.0/2.0)*( erff(Sesdp) - erff(Sesdm) );
	
      if (DbgLvl >= 4 && S[s][t] != 0.0) {
	cout << thisprog << " -D- S[" 
	     << nedb << "]["
	     << s << "]["
	     << t << "]="
	     << S[s][t] << endl;
      }

    } // loop over species t
  } // loop over species s
    
  /* ----------------------- invert S --------------------------------------
     ----------------------------------------------------------------------- */
  Sinv = Invert(S);

  /* --- test inversion --- */
  if (nedb == 48 && DbgLvl >= 3) {
    cout << thisprog << " -D- testing inversion..." << endl;
    TNT::Matrix<float> I(S.dim(1),S.dim(1), 1.0E-5);
    TNT::Matrix<float> P(S.dim(1),S.dim(1), 0.0);

    P = S * Sinv;
    // make identity matrix
    for (int i = 0; i < I.dim(1); i++){
      I[i][i] = 1.0;
    }
    
    //if (I == 1.0) cout << thisprog << " -D- I == 1.0" << endl;

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

  /* ---------------- calculate spillover rates ----------------------------
     ----------------------------------------------------------------------- */
  NspillC2 = Sinv * B;
  
  /* -------------- calculate ghost-count corrected box rates --------------
     ----------------------------------------------------------------------- */
  // FIX: only calc for species with Nspill < 0 ?
  for (int s = 0; s < grp.size(); s++){
    for (int t = 0; t < grp.size(); t++){
      if (t != s){
	// derived from equation 7
	Btil[s] += - Sinv[s][t] * B[t]
	  / Sinv[s][s];
      }
    } // loop over species t
  } // loop over species s


  /* ---------- calculate ghost-count-correct spillover rates (eq 8) -------
     ----------------------------------------------------------------------- */
  
  for (int s = 0; s < grp.size(); s++){
    if (nedb == 41){
      cout << thisprog << " -D- Nspill["
	   << s << "]=" << Nspill[s] << endl;
    }

    // if block replaces Heaviside step function, theta, in eq 8
    if (NspillC2[s] >= 0.0){
      Bcorr[s] = B[s];
    }
    else if (NspillC2[s] < 0.0){
      Bcorr[s] = Btil[s];
	
      badspecies[s] = true;
      retval = 1;

      cout << thisprog << " -D- nedb=" << nedb << " s=" << s
	   << " adding " << grp[s].name << " to removal list" 
	   << " NspillC2=" << NspillC2[s] << endl; 
    }
  }

  // equation 8
  NspilltilC2 = Sinv * Bcorr;

  return(retval);
}


/* -----------------
   PRIVATE FUNCTIONS
   -----------------
*/
