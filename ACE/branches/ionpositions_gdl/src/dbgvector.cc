
template<class T>
dbgvector<T>::dbgvector<T>(): vector<T>(0) {
}

template<class T>
dbgvector<T>::dbgvector<T>(const int &n) : vector<T>(n) {}

template<class T>
dbgvector<T>::dbgvector<T>(const int &n, const T &m) : vector<T>(n, m) {}


template<class T> 
T &dbgvector<T>::operator[](int index)
{
  if (index>int((size()-1))){
    cout << "Index Overflow : " << index << " > " << size()-1 << endl;
  }
  if (index<0){
    cout << "Index Underflow : " << index << " < " << size()-1 << endl;
  }
  return vector<T>::operator[](index);
}

// Local Variables:
// mode:C++
// End:
