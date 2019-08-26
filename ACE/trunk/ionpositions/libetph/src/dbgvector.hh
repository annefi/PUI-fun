#ifndef DBGVECTOR_H
#define DBGVECTOR_H

#include <iostream>
#include <vector>

template <class T> class dbgvector : public std::vector<T> {
public:
    dbgvector<T>();
    dbgvector<T>(const int &n);
    dbgvector<T>(const int &n,const T &m);
    T &operator[](int index);
private:
    //vector<T> dbgvec;
};



template<class T> dbgvector<T>::dbgvector()
    : std::vector<T>(0) {
}

template<class T> dbgvector<T>::dbgvector(const int &n)
    : std::vector<T>(n) {}

template<class T> dbgvector<T>::dbgvector(const int &n, const T &m)
    : std::vector<T>(n, m) {}


template<class T> T &dbgvector<T>::operator[](int index) {
    if (index>int((std::vector<T>::size()-1))){
	std::cout << "Index Overflow : " << index << " > " << std::vector<T>::size()-1 << std::endl;
    }
    if (index<0){
	std::cout << "Index Underflow : " << index << " < " << std::vector<T>::size()-1 << std::endl;
    }
    return std::vector<T>::operator[](index);
}

#endif
// Local Variables:
// mode:C++
// End:
