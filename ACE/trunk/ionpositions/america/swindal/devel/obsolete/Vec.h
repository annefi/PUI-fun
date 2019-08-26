/* Range-checked vector template 
   From: The C++ Programming Language, Special E., Bjarne Stroustrup,
   Addison-Wesley, New York 2000 p53

   NOTE: Not used.  Currently DNW!  The at() member function does not
   seem to exist in my STL implementation (or the one on the CAEN
   machines, or the SGI website).  */

template<class T> class Vec : public vector<T> {
 public:
  Vec() : vector<T>() { }
  Vec(int s) : vector<T>(s) { }

  T& operator[] (int i) { return at(i); }             // range-checked
  const T& operator[] (int i) const { return at(i); } // range-checked
};

