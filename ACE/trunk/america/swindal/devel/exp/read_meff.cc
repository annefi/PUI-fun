// test out reading SWIMS efficiencies
// Jim Raines, 03Aug2004

#include <fstream>
#include <iostream>
#include <vector>
#include <string>

using std::vector;
using std::string;
using std::cout;
using std::endl;

int main(){
  string thisprog = "read_meff";

  // ===> configure <===
  const int NUM_HEADERS = 3;
  const int NUM_COLUMNS = 3;
  const string eff_file = "../../../amlv2/ref_data/eff/allions_eff.dat";

  std::ifstream eff_fin(eff_file.c_str(), std::ios::in);
  
  if(!eff_fin.is_open()){
    cout << thisprog << " -E- could not open " << eff_file << endl;
    return(1);
  }

  // read through header lines (not saved)
  vector<string> headers;
  string tmpheader;
  for (int i = 0; i < NUM_HEADERS; i++){
    getline(eff_fin,tmpheader);
    headers.push_back(tmpheader);
  }
  
  // -- read in file to get all the values --
  vector<float> values;
  float tmpval;
  while(! eff_fin.eof()){
    eff_fin >> tmpval;
    values.push_back(tmpval);
  }

  eff_fin.close();

  // -- now, break them up into columns --
  int num_rows = values.size()/NUM_COLUMNS;
  vector<float> speed;
  vector<float> mass;
  vector<float> eff;

  int iv = 0;   // counter into 'values' array
  float min_speed=9999., max_speed=0.;
  float min_mass=9999., max_mass=0.;
  for (int irow = 0; irow < num_rows; irow++){
    speed.push_back(values[iv++]);
    if (speed[irow] > max_speed) max_speed = speed[irow];

    mass.push_back(values[iv++]);
    if (mass[irow] > max_mass) max_mass = mass[irow];

    eff.push_back(values[iv++]);
  }

  // Create and initialize the final 2D eff. array
  vector<float> tmp;
  tmp.assign(static_cast<int>(max_mass)+1, 0.0);
  vector<vector<float> > Effic;
  for (int ispeed=0; ispeed < static_cast<int>(max_speed)+1; ispeed++){
    Effic.push_back(tmp);
  }

  // fill that final array
  for (int irow=0; irow < num_rows; irow++){
    int ispeed = static_cast<int>(speed[irow]);
    int imass  = static_cast<int>(mass[irow]);

    Effic[ispeed][imass] = eff[irow];
  }
    
  return(0);
}
