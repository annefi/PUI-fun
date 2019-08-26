#include "swindal.h"

int main(int argc, char* argv[]){
  initSwindal();  // initializes global variables
  AnalysisData ad;
  ad.dump();

  vector<Ion> newgrp;

  cout << "forming newgrp and dumping newgrp[s] and ad.Ion[s]:" << endl;
  for (int s = 0; s < 3; s++){
    newgrp.push_back(ad.Ions[s]);
    cout << "ad.Ions[" << s << "]=" << endl;
    ad.Ions[s].dump();
    cout << "newgrp[" << s << "]=" << endl;
    newgrp[s].dump();

  }
  cout << "ad.Ions[1].tof[12]=" << ad.Ions[1].tof[12] << endl;
  cout << " newgrp[1].tof[12]=" << newgrp[1].tof[12] << endl;

  return(0);
}
