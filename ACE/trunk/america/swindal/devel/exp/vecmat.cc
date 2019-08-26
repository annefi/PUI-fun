#include "swindal.h"

int main(){
  int size = 4;
  int size2 = 4;

  vector<vector<bool> > Removed; // table of species removed at a give      
  vector<bool> tmpv(size, false);
  for (int nedb = 0; nedb < size2; nedb++){ // starts at zero so index=nedb
    Removed.push_back(tmpv);
  }

  Removed[0][0] = true;
  Removed[1][1] = true;
  Removed[2][2] = true;
  Removed[3][3] = true;


  cout << "Removed[][]=" << endl;
  for (int nedb = 0; nedb < size2; nedb++){ // starts at zero so index=nedb
    for (int s = 0; s < size; s++){
      cout << " " << Removed[nedb][s];	  
    }
    cout << endl;
  }

  cout << endl;
  cout << "As a truth table, Removed[][]=" << endl;
  for (int nedb = 0; nedb < size2; nedb++){ // starts at zero so index=nedb
    for (int s = 0; s < size; s++){
      //cout << " " << Removed[nedb][s];

      if (Removed[nedb][s]){
	cout << " " << "T";
      }
      else{
	cout << " " << "F ";
      }
	  
    }
    cout << endl;
  }

  return(0);
}
	 
