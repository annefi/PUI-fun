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
  int tpos;
  int epos;
  int sigtp;
  int sigtm;
  int sigep;
  int sigem;
  double velocity;

 public :
  ion(); // Constructor
  ion(const int &x); // Initialize ion to x

  // write to ion
  void put_name(const string &x);
  void put_mass(const double &x);
  void put_charge(const double &x);
  void put_peakhigh(const double &x);
  void put_tpos(const int &x);  
  void put_epos(const int &x);
  void put_sigtp(const int &x);
  void put_sigtm(const int &x);
  void put_sigep(const int &x);
  void put_sigem(const int &x);
  void put_velocity(const double &x);

  // read from ion
  void get_name(string &x);
  void get_mass(double &x);
  void get_charge(double &x);
  void get_peakhigh(double &x);
  void get_tpos(int &x);
  void get_epos(int &x);
  void get_sigtp(int &x);
  void get_sigtm(int &x);
  void get_sigep(int &x);
  void get_sigem(int &x);
  void get_velocity(double &x);

};
   
#endif
  
  
