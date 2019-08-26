// Find all Oxygen ions in grp
#include "swindal.h"

int main(int argc, char* argv[]){
  initSwindal();  // initializes global variables
  AnalysisData ad;
  ad.init(); // initialize ion arrays and other non-file dependent stuff

  cout << "Dumping ad:" << endl;
  //ad.dump();


  cout << "Using ion names in place:" << endl;
  cout << "(names are printed after symbols for successful finds)" << endl;
  vector<Ion> found;
  for (int s = 0; s < ad.Ions.size(); s++){
    printf("%s ",ad.Ions[s].name.c_str());
    if (ad.Ions[s].name.find("O") != std::string::npos){
      cout << "(oxygen) ";
      found.push_back(ad.Ions[s]);
    }
    else if (ad.Ions[s].name.find("Mg") != std::string::npos){
      cout << "(magnesium) ";
      found.push_back(ad.Ions[s]);
    }
    else if (ad.Ions[s].name.find("Ne") != std::string::npos){
      cout << "(neon) ";
      found.push_back(ad.Ions[s]);
    }
    else if (ad.Ions[s].name.find("8+") != std::string::npos){
      cout << "(charge 8+) ";
      found.push_back(ad.Ions[s]);
    }

  }
  printf("\n");

  cout << "Using ion names in local vector:" << endl;
  vector<string> ions;
  cout << "(names are printed after symbols for successful finds)" << endl;
  for (int s = 0; s < ad.Ions.size(); s++){
    printf("%s ",ad.Ions[s].name.c_str());
    ions.push_back(ad.Ions[s].name);
    //cout << ions[s].substr(0,1) + " ";
    if (ions[s].find("O") != std::string::npos){
      cout << "(oxygen) ";
    }
    else if (ions[s].find("Mg") != std::string::npos){
      cout << "(magnesium) ";
    }
    else if (ions[s].find("Ne") != std::string::npos){
      cout << "(neon) ";
    }

  }
  printf("\n");

  cout << endl;
  cout << "Found:" << endl;
  for (int s = 0; s < found.size(); s++){
    cout << found[s].name + " ";
  }
  cout << endl;

  return(0);
}
