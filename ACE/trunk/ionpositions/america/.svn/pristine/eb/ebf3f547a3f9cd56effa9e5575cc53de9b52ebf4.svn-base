#include "swindal.h"

void sub1(const vector<float>& a);
void sub2(const TNT::Matrix<float>& b);

int main(int argc, char* argv[]){

  vector<float> a; 

  for(int i = 0; i < 4; i++){
    a.push_back(i*i);

    cout << "main:  a[" << i << "]=" << a[i] << endl;
  }

  sub1(a);

  TNT::Matrix<float> b(4,4,0.0);

  for(int i = 0; i < 4; i++){
    for(int j = 0; j < 4; j++){
      b[i][j] = i*10.0 + j;
      
      cout << "main:  b[" << i << "][" << j << "]=" << b[i][j] << endl;
    }
  }

  sub2(b);

  return(0);
}

void sub1(const vector<float>& a){
  
  cout << "sub1: a[2]=" << a[2] << endl;
  
}

void sub2(const TNT::Matrix<float>& b){
  cout << "sub2: b[2][2]=" << b[2][2] << endl;
}
