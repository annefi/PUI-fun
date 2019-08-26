#include "swindal.h"

int main(){
  string s1 = "He2+";
  string s2 = "H1+";
  string filler;
  vector<string> v1;

  v1.push_back(s1);
  v1.push_back(s2);

  ofstream fout;
  fout.open("savestring.dat");
  
  fout << s1 << " " << s2 << endl;

  for (int i = 0; i < v1.size(); i++){
    fout << v1[i] << " ";
  }

  fout.close();

  ifstream fin;
  fin.open("savestring.dat");
  
  fin >> s1;
  fin >> s2;
  //fin >> filler;

  cout << "s1=" << s1 << " s2=" << s2 << endl;
  //cout << " filler=" << filler << endl;

  for (int i = 0; i < v1.size(); i++){
     fin >> v1[i];
     cout << " v1[" << i << "]=" << v1[i];
  }
  cout << endl;

  fin.close();


  return (0);
}
