/* Does not work */

#include <map>
#include <string>
#include <iostream>
#include <vector>

int repval(map< string,vector<int> > m, int i, int val);
int prepval(map< string,vector<int> > *m, int i, int val);

int main(){
  int ta[60];
  map< string,vector<int> > br;

  

  for (int i = 0; i < 60; i++){
    ta[i] = i*i;
    br["He2+"] = &ta;
  }

  cout << "He2+ br is:\n";
  for (int i = 0; i < 60; i++){
    cout << br["He2+"][i] << " ";
  }
  cout << "\n";

  //repval(br, 20, 3);

  //prepval(&br, 20, 6);

  cout << "He2+ br is:\n";
  for (int i = 0; i < 60; i++){
    cout << br["He2+"][i] << " ";
  }
  cout << "\n";

}

// int repval(map< string,int[60] > m, int i, int val){
//   map< string,vector<int> >::iterator m_it;
  
//   m["He2+"][i] = val;
//   cout << "repval -I- element " << i << " is " << m["He2+"][20] << "\n";

//   return 0;

// }

// int prepval(map< string,int[60] > *m, int i, int val){
//   map< string,vector<int> >::iterator m_it;
  
//   m_it= m->find("He2+");
//   m_it->second[i] = val;
//   m_it->second[i]++;
//   cout << "prepval -I- element " << i << " is " << m_it->second[i] << "\n";

//   return 0;

// }

