#include <list>
#include <iostream>

int main(){

  int i;
  list<int> l;
  list<int>::iterator l_it;

  for (i = 0; i < 10; i++){
    l.push_back(i);
  }

  cout << "Dumping l:\n";
  for (l_it = l.begin(); l_it != l.end(); l_it++){
    cout << *l_it << " ";
  }
  cout << "\n";

  cout << "Popping off l:\n";
  list<int>::iterator l_it2;
  l_it = l.begin();
  while (l_it != l.end()){
    for (; l_it != l.end(); l_it++){
      cout << *l_it << " ";
    }
    cout << "\n";
    l.pop_front();
    l_it = l.begin();
  }
  cout << "\n";


}
