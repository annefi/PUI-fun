/*
  File: DistFunc.h

  Description:

    Calculate observed distribution function and moments from
    probabilistic rates.

  Author: Jim Raines, 21Aug2001

  Method:

    
    
  Major Modification History:
    

*/

#include "swindal.h"

DistFunc::DistFunc(int N){
  n.reserve(N);
  v0.reserve(N);
  vth.reserve(N);
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

int DistFunc::calc(const vector<Ion>& grp, const AnalysisData& ad, ProbRates PR){
  /* Notes:

     1.  i and nedb are used interchangably to mean the number of the 
     E/q step

     2.  The variables A, v, delta_v, and n are actually
     dimension-less versions, having been divide by a reference value.
     See hardcopy notes for now.

     3.  This will (likely) work with other rates besides prob. ones

  */
  // velocity at step i
  vector <float> v;
  v.reserve(MAXEDB);

  /* delta v at step i is an ave. velocity at that step */
  vector <float> delta_v; 
  delta_v.reserve(MAXEDB);

  // A (tilde), dimension-less exp. related to dist. func.
  vector <float> A;
  A.reserve(MAXEDB);

  // E/q acceptance ranges
  vector<float> delta_eq;
  delta_eq.reserve(MAXEDB);

  // Duty Cycle
  float D = 1.0;    // 1.0, until I figure it out

  // Effeciency
  float eff = 1.0;  // 1.0, until we figure it out

  for (int nedb = FIRSTEDB; nedb < MAXEDB; nedb++){
    delta_eq[nedb] = ad.EqAcceptFac * ad.Eqtab[nedb];
  }

  for (int s = 0; s < grp.size(); s++){
    // define some notational short cuts
    float m = grp[s].mass;
    float q = grp[s].charge;

    // -- variables for holding intermediate results --

    // calc. v[i] and  for all i, km/s
    // note: constant is unit conversion, 9.648e4 e amu km^2 / keV s^2
    for (int nedb = FIRSTEDB; nedb < MAXEDB; nedb++){
      v[nedb] = sqrt( 2 * ad.Eqtab[nedb]* q/m * 9.648e4 );
    }

    // calculate A[i] for all i
    for (int nedb = FIRSTEDB; nedb < MAXEDB; nedb++){
      // calc. delta_v[i] 
      if ( nedb == FIRSTEDB ){ // WARNING: check with Nathan
	delta_v[nedb] = sqrt(v[nedb]*v[nedb+1]) -  sqrt(v[nedb]*v[nedb]);
      }
      else if ( nedb == (MAXEDB - 1) ){
	delta_v[nedb] = sqrt(v[nedb]*v[nedb]) -  sqrt(v[nedb]*v[nedb-1]);
      }
      else{
	delta_v[nedb] = sqrt(v[nedb]*v[nedb+1]) -  sqrt(v[nedb]*v[nedb-1]);
      }

      delta_v[nedb] = fabs(delta_v[nedb]); // absolute value
      
      A[nedb] = 
	PR.getProbRate(nedb,s) / (eff * v[nedb] * ( q * delta_eq[nedb] ) );
    }
    
    // calulate 0th moment (sums over i)
    float nD_over_v0 = 0.0;// n*D over v0, density * duty cycle / bulk velocity
    for (int nedb = FIRSTEDB; nedb < MAXEDB; nedb++){
      nD_over_v0 += A[nedb] * delta_v[nedb];
    }

    // calulate 1st moment (sums over i)
    float nD = 0.0;        // n*D
    for (int nedb = FIRSTEDB; nedb < MAXEDB; nedb++){
      nD += A[nedb] * v[nedb] * delta_v[nedb];
    }

    // calculate 1st state quantitie
    v0[s] = nD / nD_over_v0;

    // calulate 2nd moment (sums over i)
    float nDvth2_over_v0 = 0.0;  // n*D*vth^2 over v0, vth is thermal velocity
    for (int nedb = FIRSTEDB; nedb < MAXEDB; nedb++){
      nDvth2_over_v0 += A[nedb] * pow((v[nedb] - v0[s]),2) * delta_v[nedb];
    }

    // calculate remaining state quantities
    vth[s] = sqrt( nDvth2_over_v0 / nD_over_v0 );

    // n in nD (on rhs) is unit-less n (n~), n[s] is in cm^(-3)
    n[s] = (1.0/(ad.GeomFactor * 1.0e5)) * nD / D;     // 1.0E5 cm/km

  } // loop over species
}



