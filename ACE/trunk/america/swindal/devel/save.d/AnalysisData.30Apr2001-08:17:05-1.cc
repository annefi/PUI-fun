/* AnalysisData.cc -- Code for AnalysisData and component objects
   Jim Raines, 4Apr2001
 */

#include "swindal.h"
extern "C" {
#include "/home/jraines/ace/libhef/include/libhef.h"
}

/* ------------------- */
/* Ion Class Functions */
/* ------------------- */
// Prints values
void Ion::print(void){
  cout << "name=" << name << " mass=" << mass << " charge=" << charge << "\n";
  //printf ("name=%4s mass=%6.2f charge=%6.2f",name,mass,charge);
}

// Constructor -- initialized values
Ion::Ion(const string i_name, float i_mass, float i_charge){
  name = i_name;
  mass = i_mass;
  charge = i_charge;
}

// Equality operator for Ion class
bool Ion::operator== (const Ion &right) const {
  return( name == right.name);
}

// Load SWICS Forward Model ouput
//void Ion::lxfm(double esd, double tof, double sesd, double stof){
//}

/* ---------------------------- */
/* AnalysisData Class Functions */
/* ---------------------------- */
AnalysisData::AnalysisData(void){
  int i,j;  // loop counters
  const string thisprog = "AnalysisData::AnalysisData";

  int result;

  double PapsVolt;  // Post Acceleration Power Supply voltage in kV
  double *tmp;

  /* load values into ion objects -- read from file eventually */
  // Hydrogen
  Ions.push_back(Ion("H+",1.0,1.0));

  // Helium
  Ions.push_back(Ion("He1+",4.0,1.0));
  Ions.push_back(Ion("He2+",4.0,2.0));
  Ions.push_back(Ion("3He2+",3.0,2.0));

  // Carbon
  Ions.push_back(Ion("C4+",12.0,4.0));
  Ions.push_back(Ion("C5+",12.0,5.0));
  Ions.push_back(Ion("C6+",12.0,6.0));

  // Oxygen
  Ions.push_back(Ion("O5+",16.0,5.0));
  Ions.push_back(Ion("O6+",16.0,6.0));
  Ions.push_back(Ion("O7+",16.0,7.0));
  Ions.push_back(Ion("O8+",16.0,8.0));

  // Neon
  Ions.push_back(Ion("20Ne6+",20.0,6.0));
  Ions.push_back(Ion("20Ne7+",20.0,7.0));
  Ions.push_back(Ion("20Ne8+",20.0,8.0));

  // Magnesium
  Ions.push_back(Ion("Mg6+", 24.0,6.0));
  Ions.push_back(Ion("Mg7+", 24.0,7.0));
  Ions.push_back(Ion("Mg8+", 24.0,8.0));
  Ions.push_back(Ion("Mg9+", 24.0,9.0));
  Ions.push_back(Ion("Mg10+", 24.0,10.0));

  // Silicon
  Ions.push_back(Ion("Si7+",28.0,7.0));
  Ions.push_back(Ion("Si8+",28.0,8.0));
  Ions.push_back(Ion("Si9+",28.0,9.0));
  Ions.push_back(Ion("Si10+",28.0,10.0));
  Ions.push_back(Ion("Si11+",28.0,11.0));
  Ions.push_back(Ion("Si12+",28.0,12.0));

  // Sulfur
  Ions.push_back(Ion("S8+",32.0,8.0));
  Ions.push_back(Ion("S9+",32.0,9.0));
  Ions.push_back(Ion("S10+",32.0,10.0));
  Ions.push_back(Ion("S11+",32.0,11.0));

  // Iron
  Ions.push_back(Ion("Fe6+",56.0, 6.0));
  Ions.push_back(Ion("Fe7+",56.0, 7.0));
  Ions.push_back(Ion("Fe8+",56.0, 8.0));
  Ions.push_back(Ion("Fe9+",56.0, 9.0));
  Ions.push_back(Ion("Fe10+",56.0, 10.0));
  Ions.push_back(Ion("Fe11+",56.0, 11.0));
  Ions.push_back(Ion("Fe12+",56.0, 12.0));
  Ions.push_back(Ion("Fe13+",56.0, 13.0));
  Ions.push_back(Ion("Fe14+",56.0, 14.0));
  Ions.push_back(Ion("Fe15+",56.0, 16.0));
  Ions.push_back(Ion("Fe17+",56.0, 17.0));
  
  /* Groups of ions */
  /* -------------- */
  

  /* ----------------------------------------- */
  /* load default E/q table -- get from libhef */
  /* ----------------------------------------- */

  /* Open ACE file, get cycle and expand */
  /* ----------------------------------- */

  // ace data filename, temporarily hardcoded
  // note: using char array for easy passing to libhef
  char acelv1file[] = "/home/acedata/LV1/2000/2000158.nc";

  result = a3opencyclefile(acelv1file);

  result = a3readcycle();
  if (result > 0){
    printf("%s -E- a3readcycle returned %d\n",thisprog.c_str(), result);
  }
  else{
    result = a3expand();
    if (result > 0)
      printf("%s -E- a3readcycle returned %d\n",thisprog.c_str(), result);
  }
 
  /* set level of output messages from libhef */
  result = perr_setlevel(1);
 
  /* get PAPS voltage */
  PapsVolt = a3gxpavdpu();
  printf("%s -D- PAPS = %f kV\n",thisprog.c_str(),PapsVolt);
  
  /* actually store E/q table into Eqtab vector */
  /* ------------------------------------------ */
  for (i = 1; i < 60; i++){ /* skip one b/c of ramp up */
    Eqtab.push_back(a3gxeqdpu_i(i - 1));

  }

  a3closecyclefile();

  /* ------------------------------------------------------- */
  /* Run forward model for each ion species at each E/q step */
  /* ------------------------------------------------------- */

  for(i = 0; i < Ions.size(); i++){
    for (j = 1; j < 60; j++){ /* skip one b/c of ramp up */    
      tmp = xfm(Eqtab[j],PapsVolt,Ions[i].mass,Ions[i].charge);
      printf("%s -D- xfm returned %f %f %f %f\n",thisprog.c_str(),
	   tmp[0], tmp[1], tmp[2], tmp[3]);

      Ions[i].tof.push_back(tmp[0]);
      Ions[i].stof.push_back(tmp[1]);
      Ions[i].esd.push_back(tmp[2]);
      Ions[i].sesd.push_back(tmp[3]);
       
    }
  }

}
