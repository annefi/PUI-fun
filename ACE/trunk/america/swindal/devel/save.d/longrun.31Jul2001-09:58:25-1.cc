/* longrun.cc -- test the AnalysisData class
   Jim Raines 4Apr2001
*/

#include "swindal.h"
#include <fstream>

int main(){
  char thisprog[] = "longrun";
  int i,j;
  char tmpstring[150];
  
  int result;     // returned value from a function call, used local to call
  int lpresult;   // returned value from loadPha
  
  initSwindal();

  AnalysisData ad;

  Derivables   deriv;

  MeasurementArray MA;

  /* ===> adjustable parameters */

  /* -- run start/stop days -- */
  long int StartYdoy = 2000150;
  long int StopYdoy  = 2000165;
  
  /* Number of cycles to analyze at a time */
  int AnalysisInterval = 5;

  gDbgLvl = 0;
  int DbgLvl = gDbgLvl; // init local debugging level to global one

  char LV1DIR[] = "/home/acedata/LV1";
  
  /* end of adjustable parameters */

  if (DbgLvl > 2) {
    cout << thisprog << " -I- AnalysisData object contains:\n";
  
    cout << "+ Ions:\n";
    map<string,Ion>::iterator Ions_iter;
    for(Ions_iter = ad.Ions.begin(); Ions_iter != ad.Ions.end(); Ions_iter++){
      Ions_iter->second.print();
      cout << "\n";
    }

    cout << "\n+ E/q table:\n";
    for(i = 0; i < ad.Eqtab.size(); i++){
      printf("Eqtab[%d]=%f\n",i,ad.Eqtab[i]);
    }
  }

  // Define a group of ions to analyze
  vector<Ion> group2;
  group2.push_back(ad.Ions["H+"]);
  group2.push_back(ad.Ions["He2+"]);
  group2.push_back(ad.Ions["O6+"]);
  group2.push_back(ad.Ions["O7+"]);
  group2.push_back(ad.Ions["Fe9+"]);
  string ionnames;

  if (DbgLvl){
    cout << thisprog << " -I- group2 contains:\n";
    for (i = 0; i < group2.size(); i++){
      cout << "+ ";
      group2[i].print();
      cout << "\n";

      ionnames = ionnames + "\t" + group2[i].name;
    }
  }

  /* --- loop over days --- */
  for (long int CurYdoy = StartYdoy; 
       CurYdoy <= StopYdoy; 
       CurYdoy = incrementYdoy(CurYdoy)) {

    cout << thisprog << " -I- processing ydoy " << CurYdoy << endl;
    lpresult = 0;

    /* form filename, e.g. /home/acedata/LV1/2000/2000158.nc */
    sprintf(tmpstring, "%s/%4d/%d.nc\0",LV1DIR, CurYdoy/1000, CurYdoy);
    gCurLv1File = (string) tmpstring;

    if (DbgLvl) {
          cout << thisprog << " -I- using file " << gCurLv1File << endl;
    }

    /* --- loop over analysis intervals to get through whole day --- */
    while ( lpresult == 0 ){

      /* -- load PHAs in block so PHA vector is destroyed each time -- */ 
      {
	// create PHA vector
	vector<Pha> pha;
	
	// load an AnalysisInterval worth of PHAs
	lpresult = loadPha(&pha, AnalysisInterval);
	if (lpresult != 0) {
	  break;
	}

	// Classify PHAs into boxes
	result = boxClassify(&pha, &group2, &deriv);

	// Add to measurement array
	MA.fill(&pha);
      
	// Write out results
	cout << "Box rates:\n";
	for(i = 0; i < group2.size(); i++){
	  cout << "+ " << group2[i].name << " " ;

	  for (j =  0; j < ad.Eqtab.size() ; j++){
	    cout << deriv.getBoxrate(group2[i].name, j) << " ";
	  }

	  cout << "\n";
	}

	// force exit after one Analysis Interval for testing
	//lpresult = 1;
      }
    }

  }

  
  if (lpresult != 0 && lpresult != 2){
    cout << thisprog << " -E- loadPha returned " << lpresult << "\n";
  }

  /* --- write old-stle box rates output to file --- */
  ofstream fout ("simple-boxrates.longrun");

  fout.precision(3);

  fout << "E/q " << ionnames << endl;

  for(i = 0; i < ad.Eqtab.size() ; i++){
    fout << ad.Eqtab[i] << "\t"; 

    for(j = 0; j < group2.size(); j++){
      fout << deriv.getBoxrate(group2[j].name, i) << "\t";
    }

    fout << endl;
  }

  fout.close();

  /* --- write measurement array to file --- */

  fout.precision(3);

  TNT::Matrix<float> a(MAXTOFCH,MAXESDCH, 0.0);
  TNT::Matrix<float> sum(MAXTOFCH,MAXESDCH, 0.0);

  for(i = FIRSTEDB; i < MAXEDB ; i++){
    a = MA.getSlice(i);
    sum = sum + a;
  }

  // --- whole thing
  fout.open("ma.longrun");
  fout << "ACE/SWICS counts/second for day(s) " << StartYdoy <<
    " - " << StopYdoy << endl;
  fout << "TOF_CH ESD_CH" << endl;
  fout << "0 1023 0 255" << endl;
  fout << sum; 
  fout.close();

  /* --- subsection slices --- */
  TNT::Index1D k(300,500);
  TNT::Index1D l(1,130);

  int slices[6] = {18, 24, 30, 36, 42, 48};
  char slicefile[20];
  for (i = 0; i < 6; i++){
    sprintf(slicefile, "ma-sl%02d.%s",slices[i], thisprog);
    fout.open(slicefile);

    fout << "ACE/SWICS counts/second for day(s) " << StartYdoy <<
      " - " << StopYdoy << endl;
    fout << "TOF_CH ESD_CH" << endl;
    fout << "300 500 1 130" << endl;
 
    a = MA.getSlice(slices[i]);
    fout << a(k,l); 
    fout.close();
  }

  /* --- write mmq matrices to file --- */
  TNT::Matrix<float> mmq(NMCH,NQCH, 0.0);
  TNT::Matrix<float> mmqsum(NMCH,NQCH, 0.0);
  TNT::Matrix<float> zero(NMCH,NQCH, 0.0);

  // -- whole thing
  sprintf(slicefile, "mmq.%s",thisprog);
  fout.open(slicefile);

  fout << "ACE/SWICS m-m/q in counts/second for day(s) " << StartYdoy <<
    " - " << StopYdoy << endl;
  fout << "mass/charge mass" << endl;
  fout << "1 " << NMCH << " 1 " << NQCH << endl;
  
  for(i = FIRSTEDB; i < MAXEDB ; i++){
    a = MA.getSlice(i);
    mmq = MA.EtSlice2Mmq(a,i);
    mmqsum = mmqsum + a;
  }

  fout << mmqsum;
  fout.close();

  for (i = 0; i < 6; i++){
    sprintf(slicefile, "mmq-sl%02d.%s",slices[i], thisprog);
    fout.open(slicefile);

    fout << "ACE/SWICS m-m/q in counts/second for day(s) " << StartYdoy <<
      " - " << StopYdoy << endl;
    fout << "mass/charge mass" << endl;
    fout << "1 " << NMCH << " 1 " << NQCH << endl;
 
    a = MA.getSlice(slices[i]);
    mmq = MA.EtSlice2Mmq(a,slices[i]);

    if (mmq != zero) {
      fout << mmq; 
    }
    else if (mmq == zero){
      cout << thisprog << " -D- " 
	   << "mmq from nedb=" << slices[i] 
	   << " equals zero!"  << endl;
    }
    else {
      cout << thisprog << " -D- " 
	   << "mmq from nedb=" << slices[i] 
	   << " does not equal zero or ~zero!"  << endl;
    }
      
    fout.close();
  }

  return(0);
}  
