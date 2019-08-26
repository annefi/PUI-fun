/*
  File: correctFeFM.cc

  Description:
    Correct Iron Forward Model with deltas from offline peak pick and fit.

  Author(s): Jim Raines (jmr)

  Method:
    Uses data produced by fmpick_cfe.pro from picking Fe peaks and calculating
    the difference between these and the forward model.

  Revision controlled by CVS:
  $Id: correctFeFM.cc,v 1.2 2004/07/28 13:28:41 jraines Exp $

  Major Modification History:
    26Nov2003   jmr   initial coding

*/
#include "swindal.h"

int correctFeFM(string file, AnalysisData& ad){
  const string thisprog = "correctFeFM";

  std::ifstream fin;
  fin.open(file.c_str());
  if (! fin.good()) {
    cout << thisprog << " -F- Error opening " << file << endl;
    return(-1);
  }

  // read through headers
  string header1;
  getline(fin, header1);
  cout << "header: " << header1 << endl;
  string header2;
  getline(fin, header2);
  cout << "header: " << header2 << endl;
  string header3;
  getline(fin, header3);
  cout << "header: " << header3 << endl;

  // find first Fe ion
  int fe6;
  // fe6 = ad.IonsIndex["Fe6+"];  // DNW
  for (int s = 0; s < ad.Ions.size(); s++){
    if (ad.Ions[s].name == "Fe6+") fe6 = s;
  }
  cout << "Fe6+ is ion " << fe6 << endl;

  string fmfile;
  if (gDbgLvl >= 2) {
    cout << thisprog << " -I- dumping before modification:" << endl;
    fmfile = "correctFeFM_before.dat";
    ad.outputFM(fmfile);
  }

  int s = fe6;
  while(s < ad.Ions.size() && ! fin.eof()){
    string ion = "";
    float tof_corr = 0.0;
    float esd_corr = 0.0;
    fin >> ion >> tof_corr >> esd_corr;
    cout << "ion=" << ion << " tof_corr=" << tof_corr << " " 
	 << " esd_corr=" << esd_corr << endl;
    
    for (int nedb = FIRSTEDB; nedb < MAXEDB; nedb++){


      // Best way -- DNW
//       ad.IonsByName[ion].tof[nedb] = 
// 	ad.IonsByName[ion].tof[nedb] - tof_corr;
//       ad.IonsByName[ion].esd[nedb] = 
// 	ad.IonsByName[ion].esd[nedb] - esd_corr;

      // Good way -- DNW
//       ad.Ions[ad.IonsIndex[ion]].tof[nedb] = 
// 	ad.Ions[ad.IonsIndex[ion]].tof[nedb] - tof_corr;
//       ad.Ions[ad.IonsIndex[ion]].esd[nedb] = 
// 	ad.Ions[ad.IonsIndex[ion]].esd[nedb] - esd_corr;

      // Bad way -- works!
      ad.Ions[s].tof[nedb] = 
	ad.Ions[s].tof[nedb] - tof_corr;
      ad.Ions[s].esd[nedb] = 
	ad.Ions[s].esd[nedb] - esd_corr;
    }
    
    s++;
  }

  fin.close();

  if (gDbgLvl >= 2) {
    cout << thisprog << " -I- dumping after modification:" << endl;
    fmfile = "correctFeFM_after.dat";
    ad.outputFM(fmfile);
  }

  return(0);
}
