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
    MM.push_back(A);
    MQ.push_back(A);
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

  double timeInterval;  // seconds between first and last PHA

  vector<Pha>::iterator pha_it;
  //DbgLvl = 4;

  if (DbgLvl) {
    cout << thisprog << " -I- filling MeasurementArray..." << endl;
  }

  /* --- count PHA words with tof (channels), esd (channels) and nedb --- */
  for (pha_it = pha->begin(); pha_it != pha->end(); pha_it++){
    if (pha_it->nedb < MAXEDB){

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
      else if (DbgLvl > 3) {
	cout << thisprog << " -D- dumping meas. array coord.: "
	     << " nedb=" << pha_it->nedb 
	     << " tofch=" << pha_it->tofch 
	     << " esdch=" << pha_it->esdch 
	     << endl;
      }

      if (DbgLvl > 3) {
	cout << thisprog << "-D- before add MA[" << pha_it->nedb << "," 
	     << pha_it->tofch << "," 
	     << pha_it->esdch << "]=" 
	     << MA[pha_it->nedb][pha_it->tofch][pha_it->esdch] << endl;
      }

      /* increment counts in E-T matrix */
      MA[pha_it->nedb][pha_it->tofch][pha_it->esdch] += 1.0;

      /* store this mass */
      MM[pha_it->nedb][pha_it->tofch][pha_it->esdch] = pha_it->mm;

      /* store this m/q */
      MQ[pha_it->nedb][pha_it->tofch][pha_it->esdch] = pha_it->mq;

      if (DbgLvl > 3) {
	cout << thisprog << "-D- after add MA[" << pha_it->nedb << "," 
	     << pha_it->tofch << "," 
	     << pha_it->esdch << "]=" 
	     << MA[pha_it->nedb][pha_it->tofch][pha_it->esdch] << endl << endl;
      }

    }
  }

  /* --- normalize counts in array to counts/second --- */
  pha_it = pha->end();
  pha_it--;
  timeInterval = pha_it->scet;
  if (DbgLvl > 1) cout << thisprog << "-D- end_time=" << timeInterval << endl;
  pha_it = pha->begin();
  timeInterval = timeInterval - pha_it->scet;
  if (DbgLvl > 1) {
    cout << thisprog << "-D- start_time=" << pha_it->scet << endl;
    cout << thisprog << "-D- timeInterval=" << timeInterval << endl;
  }

  if (timeInterval > 0) {
    for (int nedb = FIRSTEDB; nedb < MAXEDB; nedb++){
      for (int ntof = 0; ntof < MAXTOFCH; ntof++){
	for (int nesd = 0; nesd < MAXESDCH; nesd++){

	  //	  if (MA[nedb][ntof][nesd] > 0.0){
// 	    cout << thisprog << "-D- before norm MA[" << nedb << "," << ntof << "," << nesd
// 		 << "]=" << MA[nedb][ntof][nesd] << endl;
// 	  }

	  MA[nedb][ntof][nesd] = MA[nedb][ntof][nesd] / (float)timeInterval;

// 	  if (MA[nedb][ntof][nesd] > 0.0){
// 	    cout << thisprog << "-D- after norm MA[" << nedb << "," << ntof 
// 		 << "," << nesd
// 		 << "]=" << MA[nedb][ntof][nesd] << endl;
// 	  }

	}
      }
    }
  }


  return 0;
}

TNT::Matrix<float> MeasurementArray::getSlice(int nedb){
  return(MA[nedb]);
}

TNT::Matrix<float> MeasurementArray::EtSlice2Mmq(TNT::Matrix<float>, int nedb){
  string thisprog = "EtSlice2Mmq";
  int DbgLvl = gDbgLvl; // init local debugging level to global one

  TNT::Matrix<float> mmq(NMCH, NQCH, 0.0);

  // find max and min for iq and im 
  // (should be hardcoded for consistent binning)
  double mm0 = 0;   // min mass
  double mm1 = 0;   // max mass
  double mq0 = 0;  // min m/q
  double mq1 = 0;  // max m/q

  int nmm = 0;
  int nmmzero = 0;
  int nmq = 0;
  int nmqzero = 0;

  /* set mass and m/q limits, either from data or hardcoded */
  if (0){
    cout << thisprog << " -I- finding limits from data" << endl;

    for (int ntof = 0; ntof < MAXTOFCH; ntof++){
      for (int nesd = 0; nesd < MAXESDCH; nesd++){

	/* Note: All the special mmch channels, ie. > NMCH, cannot
	   be converted to masses so they are multiplied by 10 and saved
	   in mm.  We don't want these to change our binning system so
	   we eliminate them.
	*/
	if (MM[nedb][ntof][nesd]  < mm0 ){
	  mm0 = MM[nedb][ntof][nesd];
	}
      
	if (MM[nedb][ntof][nesd]  > mm1 &&
	    MM[nedb][ntof][nesd]  < NMCH*10.0){
	  mm1 = MM[nedb][ntof][nesd];
	}
	
	/* Note: All the special mmch channels, ie. > NQCH, cannot
	   be converted to masses so they are multiplied by 10 and saved
	   in mm.  We don't want these to change our binning system so
	   we eliminate them.
	*/
	if (MQ[nedb][ntof][nesd]  < mq0){
	  mq0 = MQ[nedb][ntof][nesd];
	}
	
	if (MQ[nedb][ntof][nesd]  > mq1 &&
	    MQ[nedb][ntof][nesd]  < NQCH*10.0){
	  mq1 = MQ[nedb][ntof][nesd];
	}
	
      }
    }
  }
  else{
    cout << thisprog << " -I- using hardcoded limits" << endl;
    
    mm0 = 1.2;
    mm1 = 70.0;
    mq0 = 1.15;
    mq1 = 10.0;
  }
  

  if (DbgLvl){
    cout << thisprog << " -I- " 
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

      /* collect some stats on zero and nonzero mass and m/q */
      if (MM[nedb][ntof][nesd] > 0.0){
	nmm++;
      }
      else{
	nmmzero++;
      }

      if (MQ[nedb][ntof][nesd] > 0.0){
	nmq++;
      }
      else{
	nmqzero++;
      }

      mm = MM[nedb][ntof][nesd];
      mq = MQ[nedb][ntof][nesd];

      if ( (DbgLvl > 2) && (mm > 0.0 && mq > 0.0) ){
	cout << thisprog << " -D- " 
	     << " nedb=" << nedb
	     << " ntof=" << ntof
	     << " nesd=" << nesd
	     << " mm=" << mm
	     << " mq=" << mq
	     << endl;
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
      
      if ( ((im >= 0) && (iq >= 0)) &&  ((im < NMCH) && (iq < NQCH)) ){
	mmq[im][iq] += MA[nedb][ntof][nesd];

	if (DbgLvl > 2){
	  cout << thisprog << " -D- " 
	     << "mmq=" << mmq[im][iq] << endl;
	}
      }
    }
  }

  /* some stats calculations and output */
  if (DbgLvl){
    float nmmfrac, nmqfrac;
    nmmfrac = (float) nmm / (float) (nmm + nmmzero);
    nmqfrac = (float) nmq / (float) (nmq + nmqzero);
    cout << thisprog << " -D- " 
	 << " nmmfrac=" << nmmfrac
	 << " nmqfrac=" << nmqfrac
	 << endl;
  }

  return mmq;
}
