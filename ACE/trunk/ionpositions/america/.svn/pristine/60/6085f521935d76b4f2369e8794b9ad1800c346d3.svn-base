#include "swindal.h"

int main(){
  Pha pha;
  vector<string> names;
  names.push_back("He2+");
  names.push_back("O6+");
  names.push_back("O7+");
  names.push_back("Fe9+");

  float tof[] = {170.0, 347.9, 
		 193.7, 400.0, 
		 179.3,370.4, 
		 293.1, 601.7};
  float stof[] = {2.108, 4.314,
		  2.402, 4.960,
		  2.224, 4.592,
		  3.634, 7.461};
  int tofch;

  cout << "range of tof2tofch:" << endl;
  for (int i = 0; i < 8; i++){
    if (!(i % 2)) cout << names[i / 2] << endl;
    cout << tof[i] << " +/- " << stof[i];
    cout << " -> " 
	 << pha.tof2tofch(tof[i]) 
	 << " +/- " 
	 << pha.tof2tofch(stof[i])
	 << endl;
  }
}
