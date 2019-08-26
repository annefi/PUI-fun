/*
  File: outputMA.cc

  Description: 

    Output swindal MA matrices to a set of files.  NOTE: This
    is not really part of the swindal library, just stuck in here for
    now.

  Author: Jim Raines, Sep2001

  Method:
    
  Major Modification History:
    Split out from outputMats, JR, 9Oct2001

*/


#include "swindal.h"

int outputMA(string bname, MeasurementArray *MA, 
	       long int StartYdoy, long int StopYdoy, 
	       const AnalysisData& ad) {
  /* Description: Output several tof-esd and mmq matrices to files. */

  int i;
  string thisprog = "outputMA";

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

  /* --- summed MA ONC subsection ---
     -----------------------------------
  */
  outfile = bname + "_ma_onc.dat";
  fout.open(outfile.c_str());

  int regionONC[4] = {300,360,30,70};
  TNT::Index1D kONC(regionONC[0],regionONC[1]);
  TNT::Index1D lONC(regionONC[2],regionONC[3]);

  fout << "ACE/SWICS counts/second for day(s) " << StartYdoy <<
    " - " << StopYdoy << endl;
  fout << "TOF_CH ESD_CH" << endl;
  for (int j = 0; j < 4; j++){
    fout << regionONC[j] << " ";
  }
  fout << endl;

  fout << sum(kONC,lONC); 
  fout.close();

  /* --- subsection slices */
  char slicefile[20];
  if (0){
    int region[4] = {300,500,1,130};
    TNT::Index1D k(region[0],region[1]);
    TNT::Index1D l(region[2],region[3]);

    int slices[] = {18, 24, 30, 36, 41, 42, 48};
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

      a = MA->getSlice(slices[i]);

      fout << a(k,l); 

      fout.close();
    }
  }
  /* --- EDB 41 peak --- */
  if (0){
    sprintf(slicefile, "%s_ma_sl41_peak.dat",bname.c_str());
    fout.open(slicefile);

    int region41[4] = {325,375,38,65};
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
  }
  /* --- EDB 41 O7+ box --- */
  if(0){
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
  }

  return (0);
}
