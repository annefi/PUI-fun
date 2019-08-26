#ifndef RAN_URAND_H
#define RAN_URAND_H

#include <cstdlib>
#include <iostream>
#include <vector>
#include "dbgvector.hh"

//! ran_urand fills the vector ran with a mix of pseudo and real random numbers created by /dev/urandom!
void ran_urand(std::vector<double> &ran);

#endif
