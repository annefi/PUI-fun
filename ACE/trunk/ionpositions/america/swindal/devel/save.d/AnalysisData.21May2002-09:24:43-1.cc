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
  //DbgLvl = 4;
  if (DbgLvl != gDbgLvl) {
    cout << thisprog << " -I- local debugging level is " << DbgLvl 
	 <<", differs from global (" << gDbgLvl << ")." << endl;
  }

  // variables for libhef
  int result;

  double *tmp;

  /* --------------------------------------------------------------
     Define Physical Constants -- See AnalysisData.h for more info.
     --------------------------------------------------------------
  */
  EqAcceptFac = 0.043;   // dimensionless, from swindal.h ref. 1
  GeomFactor  = 0.0185;  // cm^2, from swindal.h ref. 1

  /* load values into ion objects -- read from file eventually
     ---------------------------------------------------------
  */
  // Hydrogen
  //  Ions.push_back(Ion("H+",1.0,1.0));
  
  // Helium
  //Ions.push_back(Ion("He1+",4.0,1.0));  not in range 1
  //Ions.push_back(Ion("He2+",4.0,2.0));  not in range 1
//   Ions.push_back(Ion("3He2+",3.0,2.0));

  // Carbon
  Ions.push_back(Ion("C4+",12.0,4.0));
  Ions.push_back(Ion("C5+",12.0,5.0));
  Ions.push_back(Ion("C6+",12.0,6.0));

  // Nitrogen
  Ions.push_back(Ion("N5+",14.0,5.0));
  Ions.push_back(Ion("N6+",14.0,6.0));

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
//   Ions.push_back(Ion("Mg6+",24.0,6.0));
//   Ions.push_back(Ion("Mg7+",24.0,7.0));
//   Ions.push_back(Ion("Mg8+",24.0,8.0));
//   Ions.push_back(Ion("Mg9+",24.0,9.0));
//   Ions.push_back(Ion("Mg10+",24.0,10.0));

  // Silicon
  Ions.push_back(Ion("Si7+",28.0,7.0));
  Ions.push_back(Ion("Si8+",28.0,8.0));
  Ions.push_back(Ion("Si9+",28.0,9.0));
  Ions.push_back(Ion("Si10+",28.0,10.0));
  Ions.push_back(Ion("Si11+",28.0,11.0));
  Ions.push_back(Ion("Si12+",28.0,12.0));

  // Sulfur
//   Ions.push_back(Ion("S8+",32.0,8.0));
//   Ions.push_back(Ion("S9+",32.0,9.0));
//   Ions.push_back(Ion("S10+",32.0,10.0));
//   Ions.push_back(Ion("S11+",32.0,11.0));

  // Iron
  Ions.push_back(Ion("Fe6+",56.0,6.0));
  Ions.push_back(Ion("Fe7+",56.0,7.0));
  Ions.push_back(Ion("Fe8+",56.0,8.0));
  Ions.push_back(Ion("Fe9+",56.0,9.0));
  Ions.push_back(Ion("Fe10+",56.0,10.0));
  Ions.push_back(Ion("Fe11+",56.0,11.0));
  Ions.push_back(Ion("Fe12+",56.0,12.0));
  Ions.push_back(Ion("Fe13+",56.0,13.0));
  Ions.push_back(Ion("Fe14+",56.0,14.0));
  Ions.push_back(Ion("Fe15+",56.0,15.0));
  Ions.push_back(Ion("Fe16+",56.0,16.0));
  
  /* Ions by name and index */
  /* ---------------------- */
  for(int nion = 0; nion < Ions.size(); nion++){
    IonsByName[Ions[nion].name] = Ions[nion];
//     cout << thisprog << " -D- IonsByName[" << Ions[nion].name
// 	 << "] contains: ";
//     IonsByName[Ions[nion].name].print();
//    cout << endl;
    IonsIndex[Ions[nion].name] = nion;

  }

  /* ----------------------------------------- */
  /* load default E/q table -- get from libhef */
  /* ----------------------------------------- */

  /* Open ACE file, get cycle and expand */
  /* ----------------------------------- */

  /* -- ace data filename -- */
  /* Note: using intermediate char array (acelv1file) for easy passing
     to libhef because

     result = a3opencyclefile(gCurLv1File.c_str());

     does not work.
  */
  char acelv1file[150];
  gCurLv1File = "/home/acedata/LV1/2000/2000158.nc";
  strcpy(acelv1file, gCurLv1File.c_str());
  cout << thisprog << " -I- " 
       << "reading forward model input parameters from " 
       << gCurLv1File << " (hardcoded here)" << endl;

  result = a3opencyclefile(acelv1file);
  if (result > 0){
    printf("%s -F- a3opencyclefile returned %d\n",thisprog.c_str(), result);
    return;
  }

  result = a3readcycle();
  if (result > 0){
    printf("%s -E- a3readcycle returned %d\n",thisprog.c_str(), result);
    return;
  }
  else{
    result = a3expand();
    if (result > 0)
      printf("%s -E- a3readcycle returned %d\n",thisprog.c_str(), result);
  }
 
  /* set level of output messages from libhef */
  result = perr_setlevel(2);
 
  /* get PAPS voltage */
  /* Note: This is done in a round-about way because a3gxpavdpu seems
     to report the wrong value.  The post-accel. level is retrieved
     using a3xpavlev.  Then it is converted to kV using a hardcoded
     look-up table, derived from the voltage recorded in the command log and
     the level as read from the data file for that day.

     Right now, three methods are being compared.
  */
  // method 1:  from command log and survey of pavlev
  map<int,float> pavlev2kv;
  pavlev2kv[127] = 22.8;
  pavlev2kv[171] = 26.1;
  printf("%s -D- commanded PAPS = %f kV\n",thisprog.c_str(),
	 pavlev2kv[a3xpavlev()]);

  // method 2:  libhef::a3gxpavdpu
  printf("%s -D- a3gxpavdpu PAPS = %f kV\n", thisprog.c_str(),a3gxpavdpu());

  // method 3:  applying FOT-provided (and PDB) constant to pavlev
  printf("%s -D- .15*a3xpavlev() PAPS = %f kV\n",thisprog.c_str(),
	 a3xpavlev()*.15);

  if (PapsVolt == 0.0) {
    cout << thisprog << " -F- post-accel. voltage out of range (" 
	 << PapsVolt << ").  No foward model values calculated." << endl;
    return;
  }

  PapsVolt = a3xpavlev()*.15;
  // was DbgLvl > 3
  if (1) printf("%s -D- PAPS = %f kV\n",thisprog.c_str(),PapsVolt);

  /* actually store E/q table into Eqtab vector */
  /* ------------------------------------------ */
  Eqtab.reserve(MAXEDB);
  Eqtab.assign(MAXEDB, 0.0); // init to 0.0;
  for (i = FIRSTEDB; i < MAXEDB; i++){ /* skip one b/c of ramp up */
    Eqtab[i] = a3gxeqdpu_i(i - 1);
  }

  a3closecyclefile();

  /* ------------------------------------------------------- */
  /* Run forward model for each ion species at each E/q step */
  /* ------------------------------------------------------- */

  string name;
  for (int nion = 0; nion < Ions.size(); nion++){

    for (j = FIRSTEDB; j < MAXEDB; j++){ /* skip one b/c of ramp up */    
      tmp = xfm(Eqtab[j],
		PapsVolt,
		Ions[nion].mass,
		Ions[nion].charge);
      if (DbgLvl > 3) {
	printf("%s -D- xfm returned %s %f %f %f %f\n",thisprog.c_str(),
	       Ions[nion].name.c_str(), 
	       tmp[0], tmp[1], tmp[2], tmp[3]);
      }

      Ions[nion].tof[j] = tmp[0];
      Ions[nion].stof[j] = (2.0/2.0)*tmp[1];  // on Nathan's suspicion
      Ions[nion].esd[j] = tmp[2];
      Ions[nion].sesd[j] = (2.0/2.0)*tmp[3];  // on Nathan's suspicion
       
    }

  }

}

void AnalysisData::dump(void){
  string thisprog = "AnalysisData::dump";
  
  cout << thisprog << " -I- AnalysisData object contains:\n";
  
  cout << "+ Ion list (Ions member):\n";
  for(int nion = 0; nion < Ions.size(); nion++){
    cout << "Ions[" << nion << "] := ";
    Ions[nion].print();
    cout << "\n";
  }

  // SAVE for example of iteration through map
  //  map<string,Ion>::iterator Ibn_iter;

  //  for(Ibn_iter = IonsByName.begin(); Ibn_iter != IonsByName.end(); Ibn_iter++){
  //     Ibn_iter->second.print();
  //     cout << "\n";
  //   }
  
  cout << "\n+ E/q table (Eqtab member):\n";
  for(int i = 0; i < Eqtab.size(); i++){
    printf("Eqtab[%d]=%f\n",i,Eqtab[i]);
  }

}
