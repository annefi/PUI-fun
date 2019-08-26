/* adtest.cc -- test the AnalysisData class
   Jim Raines 4Apr2001
*/

#include "swindal.h"

int main(){
  char thisprog[] = "adtest";
  int i,j;

  AnalysisData ad;


  cout << thisprog << " -I- AnalysisData object contains:\n";
  
  cout << "+ Ions:\n";
  for(i = 0; i < ad.Ions.size(); i++){
    ad.Ions[i].print();
    cout << "\n";
  }

  cout << "\n+ E/q table:\n";
  for(i = 0; i < ad.Eqtab.size(); i++){
    printf("Eqtab[%d]=%f\n",i,ad.Eqtab[i]);
  }

}  
