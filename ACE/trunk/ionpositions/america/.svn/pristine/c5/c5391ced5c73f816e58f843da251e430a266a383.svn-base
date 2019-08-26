#include "../swindal.h"
#include <fstream>

class widget {
public:
  int val;

  widget(int);

  void print(void);

private:

};

int sub1(vector<widget> *);

int main(){

  // Define a group of ions to analyze
  vector<widget> group2;
  for (int i = 0 ; i < 5; i++){
    group2.push_back(widget(i*i));
  }

  sub1(&group2);
}


int sub1(vector<widget> *grp){
  cout << "sub1 -I- grp contains:\n";
  for (int i = 0; i < grp->size(); i++){
    cout << "+ ";
    cout << (*grp)[i].val;
    (*grp)[i].print();
    cout << "\n";
  }

  return(0);
}


widget::widget(int aval){
  val = aval;
}

void widget::print(){
  cout << val;
}
