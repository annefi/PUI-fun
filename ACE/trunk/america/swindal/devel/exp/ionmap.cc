#include <stl.h>
#include <iostream>
#include <cstdlib>
#include <string>
#include <map>
#include <vector>

class Ion {
 public:
  string name;             // name of ion, includes charge (e.g. He2+)
  float mass;              // mass (in amu) of ion
  float charge;            // charge (in units of elem. charge) of ion

  /* forward model variables, one set per E/q step */
  vector<double> esd;       // Energy measured by solid state detector
  vector<double> tof;       // time of flight 
  vector<double> sesd;      // variance of esd
  vector<double> stof;      // variance of tof

  void print(void);            // print Ion
  Ion::Ion(void);
  Ion(const string i_name, float i_mass, float i_charge); // Constructor
  bool operator== (const Ion& right) const;  // define equality operator

  // Load SWICS Forward Model ouput
  //void Ion::lxfm(double, double, double, double);

 private:
};

/* ------------------- */
/* Ion Class Functions */
/* ------------------- */
// Prints values
void Ion::print(void){
  cout << "name=" << name << " mass=" << mass << " charge=" << charge << "\n";
  //printf ("name=%4s mass=%6.2f charge=%6.2f",name,mass,charge);
}

// Constructor -- zeroed values
Ion::Ion(void){
  name = "";
  mass = 0.0;
  charge = 0.0;
}

// Constructor -- initialized values
Ion::Ion(const string i_name, float i_mass, float i_charge){
  name = i_name;
  mass = i_mass;
  charge = i_charge;
}

// Equality operator for Ion class
bool Ion::operator== (const Ion &right) const {
  return( name == right.name);
}

int main(){
  map<string, Ion> Ions;

  Ions["H+"] = Ion("H+",1.0,1.0);
  Ions["He2+"]= Ion("He2+",4.0,2.0);
  Ions["C6+"] = Ion("C6+",12.0,6.0);
  
  string name = "O6+";
  Ions[name] = Ion(name,16.0,6.0);
  cout << Ions["O6+"].mass << "\n";

  map<string,Ion>::iterator iter_Ions = Ions.begin();
  while (iter_Ions != Ions.end()){
    //cout << (*iter_Ions).name << "\n";
    cout << iter_Ions->first << " mass is " <<
      iter_Ions->second.mass << "\n";
    iter_Ions++;
  }

  vector<string> group1;

  group1.push_back("H+");
  group1.push_back("He2+");
  group1.push_back("O6+");

  cout << "Group one consists of the following ions:\n";
  for (int i = 0; i < group1.size(); i++){
    cout << group1[i] << ", mass is " << Ions[group1[i]].mass <<
      ", charge is " << Ions[group1[i]].charge;
    cout << "\n";
  }

  vector<Ion> group2;

  group2.push_back(Ions["H+"]);
  group2.push_back(Ions["He2+"]);
  group2.push_back(Ions["O6+"]);

  cout << "Group two consists of the following ions:\n";
  for (int i = 0; i < group2.size(); i++){
    cout << group2[i].name << ", mass is " << group2[i].mass <<
      ", charge is " << group2[i].charge ;
    cout << "\n";
  }

}
