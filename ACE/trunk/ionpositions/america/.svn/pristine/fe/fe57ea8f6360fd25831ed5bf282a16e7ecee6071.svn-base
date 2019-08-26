/* xboxrates.cc -- test the AnalysisData class
   Jim Raines 4Apr2001
*/

#include "swindal.h"
#include <fstream>

int main(){
  char thisprog[] = "xboxrates";
  int i,j;
  
  int result;     // returned value from a function call, used local to call
  int lpresult;   // returned value from loadPha
  
  initSwindal();

  AnalysisData ad;

  Derivables   deriv;

  /* ===> adjustable parameters */
  /* Number of cycles to analyze at a time */
  int AnalysisInterval = 5;

  gDbgLvl = 1;
  int DbgLvl = gDbgLvl; // init local debugging level to global one
 
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

  cout << thisprog << " -I- group2 contains:\n";
  for (i = 0; i < group2.size(); i++){
    cout << "+ ";
    group2[i].print();
    cout << "\n";

    ionnames = ionnames + "\t" + group2[i].name;
  }

  /* --- loop over analysis intervals to get through whole day --- */

  lpresult = 0;

  while ( lpresult == 0 ){

    /* -- load PHAs in block so PHA vector is destroyed each time -- */ 
    {
      // create PHA vector
      vector<Pha> pha;

      // load an AnalysisInterval worth of PHAs
      lpresult = loadPha(&pha, AnalysisInterval);

      // Classify PHAs into boxes
      result = boxClassify(&pha, &group2, &deriv);

      // Write out results
      cout << "Box rates:\n";
      for(i = 0; i < group2.size(); i++){
	cout << "+ " << group2[i].name << " " ;

	for (j =  0; j < ad.Eqtab.size() ; j++){
	  cout << deriv.getBoxrate(group2[i].name, j) << " ";
	}

	cout << "\n";
      }
    }
  }

  
  if (lpresult != 0 && lpresult != 2){
    cout << thisprog << " -E- loadPha returned " << lpresult << "\n";
  }

  /* --- write output to file --- */
  ofstream fout ("xboxrates.dat");

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

  return(0);
}  
