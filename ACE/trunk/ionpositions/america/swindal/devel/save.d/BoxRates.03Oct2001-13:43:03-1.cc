/*  
  Filename: BoxRates.cc

  Description:
  Box rates class for swindal.  Consists of containers and functions which 
  fill them.

  Author:  Jim Raines, 1May2001

  Method:

  Major Modification History:
    Adapted from Derivables.cc, JR, 31Jul2001
*/

#include "swindal.h"

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
ostream& operator<< (ostream& out_file, const BoxRates& BR){

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
  DbgLvl = 4;

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

//       toflo = (int)( grp[s].tof[nedb] - sqrt(grp[s].stof[nedb]) + .49);
//       tofhi = (int)( grp[s].tof[nedb] + sqrt(grp[s].stof[nedb]) + .49);
//       esdlo = (int)( grp[s].esd[nedb] - sqrt(grp[s].sesd[nedb]) +.49);
//       esdhi = (int)( grp[s].esd[nedb] + sqrt(grp[s].sesd[nedb]) + .49);

      toflo = (int)( grp[s].tof[nedb] - (grp[s].stof[nedb]) + .49);
      tofhi = (int)( grp[s].tof[nedb] + (grp[s].stof[nedb]) + .49);
      esdlo = (int)( grp[s].esd[nedb] - (grp[s].sesd[nedb]) +.49);
      esdhi = (int)( grp[s].esd[nedb] + (grp[s].sesd[nedb]) + .49);

      // arbitrarily expand region to check for round-off error
      // (for debug only)
//       int arbexp = 2;
//       toflo -= arbexp;
//       tofhi += arbexp;
//       esdlo -= arbexp;
//       esdhi += arbexp;

      if (toflo < 0) toflo = 0;
      if (toflo > MAXTOFCH) toflo = MAXTOFCH - 1;
      if (tofhi < 0) tofhi = 0;
      if (tofhi > MAXTOFCH) tofhi = MAXTOFCH - 1 ;

      if (esdlo < 0) esdlo = 0;
      if (esdlo > MAXESDCH) esdlo = MAXESDCH - 1;
      if (esdhi < 0) esdhi = 0;
      if (esdhi > MAXESDCH) esdhi = MAXESDCH - 1;

      if (DbgLvl >= 4 && grp[s].name == "O7+") {
	//cout.precision(1);
	cout << thisprog << " -I- for edb " << nedb << " and species " 
	     << names[s] << ", summing over "
	     << toflo << "<=tof<=" << tofhi << " "
	     << esdlo << "<=esd<=" << esdhi
	     << endl;
	//cout.precision(3);
      }

      float sum = 0.0;
      for (int ntof = toflo; ntof <= tofhi; ntof++){
	for (int nesd = esdlo; nesd <= esdhi; nesd++){
	  sum += maslice[ntof][nesd];
	}
      } 

      B[nedb][s] =  sum;

      // ad hoc box count for debugging
      if (nedb == 41 && grp[s].name == "O7+"){
	float o7box = 0.0;
	for (int ntof = 340; ntof <= 348; ntof++){
	  for (int nesd = 46; nesd <= 57; nesd++){
	    o7box += maslice[ntof][nesd];
	  }
	} 
	cout << thisprog << " -D- o7box=" << o7box 
	     << " sum=" << sum << endl;
      }

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


/* -----------------
   PRIVATE FUNCTIONS
   -----------------
*/
