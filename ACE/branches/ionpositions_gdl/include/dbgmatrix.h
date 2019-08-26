//-----------------------------------------------------------------------------
/*! \file dbgmatrix.h
 * \version 1.0
 * \author Lars Berger 
 * \date 2005
 * \brief implementation of the matrix class based on the class dbgvector.h
 */
//-----------------------------------------------------------------------------

#ifndef DBGMATRIX_H
#define DBGMATRIX_H

#include "matrix.h"
#include <iostream>
using namespace std;
//-----------------------------------------------------------------------------
/*! \class Dbgmatrix
 * Dbgmatrix template class
 * \version 1.0
 * \author Fredy Dobler (fredy@dobler.net)
 * \date 1999-2000
 * \brief to handle matricies 
 * \warning not complete implementation, only rudimentary functions
 */
//-----------------------------------------------------------------------------
template<class T>
class Dbgmatrix : public Matrix<T> {
 public:
  Dbgmatrix<T>(); ///<consturct a empty Dbgmatrix
  Dbgmatrix<T>(const int &n, const int &m); ///<construct a n * m matrix with zeros
  vector<T> &operator[](int index);	///< access to a element in the matrix
  const vector<T> &operator[](int index)const; ///< access to a row in the matrix
};

template<class T>
Dbgmatrix<T>::Dbgmatrix<T>(): Matrix<T>() {
}

template<class T>
Dbgmatrix<T>::Dbgmatrix<T>(const int &n, const int &m): Matrix<T>(n,m) {
}

template<class T>
vector<T> &Dbgmatrix<T>::operator[](int index) {
  /*cout << "size(0) : " << size(0) << endl;
  cout << "size(1) : " << size(1) << endl;
  */
  if (index>int((size(1)-1))){
    cout << "Row/Column index Overflow : " << index << " > " << size(1)-1 << endl;
  }
  if (index<0){
    cout << "Row/Column index Underflow : " << index << " < " << "0" << endl;
  }
  /*  if (index<0){
    cout << "Column Index Underflow : " << index << " : " << size(1)-1 << endl;
  }
  */
  //  return vector<T>::operator[](index);
  return Matrix<T>::operator[](index);
}

template<class T>
const vector<T> &Dbgmatrix<T>::operator[](int index) const {
  cout << "size : " << size(0) << endl;
  if (index>int((size(0)-1))){
    cout << "Row Index Overflow : " << index << " : " << size(0)-1 << endl;
  }
  if (index<0){
    cout << "Row Index Underflow : " << index << " : " << size(0)-1 << endl;
  }
  //  return vector<T>::operator[](index);
  return Matrix<T>::operator[](index);
}



#endif

// Local Variables:
// mode:C++
// End:
