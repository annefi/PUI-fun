#include "Vec.h"
#include <iostream>
#include <vector>

using namespace std;

int main(){
  //Vec<double> esd(60);
  vector<double> esd2;

  //esd.push_back(55.5);
  for (int i = 0; i < 5; i++){
    esd2.push_back(12.0 * i);
  }

  //cout << esd[0];
  for (int i = 0; i < 5; i++){

    cout << esd2.front() << "\n";
    cout << esd2[i] << "\n";
    //cout << esd2.at(i) << "\n";
    cout << esd2.back() << "\n\n";
  }
}
