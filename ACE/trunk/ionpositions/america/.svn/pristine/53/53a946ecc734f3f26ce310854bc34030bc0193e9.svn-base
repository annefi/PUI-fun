/*
  File: AceSwicsDutyCycle.cc

  Description:
    Duty cycle combines the angular integrations performed by a
    SWICS-type instrument into one number. This module contains
    functions which calculate the duty cycle and handle associated tasks.

  Author(s): Jim Raines (jmr)

  Method:
    See 'References' in header file for this class.

  Revison controlled by CVS:
  $Id: AceSwicsDutyCycle.cc,v 1.11 2005/06/06 20:43:39 jraines Exp $

  Major Modification History:
    11Sep2003   jmr   initial coding

*/
 
#include "swindal.h"
#include "swindal_nr.h"

#include <memory>
#include <sstream>

// Removed for easier porting to OSX and because it never worked anyway
// ACE Ancillary (O/A) Data library
// namespace ancil {
//   extern "C" {
// #include "libace_ancil.h"
//   }
// }

// definition of static data members
float AceSwicsDutyCycle::MachAngle;
float AceSwicsDutyCycle::AspectAngle;

AceSwicsDutyCycle::AceSwicsDutyCycle(void){
  AncillaryFilename = "/data/asterix/ace/data/LV1";

  UseExtAspectCommand = true;
  ExtAspectCommand = "/data/asterix/ace/amerika/get_ace_aspect";

  MachAngle = 0.1;  // set default value

  AspectAngle = -1.0;

  InterpolFilename = "/data/asterix/ace/amerika/DUTYCYCL";
  InterpolAccurCutoff = 0.02;
}

float AceSwicsDutyCycle::getAspectAngle(void){
  return(AspectAngle);
}

void AceSwicsDutyCycle::setMachAngle(float value){
  MachAngle = value;
}
float AceSwicsDutyCycle::getMachAngle(void){
  return(MachAngle);
}

void AceSwicsDutyCycle::setAncillaryFilename(string filename){
  AncillaryFilename = filename;
}

string AceSwicsDutyCycle::getAncillaryFilename(){
  return(AncillaryFilename);
}

void AceSwicsDutyCycle::setExtAspectCommand(string cmd){
  ExtAspectCommand = cmd;
}

string AceSwicsDutyCycle::getExtAspectCommand(){
  return(ExtAspectCommand);
}

void AceSwicsDutyCycle::useExtAspectCommand(bool val){
  UseExtAspectCommand = val;
}

bool AceSwicsDutyCycle::useExtAspectCommand(){
  return(UseExtAspectCommand);
}

/*
  Routine: AceSwicsDutyCycle::calcByIntegration

  Description:
    Calculates the duty cycle from aspect angle (found with cycle
    time) and Mach angle.

  Arguments:
    MachAngle -- angle between ion velocity and solar wind velocity,
    typically a small number < .2

    CycleTime -- time in seconds since 1970.

  Method:
    See references section in header file for this class.
    ACE Science Center ancillary code is used to extract the aspect angle 
    for a particular cycle time (locally libace_ancil).
*/

float AceSwicsDutyCycle::calcByIntegration(double CycleTime){
  float DutyCycle;
  const string thisprog = "AceSwicsDutyCycle::calcByIntegration";

  if (gDbgLvl >= 2) cout << thisprog << " -I- entering..." << endl;

  getNewAspectAngle(CycleTime);

  // convert to radians
  AspectAngle = (AspectAngle/360.0)*(2.0*M_PI);

  /* Integrate numerically to find duty cycle
     ---------------------------------------------------------------
     Ref. 2, equation A31 with angles from A32 and A33.
  */
  float (*pintegrand) (float) = &AceSwicsDutyCycle::integrand;
  DutyCycle = (1.0/(2.0*M_PI))*nr::qtrap(pintegrand, 0.0, 2.0*M_PI);

  if (gDbgLvl >= 2) cout << thisprog << " -I- done." << endl;
  return(DutyCycle);
};

float AceSwicsDutyCycle::integrand(float phi){

  float alpha  = AspectAngle;
  float del_psi = MachAngle;

  // Calculate collimator coordinates in terms of others
  double phi_0;
  double theta_c_0;
  double phi_c_0;

  phi_0 = (cos(GAMMA)/sin(GAMMA)) * (1.0-cos(alpha))/sin(alpha);

  theta_c_0 = acos( sin(GAMMA)*cos(phi-phi_0)*sin(alpha) + cos(GAMMA)*cos(alpha) );
  phi_c_0 = asin( -sin(phi-phi_0)*sin(alpha)/sin(theta_c_0) );

  float integrand;
  float integrand2;

  // compute integrand for this phi
  double t11,t12,t21,t22;

  t11 = erf( (GAMMA - theta_c_0 + (DEL_THETA_C/2.0))/
	     (sqrt(2.0)*del_psi) );
  t12 = erf( (GAMMA - theta_c_0 - DEL_THETA_C/2.0)/
	     (sqrt(2.0)*del_psi) );
  t21 = erf( sin(theta_c_0)*(M_PI - phi_c_0)/
	     sqrt(2.0)*del_psi );
  t22 = erf( sin(theta_c_0)*(M_PI - phi_c_0 - DEL_PHI_C)/
	     sqrt(2.0)*del_psi);

  if (gDbgLvl >= 3) {
    cout << " alpha=" << alpha
	 << " del_psi=" << del_psi << endl;
    cout << " gamma=" << GAMMA 
	 << " del_phi_c=" << DEL_PHI_C 
	 << " del_theta_c=" << DEL_THETA_C << endl;
    cout << " phi=" << phi
	 << " phi_0=" << phi_0
	 << " theta_c_0=" << theta_c_0
	 << " phi_c_0=" << phi_c_0 << endl;
    cout << " t11=" << t11
	 << " t12=" << t12
	 << " t21=" << t21
	 << " t22=" << t22 << endl;
  }
  integrand = (float) (1.0/2.0 * (t11 - t12) * 1.0/2.0 * (t21 - t22));

  integrand2 = 1.0/2.0 *
    (erf( (GAMMA - theta_c_0 + (DEL_THETA_C/2.0))/
	  (sqrt(2.0)*del_psi) ) -
     erf( (GAMMA - theta_c_0 - DEL_THETA_C/2.0)/
	  (sqrt(2.0)*del_psi) )) *
    1.0/2.0 *
    (erf( sin(theta_c_0)*(M_PI - phi_c_0)/
	  sqrt(2.0)*del_psi ) -
     erf( sin(theta_c_0)*(M_PI - phi_c_0 - DEL_PHI_C)/
	  sqrt(2.0)*del_psi));

  if (gDbgLvl >= 3) {
    cout << " terms - all in one = " << integrand - integrand2 << endl ;
  }	

  // arb. change of * to + in searching for right formula
  //integrand = (float) (1.0/2.0 * (t11 - t12) + 1.0/2.0 * (t21 - t22));

  // for debugging only:  duty should be 13.1595
  //integrand = phi*phi;

  return(integrand);
}

void AceSwicsDutyCycle::setInterpolFilename(string name){
  InterpolFilename = name;
}

string AceSwicsDutyCycle::getInterpolFilename(){
  return(InterpolFilename);
}


float AceSwicsDutyCycle::calcByInterpolation (double CycleTime, 
					      float MachAngle_arg){
  
  const string thisprog = "AceSwicsDutyCycle::calcByInterpolation";

  /* ----------------------------------------------------------------------
     Angle stuff
     ---------------------------------------------------------------------- */
  getNewAspectAngle(CycleTime);
  
  setMachAngle(MachAngle_arg);

  // copy class variables to local variable names, which correspond to
  // the mathematical descriptions
  float alpha  = AspectAngle;
  float del_psi = MachAngle;

  /* ----------------------------------------------------------------------
     read in file containing tabulated duty cycle data
     ---------------------------------------------------------------------- */
  std::ifstream fin;
  fin.open(InterpolFilename.c_str());
  if (! fin.good()) cout << "Error opening " << InterpolFilename << endl;

  vector<float> values;
  float tmpval;
  int nrow = 1;
  while(! fin.eof()){
    fin >> tmpval;
    values.push_back(tmpval);
  }
  fin.close();

  /* ----------------------------------------------------------------------
     set up arrays
     ---------------------------------------------------------------------- */

  // --- delta psi ---
  // The following number of columns and x2a (delta psi) values pertain to
  // DUTYCYCL.DAT received from Ruedi von Steiger, 10Oct2003.
  const int NCOLS = 9;  // number of actual columns in file
  const int num_del_psi = NCOLS-1; // number of delta_psi values
  float *x2a;
  x2a = nr::vector(1,num_del_psi);
  //x2a[0] = -1.0;  // not used
  x2a[1] = 0.0;   // x2a values from private communication with RvS
  x2a[2] = 0.1;
  x2a[3] = 0.5;
  x2a[4] = 1.0;
  x2a[5] = 2.0;
  x2a[6] = 3.0;
  x2a[7] = 5.0;
  x2a[8] = 10.0;

  // see if input del_psi is within bounds
  // weird logic formulated to also trap 'nan'
  if ( !( del_psi > x2a[1] && del_psi < x2a[num_del_psi]) ){
    if (gDbgLvl >= 1) {
      cout << thisprog << " -E- MachAngle (" << MachAngle 
	   << ") out of bounds.  Current table supports " 
	   << x2a[1] << ".." << x2a[num_del_psi] << endl;
      cout << "+ duty cannot be calculated -- returning -1.0" << endl;
    }
    nr::free_vector(x2a, 1, num_del_psi);
    return(-1.0);
  }

  // --- alpha ---
  int nrows = values.size()/NCOLS;
  float *x1a;
  //x1a = nr::vector(1,nrows+1);  // Why nrows+1?
  x1a = nr::vector(1,nrows);
  //x1a[0] = -1.0;

  // --- duty cycle values (for given alpha and delta psi)
  float **ya;
  //ya = nr::matrix(1,nrows+1,1,NCOLS);
  ya = nr::matrix(1,nrows,1,num_del_psi);

  // --- copy values into proper vectors for NR interpolation routine --- 
  int iv = 0; // index into values vector
  int ix1a = 0;
  float duty_max = 0.;  // set to opposite extremes
  float duty_min = 1.;
  for (int row = 1; row <= nrows ; row++){
    for (int col = 1; col <= NCOLS; col++){
      if (col == 1){
	x1a[row] = values[iv];// pre-increment so index 1 is first val.
      }
      else{
	ya[row][col-1] = values[iv]; // col-1 b/c ya[][1] is at col=2

	// save max/min for double check on interpolation later
	if (ya[row][col-1] > duty_max) duty_max = ya[row][col-1];
	if (ya[row][col-1] < duty_min) duty_min = ya[row][col-1];
      }
      iv++;
    }
  }   

  // see if input alpha is within bounds
  // weird logic formulated to also trap 'nan'
  if ( !( alpha > x1a[1] && alpha < x1a[nrows]) ){
    if (gDbgLvl >= 1) {
      cout << thisprog << " -E- AspectAngle (" << AspectAngle 
	   << ") out of bounds.  Current table supports " 
	   << x1a[1] << ".." << x1a[nrows] << endl;
      cout << "+ duty cannot be calculated -- returning -1.0" << endl;
    }
    
    nr::free_vector(x1a, 1, nrows);
    nr::free_vector(x2a, 1, num_del_psi);
    nr::free_matrix(ya, 1, nrows, 1, num_del_psi);
    return(-1.0);
  }
  /* ----------------------------------------------------------------------
     Find chunk of vectors containing x values
     1)  locate index so that x is between that index and the next
     2)  calculate the lower bound on a range of indices, roughly
     centered on the location (1) containg the intended number of
     points for interpolation
     ---------------------------------------------------------------------- */
  // alpha
  unsigned long i_alpha;
  nr::locate(x1a, nrows, alpha, &i_alpha);
  cout << " x1a[" << i_alpha << "]=" << x1a[i_alpha] 
       << " <-> x1a[" << i_alpha+1 << "]=" << x1a[i_alpha+1] << endl;
  int j = 
    imin(imax((i_alpha-(NPOINT_INTERPOL-1)/2),1),nrows+1-NPOINT_INTERPOL);

  // del_psi
  unsigned long i_del_psi;
  nr::locate(x2a, num_del_psi, del_psi, &i_del_psi);
  cout << " x2a[" << i_del_psi << "]=" << x2a[i_del_psi] 
       << " <-> x2a[" << i_del_psi+1 << "]=" << x2a[i_del_psi+1]<< endl; 
  int k = 
    imin(imax((i_del_psi-(NPOINT_INTERPOL-1)/2),1),num_del_psi+1-NPOINT_INTERPOL);

  /* ----------------------------------------------------------------------
     Make a subarray for ya
     (necessary because gcc did not like passing in a 2D subarray by indexes)
     ---------------------------------------------------------------------- */
  float **yasub;
  yasub = nr::matrix(1,NPOINT_INTERPOL,1,NPOINT_INTERPOL);
  for (int nrow = 1; nrow <= NPOINT_INTERPOL; nrow++){
    for (int ncol = 1; ncol <= NPOINT_INTERPOL; ncol++){
      //yasub[nrow][ncol] = ya[nrow+j-1][ncol+k-1];
      yasub[nrow][ncol] = ya[nrow+j][ncol+k];
      //cout << yasub[nrow][ncol] << "   ";
    }
    //cout << endl;
  }
  
  /* ----------------------------------------------------------------------
     Do actual interpolation
     ---------------------------------------------------------------------- */
  float duty = -1.0;
  float accur = -1.0;
  nr::polin2(&x1a[j], &x2a[k], yasub, 
	     NPOINT_INTERPOL, NPOINT_INTERPOL,
	     alpha, del_psi, &duty, &accur);
  if (gDbgLvl >= 1) {
    cout << thisprog << " -I- duty = " << duty << ", "
	 << " accuracy = " << accur << endl;
  }

  // filter out values with bad accuracies
  // The so-called good accuracy range was very simply determined from 
  // running a few days and seeing which accuracies led to reasonable dutys.
  if (fabs(accur/duty) > InterpolAccurCutoff){
    if (gDbgLvl >= 1) {
      cout << thisprog << " -W- bad accuracy (" 
	   << accur << "); duty not usable -- returning -1.0"<< endl;
      duty = -1.0;
    }
  }

  // filter out values that are outside the table of input duties
  // (which should be impossible to arrive at via interpolation)

  if (duty > duty_max){
    if (gDbgLvl >= 1) {
      cout << thisprog << " -E- interpolated duty (" 
	   << duty << ") larger than max. input from duty table (" 
	   << duty_max << "); duty not usable -- returning -1.0" << endl;
      duty = -1.0;
    }
  }
  else if (duty < duty_min){
    if (gDbgLvl >= 1) {
      cout << thisprog << " -E- interpolated duty (" 
	   << duty << ") smaller than min. input from duty table (" 
	   << duty_min << "); duty not usable -- returning -1.0"<< endl;
      duty = -1.0;
    }
  }
  // the logic here is composed strangely to also catch 'nan' values
  else if ( !(duty > duty_min) || !(duty < duty_max ) ){
    if (gDbgLvl >= 1) {
      cout << thisprog << " -E- interpolated duty not a number (nan)" << endl;
      cout << "+ duty not usable -- returning -1.0"<< endl;
      duty = -1.0;
    }
  }
  else { // bad duties already reported
    if (gDbgLvl >= 1) {
      cout << thisprog << " -I- duty = " << duty
	   << " with last adjustment of " << accur/duty*100. 
	   << " %" << endl;
    }
  }
  nr::free_vector(x1a, 1, nrows);
  nr::free_vector(x2a, 1, num_del_psi);
  nr::free_matrix(ya, 1, nrows, 1, num_del_psi);
  nr::free_matrix(yasub, 1,NPOINT_INTERPOL,1,NPOINT_INTERPOL);

  return(duty);
}

int AceSwicsDutyCycle::imin(int a, int b){
  long lminarg1,lminarg2;
  return(lminarg1=(a),lminarg2=(b),(lminarg1) < (lminarg2) ?\
	 (lminarg1) : (lminarg2));
}

int AceSwicsDutyCycle::imax(int a, int b){
  int imaxarg1,imaxarg2;
  return(imaxarg1=(a),imaxarg2=(b),(imaxarg1) > (imaxarg2) ?\
	 (imaxarg1) : (imaxarg2));
}

int AceSwicsDutyCycle::getNewAspectAngle(double CycleTime){
  int RetVal = 0;

  const string thisprog = "AceSwicsDutyCycle::getNewAspectAngle";

  /* Get aspect angle from ACE ancillary data via ACE ancillary code
     ---------------------------------------------------------------
  */
  if (UseExtAspectCommand){
    // assemble ext. command and cycle time argument
    std::ostringstream cmd;
    cmd << ExtAspectCommand << " "
	<< static_cast<long>(CycleTime) 
        << " " << getAncillaryFilename();
    if (gDbgLvl >= 1){
      cout << thisprog << " -D- ext. aspect command string with args: " 
	 << cmd.str() << endl;
    }
    if (gDbgLvl >= 2) 
      cout << thisprog << " -D- ext. aspect command string with args: " 
	   << cmd.str() << endl;

    FILE *PIPE;
    PIPE = popen(cmd.str().c_str(), "r");
    char cmd_out[9];
    int retval;
    retval = fscanf(PIPE, "%s", cmd_out);
    if (retval >= 0){
      if (gDbgLvl >= 2) 
	cout << thisprog << " -D- string returned by ext. aspect command: " 
	     << cmd_out << endl;
      
      AspectAngle = atof(cmd_out);
    }
    else {
      cout << thisprog  
	   << "-E- fscanf on output of ext. aspect command returned " 
	   << retval << endl;
    }
    fseek(PIPE, 0, SEEK_END);
    pclose(PIPE);
  }
  else { // currently DNW -- seg. fault on a3goa_read but not from duty_exp
    // 'const' attribute of c_str() not expected by a3goa_read()

    // Removed in port to gcc 3.3 (caused errors), jmr 26Jul2004
    //ancil::a3goa_read( const_cast<char *>(AncillaryFilename.c_str()));

    //ancil::a3goa_read("/shrg1/ace/LV1/ACE_ANCIL.HDF");

    // Removed in port to gcc 3.3 (caused errors), jmr 26Jul2004
    //AspectAngle = acos(ancil::a3goa_att_RTN_r(CycleTime));
    
  }

  if (AspectAngle <= 0.0){
    cout << thisprog << " -E- aspect angle <= 0.0; setting to default (3.06)"
	 << endl;
    AspectAngle = 3.06;
    RetVal = 1;  // mark as not perfect return
  }

  if (gDbgLvl >= 1) cout << "AspectAngle = " << AspectAngle << " deg." << endl;

  return(RetVal);
}

void AceSwicsDutyCycle::setInterpolAccurCutoff(float cutoff){
  InterpolAccurCutoff = cutoff;
}

float AceSwicsDutyCycle::getInterpolAccurCutoff() const{
  return(InterpolAccurCutoff);
}
