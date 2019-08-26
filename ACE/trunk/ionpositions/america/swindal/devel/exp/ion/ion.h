/* ion.h -- definition of ion class
   Jim Raines, 28Mar2001
 */

class Ion {
 public:
  char name[4];            // name of ion, includes charge (e.g. He2+)
  float mass;              // mass (in amu) of ion
  float charge;            // charge (in units of elem. charge) of ion

  void print(void);            // print Ion
  Ion(const char i_name[], float i_mass, float i_charge); // Constructor
  bool operator== (const Ion& right) const;  // define equality operator

 private:
};
  
