/* xboxrates.cc -- test the AnalysisData class
   Jim Raines 4Apr2001
*/

#include "swindal.h"

/* Why can't these be avoided? */

// Global debugging level;
int Global::gDbgLvl = 0;    // Put in init routine later

string Global::CurLv1File;  // ACE LV1 filename

int main(){
  char thisprog[] = "xboxrates";
  int i,j;
  
  int result;     // returned value from a function call, used local to call

  /* ===> adjustable parameters */
  /* Number of cycles to analyze at a time */
  int AnalysisInterval = 5;

  int DbgLvl = Global::gDbgLvl;
  /* end of adjustable parameters */

  AnalysisData ad;

  Derivables   deriv;

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

  cout << thisprog << " -I- group2 contains:\n";
  for (i = 0; i < group2.size(); i++){
    cout << "+ ";
    group2[i].print();
    cout << "\n";
  }

  // Load PHA data
  vector<Pha> pha;
  result = 0;
  result = loadPha(&pha, AnalysisInterval);

  if (result != 0){
    cout << "$thisprog -E- loadPha returned " << result << "\n";
  }

  // Classify PHAs into boxes
  result = boxClassify(&pha, &group2, &deriv);

  // Write out results
  cout << "Matrix rates:\n";
  for(i = 0; i < group2.size(); i++){
    cout << "+ " << group2[i].name << " " << 
      deriv.boxrates[group2[i].name] << "\n";
    
  }

}  
