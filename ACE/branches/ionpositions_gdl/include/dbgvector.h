#ifndef DBGVECTOR_H
#define DBGVECTOR_H

#include <iostream>
#include <vector>

using namespace std;

template <class T>
class dbgvector : public vector<T>
{
public:
  dbgvector<T>();
  dbgvector<T>(const int &n);
  dbgvector<T>(const int &n,const T &m);
  T &operator[](int index);
  

  //T &operator[](int index);
private:
  //vector<T> dbgvec;
};


#include "../src/dbgvector.cc"


#endif

// Local Variables:
// mode:C++
// End:
