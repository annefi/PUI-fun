/*
  File: AnalysisData.cc

  Description:
    Containers and data for data analysis without regard to specific
    (SWICS-style) instrument.

  Author: Jim Raines (jmr) 

  Method:
    
  Revision controlled by CVS:
  $Id: AnalysisData.cc,v 1.17 2005/06/09 04:06:12 jraines Exp $
  
  Major Modification History:
    04Apr2001   jmr   Initial coding
    10Oct2003   jmr   Inserted duty cycle code.

*/

#include "swindal.h"

/* ---------------------------- */
/* AnalysisData Class Functions */
/* ---------------------------- */
AnalysisData::AnalysisData(void){
  Eqtab.reserve(MAXEDB);
  Eqtab.assign(MAXEDB, 0.0); // init to 0.0;
  
  CycleTime = -1.0;
  Doyfr = -1.0;
  
}

int AnalysisData::init(void){
  const string thisprog = "AnalysisData::init";
  int DbgLvl = gDbgLvl;      // Set local debug level to global level

  /* --------------------------------------------------------------
     Define Physical Constants -- See AnalysisData.h for more info.
     --------------------------------------------------------------
  */
  //  EqAcceptFac = 0.043;   // dimensionless, from swindal.h ref. 1
  EqAcceptFac = 0.064;   // dimensionless, from ACE paper
  GeomFactor  = 0.0185;  // cm^2, from swindal.h ref. 1

  /* load values into ion objects -- read from file eventually
     ---------------------------------------------------------
  */
  
  return(0);
}

int AnalysisData::getIonIndex(string ion){
  static bool FirstTime = true;

  // generate table on first run only
  if (FirstTime){
    for(int s = 0; s < Ions.size(); s++){
      IonsByName[Ions[s].name] = Ions[s];
      IonsIndex[Ions[s].name] = s;
    }
  }

  return(IonsIndex[ion]);
}

Ion AnalysisData::getIon(string ion){
  static bool FirstTime = true;

  // generate table on first run only
  if (FirstTime){
    for(int s = 0; s < Ions.size(); s++){
      IonsByName[Ions[s].name] = Ions[s];
    }
  }

  return(IonsByName[ion]);
}

int AnalysisData::loadInstParam(const AceSwicsData& swxdata){
  const string thisprog = "AnalysisData::loadInstParam";

  // load E/q table
  for (int nedb = FIRSTEDB; nedb < MAXEDB; nedb++){
    Eqtab[nedb] = swxdata.getEqtab(nedb);
  }

  // load cycle time from first PHA of this current group
  // note: the following two lines stopped working once the swxdata copying was 
  //       put into axlv2.cc
  //Pha lpha = swxdata.getPha(0);
  // CycleTime = lpha.scet;
  CycleTime = swxdata.getCycleTime();
  Doyfr = swxdata.ss1970_to_doyfr(CycleTime);

  return(0);
}

void AnalysisData::loadIon(string name, string element, 
			   float mass, float charge){
  Ions.push_back(Ion(name, element, mass, charge));
  return;
}

void AnalysisData::outputFM(){
  const string thisprog = "AnalysisData::outputFM";
  string namew="fmout.dat";
  char line[150];
  std::ofstream file(namew.c_str());
  for (int nedb = FIRSTEDB; nedb < MAXEDB; nedb++){
    sprintf(line,"step : %i   numberions : 21\n",nedb-1);
    file << line;
    sprintf(line,"name   tof   ech   stof sech\n",nedb);
    file << line;
    for (int nion =0; nion < Ions.size(); nion++){
      printf("%s -D- step %i %s %f %f %f %f\n",thisprog.c_str(),nedb-1,
	     Ions[nion].name.c_str(), 
	     Ions[nion].tof[nedb], Ions[nion].stof[nedb],Ions[nion].esd[nedb],Ions[nion].sesd[nedb]);
      if (nion==0 || nion==1 || nion==2 ||nion==3 || nion==4 || nion==8 || nion==9 || nion==10 || nion==15 ||nion==16 || nion==17 || nion==23|| nion==24 || nion==25 ||nion==27 || nion==29 || nion==30||nion==31 || nion==32 || nion==33){
	sprintf(line,"%s   %f   %f   %f   %f\n",
		Ions[nion].name.c_str(), 
		Ions[nion].tof[nedb],Ions[nion].esd[nedb],Ions[nion].stof[nedb],Ions[nion].sesd[nedb]);
	file << line;
      }
    }
  }
}

int AnalysisData::loadFM(const AceSwicsData& swxdata){
  return(loadFM(swxdata, swxdata.getPav()));
}


int AnalysisData::loadFM(const AceSwicsData& swxdata, double pav){
  const string thisprog = "AnalysisData::loadFM";

  int DbgLvl = gDbgLvl;      // Set local debug level to global level

  // actually set the voltage that will be used in FM and rest of sw.
  PapsVolt = pav;

  /* ------------------------------------------------------- */
  /* Run forward model for each ion species at each E/q step */
  /* ------------------------------------------------------- */
  double *xfm;
  for (int nion = 0; nion < Ions.size(); nion++){
    for (int nedb = FIRSTEDB; nedb < MAXEDB; nedb++){
      xfm = swxdata.getFM(Eqtab[nedb],
		PapsVolt,
		Ions[nion].mass,
		Ions[nion].charge);

      if (DbgLvl >= 3) {
	printf("%s -D- xfm returned %s %f %f %f %f\n",thisprog.c_str(),
	       Ions[nion].name.c_str(), 
	       xfm[0], xfm[1], xfm[2], xfm[3]);
      }

      Ions[nion].tof[nedb]  = xfm[0];
      Ions[nion].stof[nedb] = xfm[1];
      Ions[nion].esd[nedb]  = xfm[2];
      Ions[nion].sesd[nedb] = xfm[3];
       
    }
  }

  return(0);
}

/* ---- experimental FM ---- */
int AnalysisData::loadFMexp(const AceSwicsData& swxdata){
  return(loadFMexp(swxdata, swxdata.getPav()));
}

int AnalysisData::loadFMexp(const AceSwicsData& swxdata, double pav){
  const string thisprog = "AnalysisData::loadFMexp";

  int DbgLvl = gDbgLvl;      // Set local debug level to global level

  // actually set the voltage that will be used in FM and rest of sw.
  PapsVolt = pav;

  /* ------------------------------------------------------- */
  /* Run forward model for each ion species at each E/q step */
  /* ------------------------------------------------------- */
  double *xfm;
  for (int nion = 0; nion < Ions.size(); nion++){
    for (int nedb = FIRSTEDB; nedb < MAXEDB; nedb++){
      xfm = xfmexp(Eqtab[nedb],
		PapsVolt,
		Ions[nion].mass,
		Ions[nion].charge);

      if (DbgLvl > 3) {
	printf("%s -D- xfm returned %s %f %f %f %f\n",thisprog.c_str(),
	       Ions[nion].name.c_str(), 
	       xfm[0], xfm[1], xfm[2], xfm[3]);
      }

      Ions[nion].tof[nedb]  = xfm[0];
      Ions[nion].stof[nedb] = xfm[1];
      Ions[nion].esd[nedb]  = xfm[2];
      Ions[nion].sesd[nedb] = xfm[3];
       
    }
  }

  return(0);
}

void AnalysisData::print(void){
  string thisprog = "AnalysisData::print";
  
  cout << thisprog << " -I- AnalysisData object contains:\n";
  
  cout << "+ Ion list (Ions member):\n";
  for(int nion = 0; nion < Ions.size(); nion++){
    cout << "Ions[" << nion << "] := ";
    Ions[nion].print();
    cout << "\n";
  }
}

void AnalysisData::dump(void){
  string thisprog = "AnalysisData::dump";
  
  cout << thisprog << " -I- AnalysisData object contains:\n";
  
  cout << "+ Ion list (Ions member):\n";
  for(int nion = 0; nion < Ions.size(); nion++){
    cout << "Ions[" << nion << "] := ";
    Ions[nion].dump();
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

// output forward model parameters for overlay on E-T slices by IDL code
void AnalysisData::outputFM(string outfile){
  FILE *FMCF; // Forward Model Comparison File (pointer)
  FMCF = fopen(outfile.c_str(), "w+");

  // keep fields the same total width!
  char hdrfmt[] ="# %3s %6s %6s %6s %6s %6s %6s\n";
  char datafmt[]=
  "  %3d %6.2f %6s %6.2f %6.2f %6.2f %6.2f \n";

  // --- print file header ---
  fprintf(FMCF,"# Forward Model parameters from ACE Level II data processor (v2.0)\n");

  // get and format calendar time for header
  time_t now;
  char timestr[19];
  time(&now);
  strftime(timestr, 19, "%d%b%Y %H:%M:%S", localtime(&now));
  fprintf(FMCF,"# Created: %s\n", timestr);

  // print column headings
  fprintf(FMCF,hdrfmt,"EDB","E/q","ion","tof","tofsig","esd","esdsig");

  // --- write output line for each EDB for each species ---
  for (int nedb = FIRSTEDB; nedb < MAXEDB; nedb++){
    for (int s = 0; s < Ions.size(); s++){
      fprintf(FMCF, datafmt, nedb, Eqtab[nedb],Ions[s].name.c_str(),
	      Ions[s].tof[nedb],Ions[s].stof[nedb],
	      Ions[s].esd[nedb],Ions[s].sesd[nedb]);
    }
  }

  fclose(FMCF);
}
