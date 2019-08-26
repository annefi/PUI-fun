/* AnalysisData.cc -- Code for AnalysisData and component objects
   Jim Raines, 4Apr2001
 */

#include "swindal.h"
extern "C" {
#include "libhef.h"
}

/* ---------------------------- */
/* AnalysisData Class Functions */
/* ---------------------------- */
AnalysisData::AnalysisData(void){
  int i,j;  // loop counters
  const string thisprog = "AnalysisData::AnalysisData";

  //initSwindal();

  int DbgLvl = gDbgLvl;      // Set local debug level to global level

  // variables for libhef
  int result;
  //  char acelv1file[150];
  char acelv1file[] = "/home/acedata/LV1/2000/2000158.nc";

  double PapsVolt;  // Post Acceleration Power Supply voltage in kV
  double *tmp;


  /* load values into ion objects -- read from file eventually
     ---------------------------------------------------------
  */
  // Hydrogen
  Ions["H+"]  = Ion("H+",1.0,1.0);

  // Helium
  Ions["He1+"] = Ion("He1+",4.0,1.0);
  Ions["He2+"] = Ion("He2+",4.0,2.0);
  Ions["3He2+"] = Ion("3He2+",3.0,2.0);

  // Carbon
  Ions["C4+"] = Ion("C4+",12.0,4.0);
  Ions["C5+"] = Ion("C5+",12.0,5.0);
  Ions["C6+"] = Ion("C6+",12.0,6.0);

  // Oxygen
  Ions["O5+"] = Ion("O5+",16.0,5.0);
  Ions["O6+"] = Ion("O6+",16.0,6.0);
  Ions["O7+"] = Ion("O7+",16.0,7.0);
  Ions["O8+"] = Ion("O8+",16.0,8.0);

  // Neon
  Ions["20Ne6+"] = Ion("20Ne6+",20.0,6.0);
  Ions["20Ne7+"] = Ion("20Ne7+",20.0,7.0);
  Ions["20Ne8+"] = Ion("20Ne8+",20.0,8.0);

  // Magnesium
  Ions["Mg6+"] = Ion("Mg6+",24.0,6.0);
  Ions["Mg7+"] = Ion("Mg7+",24.0,7.0);
  Ions["Mg8+"] = Ion("Mg8+",24.0,8.0);
  Ions["Mg9+"] = Ion("Mg9+",24.0,9.0);
  Ions["Mg10+"] = Ion("Mg10+",24.0,10.0);

  // Silicon
  Ions["Si7+"] = Ion("Si7+",28.0,7.0);
  Ions["Si8+"] = Ion("Si8+",28.0,8.0);
  Ions["Si9+"] = Ion("Si9+",28.0,9.0);
  Ions["Si10+"] = Ion("Si10+",28.0,10.0);
  Ions["Si11+"] = Ion("Si11+",28.0,11.0);
  Ions["Si12+"] = Ion("Si12+",28.0,12.0);

 // Sulfur
  Ions["S8+"] = Ion("S8+",32.0,8.0);
  Ions["S9+"] = Ion("S9+",32.0,9.0);
  Ions["S10+"] = Ion("S10+",32.0,10.0);
  Ions["S11+"] = Ion("S11+",32.0,11.0);

  // Iron
  Ions["Fe6+"] = Ion("Fe6+",56.0,6.0);
  Ions["Fe7+"] = Ion("Fe7+",56.0,7.0);
  Ions["Fe8+"] = Ion("Fe8+",56.0,8.0);
  Ions["Fe9+"] = Ion("Fe9+",56.0,9.0);
  Ions["Fe10+"] = Ion("Fe10+",56.0,10.0);
  Ions["Fe11+"] = Ion("Fe11+",56.0,11.0);
  Ions["Fe12+"] = Ion("Fe12+",56.0,12.0);
  Ions["Fe13+"] = Ion("Fe13+",56.0,13.0);
  Ions["Fe14+"] = Ion("Fe14+",56.0,14.0);
  Ions["Fe15+"] = Ion("Fe15+",56.0,16.0);
  Ions["Fe17+"] = Ion("Fe17+",56.0,17.0);

  
  /* Groups of ions */
  /* -------------- */
  vector<Ion> group0;
  group0.push_back(Ions["3He2+"]);
  group0.push_back(Ions["He2+"]);
  group0.push_back(Ions["C4+"]);
  group0.push_back(Ions["N5+"]);
  group0.push_back(Ions["O5+"]);
  group0.push_back(Ions["Ne6+"]);
  group0.push_back(Ions["Mg6+"]);
  group0.push_back(Ions["Si7+"]);
  group0.push_back(Ions["S8+"]);
  group0.push_back(Ions["Fe6+"]);

  vector<Ion> group1;
  group1.push_back(Ions["3He2+"]);
  group1.push_back(Ions["He2+"]);
  group1.push_back(Ions["C6+"]);
  group1.push_back(Ions["N6+"]);
  group1.push_back(Ions["O8+"]);
  group1.push_back(Ions["Ne8+"]);
  group1.push_back(Ions["Mg10+"]);
  group1.push_back(Ions["Si12+"]);
  group1.push_back(Ions["S11+"]);
  group1.push_back(Ions["Fe16+"]);

  /* ----------------------------------------- */
  /* load default E/q table -- get from libhef */
  /* ----------------------------------------- */

  /* Open ACE file, get cycle and expand */
  /* ----------------------------------- */

  // ace data filename, temporarily hardcoded
  // note: using intermediate char array for easy passing to libhef
  //gCurLv1File = "/home/acedata/LV1/2000/2000158.nc";

  //sprintf(acelv1file, "%s\0", gCurLv1File.c_str());
  //strcpy(acelv1file, gCurLv1File.c_str());
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
  if (DbgLvl > 3) printf("%s -D- PAPS = %f kV\n",thisprog.c_str(),PapsVolt);
  
  /* actually store E/q table into Eqtab vector */
  /* ------------------------------------------ */
  for (i = 2; i < 60; i++){ /* skip one b/c of ramp up */
    Eqtab.push_back(a3gxeqdpu_i(i - 1));

  }

  a3closecyclefile();

  /* ------------------------------------------------------- */
  /* Run forward model for each ion species at each E/q step */
  /* ------------------------------------------------------- */

  map<string,Ion>::iterator Ions_iter;
  for(Ions_iter = Ions.begin(); Ions_iter != Ions.end(); Ions_iter++){
    for (j = 1; j < 60; j++){ /* skip one b/c of ramp up */    
      tmp = xfm(Eqtab[j],
		PapsVolt,
		Ions_iter->second.mass,
		Ions_iter->second.charge);
      if (DbgLvl > 3) {
	printf("%s -D- xfm returned %f %f %f %f\n",thisprog.c_str(),
	       tmp[0], tmp[1], tmp[2], tmp[3]);
      }

      Ions_iter->second.tof.push_back(tmp[0]);
      Ions_iter->second.stof.push_back(tmp[1]);
      Ions_iter->second.esd.push_back(tmp[2]);
      Ions_iter->second.sesd.push_back(tmp[3]);
       
    }
  }

}
