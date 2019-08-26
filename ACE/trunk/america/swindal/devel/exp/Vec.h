/* Range-checked vector template 
   From: The C++ Programming Language, Special E., Bjarne Stroustrup,
   Addison-Wesley, New York 2000 p53
*/
#include <stl.h>

template<class T> class Vec : public vector<T> {
 public:
  Vec() : vector<T>() { }
  Vec(int s) : vector<T>(s) { }

  T& operator[] (int i) { return at(i); }             // range-checked
  const T& operator[] (int i) const { return at(i); } // range-checked
};
