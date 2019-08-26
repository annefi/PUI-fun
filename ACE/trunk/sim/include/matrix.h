//-----------------------------------------------------------------------------
/*! \file matrix.hh
 * \version 1.0
 * \author Fredy Dobler (dobler@phim.unibe.ch)
 * \author Lars Berger <berger@physik.uni-kiel.de>
 * \author Onno Kortmann <kortmann@physik.uni-kiel.de>
 * \date 1999-2000
 * \brief implementation of the matrix class
 */
//-----------------------------------------------------------------------------

#ifndef LIBETPH_MATRIX_HH
#define LIBETPH_MATRIX_HH
#include <algorithm>
#include <vector>
#include <iostream>
//-----------------------------------------------------------------------------
/*! \class Matrix
 * Matrix template class
 * \version 1.0
 * \author Fredy Dobler (fredy@dobler.net)
 * \date 1999-2000
 * \brief to handle matricies 
 * \warning not complete implementation, only rudimentary functions
 */
//-----------------------------------------------------------------------------
template<class T>
class Matrix {
 public:
  Matrix<T>(); ///<consturct a empty Matrix
  Matrix<T>(const int &n, const int &m); ///<construct a n * m matrix with zeros
  Matrix<T>(const Matrix<T> &copy); ///<Matrix copy constructor
  Matrix<T>(const std::vector<std::vector<T> > &copy);///<Vector copy constructor
  
  Matrix<T> operator*(const Matrix<T> &rh)const;///<Matrix multiplication
  Matrix<T> operator*(const T &skalar)const;///<skalar * Matrix
  Matrix<T> operator+(const Matrix<T> &rh) const;///<Matrix addition
  Matrix<T> operator-(const Matrix<T> &rh) const;///<Matrix subtraction
  std::vector<T> &operator[](int index);	///< access to a element in the matrix
  const std::vector<T> &operator[](int index)const; ///< access to a row in the matrix
  void transpose(); ///< Matrix transposition
  unsigned int size(int i) const; ///< Matrix size
  ///get the matrix as a std::vector<vector> >
  std::vector<std::vector<T> > getVecVec() const {return matrix;};

  //! sort the matrix according to one column
  void sort(size_t col);
  
  ///set all elements to 0
  void setzero();
  
 private:
  std::vector<std::vector<T> > matrix; ///<the matrix container
};

template<class T> Matrix<T>::Matrix(): matrix(0,std::vector<T>(0)) {
}

template<class T> Matrix<T>::Matrix(const int &n, const int &m): matrix(n,std::vector<T>(m)) {
}

template<class T> Matrix<T>::Matrix(const Matrix<T> &copy) {
	matrix=copy.getVecVec();
}

template<class T> Matrix<T>::Matrix(const std::vector<std::vector<T> > &copy): matrix(copy) {
}

template<class T> unsigned int Matrix<T>::size(int i) const {
 if (i == 0) return matrix.size();
 if (matrix.size())
   return matrix[0].size();
 return 0;
}

//tranpose the Object 
template<class T>
void Matrix<T>::transpose() {
  if (!matrix.size()) return;
  int m=matrix.size(),n=matrix[0].size();
  std::vector<std::vector<T> > vtmp(n,std::vector<T>(m)); 
  for (int i=0;i<n;i++){
   	for (int j=0;j<m;j++) {
   		vtmp[i][j]=matrix[j][i];
   	}
  }
  matrix=vtmp;
}


//matrix multiplication
template<class T>
Matrix<T> Matrix<T>::operator*(const Matrix<T> &rh) const {
  if (!matrix.size()) return Matrix(0,0);
  int m1=matrix.size(),n1=matrix[0].size();
  int m2=rh.size(0),n2=rh.size(1);
  if (n1 != m2) {
      std::cerr << "Error in matrix_multiply, dimension error! n1!=m2\n";
      std::cerr << "n1=" << n1 << " m2=" << m2 << std::endl;
    return Matrix(0,0);
  }
  Matrix<T>  vtmp(m1,n2);
  for (int i=0;i<m1;i++) {
    for (int k=0;k<n2;k++) {
      	vtmp[i][k]=0;
      for(int j=0;j<n1;j++){
	  	vtmp[i][k]+=matrix[i][j]*rh[j][k];
      }
    }
  }
  return vtmp;
}
//skalar matrix multiplication
template<class T>
Matrix<T> Matrix<T>::operator*(const T &rh) const {
  if (!matrix.size()) return;
  int m=matrix.size(),n=matrix[0].size();
  Matrix<T>  vtmp(m,n);
  for (int i=0;i<m;i++) {
    for (int k=0;k<n;k++) {
	  	vtmp[i][k]=rh*matrix[i][k];
    }
  }
  return vtmp;
}

//matrix addition
template<class T>
Matrix<T> Matrix<T>::operator+(const Matrix<T> &rh) const {
  if (!matrix.size()) return;
  int m1=matrix.size(),n1=matrix[0].size();
  int m2=rh.size(0),n2=rh.size(1);
  if (n1 != n2 || m1 != m2) {
      std::cerr << "Error in matrix addition, dimension error!\n";
      std::cerr << "n1=" << n1 << " m1=" << m1 << std::endl;
      std::cerr << "n2=" << n2 << " m2=" << m2 << std::endl;
      return Matrix<T>(0,0);
  }
  std::vector<std::vector<T> > vtmp(m1,std::vector<T>(n1,0.0));
  for (int i=0;i<m1;i++) {
    for (int k=0;k<n1;k++) {
      vtmp[i][k]=rh[i][k]+matrix[i][k];
    }
  }
  return vtmp;
}

template<class T>
Matrix<T> Matrix<T>::operator-(const Matrix<T> &rh) const {
	return *this+(rh*(-1));
}

template<class T>
std::vector<T> &Matrix<T>::operator[](int index) {
	return matrix[index];
}

template<class T>
const std::vector<T> &Matrix<T>::operator[](int index) const {
	return matrix[index];
}
/*
template<class T>
Matrix<T> operator*(const T &lh,const Matrix<T> &rh) {
  if (!matrix.size()) return;
  int m=rh.size(0),n=rh.size(1);
  std::vector<std::vector<T> > vtmp(rh.getVecVec());
  for (int i=0;i<m;i++) {
    for (int k=0;k<n;k++) {
		vtmp[i][k]=lh*vtmp[i][k];
    }
  }
  return vtmp;	
}
*/

template<class T>
void Matrix<T>::setzero() {
  for (unsigned int i=0;i<size(0);i++) {
    for (unsigned int k=0;k<size(1);k++) {
      matrix[i][k]=0;
    }
  }	
}

template<class T> class vector_compare {
 public:
    vector_compare(size_t _col) : col(_col) {}
    bool operator()(const std::vector<T> &a, const std::vector<T> &b) {
	return a[col]<b[col];
    }
 private:
    size_t col;
};

template<class T> void Matrix<T>::sort(size_t col) {
    std::sort(matrix.begin(), matrix.end(), vector_compare<T>(col));
}

#endif
