//#include "swindal.h"
#include <stl.h>
#include <sstream>
#include <iomanip>

int main(int argc, char* argv[]){
  
  vector<float> doyfrs;
  doyfrs.push_back(302.04);
  doyfrs.push_back(302.08);
  doyfrs.push_back(302.12);
  doyfrs.push_back(2.89);

  string outfile;
  int idoy, ifr;
  float doy,fr;
  for(int i = 0; i < doyfrs.size(); i++){
    idoy = static_cast<int> (doyfrs[i]);

    doy  = static_cast<float> (idoy);

    ifr  = static_cast<int> (doyfrs[i]*100.0 + .5) % 100;

    cout << "doyfrs["<<i<<"]="<<doyfrs[i]
	 << " idoy=" << idoy << " doy=" << doy
	 << " ifr=" << ifr << " fr=" << fr << endl;

    ostringstream doyfr_str;
    doyfr_str << setfill('0') << setw(3) << idoy << "_" << setw(2) << ifr;
    outfile = "axlv2_et_slices_" + doyfr_str.str() + ".dat";
    cout << "outfile: " << outfile << endl;
  }
  
  
  return(0);
}
