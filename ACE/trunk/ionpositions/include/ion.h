#ifndef ION_H
#define ION_H

#include <string>
using namespace std;
class ion{
 private :
  string name;
  double mass;
  double charge;
  double peakhigh;
  double tpos;
  double epos;
  double sigtp;
  double sigtm;
  double sigep;
  double sigem;
  double velocity;

 public :
  ion(); // Constructor
  ion(const double &x); // Initialize ion to x

  // write to ion
  void put_name(const string &x);
  void put_mass(const double &x);
  void put_charge(const double &x);
  void put_peakhigh(const double &x);
  void put_tpos(const double &x);  
  void put_epos(const double &x);
  void put_sigtp(const double &x);
  void put_sigtm(const double &x);
  void put_sigep(const double &x);
  void put_sigem(const double &x);
  void put_velocity(const double &x);

  // read from ion
  void get_name(string &x);
  void get_mass(double &x);
  void get_charge(double &x);
  void get_peakhigh(double &x);
  void get_tpos(double &x);
  void get_epos(double &x);
  void get_sigtp(double &x);
  void get_sigtm(double &x);
  void get_sigep(double &x);
  void get_sigem(double &x);
  void get_velocity(double &x);

};
   
#endif
  
  
