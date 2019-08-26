/*  
  Filename: BoxRates.cc

  Description:
  Box rates class for swindal.  Consists of containers and functions which 
  fill them.

  Author:  Jim Raines, 1May2001

  Method:

  Revision controlled by CVS:
  $Id: BoxRates.cc,v 1.9 2005/06/07 00:06:40 jraines Exp $

  Major Modification History:
    Adapted from Derivables.cc, JR, 31Jul2001
*/

#include "swindal.h"

// include files for creation time and mod. time in output files
#include <sys/types.h>   // for FM mod. time (open)
#include <sys/stat.h>    // for FM mod. time (fstat)
#include <fcntl.h>       // for FM mod. time (open)
#include <unistd.h>      // for FM mod. time (fstat)

#include <time.h>        // for creation time in header

/* ----------------
   PUBLIC FUNCTIONS
   ----------------
*/

// Constructor
BoxRates::BoxRates(int N){
  TNT::Vector<float> tmp(N, 0.0);

  for (int i = 0; i < MAXEDB; i++){
    B.push_back(tmp);
  }
}

void BoxRates::print(void){
  float sum;

  for (int s = 0; s < names.size(); s++){
    sum = 0.0;

    for (int nedb = FIRSTEDB; nedb < MAXEDB; nedb++){
      sum += B[nedb][s];
    }

    cout << names[s] << " " << sum << "(";
    for (int nedb = FIRSTEDB; nedb < MAXEDB; nedb++){    
      cout << " " << B[nedb][s];
    }
    cout << ")" << endl;

  }

  return;
}

// a version of print for debugging
void BoxRates::print(int s,const AnalysisData& ad){
  float sum;
  int precision; 

  precision = cout.precision();
  cout.precision(3);

  sum = 0.0;

  for (int nedb = FIRSTEDB; nedb < MAXEDB; nedb++){
    sum += B[nedb][s];
  }

  cout << names[s] << " sum over EDBs=" << sum << endl;

  for (int nedb = FIRSTEDB; nedb < MAXEDB; nedb++){    
    cout << "nedb=" << nedb << " boxrate=" << B[nedb][s];
    cout << " e/q=" << ad.Eqtab[nedb] 
	 << " tof=" << ad.Ions[s].tof[nedb]
	 << " stof=" << ad.Ions[s].stof[nedb]
	 << " esd=" << ad.Ions[s].esd[nedb]
	 << " sesd=" << ad.Ions[s].sesd[nedb] 
	 << " name=" << ad.Ions[s].name << endl;
  }

  cout.precision(precision);
  return;
}

/* Overload output operator
   from Stroustrup, p 612, plus help from Deitel and Deitel
*/
std::ostream& operator<< (std::ostream& out_file, const BoxRates& BR){

  float sum;

  for (int s = 0; s < BR.names.size(); s++){
    sum = 0.0;

    for (int nedb = FIRSTEDB; nedb < MAXEDB; nedb++){
      sum += BR.B[nedb][s];
    }

    out_file << BR.names[s] << " " << sum << endl;
  }

  return(out_file);
}

/* Calc. boxrates by summing within forward model region */
int BoxRates::calc(MeasurementArray* MA , const vector<Ion>& grp){
  string thisprog = "BoxRates::calc";
  int i,j;      // loop counters
  int DbgLvl = gDbgLvl;  // init local debug to global value
  //DbgLvl = 4;

  /* --  local copies of or pointers to data items --
         Used to make notation manageable.
  */
  int toflo, tofhi; // tof (in channels) range over which to sum for box rate
  int esdlo, esdhi; // esd (in channels) range over which to sum for box rate
  int nedb;         // EDB number

  bool fMatch;   // flag indicating that a PHA is in a range/box

  Pha pha;       // need tof and esd conversion functions
  
  // grab ion names for printing and stuff
  for (int s = 0; s < grp.size(); s++){
    names.push_back(grp[s].name);
    //cout << thisprog << " -D- analyzing ion " << names[s] 
    //<< (*grp)[s].name << endl;
  }


  // -- MA slices (by EDB number) --
  TNT::Matrix<float> maslice(MAXTOFCH,MAXESDCH, 0.0);  
  for (int nedb = FIRSTEDB; nedb < MAXEDB; nedb++){
    maslice = MA->getSlice(nedb);

    // -- Loop over ions in analysis group --
    for (int s = 0; s < grp.size(); s++){

      // set tof/esd bounds; .49 is to round properly
      toflo = (int)( grp[s].tof[nedb] - (grp[s].stof[nedb]) + .49);
      tofhi = (int)( grp[s].tof[nedb] + (grp[s].stof[nedb]) + .49);
      esdlo = (int)( grp[s].esd[nedb] - (grp[s].sesd[nedb]) +.49);
      esdhi = (int)( grp[s].esd[nedb] + (grp[s].sesd[nedb]) + .49);

      if (toflo < 0) toflo = 0;
      if (toflo > MAXTOFCH-1) toflo = MAXTOFCH - 1;
      if (tofhi < 0) tofhi = 0;
      if (tofhi > MAXTOFCH-1) tofhi = MAXTOFCH - 1 ;

      // manually exclude energy channel 0 to keep double coincident ions out
      //      if (esdlo < 0) esdlo = 0;
      if (esdlo < 0) esdlo = 1;
      if (esdlo > MAXESDCH-1) esdlo = MAXESDCH - 1;
      //      if (esdhi < 0) esdhi = 0;
      if (esdhi < 0) esdhi = 1;
      if (esdhi > MAXESDCH-1) esdhi = MAXESDCH - 1;

      float sum = 0.0;
      for (int ntof = toflo; ntof <= tofhi; ntof++){
	for (int nesd = esdlo; nesd <= esdhi; nesd++){
	  sum += maslice[ntof][nesd];
	}
      } 

      B[nedb][s] =  sum;

    } // loop over ions in group
     
  } // loop over slices (nedb)

  return (0);
}

// access function for entire array
vector<TNT::Vector<float> > BoxRates::getBoxrates(void){
  return (B);
}

// access funtion for specific rate
float BoxRates::getBoxrate(int nedb, int s){
  return (B[nedb][s]);
}

float BoxRates::getBoxrate(int s){
  float sum = 0.0;
  for (int nedb = FIRSTEDB; nedb < MAXEDB; nedb++){
    sum += B[nedb][s];
  }
  return (sum);
}

int BoxRates::output(FILE *BRF, float doyfr, const AnalysisData& ad){

  static bool FirstTime = true;

  // keep fields the same total width!
  char hdrfmt[] ="# %7s %3s %8s %6s %10s %10s\n";
  char datafmt[]=
  "  %7.3f %3d %8.2f %6s %10.2e %10.2e\n";

  if (FirstTime) {  // print header first time through 
    fprintf(BRF,"# Box rates from ACE Level II data processor (v2.0)\n");

    // get and format calendar time for header
    time_t now;
    char timestr[19];
    time(&now);
    strftime(timestr, 19, "%d%b%Y %H:%M:%S", localtime(&now));
    fprintf(BRF,"# Created: %s\n", timestr);

    fprintf(BRF,"# BoxRates: %s\n", "$Id: BoxRates.cc,v 1.9 2005/06/07 00:06:40 jraines Exp $");

    // column headings
    fprintf(BRF,hdrfmt,"doyfr", "EDB", "E/q","ion","boxrate",
	    "boxcnt");

    FirstTime = false;
  }

  float br;
  for (int s = 0; s < ad.Ions.size(); s++){
    for (int nedb = FIRSTEDB; nedb < MAXEDB; nedb++){
      br = getBoxrate(nedb, s);
      fprintf(BRF, datafmt, doyfr, nedb, ad.Eqtab[nedb], 
	      ad.Ions[s].name.c_str(),
	      getBoxrate(nedb, s), gAccumTime*getBoxrate(nedb,s));
    }
  }

}


  


/* -----------------
   PRIVATE FUNCTIONS
   -----------------
*/
