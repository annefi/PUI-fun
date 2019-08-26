// parse ion name, e.g. 20Ne8+, to element name, Ne.
// J. Raines, 29Oct2003

#include <string>
#include <stl.h>
#include <iostream>

// in order of increasing atomic number
enum Element {H, He, C, N, O, Ne, Mg, Si, S, Ar, Fe, Kr};
const int NElement = 12;  // number of Elements

int main(){

  string ion;
  string element_name;
  Element elem;
  string file;

  while(1){
    cout << "ion: ";
    cin >> ion;

    if (ion.find("He") != std::string::npos){  // He out of order so it's found before H
      element_name = "He";
      elem = He;
      file = "HE_MOD.DAT";
    }
    else if (ion.find("H") != std::string::npos){
      element_name = "H";
      elem = H;
      file = "H__MOD.DAT";
    }
    else if (ion.find("C") != std::string::npos){
      element_name = "C";
      elem = C;
      file = "C__MOD.DAT";
    }
    else if (ion.find("Ne") != std::string::npos){
      element_name = "Ne";
      elem = Ne;
      file = "NE_MOD.DAT";
    }
    else if (ion.find("N") != std::string::npos){
      element_name = "N";
      elem = N;
      file = "N__MOD.DAT";
    }
    else if (ion.find("O") != std::string::npos){
      element_name = "O";
      elem = O;
      file = "O__MOD.DAT";
    }
    else if (ion.find("Mg") != std::string::npos){
      element_name = "Mg";
      elem = Mg;
      file = "MG_MOD.DAT";
    }
    else if (ion.find("S") != std::string::npos){
      element_name = "S";
      elem = S;
      file = "S__MOD.DAT";
    }
    else if (ion.find("Si") != std::string::npos){
      element_name = "Si";
      elem = Si;
      file = "SI_MOD.DAT";
    }
    else if (ion.find("Ar") != std::string::npos){
      element_name = "Ar";
      elem = Ar;
      file = "AR_MOD.DAT";
    }
    else if (ion.find("Fe") != std::string::npos){
      element_name = "Fe";
      elem = Fe;
      file = "FE_MOD.DAT";
    }
    else if (ion.find("Kr") != std::string::npos){
      element_name = "Kr";
      elem = Kr;
      file = "KR_MOD.DAT";
    }

    cout << " element_name=" << element_name
	 << " elem=" << elem
	 << " file=" << file << endl;

  }  
}
