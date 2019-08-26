#include "../swindal.h"
#include <fstream>

int sub1(vector<int> *);

int main(){

  // Define a group of ions to analyze
  vector<int> group2;
  for (int i = 0; i < 5; i++){
    group2.push_back(i);
  }

  sub1(&group2);
}


int sub1(vector<int> *grp){
  cout << "sub1 -I- grp contains:\n";
  for (int i = 0; i < grp->size(); i++){
    cout << "+ ";
    cout << (*grp)[i];
    cout << "\n";
  }

  return(0);
}
