/*
  File: MeasurementArray.cc

  Description:
    Code for MeasurementArray class

  Author: Jim Raines, 6Jun2001

  Method:
    
  Major Modification History:
    

*/

#include "swindal.h"

// Constructor 
MeasurementArray::MeasurementArray(void){
  TNT::Matrix<float> A(MAXTOFCH,MAXESDCH, 0.0);
  
  /* --- fill vector with (tofch,esdch) matrices --- */
  for (int i = 0; i < MAXEDB; i++){
    MA.push_back(A);
    MAcounts.push_back(A);
  }

}

int MeasurementArray::fill(vector<Pha> *pha){
/*
  Description:

    Make measurement array.  This routine builds and returns the
    measurement array (tof, esd, nedb).  The elements of the array are
    in counts per second, while the tof and esd indices are in
    channels.  Inclusion of the nedb dimension makes a cube of
    (tof,esd) matrices, where the nedb index is the number of the EDB
    in which the (tof,esd) values were collected (which corresponds to
    the E/q value).

  Author: Jim Raines, 

  Method:
    
  Major Modification History:
    

*/
  string thisprog = "MeasurementArray::fill";  // name of this routine
  int DbgLvl = gDbgLvl;  // debugging level, init. to global value
  DbgLvl = 2;

  double timeInterval;  // seconds between first and last PHA

  vector<Pha>::iterator pha_it;

  if (DbgLvl) {
    cout << thisprog << " -I- filling MeasurementArray..." << endl;
  }

  /* --- count PHA words with tof (channels), esd (channels) and nedb --- */
  int nphatot = 0;  // number of pha in analyzed for filling into MA
  float do7 = 0; // (debugging) number of PHAs at edb 40, tof 343, esd 52

  cout << thisprog << " -I- only taking PHAs from region 1" << endl;
  for (pha_it = pha->begin(); pha_it != pha->end(); pha_it++){

    if (pha_it->nedb < MAXEDB && pha_it->range == 1){

      nphatot++;

      if ( pha_it->tofch > 1023 ) {
	cout << thisprog << " -W- tofch out of range (1023 max):" 
	     << " nedb=" << pha_it->nedb 
	     << " tofch=" << pha_it->tofch 
	     << " esdch=" << pha_it->esdch 
	     << endl;
      }

      if ( pha_it->esdch > 255) {
	cout << thisprog << " -W- esdch out of range (255 max):"
	     << " nedb=" << pha_it->nedb 
	     << " tofch=" << pha_it->tofch 
	     << " esdch=" << pha_it->esdch 
	     << endl;
      }

      if (DbgLvl >= 3) {
	cout << thisprog << " -D- dumping meas. array coord.: "
	     << " nedb=" << pha_it->nedb 
	     << " tofch=" << pha_it->tofch 
	     << " esdch=" << pha_it->esdch 
	     << endl;
      }

      if (DbgLvl >= 4) {
	cout << thisprog << "-D- before add MAcounts[" << pha_it->nedb << "," 
	     << pha_it->tofch << "," 
	     << pha_it->esdch << "]=" 
	     << MAcounts[pha_it->nedb][pha_it->tofch][pha_it->esdch] << endl;
      }

      /* increment counts in E-T matrix */
      MAcounts[pha_it->nedb][pha_it->tofch][pha_it->esdch] += 1.0;

      if (DbgLvl >= 4) {
	cout << thisprog << "-D- after add MAcounts[" << pha_it->nedb << "," 
	     << pha_it->tofch << "," 
	     << pha_it->esdch << "]=" 
	     << MAcounts[pha_it->nedb][pha_it->tofch][pha_it->esdch] 
	     << endl << endl;
      }


      // ad hoc O7+ box count for debugging
      if (0 && pha_it->nedb == 41){
	if ( (pha_it->tofch >= 338) && (pha_it->tofch <= 350) ){
	  if( (pha_it->esdch >= 44) && (pha_it->esdch <= 59) ){
	    do7 += 1.0;

	    cout << thisprog << " -D- do7=" << do7 << " MAcounts=" << 
	      MAcounts[pha_it->nedb][pha_it->tofch][pha_it->esdch];
	    if (do7 != MAcounts[pha_it->nedb][pha_it->tofch][pha_it->esdch]){
	      cout << " -- NOT EQUAL!" << endl;
	    }
	    else{
	      cout << " -- equal." << endl;
	    }
	  }
	}
      }


    }
  }

  if (DbgLvl >= 1){
    cout << thisprog << " -D- npha used to fill array = " << nphatot << endl;;
  }

  /* --- normalize counts in array to counts/second --- */
  pha_it = pha->end();
  pha_it--;  // end() returns one past the last pha
  timeInterval = pha_it->scet;
  if (DbgLvl >= 2) cout << thisprog << "-D- end_time=" << timeInterval << endl;
  pha_it = pha->begin();
  timeInterval = timeInterval - pha_it->scet;

  /* Differences between cycle times will not include time for the last
     cycle read.  Therefore, add a typical cycle time to the calc. interval.
  */
  timeInterval += 12;

  if (DbgLvl >= 2) {
    cout << thisprog << "-D- start_time=" << pha_it->scet << endl;
    cout << thisprog << "-D- timeInterval=" << timeInterval << endl;
  }

  float ma_sum = 0.0;
  float macounts_sum = 0;
  for (int nedb = FIRSTEDB; nedb < MAXEDB; nedb++){
    for (int ntof = 0; ntof < MAXTOFCH; ntof++){
      for (int nesd = 0; nesd < MAXESDCH; nesd++){

	if (DbgLvl >= 4 && MA[nedb][ntof][nesd] > 0.0){
	  cout << thisprog << "-D- before norm MA[" << nedb 
	       << "," << ntof << "," << nesd
	       << "]=" << MA[nedb][ntof][nesd] << endl;
	}

	MA[nedb][ntof][nesd] += 
	  MAcounts[nedb][ntof][nesd] / (float)timeInterval;

	MAcounts[nedb][ntof][nesd] = 0.0;

	// for debugging
	ma_sum += MA[nedb][ntof][nesd];
	macounts_sum += MAcounts[nedb][ntof][nesd];

	if (DbgLvl >= 4 && MA[nedb][ntof][nesd] > 0.0){
	  cout << thisprog << "-D- after norm MA[" << nedb << "," << ntof 
	       << "," << nesd
	       << "]=" << MA[nedb][ntof][nesd] << endl;
	}

      } // loop over nesd
    } // loop over ntof
  } // loop over EDBs

  if (DbgLvl >= 2){
    cout << thisprog << " -D- sum of all element of MA = " << ma_sum << endl;;
    cout << thisprog << " -D- sum of all element of MAcounts = " 
	 << macounts_sum << endl;;
  }

return 0;
}

TNT::Matrix<float> MeasurementArray::getSlice(int nedb){
  return(MA[nedb]);
}

TNT::Matrix<float> MeasurementArray::EtSlice2Mmq(TNT::Matrix<float> slice, 
  int nedb, const AnalysisData& ad){

  string thisprog = "EtSlice2Mmq";
  int DbgLvl = gDbgLvl; // init local debugging level to global one
  //DbgLvl = 4;

  TNT::Matrix<float> mmq(NQCH, NMCH, 0.0);

  // find max and min for iq and im 
  // (should be hardcoded for consistent binning)
  double mm0 = 0.0;   // min mass
  double mm1 = 0.0;   // max mass
  double mq0 = 0.0;  // min m/q
  double mq1 = 0.0;  // max m/q

  int nmm = 0;
  int nmmzero = 0;
  int nmq = 0;
  int nmqzero = 0;

  /* set mass and m/q limits */
    mm0 = 1.2;
    mm1 = 70.0;
    mq0 = 1.15;
    mq1 = 10.0;

  if (DbgLvl){
    cout << thisprog << " -I- using hardcoded limits" 
	 << " mm0=" << mm0
	 << " mm1=" << mm1
	 << " mq0=" << mq0
	 << " mq1=" << mq1
	 << endl;
  }


  double mm;   // mass for current E-T coordinate
  double mq;   // m/q for current E-T coordinate
  int   im;   // mass bin
  int   iq;   // m/q bin

  for (int ntof = 0; ntof < MAXTOFCH; ntof++){
    for (int nesd = 0; nesd < MAXESDCH; nesd++){

      eqte2mmq(ad.Eqtab[nedb], ad.PapsVolt, ntof, nesd, mm, mq);

      if ( (DbgLvl > 2) && (mm > 0.0 && mq > 0.0) ){
	cout << thisprog << " -D- " 
	     << " nedb=" << nedb
	     << " ntof=" << ntof
	     << " nesd=" << nesd
	     << " mm=" << mm
	     << " mq=" << mq
	     << endl;
      }
      
      /* collect some stats on zero and nonzero mass and m/q */
      if (mm > 0.0){
	nmm++;
      }
      else{
	nmmzero++;
      }

      if (mq > 0.0){
	nmq++;
      }
      else{
	nmqzero++;
      }

      im =  int ( (NMCH - 1) * log(mm/mm0)/log(mm1/mm0) );

      iq =  int ( (NQCH - 1) * log(mq/mq0)/log(mq1/mq0) );

      if ( (DbgLvl > 2) && (im > 0.0 && iq > 0.0) ){
	cout << thisprog << " -D- " 
	     << " nedb=" << nedb
	     << " ntof=" << ntof
	     << " nesd=" << nesd
	     << " im=" << im
	     << " iq=" << iq
	     << endl;
      }
      
      // assign if within mmq dimensions
      if ( ((im >= 0) && (iq >= 0)) &&  ((im < NMCH) && (iq < NQCH)) ){
	mmq[iq][im] += slice[ntof][nesd];

	if (DbgLvl > 2){
	  cout << thisprog << " -D- " 
	       << "mmq=" << mmq[iq][im] << endl;
	}
      }
    }
  }

  /* some stats calculations and output */
  if (DbgLvl){
    float nmmfrac, nmqfrac;
    nmmfrac = (float) nmm / (float) (nmm + nmmzero);
    nmqfrac = (float) nmq / (float) (nmq + nmqzero);
    cout << thisprog << " -D- Non-zero:" 
	 << " nmmfrac=" << nmmfrac
	 << " nmqfrac=" << nmqfrac
	 << endl;
  }

  return mmq;
}

int MeasurementArray::save(string file){

  ofstream fout;
  fout.open(file.c_str());
  fout.precision(10);

  if (gDbgLvl) {
    cout << "MeasurementArray::save -I- saving MA to " << file << endl;
  }

  for (int nedb = FIRSTEDB; nedb < MAXEDB; nedb++){
    fout << MA[nedb];
  }
  fout.close();

  return(0);
}


int MeasurementArray::load(string file){
  string thisprog = "MeasurementArray::load";
  
  ifstream fin;
  fin.open(file.c_str());

  if (gDbgLvl) {
    cout << thisprog << " -I- loading MA from " << file << endl;
  }

  for (int nedb = FIRSTEDB; nedb < MAXEDB; nedb++){
    fin >> MA[nedb];
  }

  return(0);
}

float MeasurementArray::getElement(int nedb, int tofch, int esdch) const {
  /* Is the bounds check here really needed since the TNT array is bounds 
     checked?  At least the nedb condition is because the STL vector is not 
     bounds checked.
  */

  if ( (nedb < MAXEDB) &&
       (tofch < MAXTOFCH) &&
       (esdch < MAXESDCH) ){

    return(MA[nedb][tofch][esdch]);
  }
  else {
    return(-1.0);
  }
}
