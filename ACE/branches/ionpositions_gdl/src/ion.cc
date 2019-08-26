#include "ion.h"

ion::ion(){
  name = "";
  mass = 0.;
  charge = 0.;
  peakhigh = 0.;
  tpos = 0.;
  epos = 0.;
  sigtp = 0.;
  sigtm = 0.;
  sigep = 0.;
  sigem = 0.;
  velocity = 0.;
}


ion::ion(const double &x){
  name = "";
  mass = x;
  charge = x;
  peakhigh = x;
  tpos = x;
  epos = x;
  sigtp = x;
  sigtm = x;
  sigep = x;
  sigem = x;
  velocity = x;
}

void ion::put_name(const string &x){
  name = x;
}
void ion::put_mass(const double &x){
  mass = x;
}
void ion::put_charge(const double &x){
  charge = x;
}
void ion::put_peakhigh(const double &x){
  peakhigh = x;
}
void ion::put_tpos(const double &x){
  tpos = x;
}
void ion::put_epos(const double &x){
  epos = x;
}
void ion::put_sigtp(const double &x){
  sigtp = x;
}
void ion::put_sigtm(const double &x){
  sigtm = x;
}
void ion::put_sigep(const double &x){
  sigep = x;
}
void ion::put_sigem(const double &x){
  sigem = x;
}
void ion::put_velocity(const double &x){
  velocity = x;
}

void ion::get_name(string &x){
  x = name;
}
void ion::get_mass(double &x){
  x = mass;
}
void ion::get_charge(double &x){
  x = charge;
}
void ion::get_peakhigh(double &x){
  x = peakhigh;
}
void ion::get_tpos(double &x){
  x = tpos;
}
void ion::get_epos(double &x){
  x = epos;
}
void ion::get_sigtp(double &x){
  x = sigtp;
}
void ion::get_sigtm(double &x){
  x = sigtm;
}
void ion::get_sigep(double &x){
  x = sigep;
}
void ion::get_sigem(double &x){
  x = sigem;
}
void ion::get_velocity(double &x){
  x = velocity;
}
