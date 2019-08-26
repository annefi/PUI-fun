#include "ran_urand.h"
using namespace std;

void ran_urand(vector<double> &ran) {
  unsigned int j = (unsigned int)-1;
  
  static FILE *f;
  if (!f) {
    f=fopen("/dev/urandom", "rb");
    if (!f) {
      cerr << "aaah.\n"; exit(1);
    }
  }
  for (int i=0; i < ran.size(); i++) {
    unsigned int r;
    fread(&r, sizeof(r), 1, f);
    ran[i]=double(r)/double(j);
    //    cout << double(r) << "/" << double(j) <<" = " << double(r)/double(j)<< endl;
    
  }
  //fclose (f);
}
