#include "swindal.h"

int main(int argc, char* argv[]){
  initSwindal();  // initializes global variables
  AnalysisData ad;
  vector<Ion> grp2;
  cout << "after declaration:"
       << " grp2.size()=" << grp2.size() 
       << " grp2.capacity()=" << grp2.capacity()
       << endl;

  grp2.reserve(3);
  grp2.assign(3,ad.Ions[0]);

  cout << "after assign:"
       << " grp2.size()=" << grp2.size() 
       << " grp2.capacity()=" << grp2.capacity()
       << endl;

  grp2.push_back(ad.Ions[0]);
  grp2.push_back(ad.Ions[1]);
  grp2.push_back(ad.Ions[2]);

  cout << "after push_backs:"
       << " grp2.size()=" << grp2.size() 
       << " grp2.capacity()=" << grp2.capacity()
       << endl;

  cout << "dumping grp2:" << endl;
  for (int s = 0; s < 3; s++){
    grp2[s].dump();
  }

  return(0);
}
