// Try out a string, float map
// JR, 22Mar2004

#include <iostream>
#include <map>
#include <string>
#include <iostream>
#include <vector>

int main(){
  
  map<string, float> hk;

  //  hk.insert(make_pair("V_hyp", 23.3));
  //  hk.insert(make_pair("V_f", 0.0));
  hk["V_hyp"] =  23.3;
  hk["V_f"] = 0.0;

  cout << "hk[V_hyp]=" << hk["V_hyp"] << endl;
  cout << "hk[V_f]=" << hk["V_f"] << endl;

}
// works!
