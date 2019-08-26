#ifndef LIBETPH_MATRIXIO_HH
#define LIBETPH_MATRIXIO_HH
//-----------------------------------------------------------------------------
#include "matrix.hh"

template<class T> std::ostream& operator<<(std::ostream &os, std::vector<T> v) {
    for (size_t i=0; i < v.size(); i++)
	os << v[i] << std::endl;
    return os;
}

template<class T> std::ostream& operator<<(std::ostream &os, Matrix<T> m) {
    os << '[' << std::endl;
    for (size_t i=0; i < m.size(0); i++) {
	os << (m[i]) << std::endl;
    }
    os << ']' << std::endl;
    return os;
}
//-----------------------------------------------------------------------------
#endif
