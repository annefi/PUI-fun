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

      MA[pha_it->nedb][pha_it->tofch][pha_it->esdch] += 1.0;

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

TNT::Matrix<float> MeasurementArray::EtSlice2Mmq(int nedb){

}
