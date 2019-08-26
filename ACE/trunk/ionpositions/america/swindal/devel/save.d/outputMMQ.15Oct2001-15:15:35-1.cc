/*
  File: outputMMQ.cc

  Description: 

    Output swindal MMQ matrices to a set of files.  NOTE: This is not
    really part of the swindal library, just stuck in here for now.

  Author: Jim Raines, Sep2001

  Method:
    
  Major Modification History:
    Split out from outputMats, JR, 9Oct2001

*/


#include "swindal.h"

int outputMMQ(string bname, MeasurementArray *MA, 
	       long int StartYdoy, long int StopYdoy, 
	       const AnalysisData& ad) {
  /* Description: Output several tof-esd and mmq matrices to files. */

  string thisprog = "outputMMQ";

  ofstream fout;
  fout.precision(3);
  char outfile[20];

  TNT::Matrix<float> a(MAXTOFCH,MAXESDCH, 0.0);
  TNT::Matrix<float> sum(MAXTOFCH,MAXESDCH, 0.0);

  /* --- write mmq matrices to file ---
     ----------------------------------
  */
  TNT::Matrix<float> mmq(NQCH,NMCH, 0.0);
  TNT::Matrix<float> mmqsum(NQCH,NMCH, 0.0);
  TNT::Matrix<float> zero(NQCH,NMCH, 0.0);

  // -- whole thing -- using matrices
  sprintf(outfile, "%s_mmq.dat",bname.c_str());
  fout.open(outfile);

  fout << "ACE/SWICS m-m/q in counts/second for day(s) " << StartYdoy <<
    " - " << StopYdoy << endl;
  fout << "mass/charge mass" << endl;
  fout << "1 " << NQCH << " 1 " << NMCH << endl;
  
  mmqsum = 0.0;
  for(int nedb = FIRSTEDB; nedb < MAXEDB ; nedb++){
    a = MA->getSlice(nedb);
    mmq = MA->EtSlice2Mmq(a,nedb,ad);
    mmqsum = mmqsum + mmq;
  }

  fout << mmqsum;
  fout.close();

  // -- edb slices
  if (0) {
    int slices[] = {18, 24, 30, 36, 41, 42, 48};
    for (int i = 0; i < 6; i++){
      sprintf(outfile, "%s_mmq_sl%02d.dat",bname.c_str(),slices[i]);
      fout.open(outfile);

      fout << "ACE/SWICS m-m/q in counts/second for day(s) " << StartYdoy <<
	" - " << StopYdoy << endl;
      fout << "mass/charge mass" << endl;
      fout << "1 " << NMCH << " 1 " << NQCH << endl;
 
      a = MA->getSlice(slices[i]);
      mmq = MA->EtSlice2Mmq(a,slices[i],ad);

      fout.close();
    }
  } // block for writing slices to files

  return (0);
}
