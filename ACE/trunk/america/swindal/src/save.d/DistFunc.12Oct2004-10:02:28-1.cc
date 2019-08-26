/*
  File: DistFunc.h

  Description:

    Calculate observed distribution function and moments from
    probabilistic rates.

  Author: Jim Raines, 21Aug2001

  Method:

  Revision controlled by CVS:
  $Id: DistFunc.cc,v 1.10 2004/09/24 15:24:45 jraines Exp $
    
  Major Modification History:
    01Jun2004  jmr  Changed to newly derived distribution function equations.
                    Old version became DistFunc1.

*/

#include "swindal.h"

// for output function
#include <sys/types.h>   // for FM mod. time (open)
#include <sys/stat.h>    // for FM mod. time (fstat)
#include <fcntl.h>       // for FM mod. time (open)
#include <unistd.h>      // for FM mod. time (fstat)
#include <time.h>        // for creation time in header


DistFunc::DistFunc(int N){
  n.assign(N,0.0);
  v0.assign(N,0.0);
  vth.assign(N,0.0);

  // build initial A array, 
  vector<float> tmp;
  tmp.assign(MAXEDB, 0.0);
  for (int i = 0; i < N; i++){
    A.push_back(tmp);
  }
  
}

float DistFunc::getDensity(int s){
  return(n[s]);
}

float DistFunc::getBulkVelocity(int s){
  return(v0[s]);
}

float DistFunc::getThermVelocity(int s){
  return(vth[s]);
}

int DistFunc::calc(const vector<Ion>& grp, const AnalysisData& ad, 
		   ProbRates PR, AceSwicsDutyCycle duty){
  /* Notes:

     1.  i and nedb are used interchangably to mean the number of the 
     E/q step

     2.  The variables A, v, delta_v, and n are actually
     dimension-less versions, having been divided by a reference value.
     See hardcopy notes for now.

     3.  This will (likely) work with other rates besides prob. ones
         if the variable type was changed in the prototype.

     4.  These equations were derived by Sue and confirmed by Thomas and Jim, 
         May 2004.
  */
  string thisprog = "DistFunc::calc";

  // velocity at step i
  vector <float> v;
  v.reserve(MAXEDB);

  /* delta v at step i is an ave. velocity at that step */
  vector <float> delta_v; 
  delta_v.reserve(MAXEDB);

  // E/q acceptance ranges
  vector<float> delta_eq;
  delta_eq.reserve(MAXEDB);

  // efficiency object
  UlyssesSwicsEffic eff_obj;
  string dir = "/shrg1/ulysses/calib/effic";  // FIX: do not embed here
  eff_obj.setEfficDirectory(dir);

  // no longer needed
  //   for (int nedb = FIRSTEDB; nedb < MAXEDB; nedb++){
  //     delta_eq[nedb] = ad.EqAcceptFac * ad.Eqtab[nedb];
  //   }

  for (int s = 0; s < grp.size(); s++){
    // define some notational short cuts
    float m = grp[s].mass;
    float q = grp[s].charge;

    // -- variables for holding intermediate results --

    // calc. v[i] and  for all i, km/s
    // note: constant is unit conversion, 9.648e4 e amu km^2 / keV s^2
    for (int nedb = FIRSTEDB; nedb < MAXEDB; nedb++){
      v[nedb] = sqrt( 2.0 * ad.Eqtab[nedb]* q/m * 9.648e4 );
    }

    // calculate phase space density (A[i]) for all i
    // A[i] = Nsi / (sqrt(delta_eq) tau g eta vi^4)
    // units: s^3/(cm^2 km^4)
    float sum_A = 0.;  // sum of A over nedb for normalization
    for (int nedb = FIRSTEDB; nedb < MAXEDB; nedb++){
//       // calc. delta_v[i] 
//       if ( nedb == FIRSTEDB ){ // WARNING: Not in Nathan's derivation
// 	delta_v[nedb] = sqrt(v[nedb]*v[nedb+1]) -  sqrt(v[nedb]*v[nedb]);
//       }
//       else if ( nedb == (MAXEDB - 1) ){
// 	delta_v[nedb] = sqrt(v[nedb]*v[nedb]) -  sqrt(v[nedb]*v[nedb-1]);
//       }
//       else{
// 	delta_v[nedb] = sqrt(v[nedb]*v[nedb+1]) -  sqrt(v[nedb]*v[nedb-1]);
//       }

      // calc. delta_v[i] between each v[i]
      if ( nedb == (MAXEDB - 1) ){
	/* This is somewhat arbitrary but few if any counts should land 
	   here so it should not matter. */
	delta_v[nedb] = delta_v[nedb-1];
      }
      else{
	delta_v[nedb] = v[nedb] - v[nedb+1];
      }
      delta_v[nedb] = fabs(delta_v[nedb]); // absolute value
      
      // Efficiency
      float etot = ad.Eqtab[nedb] + ad.Ions[s].charge*ad.PapsVolt;
      float eff = eff_obj.getEffic(ad.Ions[s].name , etot);
      //float eff = 1.0;  // for testing

      if (eff >= 0.) {
	A[s][nedb] = PR.getProbRate(nedb,s) * pow(438.,2.0) / 
	  (ad.EqAcceptFac * eff * ad.GeomFactor * pow(v[nedb],4));
      }
      else A[s][nedb] = 0.0; //FIX: is this what we want?

      sum_A += A[s][nedb];
    }
    
    cout << thisprog << " -I- sum_A = " << sum_A << endl;

    // This did not work
//     // normalize A
//     for (int nedb = FIRSTEDB; nedb < MAXEDB; nedb++){
//       A[s][nedb] = A[s][nedb]/sum_A;
//     }    

    // calculate 0th moment (sums over i)
    // F0 = n D / v0^2
    // units: s^2/(cm^2 km^3)
    float F0 = 0.0;
    for (int nedb = FIRSTEDB; nedb < MAXEDB; nedb++){
      F0 += A[s][nedb] * delta_v[nedb];
    }

    // calculate 1st moment (sums over i)
    // F1 = n D / v0
    // units: s/(cm^2 km^2)
    float F1 = 0.0;
    for (int nedb = FIRSTEDB; nedb < MAXEDB; nedb++){
      F1 += A[s][nedb] * v[nedb] * delta_v[nedb]; 
    }

    // calculate state quantity: bulk velocity (v0) in km/s
    v0[s] = F1/F0;

    // calculate 2nd moment (sums over i)
    // F2 = n D vth^2 / v0^2
    // units: 1/(cm^2 km)
    float F2 = 0.0;
    for (int nedb = FIRSTEDB; nedb < MAXEDB; nedb++){
      F2 += A[s][nedb] * pow((v[nedb] - v0[s]),2) * delta_v[nedb];
    }

    // calculate state quantity: thermal velocity (vth) in km/s
    // vth = sqrt( (n D vth^2 / v0^2) * (v0^2/ n D) )
    vth[s] = sqrt( F2 / F0 );

    // Duty Cycle
    float delta_psi = vth[s]/v0[s];
    if (gDbgLvl >= 1) {
      cout << thisprog << " -I- delta_psi = " << delta_psi << endl;
      cout << thisprog << " -I- CycleTime = " << ad.CycleTime << endl;
    }
    float D = duty.calcByInterpolation(ad.CycleTime, delta_psi);

    // calculate state quantity: density (n) in cm^-3
    // n = (n D / v0)^2 * n D / v0^2 D
    // factor 1 km / 1.0e5 cm converts from cm^-2 km^-1 to cm^-3
    if (D > 0.) {
      //n[s] = F1 * v0[s] / (D * 1.0e5);
      n[s] = pow(F1,2.0) / (D * F0 * 1.0e5);
    }
    else {
      n[s] = -1.0;
    }

  } // loop over species
}


int DistFunc::outputNVT(FILE *OUT, float doyfr, AnalysisData ad){
  const char fmfile[] = "/home/jraines/ace/axfmtweak/xfmexp.cc";

  static bool FirstTime = true;

  // keep fields the same total width!
  char hdrfmt[] ="# %6s %6s %8s %8s %8s\n";
  char datafmt[]="  %6.2f %6s %8.2e %8.2e %8.2e\n";

  if (FirstTime) {  // print header first time through 
    fprintf(OUT,"# State variables from ACE Level II data processor (v2.0)\n");

    // get and format calendar time for header
    time_t now;
    char timestr[19];
    time(&now);
    strftime(timestr, 19, "%d%b%Y %H:%M:%S", localtime(&now));
    fprintf(OUT,"# Created: %s\n", timestr);

    // get and format modification time for xfmexp
    struct stat fmstat;
    int FMFILE = open(fmfile, O_RDONLY);
    fstat(FMFILE, &fmstat);
    close(FMFILE);
    strftime(timestr, 19, "%d%b%Y %H:%M:%S", localtime(&fmstat.st_mtime));
    fprintf(OUT,"# FM Last Modified: %s\n", timestr);

    // column headings
    fprintf(OUT,hdrfmt,"doyfr","ion","n","v", "vth");

    FirstTime = false;
  }

  for (int s = 0; s < ad.Ions.size(); s++){
    fprintf(OUT, datafmt, doyfr, ad.Ions[s].name.c_str(),
	    getDensity(s), getBulkVelocity(s), getThermVelocity(s));
  }


}

int DistFunc::outputDF(FILE *OUT, float doyfr, AnalysisData ad){
  const char fmfile[] = "/home/jraines/ace/axfmtweak/xfmexp.cc";

  static bool FirstTime = true;

  // keep fields the same total width!
  char hdrfmt[] ="# %6s %3s %8s %6s %10s %10s\n";
  char datafmt[]="  %6.2f %3d %8.2f %6s %10.2e %10.2e\n";

  if (FirstTime) {  // print header first time through 
    fprintf(OUT,"# Distribution function from ACE Level II data processor (v2.0)\n");

    // get and format calendar time for header
    time_t now;
    char timestr[19];
    time(&now);
    strftime(timestr, 19, "%d%b%Y %H:%M:%S", localtime(&now));
    fprintf(OUT,"# Created: %s\n", timestr);

    // get and format modification time for xfmexp
    struct stat fmstat;
    int FMFILE = open(fmfile, O_RDONLY);
    fstat(FMFILE, &fmstat);
    close(FMFILE);
    strftime(timestr, 19, "%d%b%Y %H:%M:%S", localtime(&fmstat.st_mtime));
    fprintf(OUT,"# FM Last Modified: %s\n", timestr);

    // column headings
    // note: 'fill' column is present only to mimic format of other rate files
    fprintf(OUT,hdrfmt,"doyfr","edb","E/q","ion","distfunc", "fill");

    FirstTime = false;
  }

  for (int s = 0; s < ad.Ions.size(); s++){
    for (int nedb = FIRSTEDB; nedb < MAXEDB; nedb++){
       fprintf(OUT, datafmt, doyfr, nedb, ad.Eqtab[nedb],
             ad.Ions[s].name.c_str(), A[s][nedb], -1.0);
     }
   }

 }
