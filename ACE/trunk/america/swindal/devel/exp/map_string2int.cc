// Experiment with a map where strings key to int values
// JR, 25Feb2004

#include "swindal.h"

int main (){

  map<string,int> IonsIndex;
  vector<string> names;

  names.push_back("H+");
  names.push_back("He2+");
  names.push_back("O6+");
  //  names.push_back();
  //IonsIndex.insert("H+",1);
  for(int s = 0; s < names.size(); s++){
    IonsIndex[names[s]] = s;
    IonsIndex[names[s]] = s;
    IonsIndex[names[s]] = s;
  }

  for(int s = 0; s < names.size(); s++){
    cout << "IonsIndex[" << names[s] << "]=" << IonsIndex[names[s]] << endl;
  }  

  int s;
  s = 2;
  cout << "IonsIndex[" << names[s] << "]=" << IonsIndex[names[s]] << endl;
  s = 0;
  cout << "IonsIndex[" << names[s] << "]=" << IonsIndex[names[s]] << endl;
  s = 1;
  cout << "IonsIndex[" << names[s] << "]=" << IonsIndex[names[s]] << endl;

  // Works fine!

  return(0);

}
