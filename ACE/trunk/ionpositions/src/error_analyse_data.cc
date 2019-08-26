//  ************************************************
//  *                                              *
//  * file:      ion_pos.cpp                       *
//  *                                              *
//  * author:                                      *
//  *            Lars Berger                       *
//  *            <berger@physik.uni-kiel.de>       *
//  *                                              *
//  * version:   1.00                              *
//  *                                              *
//  * rev. date: 17.05.2005                        *
//  *                                              *
//  *                                              *
//  *                                              *
//  *                                              *
//  *                                              *
//  *                                              *
//  *                                              *
//  ************************************************/

#include "error_analyse_data.h"

int XDIM = 512;
int YDIM = 128;
int DIM=60;

using namespace std;

int main()
{
  // Variable declaration

  const int numparaion = 7;
  const double sig0 = 2.;
  string tmp1; // Dummies 
  int tmp2; // Dummies
  double tmp4; // Dummies
  double tmp3;
  double merit = 0.;

  string thisprogram = "main : ";
  string filenamelist ="";
  string filenamedata ="";
  string filenameergin = "";
  string filenameionpos= "";
  string filenameerg = "";

  int dbglvl = 1;
  
  int numberions=0; // Complete number of Ions for Each E/q step
  mdouble et_mat;
  mdouble alpha;
  mdouble covar;
  
  double (*func) (int ,int , vdouble &, vdouble &, int , int, vint &, double) = twodgauss4sig;  // Function used for fitting
  
  char line[200];
  string line2;
  const char* format = "%-10s%8.2f%8.2f%8.2f%8.2f%8.2f%8.2f%8.2f%8.2f%8.2f%16.2f%12.2f";
  const char* format2 = "erg_error_data_%s_step%i_%.0f_%.1f_%s.dat";
  
  // Initialization
  tmp1 = "";
  tmp2 = 0;
  tmp3 = 0.;
  tmp4 = 0.;
  double tmp5 = 0.;
  double tmp6 = 0.;
  double tmp7 = 0.;
  double tmp8 = 0.;
  double tmp9 = 0.;
  double tmp10 = 0.;
  double tmp11 = 0.;
  double tmp12 = 0.;
  string tmp13 = "";
  et_mat= mdouble(YDIM,XDIM);  
  int lowerstep=0;
  int upperstep=0;
  int fitmode=0;


  // several settings are done
  
  // list of names containing error data is set
  filenamelist="paralist.in";

  // global dbglvl is set
  dbglvl=1;

  // lower and upper limit for steps to be fitted
  lowerstep = 1;
  upperstep = 200;

  // fitmode is set
  fitmode=1;
  
  ifstream filelistin(filenamelist.c_str());
  int numberfiles=0;
  filelistin >> tmp2;
  numberfiles=tmp2;

  for (int file=0;file < numberfiles;file++){
 
  // Read parameter file "ion_para.dat" (name comes from "ion_pos.in"). These ions are beeing held fixed during the fitting

    string parafilename;
    string name;
    string ionname;
    int ionstep;
    double counts;
    double frac;
    ion iondat;
    vion ionsdat(vion(0));

    filelistin >> tmp1;
    parafilename=tmp1;

    ifstream parain(parafilename.c_str());
    parain >> tmp1;
    name=tmp1;
    parain >> tmp2;
    ionstep=tmp2;
    parain >> tmp12;
    parain >> tmp12;
    counts=tmp12;
    parain >> tmp12;
    frac=tmp12;
    parain >> tmp1;

    parain >> tmp1 >> tmp1 >> tmp1 >> tmp1 >> tmp1 >> numberions;
    cout << "numberions = " << numberions << endl;
    parain >> tmp1 >> tmp1 >> tmp1 >> tmp1 >> tmp1 >> tmp1 >> tmp1 >> tmp1 >> tmp1 >> tmp1 >> tmp1;
    tmp2 = 0; 
    while (tmp2 < numberions){
      parain >> tmp1 >> tmp3 >> tmp4 >> tmp5 >> tmp6 >> tmp7 >> tmp8 >> tmp9 >> tmp10 >> tmp11 >> tmp12; 
      iondat = ion(sig0);
      iondat.put_name(tmp1);
      iondat.put_mass(tmp10);
      iondat.put_charge(tmp11);
      iondat.put_tpos(tmp3);
      iondat.put_epos(tmp4);
      iondat.put_peakhigh(tmp12);
      iondat.put_velocity(tmp9);
      iondat.put_sigtp(tmp5);
      iondat.put_sigtm(tmp6);
      iondat.put_sigep(tmp7);
      iondat.put_sigem(tmp8);
      tmp2 ++;
      ionsdat.push_back(iondat);
    }
  
    parain.close();
    // Finish reading ion_para.dat

    for (int ion=1;ion<numberions;ion++){
      string ionname;
      ionsdat[ion].get_name(ionname);
      sprintf(line,format2,name.c_str(),ionstep,counts,frac,ionname.c_str());
      line2 = line;
      filenameerg=line2;

      cout << "ionname = "<< ionname << std::endl;

      // opening file for output (it is closed after mainloop)
      ofstream fileerg(filenameerg.c_str());
      cout << "opening ergfile for output " << filenameerg << endl;
      // mainloop where fitting is done starts here 
      for (int step = lowerstep-1; step < upperstep;step++){

	fileerg << "Step : " << step << "  Numberions = 2" << endl;
	fileerg << "Name          xpos    ypos   sigxp   sigxm   sigyp   sigym    vel     mass    charge         fiterg     normerg" << endl;
    
	if (numberions > 0){

	  if (dbglvl >= 1){
	    cout << thisprogram << "Finished reading data" << endl;
	  }
      
	  alpha = mdouble(2*numparaion,2*numparaion);
	  covar = mdouble(2*numparaion,2*numparaion);
	  vdouble param(2*numparaion,sig0);

	  // nlow and nhigh are obsolete and not used in fitting.cc but for they are needed in ion_pos.cc are left into fitting.cc 
	  vdouble nlow(2*numparaion,0.);
	  vdouble nhigh(2*numparaion,0.);

	  
	  // loop : parameters of ions held fixed are read in

	  ionsdat[0].get_peakhigh(tmp4);
	  param[0] = tmp4; // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	  ionsdat[0].get_tpos(tmp4);
	  param[1] = tmp4;
	  ionsdat[0].get_epos(tmp4);
	  param[2] = tmp4;
	  ionsdat[0].get_sigtp(tmp4);
	  param[3] = tmp4;
	  ionsdat[0].get_sigtm(tmp4);
	  param[4] = tmp4;
	  ionsdat[0].get_sigep(tmp4);
	  param[5] = tmp4;
	  ionsdat[0].get_sigem(tmp4);
	  param[6] = tmp4;

	  ionsdat[ion].get_peakhigh(tmp4);
	  param[7] = tmp4; // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	  ionsdat[ion].get_tpos(tmp4);
	  param[8] = tmp4;
	  ionsdat[ion].get_epos(tmp4);
	  param[9] = tmp4;
	  ionsdat[ion].get_sigtp(tmp4);
	  param[10] = tmp4;
	  ionsdat[ion].get_sigtm(tmp4);
	  param[11] = tmp4;
	  ionsdat[ion].get_sigep(tmp4);
	  param[12] = tmp4;
	  ionsdat[ion].get_sigem(tmp4);
	  param[13] = tmp4;

	  cout << "begin datageneration" << endl;
	  et_mat=datagen(param);
	  cout << "end datageneration" << endl;

	  boxrates(et_mat,param);

	  vint parause(2*numparaion,0);

	  if (dbglvl >= 1){
	    for (int i = 0; i < 2*numparaion; i++){
	      cout << "param[" << i << "]= " << param[i] << endl;
	    }
	  }
	  vdouble dyda(2*numparaion,0.);

	  if (dbglvl >= 1){
	    cout << "numberions = " << 2 << endl;
	  }
	  cout << thisprogram << "step " << step+1 << endl;
	  for (int it = 0;it < 2;it++){                                  	   // loop : number of iterations
	    if (fitmode==1){
	      for (int k = 0; k < 2*numparaion;k++){
		parause[k] = 0;
	      }
	      for (int m = 0; m < 2; m++){  // loop : number of ions to be fitted
		parause[(m*numparaion)] = 1;                             // parameter to be fitted is set
	      }
	      // used parameters are displayed
	      for (int l=0;l<2*numparaion;l++){
		if (parause[l]){
		  cout << thisprogram << "fitting param[" << l << "]" << endl;
		}
	      }

	      if (dbglvl >= 1){
		for (int m = 0; m < 2*numparaion;m++){
		  if (parause[m]){
		    cout << thisprogram << "parause[" << m << "] = " << parause[m] << endl;
		  }
		}
	      }
	    
	      if (dbglvl >= 1){
		cout << thisprogram << "calling maxlifit" << endl;
	      }
	      while (!maxlifit(et_mat,param,nlow,nhigh,parause,covar,alpha,merit,func)) cout << thisprogram << "calling maxlifit" << endl;
	      if (dbglvl >= 1){
		cout << thisprogram << "leaving maxlifit" << endl;
	      }
	      // fitted parameters are displayed
	      for (int l=0;l<2*numparaion;l++){
		if (parause[l]){
		  cout << thisprogram << "param[" << l << "] = " << param[l] << endl;
		}
	      }
	    }
	  }

	  vdouble normparam(2*numparaion,0.);
	  cout << thisprogram << "entering normfit" << endl;
	  normparam=normfit(param,et_mat,func);
	  cout << thisprogram << "leaving normfit" << endl;
	  //	param=normparam;
	
	  // fiiting results are written to stdout

	  for (int i = 0; i < 2; i++){
	    for (int k = 0; k < numparaion; k++){
	      cout << thisprogram << "param[" << (i*numparaion)+k << "]= " << param[(i*numparaion)+k] << endl;
	    }
	  }

	  // fitting results are written to outputfile 

	  line2 = "";
	  ionsdat[0].get_name(tmp1);
	  ionsdat[0].get_velocity(tmp5);
	  ionsdat[0].get_mass(tmp6);
	  ionsdat[0].get_charge(tmp7);
	  sprintf(line,format,tmp1.c_str(),param[1],param[2],param[3],param[4],param[5],param[6],tmp5,tmp6,tmp7,param[0],normparam[0]);
	  line2 = line;
	  fileerg << line2 << endl;
	  line2 = "";
	  ionsdat[ion].get_name(tmp1);
	  ionsdat[ion].get_velocity(tmp5);
	  ionsdat[ion].get_mass(tmp6);
	  ionsdat[ion].get_charge(tmp7);
	  sprintf(line,format,tmp1.c_str(),param[(numparaion)+1],param[(numparaion)+2],param[(numparaion)+3],param[(numparaion)+4],param[(numparaion)+5],param[(numparaion)+6],tmp5,tmp6,tmp7,param[(numparaion)],normparam[(numparaion)]);
	  line2 = line;
	  fileerg << line2 << endl;

	  // all parameters are set to "nofit"

	  for (int i = 0;i < 2*numparaion;i++){
	    parause[i] = 0;
	  }

	}
  
      }
      fileerg.close();
    }
  }
}
 /*
 * Overrides for Emacs so that we follow a common tabbing style.
 * Emacs will notice this stuff at the end of the file and automatically
 * adjust the settings for this buffer only.  This must remain at the end
 * of the file.
 * ---------------------------------------------------------------------------
 * Local variables:
 * c-file-style: "gnu"
 * End:
 */
