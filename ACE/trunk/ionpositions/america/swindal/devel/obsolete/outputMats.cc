/*
  File: outputMats.cc

  Description: 

    Output swindal MA and MMQ matrices to a set of files.  NOTE: This
    is not really part of the swindal library, just stuck in here for
    now.

  Author: Jim Raines, Sep2001

  Method:
    
  Major Modification History:
    

*/


#include "swindal.h"

int outputMats(string bname, MeasurementArray *MA, 
	       long int StartYdoy, long int StopYdoy, 
	       const AnalysisData& ad) {
  /* Description: Output several tof-esd and mmq matrices to files. */

  int i;
  string thisprog = "outputMats";

  ofstream fout;
  fout.precision(3);
  string outfile;

  TNT::Matrix<float> a(MAXTOFCH,MAXESDCH, 0.0);
  TNT::Matrix<float> sum(MAXTOFCH,MAXESDCH, 0.0);

  /* --- output sum of all MA slices ---
     -----------------------------------
  */
  cout << thisprog << " -D- summing slices..." << endl;
  float slsum;
  for(i = FIRSTEDB; i < MAXEDB ; i++){
    a = MA->getSlice(i);
    sum = sum + a;

    // sum each slice (for debugging boxrates)
    slsum = 0.0;
    for(int ntof = 0; ntof < MAXTOFCH; ntof++){
      for(int nesd = 0; nesd < MAXESDCH; nesd++){
	slsum += a[ntof][nesd];
      }
    }
    cout << "+ nedb=" << i << " sum_of_slice=" << slsum << endl;
    
  }

  outfile = bname + "_ma.dat";
  fout.open(outfile.c_str());
  fout << "ACE/SWICS counts/second for day(s) " << StartYdoy <<
    " - " << StopYdoy << endl;
  fout << "TOF_CH ESD_CH" << endl;
  fout << "0 1023 0 255" << endl;
  fout << sum; 
  fout.close();

  /* --- subsection slices */
  int region[4] = {300,500,1,130};
  TNT::Index1D k(region[0],region[1]);
  TNT::Index1D l(region[2],region[3]);

  int slices[] = {18, 24, 30, 36, 41, 42, 48};
  char slicefile[20];
  for (i = 0; i < 7; i++){
    sprintf(slicefile, "%s_ma_sl%02d.dat",bname.c_str(),slices[i]);
    fout.open(slicefile);

    // write header
    fout << "ACE/SWICS counts/second for day(s) " << StartYdoy <<
      " - " << StopYdoy << endl;
    fout << "TOF_CH ESD_CH" << endl;
    for (int j = 0; j < 4; j++){
      fout << region[j] << " ";
    }
    fout << endl;

    //fout << "300 500 1 130" << endl;
 
    a = MA->getSlice(slices[i]);

    fout << a(k,l); 

    fout.close();
  }

  /* --- EDB 41 peak --- */
  sprintf(slicefile, "%s_ma_sl41.dat",bname.c_str());
  fout.open(slicefile);

  int region41[4] = {300,350,1,30};
  TNT::Index1D k41(region41[0],region41[1]);
  TNT::Index1D l41(region41[2],region41[3]);
  
  // write header
  fout << "ACE/SWICS counts/second for day(s) " << StartYdoy <<
    " - " << StopYdoy << endl;
  fout << "TOF_CH ESD_CH" << endl;
  for (int j = 0; j < 4; j++){
    fout << region41[j] << " ";
  }
  fout << endl;
  
  a = MA->getSlice(41);

  fout << a(k41,l41);

  fout.close();

  /* --- EDB 41 O7+ box --- */
  sprintf(slicefile, "%s_ma_sl41_o7.dat",bname.c_str());
  fout.open(slicefile);

  int region41o7[4] = {338,350,44,59};
  TNT::Index1D k41o7(region41o7[0],region41o7[1]);
  TNT::Index1D l41o7(region41o7[2],region41o7[3]);
  
  // write header
  fout << "ACE/SWICS counts/second for day(s) " << StartYdoy <<
    " - " << StopYdoy << endl;
  fout << "TOF_CH ESD_CH" << endl;
  for (int j = 0; j < 4; j++){
    fout << region41o7[j] << " ";
  }
  fout << endl;
  
  a = MA->getSlice(41);

  fout << a(k41o7,l41o7);

  fout.close();

  /* --- write mmq matrices to file ---
     ----------------------------------
  */
  TNT::Matrix<float> mmq(NQCH,NMCH, 0.0);
  TNT::Matrix<float> mmqsum(NQCH,NMCH, 0.0);
  TNT::Matrix<float> zero(NQCH,NMCH, 0.0);

  // -- whole thing
  sprintf(slicefile, "%s_mmq.dat",bname.c_str());
  fout.open(slicefile);

  fout << "ACE/SWICS m-m/q in counts/second for day(s) " << StartYdoy <<
    " - " << StopYdoy << endl;
  fout << "mass/charge mass" << endl;
  fout << "1 " << NQCH << " 1 " << NMCH << endl;
  
  for(i = FIRSTEDB; i < MAXEDB ; i++){
    a = MA->getSlice(i);
    mmq = MA->EtSlice2Mmq(a,i,0,ad);
    mmqsum = mmqsum + mmq;
  }

  fout << mmqsum;
  fout.close();

  for (i = 0; i < 6; i++){
    sprintf(slicefile, "%s_mmq_sl%02d.dat",bname.c_str(),slices[i]);
    fout.open(slicefile);

    fout << "ACE/SWICS m-m/q in counts/second for day(s) " << StartYdoy <<
      " - " << StopYdoy << endl;
    fout << "mass/charge mass" << endl;
    fout << "1 " << NMCH << " 1 " << NQCH << endl;
 
    a = MA->getSlice(slices[i]);
    mmq = MA->EtSlice2Mmq(a,slices[i],0,ad);

    if (mmq != zero) {
      fout << mmq; 
    }
    else if (mmq == zero){
      cout << thisprog << " -D- " 
	   << "mmq from nedb=" << slices[i] 
	   << " equals zero!"  << endl;
    }
    else {
      cout << thisprog << " -D- " 
	   << "mmq from nedb=" << slices[i] 
	   << " does not equal zero or ~zero!"  << endl;
    }
      
    fout.close();
  }
  return (0);
}
