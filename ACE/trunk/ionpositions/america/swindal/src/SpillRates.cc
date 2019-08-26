/*  
  Filename: SpillRates.cc

  Description:
    This class contains spillover matrices and routines needed to perform
    spillover correction of box rates.

  Author:  Jim Raines, 31Jul2001

  Method:

  Revision controlled by CVS:
  $Id: SpillRates.cc,v 1.10 2005/06/07 00:06:40 jraines Exp $

  Major Modification History:

*/

#include "swindal.h"
#include "swindal_nr.h"

// include files for creation time and mod. time in output files
#include <sys/types.h>   // for FM mod. time (open)
#include <sys/stat.h>    // for FM mod. time (fstat)
#include <fcntl.h>       // for FM mod. time (open)
#include <unistd.h>      // for FM mod. time (fstat)

#include <time.h>        // for creation time in header

using std::ofstream;

SpillRates::SpillRates(int N){

  TNT::Vector<float> tmpv(N, 0.0);
  for (int i = 0; i < MAXEDB; i++){
    Nspill.push_back(tmpv);
    Nspilltil.push_back(tmpv);
  }

  names.reserve(N);

  negRateCutoff = 0.03;
  maxIterations = 5;
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

int SpillRates::calc(vector<Ion>& orig_grp, BoxRates BR){
  /* Method: 

       While looping over EDBs (charge steps), the passed in group is
       first run through calc2.  Calc2 returns a list of ions had
       negative spill rates at that EDB.  These ions are then removed
       from the group and passed into calc2 again.  There is
       currently *only* one of these iterations.
  */

  string thisprog = "SpillRates::calc";
  int result;

  // grab ion names for printing and misc
  names.clear();  // get rid of previous names, prob un-needed
  vector<Ion> grp; // local group, changes in size with iterations
  for (int s = 0; s < orig_grp.size(); s++){
    names.push_back(orig_grp[s].name);
    grp.push_back(orig_grp[s]);
  }
  
  vector<TNT::Vector<float> > B;  
  B = BR.getBoxrates();

  int niter;
  for (int nedb = FIRSTEDB; nedb < MAXEDB; nedb++){
    // init B for this EDB to size of original group
    TNT::Vector<float> Bedb(orig_grp.size(), 0.0);
    Bedb = B[nedb];

    // init grp for this EDB to size of original group
    vector<Ion> grp; // local group, changes in size with iterations
    grp.clear();
    for (int s = 0; s < orig_grp.size(); s++){
      grp.push_back(orig_grp[s]);
    }

    // local versions of class arrays; C2 refers to routine name calc2
    vector<bool> badspecies(orig_grp.size(), false); // badspecies[s] = true
					      // means species s to be
                                              // removed from analysis

    TNT::Vector<float> NspillC2(orig_grp.size(),0.0);    // spillover rates
    TNT::Vector<float> NspilltilC2(orig_grp.size(),0.0); // ghost-count-corrected

    niter = 1;
    while (niter < maxIterations){ // iterate calc2

      if (gDbgLvl >= 1) {
	cout << thisprog << " -I- working on iteration " << niter << endl;
      }

      result = calc2(grp,nedb,Bedb,NspillC2,NspilltilC2,badspecies);

      if (result == 0) break;  // we are done, why bother

      int newsize = grp.size();  // newsize starts with old size
      float sumPosNSpilltilC2 = 0.0;
      for (int s = 0; s < grp.size(); s++){
	if (NspilltilC2[s] < 0.0) {
	  badspecies[s] = true;
	  newsize--;
	}
	else { // calculate sum of positive rates
	  sumPosNSpilltilC2 += NspillC2[s];
	}
      }

      if (newsize == grp.size()) break;  // no bad spill rates, done w/iter

      /* ---------------------------------------------------------------------
	 Re-check bad species to be sure they are big enough to worry about
	 ---------------------------------------------------------------------
      */
      float frac;
      for (int s = 0; s < grp.size(); s++){
        // Remove 'bad' flag for species with small enough spill rates
	if (badspecies[s]){
	  frac = fabs(NspilltilC2[s]/sumPosNSpilltilC2);
	  if ( frac <= negRateCutoff ){ // put it back
	    badspecies[s] = false;
	    newsize++;
	  }
	}
      }

      if (newsize == grp.size()) break;  // no bad spill rates, done w/iter

      /* ---------------------------------------------------------------------
	 Copy into tmp. variables
	 NOTE:  Temporary variables must be used since resize cannot be done 
	 until good species are copied out.
	 ---------------------------------------------------------------------
      */
      vector<Ion> tmpgrp;
      TNT::Vector<float> tmpB(newsize, 0.0);
      TNT::Vector<float> tmpNspillC2(newsize, 0.0);
      TNT::Vector<float> tmpNspilltilC2(newsize, 0.0);
      int t = 0;
      for (int s = 0; s < grp.size(); s++){
	// Form new group (etc) excluding 'bad' species
	if ( ! badspecies[s]){
	  if (t < newsize){
	    tmpgrp[t] = grp[s];
	    tmpB[t] = Bedb[s];
	    t++;
	  }
	  else{
	    cout << thisprog << " -E- tried to write beyond (t=" << t
		 << ") new group size ("
		 << newsize << ")" << endl;
	  }
	}
	else {
	  if (gDbgLvl >= 3){
	    cout << thisprog << " -I- " 
		 << grp[s].name 
		 << " (s=" << s << ") REMOVED from analysis in edb " 
		 << nedb << endl;
	  }
	}	  
      }

      /* -------------------------------------------------------------------
	 Resize non-tmp arrays and fill with contents of tmp arrays
	 ------------------------------------------------------------------- */
      // is group right size?
      TNT::Vector<float> Bedb(newsize,0.0);
      TNT::Vector<float> NspillC2(newsize,0.0);    // spillover rates
      TNT::Vector<float> NspilltilC2(newsize,0.0); // ghost-count-corrected
      for (int s = 0; s < newsize; s++){
	NspillC2[s] = tmpNspillC2[s];
	NspilltilC2[s] = tmpNspilltilC2[s];
	Bedb[s] = tmpB[s];
      }
      // resize grp to the size of tmpgrp and copies in elements of tmpgrp
      grp.swap(tmpgrp);  

      // Does not work; causes endless loop
      //tmpgrp.~vector<Ion>();  // destroy tmpgrp

      // re-init and resize
      vector<bool> badspecies(newsize, false);

      niter++;
    }

    // copy results into class-wide vectors, taking missing into account,
    // now that we are done iterating this EDB.
    int sC2 = 0;  // species counter in C2 arrays
    static bool FirstTime = true;
    for(int s = 0; s < orig_grp.size(); s++){
      if (orig_grp[s].name == grp[sC2].name){
	if (NspilltilC2[sC2] >= 0.0){
	  Nspill[nedb][s] = NspillC2[sC2];
	  Nspilltil[nedb][s] = NspilltilC2[sC2];
	}
	else {
	  Nspill[nedb][s] = 0.0;
	  Nspilltil[nedb][s] = 0.0;
	}

	/* Zero spillover rates corresponding to zero box rates 
	   ----------------------------------------------------
	   The thinking here is that the forward model should not
	   align so poorly as to miss an entire peak.  Therefore,
	   these rates must be generated by the spillover removal,
	   probably as residuals in the matrix inversion.  */
	if (FirstTime && gDbgLvl >= 1) {
	  cout << thisprog << " -I- manually zeroing spillover rates "
	       << "corresponding to zero box rates" << endl;
	  FirstTime = false;
	}
	if (B[nedb][s] <= 0.) {
	  Nspill[nedb][s] = 0.0;
	  Nspilltil[nedb][s] = 0.0;
	}

	sC2++;
      }
      else{
 	Nspill[nedb][s] = 0.0;
	Nspilltil[nedb][s] = 0.0;
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

      S[s][t] = (1.0/2.0)*( nr::erff(Stofp) - nr::erff(Stofm) ) *
	(1.0/2.0)*( nr::erff(Sesdp) - nr::erff(Sesdm) );
	
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
  
  /* --- calculate ghost-count-correct box and spillover rates (eq 8) ------
     ----------------------------------------------------------------------- */
  // FIX: only calc for species with Nspill < 0 ?
  for (int s = 0; s < grp.size(); s++){
    // if-block replaces Heaveside step function, theta, in eq 8
    if (NspillC2[s] >= 0.0){  // Bcorr[s] is B[s]  
      Bcorr[s] = B[s];
    }
    else if (NspillC2[s] < 0.0){ // Bcorr[s] is Btil[s] in eq. 8
      for (int t = 0; t < grp.size(); t++){
	if (t != s){
	  // derived from equation 7
	  Bcorr[s] += - Sinv[s][t] * B[t]
	    / Sinv[s][s];
	}
      } // loop over species t
    }
  } // loop over species s

  NspilltilC2 = Sinv * Bcorr;

  return(retval);
}

void SpillRates::setNegRateCutoff(float cutoff){
  if (cutoff > 0 && cutoff < 1.0)  negRateCutoff = cutoff;
  else if (gDbgLvl >= 1)
    cout << "SpillRates::setNegRateCutoff -E- cutoff out of range ("
	 << cutoff << "); " 
	 << "should be 0 < cutoff < 1.0" << endl;
}

float SpillRates::getNegRateCutoff(void){
  return(negRateCutoff);
}

void SpillRates::setMaxIterations(unsigned int maxiter){
  maxIterations = maxiter;
}
int  SpillRates::getMaxIterations(void){
  return(maxIterations);
}

int SpillRates::output(FILE *SRF, float doyfr, const AnalysisData& ad){

  static bool FirstTime = true;

  // keep fields the same total width!
  char hdrfmt[] ="# %7s %3s %8s %6s %10s %10s\n";
  char datafmt[]=
  "  %7.3f %3d %8.2f %6s %10.2e %10.2e\n";

  if (FirstTime) {  // print header first time through 
    fprintf(SRF,"# Spillover rates from ACE Level II data processor (v2.0)\n");

    // get and format calendar time for header
    time_t now;
    char timestr[19];
    time(&now);
    strftime(timestr, 19, "%d%b%Y %H:%M:%S", localtime(&now));
    fprintf(SRF,"# Created: %s\n", timestr);

    fprintf(SRF,"# SpillRates: %s\n", "$Id: SpillRates.cc,v 1.10 2005/06/07 00:06:40 jraines Exp $");

    // column headings
    fprintf(SRF,hdrfmt,"doyfr", "EDB", "E/q","ion","spillrate",
	    "spillcnt");

    FirstTime = false;
  }

  float sr;
  for (int s = 0; s < ad.Ions.size(); s++){
    for (int nedb = FIRSTEDB; nedb < MAXEDB; nedb++){
      sr = getCorSpillRate(nedb, s);
      fprintf(SRF, datafmt, doyfr, nedb, ad.Eqtab[nedb], 
	      ad.Ions[s].name.c_str(),
	      getCorSpillRate(nedb, s), 
	      gAccumTime*getCorSpillRate(nedb,s));
    }
  }

}


  

/* -----------------
   PRIVATE FUNCTIONS
   -----------------
*/

