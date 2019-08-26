/*
  File: DistFunc.h

  Description:

    Calculate observed distribution function and moments from
    probabilistic rates.

  Author: Jim Raines, 21Aug2001

  Method:

  Revision controlled by CVS:
  $Id: DistFunc.cc,v 1.50 2005/06/09 04:06:12 jraines Exp $
    
  Major Modification History:
    01Jun2004  jmr  Changed to newly derived distribution function equations.
                    Old version became DistFunc1.
    -------->  jmr  Many unrecorded changes to DF equations(->3d->1d->1/439...)
    22Nov2004  jmr  Switched back to 3d before sending to Ruedi
*/

#include "swindal.h"
#include "nr.h"
#include "nrutil.h"

// for output function
#include <sys/types.h>   // for FM mod. time (open)
#include <sys/stat.h>    // for FM mod. time (fstat)
#include <fcntl.h>       // for FM mod. time (open)
#include <unistd.h>      // for FM mod. time (fstat)
#include <time.h>        // for creation time in header


DistFunc::DistFunc(int N){
  n.assign(N,0.0);
  n_err.assign(N,0.0);
  v0.assign(N,0.0);
  vth.assign(N,0.0);

  fit_n.assign(N,0.0);
  fit_v0.assign(N,0.0);
  fit_vth.assign(N,0.0);
  fit_err.assign(N,0.0);

  quality.assign(N,0);

  // build initial A array, 
  vector<float> zero;
  vector<float> neg_one;
  zero.assign(MAXEDB, 0.0);
  neg_one.assign(MAXEDB, -1.0);
  for (int i = 0; i < N; i++){
    v.push_back(zero);
    A.push_back(zero);
    ErrA.push_back(zero);
    fit_A.push_back(zero);
    Err_fit_A.push_back(neg_one);
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
		   ProbRates PR, AceSwicsDutyCycle duty,
		   UlyssesSwicsEffic eff_obj){
  /* Notes:

     1.  i and nedb are used interchangably to mean the number of the 
     E/q step

     2.  This will (likely) work with other rates besides prob. ones
         if the variable type was changed in the prototype.

  */
  string thisprog = "DistFunc::calc";

  /* delta v at step i is an ave. velocity at that step */
  vector <float> delta_v; 
  delta_v.reserve(MAXEDB);

  // E/q acceptance ranges
  vector<float> delta_eq;
  delta_eq.reserve(MAXEDB);

  // efficiency object
  ;
  // no longer needed
  //   for (int nedb = FIRSTEDB; nedb < MAXEDB; nedb++){
  //     delta_eq[nedb] = ad.EqAcceptFac * ad.Eqtab[nedb];
  //   }

  for (unsigned int s = 0; s < grp.size(); s++){
    if (gDbgLvl >= 1){
      cout << thisprog << " -I- calculating nvt for " << ad.Ions[s].name
	   << endl;
    }

    // define some notational short cuts
    float m = grp[s].mass;
    float q = grp[s].charge;

    // -- variables for holding intermediate results --

    // calc. v[i] and  for all i, km/s
    // note: constant is unit conversion, 9.648e4 e amu km^2 / keV s^2
    for (int nedb = FIRSTEDB; nedb < MAXEDB; nedb++){
      v[s][nedb] = sqrt( 2.0 * ad.Eqtab[nedb]* q/m * 9.648e4 );
    }

    // calculate phase space density (A[i]) for all i
    // A[i] = Nsi / (sqrt(delta_eq) tau g eta vi^4)
    // units: s^3/(cm^2 km^4)
    float sum_A = 0.;  // sum of A over nedb for normalization
    float sigsq_f1_dc = 0.;
    float f1_dc = 0.;
    float sigsq_f0_dc = 0.;
    float f0_dc = 0.;
    for (int nedb = FIRSTEDB; nedb < MAXEDB; nedb++){

      // calc. delta_v[i] between each v[i]
      if ( nedb == (MAXEDB - 1) ){
	/* This is somewhat arbitrary but few if any counts should land 
	   here so it should not matter. */
	delta_v[nedb] = delta_v[nedb-1];
      }
      else{
	delta_v[nedb] = v[s][nedb] - v[s][nedb+1];
      }
      delta_v[nedb] = fabs(delta_v[nedb]); // absolute value
      
      // Efficiency
      float etot = ad.Eqtab[nedb] + ad.Ions[s].charge*ad.PapsVolt;
      float eff = eff_obj.getEffic(ad.Ions[s].name , etot);
      //float eff = 1.0;  // for testing
      //cout << thisprog << " -W- eff hardcoded to " << eff
      //   << " for debugging" << endl;

      if (eff >= 0.) {
	// distribution function in s^3/km^6
	A[s][nedb] = 2 * PR.getProbRate(nedb,s) * 1.e10 / 
	  (ad.EqAcceptFac * eff * ad.GeomFactor * pow(v[s][nedb],4));

	// Error
	if (PR.getProbRate(nedb,s) > 0.) {
	  ErrA[s][nedb] = sqrt( PR.getProbRate(nedb,s)*gAccumTime ) /
	    (PR.getProbRate(nedb,s)*gAccumTime);

	  // NOTE:  These formulas assume 1D moments used below
	  // square of error in F1 (divided by constants (dc))
	  sigsq_f1_dc += PR.getProbRate(nedb,s) * gAccumTime *
	    pow( delta_v[nedb] / pow(v[s][nedb],3) / eff ,2);

	  // F1 (divided by constants (dc))
	  f1_dc += PR.getProbRate(nedb,s) * gAccumTime *
	    delta_v[nedb] / pow(v[s][nedb],3) / eff;

	  // square of error in F0 (divided by constants (dc))
	  sigsq_f0_dc += PR.getProbRate(nedb,s) * gAccumTime *
	    pow( delta_v[nedb] / pow(v[s][nedb],4) / eff ,2);

	  // F0 (divided by constants (dc))
	  f0_dc += PR.getProbRate(nedb,s) * gAccumTime *
	    delta_v[nedb] / pow(v[s][nedb],4) / eff;
	}
	else {
	  ErrA[s][nedb] = 0.0;
	}
      }
      else {
	A[s][nedb] = 0.0; //FIX: is this what we want?
	ErrA[s][nedb] = -1.0;
      }

      sum_A += A[s][nedb];
    }
    
    // calculate error in density
    n_err[s] = sqrt(4. * sigsq_f1_dc / pow(f1_dc,2) +
		    sigsq_f0_dc / pow(f0_dc,2));

    cout << thisprog << " -I- sum_A = " << sum_A << endl;

    // This did not work
//     // normalize A
//     for (int nedb = FIRSTEDB; nedb < MAXEDB; nedb++){
//       A[s][nedb] = A[s][nedb]/sum_A;
//     }    

    float n_local, v0_local, vth_local;
    calc1dMoments(s, A, delta_v, duty, ad, n_local, v0_local, vth_local);

    v0[s] = v0_local;
    vth[s] = vth_local;
    n[s] = n_local;

    /* -----------------------------------------------------------------
       Calculate n, v0, and vth via gauss fitting if appropriate
       ----------------------------------------------------------------- */
    if (v0[s] > 0.0 && n[s] > 0.){
      //    if (v0[s] > 0.0 && n[s] > 0. && ad.Ions[s].name == "He2+"){
      cout << thisprog << " -I- gauss fitting A for " << ad.Ions[s].name 
	   << endl;
      //int fit_result = GaussFitA(s);

      calc1dMoments(s, fit_A, delta_v, duty, ad, 
		  n_local, v0_local, vth_local);
      /* NOTE:  n_err is calculated above assuming 1D moments so it will be 
	 wrong if 3D moments are used here (in previous line).  
      */

      /* re-assign v0 and vth to moment-derived values
	 true => v0 and vth from moment calculation
	 false => v0 and vth from GaussFitA, i.e. center and width of Gaussian
      */
      if (1){
	fit_v0[s] = v0_local;
	fit_vth[s] = vth_local;
      }
      fit_n[s] = n_local;
    }


  } // loop over species

  int total_quality = determineQuality();

  return(0);
}

int DistFunc::calc3dMoments(const int& s, 
			  const vector< vector<float> >& A_local, 
			  const vector<float>& delta_v, 
			  AceSwicsDutyCycle duty, const AnalysisData& ad,
			  float& n_local, float& v0_local, float& vth_local){

  /* Notes

     1.  These equations have been re-derived many times and are not
     yet confirmed.
  */
  string thisprog = "DistFunc::calcMoments";


  // calculate 0th moment (sums over i)
  // F0 =  n / D
  // units: 1/km^3
  float F0 = 0.0;
  for (int nedb = FIRSTEDB; nedb < MAXEDB; nedb++){
    F0 += A_local[s][nedb] * pow(v[s][nedb],2.0) * delta_v[nedb];
  }

  // calculate 1st moment (sums over i)
  // F1 = n v0 / D
  // units: 1/(km^2 s)
  float F1 = 0.0;
  for (int nedb = FIRSTEDB; nedb < MAXEDB; nedb++){
    F1 += A_local[s][nedb] * pow(v[s][nedb],3.0) * delta_v[nedb]; 
  }

  v0_local = F1/F0;

  // calculate 2nd moment (sums over i)
  // F2 = n D vth^2
  // units: 1/(km s^2)
  float F2 = 0.0;
  for (int nedb = FIRSTEDB; nedb < MAXEDB; nedb++){
    F2 += A_local[s][nedb] * pow((v[s][nedb] - v0_local),2) * 
      pow(v[s][nedb],2.0) * delta_v[nedb];
  }

  // calculate state quantity: thermal velocity (vth) in km/s
  vth_local = sqrt( F2 / F0 );

  // Duty Cycle
  float delta_psi = vth_local/v0_local;
  if (gDbgLvl >= 1) {
    cout << thisprog << " -I- delta_psi = " << delta_psi << endl;
    cout << thisprog << " -I- CycleTime = " << ad.CycleTime << endl;
  }
  float D = duty.calcByInterpolation(ad.CycleTime, delta_psi);

  // calculate state quantity: density (n) in cm^-3
  // n =  n D / factor
  // factor (1 km / 1.0e5 cm)^3 converts from km^-3 to cm^-3
  if (D > 0.) {
    n_local = F0 * D / (1.0e15);
  }
  else {
    n_local = -1.0;
  }


  return(0);
}

int DistFunc::calc1dMoments(const int& s, 
			  const vector< vector<float> >& A_local, 
			  const vector<float>& delta_v, 
			  AceSwicsDutyCycle duty, const AnalysisData& ad,
			  float& n_local, float& v0_local, float& vth_local){

  /* Notes

     1.  These equations have been re-derived many times and are not
     yet confirmed.
  */
  string thisprog = "DistFunc::calc1dMoments";


  // calculate 0th moment (sums over i)
  // F0/D =  n / v0^2
  // units: s^2/km^5
  float F0 = 0.0;
  for (int nedb = FIRSTEDB; nedb < MAXEDB; nedb++){
    F0 += A_local[s][nedb] * delta_v[nedb];
  }

  // calculate 1st moment (sums over i)
  // F1/D = n / v0
  // units: s/km^4
  float F1 = 0.0;
  for (int nedb = FIRSTEDB; nedb < MAXEDB; nedb++){
    F1 += A_local[s][nedb] * v[s][nedb] * delta_v[nedb]; 
  }

  v0_local = F1/F0;

  // calculate 2nd moment (sums over i)
  // F2 / D = n vth^2 / v0^2
  // units: 1/(km^3)
  float F2 = 0.0;
  for (int nedb = FIRSTEDB; nedb < MAXEDB; nedb++){
    F2 += A_local[s][nedb] * pow((v[s][nedb] - v0_local),2) * delta_v[nedb];
  }

  // calculate state quantity: thermal velocity (vth) in km/s
  vth_local = sqrt( F2 / F0 );

  // Duty Cycle
  float delta_psi = vth_local/v0_local;
  if (gDbgLvl >= 1) {
    cout << thisprog << " -I- delta_psi = " << delta_psi << endl;
    cout << thisprog << " -I- CycleTime = " << ad.CycleTime << endl;
  }
  float D = duty.calcByInterpolation(ad.CycleTime, delta_psi);

  // calculate state quantity: density (n) in cm^-3
  // n =  F1^2 / (D F0 factor)
  // factor (1 km / 1.0e5 cm)^3 converts from km^-3 to cm^-3
  if (D > 0.) {
    n_local = pow(F1,2.) / (D * F0 * 1.0e15);
  }
  else {
    n_local = -1.0;
  }


  return(0);
}

int DistFunc::GaussFitA(int s){
  const string thisprog = "DistFunc::GaussFitA";

  /* 0 => normal
     1 => error
  */
  int status = 0; 
  
  /* ----------------------------------------------------------------------
     Set up arrays
     ---------------------------------------------------------------------- */
//   // copy into correct type and eliminating unused elements 0 and 1
//   Vec_DP x(MAXEDB-FIRSTEDB, 0.);
//   Vec_DP y(MAXEDB-FIRSTEDB, 0.);
//   cout << thisprog << " -D- dumping x/y..." << endl;
//   for (int nedb=FIRSTEDB; nedb<MAXEDB; nedb++){
//     x[nedb-FIRSTEDB] = v[s][nedb];
//     y[nedb-FIRSTEDB] = A[s][nedb];
//     cout << "+ nedb=" << nedb << " x=" << x[nedb-FIRSTEDB]
// 	 << " y=" << y[nedb-FIRSTEDB] << endl;
//   }

//  const int MinEDB    = 22; // FIRSTEDB;
//  const int MaxEDB    = 36; // MAXEDB - 1;
  const int MinEDB    = FIRSTEDB;
  const int MaxEDB    = MAXEDB - 1;
  int NumPoints = MaxEDB - MinEDB + 1;
  TNT::Vector<double> x(NumPoints, 0.);
  TNT::Vector<double> y(NumPoints, 0.);

  if (gDbgLvl >= 3) cout << thisprog << " -D- dumping x/y..." << endl;

  float ymax = -1.0;
  for (int nedb=MinEDB; nedb<MaxEDB; nedb++){
    x[nedb-MinEDB] = static_cast<double>(v[s][nedb]);
    y[nedb-MinEDB] = static_cast<double>(A[s][nedb]);

    if (gDbgLvl >= 3){
      cout << "+ nedb=" << nedb << " x=" << x[nedb-MinEDB]
	   << " y=" << y[nedb-MinEDB] << endl;
    }
  
    if (y[nedb-MinEDB] > ymax) ymax = y[nedb-MinEDB];
  }

  // set sigma(As[nedb]) to dummy value
  // FIX: calculate actual
  TNT::Vector<double> sigmas(NumPoints, 0.1);

  // initialize gaussian parameters
  TNT::Vector<double> a(3);  // one 3 parameter Gaussian
  Vec_I_BOOL ia(a.size());
  a[0] = ymax;
  ia[0] = true;
  a[1] = v0[s];
  ia[1] = true;
  a[2] = vth[s];
  ia[2] = true;

  DP alamda = -1.0; // -1 => initialization

  // working variables for mrqmin
  //Mat_O_DP covar(a.size(),a.size());
  //Mat_O_DP alpha(a.size(),a.size());
  TNT::Matrix<DP> covar(a.size(),a.size());
  TNT::Matrix<DP> alpha(a.size(),a.size());
  DP chisq = 1.0;
  
  bool Converged = false;
  bool OneMore = false;
  int num_iter = 1;
  int num_iter_max = 10000;
  DP last_chisq = 0.0;
  DP delta_chisq_cutoff = 1.0e-3;
  while (!Converged  || OneMore){
    /* Fit is judged converged when the fractional change in chisq is
       below the cutoff.  After that, one more call of mrqmin must be
       made, after alamda=0.0, to cause mrqmin to set covar and alpha
       to be set to covariance and curvature matrix for converged
       parameters.  This, unfortunately, complicates the loop logic somewhat.
    */

    // toggle back to false if set; to ensure only *one* more iteration
    if (OneMore) OneMore = false;

    NR::mrqmin(x, y, sigmas, a, ia, covar, alpha, chisq, NR::fgauss, alamda);
    
    if (!Converged){
      DP delta_chisq_frac = abs(last_chisq - chisq)/chisq;
      last_chisq = chisq;
      if ( (delta_chisq_frac <= delta_chisq_cutoff)  && 
	   (num_iter > 1) ){
      // have to have > 1 iteration to see chisq change!

	Converged = true;
	OneMore = true;

	/* setting alamda = 0.0 causes  */
	alamda = 0.0;  

	if (gDbgLvl >= 3){
	  cout << thisprog << " -I- fit converged on iteration=" << num_iter 
	       << endl;
	}
      }
      if (gDbgLvl >= 3 || (gDbgLvl >= 1 && OneMore)){ 
	cout << thisprog << " -I- iteration=" << num_iter << " chisq="
	     << chisq << " last change: " << delta_chisq_frac << endl;
      }
    }
      
    // get out after max iterations
    if (num_iter > num_iter_max) {
      cout << thisprog << " -W- gauss fit failed to converge after " 
	   << num_iter_max << " iterations.  Aborting..." << endl;
      break;
    }

    num_iter++;
  }

  /* ----------------------------------------------------------------------
     Evaluate quality of fit
     ---------------------------------------------------------------------- */
  // Compute the quality of the fit
  // NR C++ sec. 15.1 (p665)
  double Q = NR::gammq(.5*(NumPoints - a.size()),.5*chisq); 

  string quality;
  if (Q < 0.001){
    status = 1;
    quality = "low";
  }
  if (Q > 0.001 && Q < 0.1){
    status = 0;
    quality = "possible, but not well determined";
  }
  if (Q > .1) {
    status = 0;
    quality = "hi";
  }

  if (gDbgLvl >= 1){
    cout << thisprog << " -I- quality of fit:" << endl;
    cout << "+ chisq=" << chisq << endl;
    cout << "+ gammq(.5*" <<NumPoints - a.size() << ", .5*chisq) = " 
	 << Q << endl;
    cout << "+ chances that model parameters fit data: " << quality << endl;

  }

  /* ----------------------------------------------------------------------
     Create a modeled (fit) A and calculate physical parameters
     ---------------------------------------------------------------------- */
  //  if (status == 1 || status == 0){ // no need if fit was bad
  if (1){  // hardcode on for dbg
    DP fit_y;
    TNT::Vector<double> dyda(a.size(), 0.0);
    for (int nedb = MinEDB; nedb <= MaxEDB; nedb++){
      NR::fgauss(x[nedb-MinEDB], a, fit_y, dyda);
      fit_A[s][nedb] = fit_y;

      fit_n[s] += fit_A[s][nedb];
    }

    fit_v0[s] = a[1];
    fit_vth[s] = a[2];
    fit_err[s] = Q; // FIX: this may not be completely true but it is related
  }

  return status;
}

int DistFunc::outputDF(FILE *OUT, float doyfr, AnalysisData ad){
  const char fmfile[] = "/home/jraines/ace/axfmtweak/xfmexp.cc";

  static bool FirstTime = true;

  // keep fields the same total width!
  char hdrfmt[] ="# %7s %3s %8s %8s %6s %10s %10s %10s %10s\n";
  char datafmt[]="  %7.3f %3d %8.2f %8.2f %6s %10.2e %10.2e %10.2e %10.2e\n";

  if (FirstTime) {  // print header first time through 
    fprintf(OUT,"# Distribution function from ACE Level II data processor (v2.0)\n");

    // get and format calendar time for header
    time_t now;
    char timestr[19];
    time(&now);
    strftime(timestr, 19, "%d%b%Y %H:%M:%S", localtime(&now));
    fprintf(OUT,"# Created: %s\n", timestr);

    // include RCS ID in header
    fprintf(OUT,"# DistFunc: %s\n", "$Id: DistFunc.cc,v 1.50 2005/06/09 04:06:12 jraines Exp $");

    // column headings
    // note: 'fill' column is present only to mimic format of other rate files
    fprintf(OUT,hdrfmt,"doyfr","edb","E/q","v",
	    "ion","df", "df_err","fit_df", "fit_df_err");

    FirstTime = false;
  }

  for (unsigned int s = 0; s < ad.Ions.size(); s++){
    for (int nedb = FIRSTEDB; nedb < MAXEDB; nedb++){
      fprintf(OUT, datafmt, doyfr, nedb, ad.Eqtab[nedb],v[s][nedb],
	       ad.Ions[s].name.c_str(), A[s][nedb], ErrA[s][nedb],
	       fit_A[s][nedb], Err_fit_A[s][nedb]);
    }
  }

  return(0);
}

int DistFunc::outputNVT(FILE *OUT, float doyfr, AnalysisData ad){
  const char fmfile[] = "/home/jraines/ace/axfmtweak/xfmexp.cc";

  static bool FirstTime = true;

  // keep fields the same total width!
  char hdrfmt[] ="# %7s %6s %9s %9s %9s %9s %9s %9s %9s %9s %9s\n";
  char datafmt[]="  %7.3f %6s %9.2e %9.2e %9.2e %9.2g %9.2e %9.2e %9.2e %9.2g %8d\n";

  if (FirstTime) {  // print header first time through 
    fprintf(OUT,"# State variables from ACE Level II data processor (v2.0)\n");

    // get and format calendar time for header
    time_t now;
    char timestr[19];
    time(&now);
    strftime(timestr, 19, "%d%b%Y %H:%M:%S", localtime(&now));
    fprintf(OUT,"# Created: %s\n", timestr);

    // include RCS ID in header
    fprintf(OUT,"# DistFunc: %s\n", "$Id: DistFunc.cc,v 1.50 2005/06/09 04:06:12 jraines Exp $");

    // column headings
    fprintf(OUT,hdrfmt,"doyfr","ion","n","v", "vth","n_err",
	    "fit_n","fit_v", "fit_vth", "fit_err", "quality");

    FirstTime = false;
  }

  for (unsigned int s = 0; s < ad.Ions.size(); s++){
    fprintf(OUT, datafmt, doyfr, ad.Ions[s].name.c_str(),
	    getDensity(s), getBulkVelocity(s), getThermVelocity(s), 
	    n_err[s], 
	    fit_n[s], fit_v0[s], fit_vth[s],
	    fit_err[s],
	    quality[s]);
  }

  return(0);
}

int DistFunc::outputDelivNVT(FILE *OUT, float doyfr, AnalysisData ad){
  static bool FirstTime = true;

  const float DENSITY_CALIB = 150.0;

  if (FirstTime) {  // print header first time through 
    fprintf(OUT,"# State variables from ACE/SWICS Level II data processor\n");
    fprintf(OUT,"# Data version: 2.0 (%6.2f)\n",DENSITY_CALIB);
    fprintf(OUT,"# Contact: Jim Raines (jraines@umich.edu)\n");
    fprintf(OUT,"# Doc: http://www.srl.caltech.edu/ACE/\n");
    fprintf(OUT,"# Fill: -1.0\n");

    // get and format calendar time for header
    time_t now;
    char timestr[19];
    time(&now);
    strftime(timestr, 19, "%d%b%Y %H:%M:%S", localtime(&now));
    fprintf(OUT,"# Created: %s\n", timestr);

    char hdrfmt_he[]=" %11s %9s %9s %4s";
    char hdrfmt[]   =" %9s %9s %4s";

    // --- column names ---
    fprintf(OUT,"# %7s","doyfr");

    fprintf(OUT,hdrfmt_he,"nHe2","vHe2","vthHe2","qual");
    fprintf(OUT,hdrfmt,"vC5","vthC5","qual");
    fprintf(OUT,hdrfmt,"vO6","vthO6","qual");
    fprintf(OUT,hdrfmt,"vFe10","vthFe10","qual");
    fprintf(OUT," %9s %7s","Fe/O","QF_Fe/O");
    fprintf(OUT,"\n");

        // --- column units ---
    fprintf(OUT,"# %7s","days");

    fprintf(OUT,hdrfmt_he,"cm^-3","km/s","km/s","[1]");
    fprintf(OUT,hdrfmt,"km/s","km/s","[1]");
    fprintf(OUT,hdrfmt,"km/s","km/s","[1]");
    fprintf(OUT,hdrfmt,"km/s","km/s","[1]");
    fprintf(OUT," %9s %7s","[1]","[1]");
    fprintf(OUT,"\n");

    FirstTime = false;
  }

  int s;
  float n_he, n_ratio;
  fprintf(OUT, "  %7.3f", doyfr);

  char datafmt_he[]=" %11.2e %9.2e %9.2e %4d";
  char datafmt[]=" %9.2e %9.2e %4d";

  s = ad.getIonIndex("He2+");
  n_he = getDensity(s); 
  fprintf(OUT, datafmt_he, n_he*DENSITY_CALIB, getBulkVelocity(s), 
	  getThermVelocity(s), quality[s]);

  s = ad.getIonIndex("C5+");
  fprintf(OUT, datafmt, getBulkVelocity(s), getThermVelocity(s), 
	  quality[s]);

  s = ad.getIonIndex("O6+");
  fprintf(OUT, datafmt, getBulkVelocity(s), getThermVelocity(s), 
	  quality[s]);

  s = ad.getIonIndex("Fe10+");
  fprintf(OUT, datafmt, getBulkVelocity(s), getThermVelocity(s), 
	  quality[s]);

  /* one elemental abundance thrown in because we promised it at 12
     min time resolution -- the same as the above

     This code borrowed from outputDelivElemAbun.*/
  string element;
  float n_sum;
  int qual = 0;

  element = "O";
  int oxy_qual = 0;
  float n_oxy_sum = calc_elem_n_sum(element, ad, oxy_qual);
  if (oxy_qual > 0){ // bad O quality indicates bad data so put in FILL
    fprintf(OUT, " %9.2e %7d", FILL, 0);
  }
  else {
    element = "Fe";
    n_sum = calc_elem_n_sum(element, ad, qual);
    n_ratio = calc_n_ratio(n_sum,n_oxy_sum);
    fprintf(OUT, " %9.2e %7d", n_ratio, qual);
  }    

  fprintf(OUT, "\n");

  return(0);
}

int DistFunc::outputDelivElemAbun(FILE *OUT, float doyfr, AnalysisData ad){
  static bool FirstTime = true;

  const int NUM_ELEM_ABUN = 6;

  if (FirstTime) {  // print header first time through 
    fprintf(OUT,"# Elemental abundances from ACE/SWICS Level II data processor\n");
    fprintf(OUT,"# Data version: 2.0\n");
    fprintf(OUT,"# Contact: Jim Raines (jraines@umich.edu)\n");
    fprintf(OUT,"# Doc: http://www.srl.caltech.edu/ACE/\n");
    fprintf(OUT,"# Fill: -1.0\n");

    // get and format calendar time for header
    time_t now;
    char timestr[19];
    time(&now);
    strftime(timestr, 19, "%d%b%Y %H:%M:%S", localtime(&now));
    fprintf(OUT,"# Created: %s\n", timestr);

    // keep fields the same total width!
    char hdrfmt[] =" %9s %7s";

    // column names
    // note:  remember to change NUM_ELEM_ABUN above
    fprintf(OUT,"# %7s","doyfr");
    fprintf(OUT,hdrfmt,"4He/O","QF_He/O");
    fprintf(OUT,hdrfmt,"C/O","QF_C/O");
    fprintf(OUT,hdrfmt,"Ne/O","QF_Ne/O");
    fprintf(OUT,hdrfmt,"Mg/O","QF_Mg/O");
    fprintf(OUT,hdrfmt,"Si/O","QF_Si/O");
    fprintf(OUT,hdrfmt,"Fe/O","QF_Fe/O");
    fprintf(OUT,"\n");

    // column units
    fprintf(OUT,"# %7s","hours");
    fprintf(OUT,hdrfmt,"[1]","[1]");
    fprintf(OUT,hdrfmt,"[1]","[1]");
    fprintf(OUT,hdrfmt,"[1]","[1]");
    fprintf(OUT,hdrfmt,"[1]","[1]");
    fprintf(OUT,hdrfmt,"[1]","[1]");
    fprintf(OUT,hdrfmt,"[1]","[1]");
    fprintf(OUT,"\n");

    FirstTime = false;
  }

  string element;
  float n_ratio, n_sum;
  int qual = 0;
  fprintf(OUT, "  %7.3f", doyfr);

  char datafmt[]=" %9.2e %7d";

  element = "O";
  int oxy_qual = 0;
  float n_oxy_sum = calc_elem_n_sum(element, ad, oxy_qual);

  // report all fill values if O is marked as low statistics
  if (oxy_qual > 0){
    for (int i = 0; i < NUM_ELEM_ABUN; i++){
      fprintf(OUT, datafmt, FILL, 0);
    }
    fprintf(OUT, "\n");
    return(0);
  }
      
  element = "He";
  float mass = 4.0;
  n_sum = calc_isotope_n_sum(element, mass, ad, qual);
  n_ratio = calc_n_ratio(n_sum,n_oxy_sum);
  fprintf(OUT, datafmt, n_ratio, qual);

  element = "C";
  n_sum = calc_elem_n_sum(element, ad, qual);
  n_ratio = calc_n_ratio(n_sum,n_oxy_sum);
  fprintf(OUT, datafmt, n_ratio, qual);

  element = "Ne";
  n_sum = calc_elem_n_sum(element, ad, qual);
  n_ratio = calc_n_ratio(n_sum,n_oxy_sum);
  fprintf(OUT, datafmt, n_ratio, qual);

  element = "Mg";
  n_sum = calc_elem_n_sum(element, ad, qual);
  n_ratio = calc_n_ratio(n_sum,n_oxy_sum);
  fprintf(OUT, datafmt, n_ratio, qual);

  element = "Si";
  n_sum = calc_elem_n_sum(element, ad, qual);
  n_ratio = calc_n_ratio(n_sum,n_oxy_sum);
  fprintf(OUT, datafmt, n_ratio, qual);

  element = "Fe";
  n_sum = calc_elem_n_sum(element, ad, qual);
  n_ratio = calc_n_ratio(n_sum,n_oxy_sum);
  fprintf(OUT, datafmt, n_ratio, qual);

  fprintf(OUT, "\n");

  return(0);
}

int DistFunc::outputDelivElemAbunLA(FILE *OUT, float doyfr, AnalysisData ad){
  // This is the low abundance (LA) version

  static bool FirstTime = true;

  if (FirstTime) {  // print header first time through 
    fprintf(OUT,"# Elemental abundances from ACE/SWICS Level II data processor\n");
    fprintf(OUT,"# Data version: 2.0\n");
    fprintf(OUT,"# Contact: Jim Raines (jraines@umich.edu)\n");
    fprintf(OUT,"# Doc: http://www.srl.caltech.edu/ACE/\n");
    fprintf(OUT,"# Fill: -1.0\n");

    // get and format calendar time for header
    time_t now;
    char timestr[19];
    time(&now);
    strftime(timestr, 19, "%d%b%Y %H:%M:%S", localtime(&now));
    fprintf(OUT,"# Created: %s\n", timestr);

    // keep fields the same total width!
    char hdrfmt[] =" %9s %7s";

    // column names
    fprintf(OUT,"# %7s","doyfr");
    fprintf(OUT,hdrfmt,"3He/4He","QF_3/4");
    fprintf(OUT,hdrfmt,"N/O","QF_N/O");
    fprintf(OUT,hdrfmt,"S/O","QF_S/O");
    fprintf(OUT,"\n");

    // column units
    fprintf(OUT,"# %7s","hours");
    fprintf(OUT,hdrfmt,"[1]","[1]");
    fprintf(OUT,hdrfmt,"[1]","[1]");
    fprintf(OUT,hdrfmt,"[1]","[1]");
    fprintf(OUT,"\n");

    FirstTime = false;
  }

  string element;
  float n_ratio, n_sum;
  int qual = 0;
  fprintf(OUT, "  %7.3f", doyfr);

  char datafmt[]=" %9.2e %7d";

  element = "O";
  int oxy_qual = 0;
  float n_oxy_sum = calc_elem_n_sum(element, ad, oxy_qual);

  // report all fill values if O is marked as low statistics
  // FIX: hardcoded number of elements
  if (oxy_qual > 0){
    for (int i = 0; i < 3; i++)
      fprintf(OUT, datafmt, -1.0, 0);
    return(0);
  }

  float mass, m3_he_sum, m4_he_sum;
  element = "He";
  mass = 3.0;
  m3_he_sum = calc_isotope_n_sum(element, mass, ad, qual);
  element = "He";
  mass = 4.0;
  m4_he_sum = calc_isotope_n_sum(element, mass, ad, qual);
  n_ratio = calc_n_ratio(m3_he_sum,m4_he_sum);
  fprintf(OUT, datafmt, n_ratio, qual);

  element = "N";
  n_sum = calc_elem_n_sum(element, ad, qual);
  n_ratio = calc_n_ratio(n_sum,n_oxy_sum);
  fprintf(OUT, datafmt, n_ratio, qual);

  element = "S";
  n_sum = calc_elem_n_sum(element, ad, qual);
  n_ratio = calc_n_ratio(n_sum,n_oxy_sum);
  fprintf(OUT, datafmt, n_ratio, qual);

  fprintf(OUT, "\n");

  return(0);
}

int DistFunc::outputDelivQRatio(FILE *OUT, float doyfr, AnalysisData ad){
  static bool FirstTime = true;

  if (FirstTime) {  // print header first time through 
    fprintf(OUT,"# Charge state ratios from ACE/SWICS Level II data processor\n");
    fprintf(OUT,"# Data version: 2.0\n");
    fprintf(OUT,"# Contact: Jim Raines (jraines@umich.edu)\n");
    fprintf(OUT,"# Doc: http://www.srl.caltech.edu/ACE/\n");
    fprintf(OUT,"# Fill: -1.0\n");

    // get and format calendar time for header
    time_t now;
    char timestr[19];
    time(&now);
    strftime(timestr, 19, "%d%b%Y %H:%M:%S", localtime(&now));
    fprintf(OUT,"# Created: %s\n", timestr);

    char hdrfmt[]=" %9s %10s";

    // --- column names ---
    fprintf(OUT,"# %7s","doyfr");

    fprintf(OUT,hdrfmt,"nC6/nC5","qf_nC6/nC5");
    fprintf(OUT,hdrfmt,"nO7/nO6","qf_nO7/nO6");
    fprintf(OUT,hdrfmt,"ave_q_C","qf_ave_q_C");
    fprintf(OUT,hdrfmt,"ave_q_O","qf_ave_q_O");
    fprintf(OUT,hdrfmt,"ave_q_fe","qf_ave_q_fe");

    fprintf(OUT,"\n");

    // --- column units ---
    fprintf(OUT,"# %7s","hours");

    fprintf(OUT,hdrfmt,"[1]","[1]");
    fprintf(OUT,hdrfmt,"[1]","[1]");
    fprintf(OUT,hdrfmt,"e","[1]");
    fprintf(OUT,hdrfmt,"e","[1]");
    fprintf(OUT,hdrfmt,"e","[1]");

    fprintf(OUT,"\n");

    FirstTime = false;
  }

  int s_num,s_den;
  float n_ratio, qual_ratio;
  fprintf(OUT, "  %7.3f", doyfr);

  char datafmt[]=" %9.2e %10d";

  s_num = ad.getIonIndex("C6+");
  s_den = ad.getIonIndex("C5+");
  n_ratio = calc_n_ratio(getDensity(s_num),getDensity(s_den));
  qual_ratio = (quality[s_num] == 1) || (quality[s_den] == 1);
  fprintf(OUT, datafmt, n_ratio, qual_ratio);

  s_num = ad.getIonIndex("O7+");
  s_den = ad.getIonIndex("O6+");
  n_ratio = calc_n_ratio(getDensity(s_num),getDensity(s_den));
  qual_ratio = (quality[s_num] == 1) || (quality[s_den] == 1);
  fprintf(OUT, datafmt, n_ratio, qual_ratio);

  int qual = 0;
  n_ratio = calc_ave_q("C", ad, qual);
  qual_ratio = (qual > 0);
  fprintf(OUT, datafmt, n_ratio, qual_ratio);

  qual = 0;
  n_ratio = calc_ave_q("O", ad, qual);
  qual_ratio = (qual > 0);
  fprintf(OUT, datafmt, n_ratio, qual_ratio);

  qual = 0;
  n_ratio = calc_ave_q("Fe", ad, qual);
  qual_ratio = (qual > 0);
  fprintf(OUT, datafmt, n_ratio, qual_ratio);

  fprintf(OUT, "\n");

  return(0);
}

int DistFunc::outputDelivQDist(FILE *OUT, float doyfr, AnalysisData ad,
			       string element){
  static bool PrintHeader;
  static vector<string> elements_processed;

  string thisprog = "DistFunc::outputDelivQDist";

  // check to see if this element has been processed before
  PrintHeader = true;
  for (int i = 0; i < elements_processed.size(); i++){
    if (elements_processed[i] == element) {
      PrintHeader = false;
      break;
    }
  }

  if (PrintHeader) {  // print header on first processing of element only
    fprintf(OUT,"# %s charge state distribution from ACE/SWICS Level II data processor\n", element.c_str());
    fprintf(OUT,"# Data version: 2.0\n");
    fprintf(OUT,"# Contact: Jim Raines (jraines@umich.edu)\n");
    fprintf(OUT,"# Doc: http://www.srl.caltech.edu/ACE/\n");
    fprintf(OUT,"# Fill: -1.0\n");

    // get and format calendar time for header
    time_t now;
    char timestr[19];
    time(&now);
    strftime(timestr, 19, "%d%b%Y %H:%M:%S", localtime(&now));
    fprintf(OUT,"# Created: %s\n", timestr);

    char hdrfmt[]=" %7s %3s %9s %10s";

    // --- column names ---
    fprintf(OUT,"# %7s","doyfr");
    fprintf(OUT,hdrfmt,"ion","chg", "rel_abun","qf_rel_abun");
    fprintf(OUT,"\n");

    // --- column units ---
    fprintf(OUT,"# %7s","hours");
    fprintf(OUT,hdrfmt,"n/a","e","[1]","[1]");
    fprintf(OUT,"\n");

    // save this one so the header is not printed again
    elements_processed.push_back(element);
  }


  int qual = -1;
  float elem_n_sum = calc_elem_n_sum(element, ad, qual);
  cout << thisprog << " -D- sum of " << element << " densities is " << elem_n_sum << endl;

  // find range to deliver
  float lo_chg = 0.;
  float hi_chg = 0.;
  for (int i = 0; i < DeliverableRanges.size(); i++){
    if (DeliverableRanges[i].name == element) {
      lo_chg = DeliverableRanges[i].lo_chg;
      hi_chg = DeliverableRanges[i].hi_chg;
      break;
    }
  }
  
  char datafmt[]="  %7.3f %7s %3.0f %9.2e %10d\n";
  float n_ratio;
  for (unsigned int s = 0; s < ad.Ions.size(); s++){
    if (ad.Ions[s].element == element && 
	(ad.Ions[s].charge >= lo_chg && ad.Ions[s].charge <= hi_chg)){
      n_ratio = calc_n_ratio(getDensity(s),elem_n_sum);
      fprintf(OUT, datafmt, doyfr, ad.Ions[s].name.c_str(), 
	      ad.Ions[s].charge, n_ratio, quality[s]);
    }
  }

  return(0);
}

int DistFunc::determineQuality(){
  return(0);
}

void DistFunc::filterNvtByQuality(AnalysisData ad){
  string thisprog = "DistFunc::filterNvtByQuality";

  // move these to somewhere else later
  const int QF_LOW_STATS = 1;
  const int QF_VERY_LOW_STATS = 2;
  const int QF_NON_THERMAL = 4;
  const int QF_NO_DATA = 8;

  for (unsigned int s = 0; s < ad.Ions.size(); s++){
    // dbg
    ad.Ions[s].print();

    // set flag for missing data and do not set others
    if (n[s] < 0.) {
      quality[s] = QF_NO_DATA;
      n[s] = FILL;
      n_err[s] = FILL;
      v0[s] = FILL;
      vth[s] = FILL;
      continue;
    }

    // density
    // --- yellow
    if (n_err[s] > ad.Ions[s].errlvl.n_yellow) { 
      quality[s] = quality[s] | QF_LOW_STATS;
    }
    // --- red
    else if (n_err[s] > ad.Ions[s].errlvl.n_red) {
      quality[s] = quality[s] | QF_VERY_LOW_STATS;
      n[s] = FILL;
    }

    // velocity
    float comp_v = abs(1 - (v0[s]/fit_v0[s]));
    // -- no velocity filter is currently being applied --

    // thermal velocity
    // --- red
    float comp_vth = 2*abs(vth[s]-fit_vth[s])/
      (ad.EqAcceptFac*v0[s]);
    if (comp_vth > ad.Ions[s].errlvl.vth_red) {
      quality[s] = quality[s] | QF_NON_THERMAL;
      vth[s] = FILL;
    }
  }

  return;
}

float  DistFunc::calc_n_ratio(float n_num, float n_denom){
  float ratio;

  // not logic keeps out NaNs
  if ( ! (n_denom > 0.)) ratio = FILL;
  else if ( ! (n_num > 0.)) ratio = FILL;
  else ratio = n_num/n_denom;

  return(ratio);
}

float DistFunc::calc_elem_n_sum(string element, AnalysisData ad, int& qual){

  float n_sum = 0.;
  float qual_sum = 0.;

  for (int s = 0; s < ad.Ions.size(); s++){
    if (ad.Ions[s].element == element && n[s] > 0.){ 
      // last clause keeps out -1.0 fill
      n_sum += n[s];
      qual_sum += n[s]*static_cast<float>(quality[s]);
    }
  }

  qual = 1;
  if (n_sum > 0.){
    if (qual_sum/n_sum >= .5) qual = 1;  // somewhat arbitrary cutoff
    else qual = 0;
  }

  return(n_sum);
}

float DistFunc::calc_isotope_n_sum(string element, float mass,
				   AnalysisData ad, int& qual){

  float n_sum = 0.;
  float qual_sum = 0.;

  for (int s = 0; s < ad.Ions.size(); s++){
    if (ad.Ions[s].element == element && ad.Ions[s].mass == mass
	&& n[s] > 0.){ 
      // last clause keeps out -1.0 fill
      n_sum += n[s];
      qual_sum += n[s]*static_cast<float>(quality[s]);
    }
  }

  qual = 1;
  if (n_sum > 0.){
    if (qual_sum/n_sum >= .5) qual = 1;  // somewhat arbitrary cutoff
    else qual = 0;
  }

  return(n_sum);
}

float DistFunc::calc_ave_q(string element, AnalysisData ad, int& qual){

  float n_sum = 0.;
  float q_sum = 0.;
  float qual_sum = 0;
  for (int s = 0; s < ad.Ions.size(); s++){
    if (ad.Ions[s].element == element){
      if (n[s] > 0.) { // filter out fill values (-1.0)
	q_sum += n[s]*ad.Ions[s].charge;
	qual_sum += n[s]*static_cast<float>(quality[s]);
	n_sum += n[s];
      }
    }
  }

  float ave_q = 0.;
  qual = 1;
  if (n_sum > 0. && q_sum > 0.){
    ave_q = q_sum/n_sum;

    if (qual_sum/n_sum >= .5) qual = 1; // somewhat arbitrary cutoff
    else qual = 0;
  }
  else
    ave_q = -1.0;

  return(ave_q);
}

void DistFunc::keepOnlyDeliv(const AnalysisData& ad, string element, 
			     float lo_chg, float hi_chg){
  /* zero n, v, vth for specified element outside of specified charge
     range, inclusive */

  for (int s=0; s < ad.Ions.size(); s++){
    if (ad.Ions[s].element == element &&
	(ad.Ions[s].charge < lo_chg || ad.Ions[s].charge > hi_chg)){
      n[s] = FILL;
      n_err[s] = FILL;
      v0[s] = FILL;
      vth[s] = FILL;

      fit_n[s] = FILL;
      fit_v0[s] = FILL;
      fit_vth[s] = FILL;
      fit_err[s] = FILL;
    }
  }

  DeliverableRanges.push_back(deliv_element(element,lo_chg,hi_chg));

  return;
}

DistFunc::deliv_element::deliv_element(string element, float lo,
					    float hi){
  name = element;
  lo_chg = lo;
  hi_chg = hi;
}
