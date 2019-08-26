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

#include "ion_pos.h"

int XDIM = 512;
int YDIM = 128;

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
  int tmp0 = 0;

  string thisprogram = "main : ";
  string filenamedata ="";
  string filenameergin = "";
  string filenameionpos= "";
  string filenameerg = "";

  int dbglvl = 1;

  ion iondat;
  
  vint useparameter(numparaion,0); // is set from ion_pos.in -> which parameters are to be fitted
  vint numberionsfixed(60,0); // Number if Ions held to be fixed for each E/q step
  vint numberions(60,0); // Complete number of Ions for Each E/q step
  vint numberparam(60,0); // Number of Parameters for Each E/q step
  dbgvector<vion> ionsdat(60,vion(0));
  mdouble et_mat;
  mdouble alpha;
  mdouble covar;
  
  double (*func) (int ,int , vdouble &, vdouble &, int , int, vint &, double) = twodgauss4sig;  // Function used for fitting
  
  char line[200];
  string line2;
  const char* format = "%-10s%8.2f%8.2f%8.2f%8.2f%8.2f%8.2f%8.2f%8.2f%8.2f%16.2f";
  
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
  int tmp14 = 0;
  et_mat= mdouble(YDIM,XDIM);  
  int lowerstep=0;
  int upperstep=0;
  int fitparafile=0;
  int fitmode=0;

  double tolnegxpos=2.;
  double tolposxpos=2.;
  double tolnegypos=2.;
  double tolposypos=2.;



  // Read ion_pos.in -> several settings are done
  
  string filenameionposin = "ion_pos.in";
  
  ifstream fileionposin(filenameionposin.c_str());
  

  // name of data file is read
  fileionposin >> filenamedata;
  getline(fileionposin,tmp13);
  cout << filenamedata << endl;
  
  // name of results file for in and output is read
  fileionposin >> filenameergin;
  filenameerg=filenameergin;
  getline(fileionposin,tmp13);

  // name of prel. results from ion_pos.pro is read
  fileionposin >> filenameionpos;
  getline(fileionposin,tmp13);

  // list of used parameters is loaded
  for (int i = 0; i < numparaion; i++){
    fileionposin >> tmp14;
    useparameter[i]=tmp14;
    getline(fileionposin,tmp13);
  }

  // global dbglvl is set
  fileionposin >> dbglvl;
  getline(fileionposin,tmp13);

  // lower and upper limit for steps to be fitted

  fileionposin >> lowerstep;
  getline(fileionposin,tmp13);

  fileionposin >> upperstep;
  getline(fileionposin,tmp13);

  // tolerance limits for position fitting

  fileionposin >> tolnegxpos;
  getline(fileionposin,tmp13);

  fileionposin >> tolposxpos;
  getline(fileionposin,tmp13);

  fileionposin >> tolnegypos;
  getline(fileionposin,tmp13);

  fileionposin >> tolposypos;
  getline(fileionposin,tmp13);

  fileionposin >> fitparafile;
  getline(fileionposin,tmp13);

  fileionposin >> fitmode;
  getline(fileionposin,tmp13);

  
  fileionposin.close();

  if (dbglvl >= 1){
    cout << "finished reading ion_pos.in" << endl;
  }
  
  // Read parameter file "ion_para.dat" (name comes from "ion_pos.in"). These ions are beeing held fixed during the fitting

  ifstream fileergin(filenameergin.c_str());

  for (int i = 0; i < 60; i++){
    fileergin >> tmp1 >> tmp1 >> tmp1 >> tmp1 >> tmp1 >> numberionsfixed[i];
    cout << "numberionsfixed[" << i << "] = "<< numberionsfixed[i] << endl;
    fileergin >> tmp1 >> tmp1 >> tmp1 >> tmp1 >> tmp1 >> tmp1 >> tmp1 >> tmp1 >> tmp1 >> tmp1 >> tmp1;
    tmp2 = 0; 
    while (tmp2 < numberionsfixed[i]){
      fileergin >> tmp1 >> tmp3 >> tmp4 >> tmp5 >> tmp6 >> tmp7 >> tmp8 >> tmp9 >> tmp10 >> tmp11 >> tmp12; 
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
      ionsdat[i].push_back(iondat);
    }
  }

  fileergin.close();

  // Read "ion_pos.dat"(meantime name is read from "ion_pos.in"), created by ion_pos.pro (IDL/actually created by srim2ionpos.py). The ions that are in this file and are not in ion_para.dat s.a. are beeing fitted.

  /*
  ifstream file(filenameionpos.c_str());
  
  for (int i = 0; i < 60; i++){
    file >> tmp1 >> tmp1 >> tmp2 >> tmp1 >> tmp1 >> tmp1 >> numberions[i];
    file >> tmp1 >> tmp1 >> tmp1 >> tmp1 >> tmp1 >> tmp1 >> tmp1;
    tmp2 = 0; 
    tmp0 = numberions[i];
    while (tmp2 < numberions[i]){
      tmp14 = 1;
      file >> tmp1 >> tmp4 >> tmp5 >> tmp3 >> tmp8 >> tmp6 >> tmp7; 
      for (int k = 0; k < numberionsfixed[i];k++){
	ionsdat[i][k].get_name(tmp13);
	if (tmp1 == tmp13){
	  tmp0--;
	  tmp14 = 0;
	}
      }
      if (tmp14){
	iondat = ion(sig0);
	iondat.put_name(tmp1);
	iondat.put_mass(tmp4);
	iondat.put_charge(tmp5);
	iondat.put_tpos(tmp3);
	iondat.put_epos(tmp8);
	iondat.put_peakhigh(tmp6);
	iondat.put_velocity(tmp7);
	ionsdat[i].push_back(iondat);
      }
      tmp2++;
    }
    file >> tmp1;
    numberions[i] = tmp0;
  }

  file.close();

  */

  if (dbglvl >= 1){
    cout << thisprogram << "Finished reading ion_pos.dat" << endl;
  }
  // Finish reading ion_pos.dat
  
  // opening file for output (it is closed after mainloop)

  filenameerg="erg_"+filenameergin;
  ifstream datain(filenamedata.c_str());
  ofstream fileerg(filenameerg.c_str());
  read_header(datain);
  read_data(datain,lowerstep-1,et_mat,0);

  // mainloop where fitting is done starts here 

  for (int step = lowerstep-1; step < upperstep;step++){

    numberions[step] = numberions[step] + numberionsfixed[step];
    
    fileerg << "Step : " << step+1 << "  Numberions = " << numberions[step] << endl;
    fileerg << "Name          xpos    ypos   sigxp   sigxm   sigyp   sigym    vel     mass    charge       peakhigh" << endl;
    
    if (numberions[step] > 0){
      
      read_data(datain,1,et_mat,0);
      
      if (dbglvl >= 1){
	cout << thisprogram << "Finished reading data" << endl;
      }
      
      alpha = mdouble(numberions[step]*numparaion,numberions[step]*numparaion);
      covar = mdouble(numberions[step]*numparaion,numberions[step]*numparaion);
      vdouble nlow(numberions[step]*numparaion,0.),nhigh(numberions[step]*numparaion,0.);
      vdouble param(numberions[step]*numparaion,sig0);
      vdouble normparam(numberions[step]*numparaion,sig0);

      // loop : parameters of ions held fixed are read in

      for (int i = 0; i < numberionsfixed[step];i++){
	int A = (i*numparaion);
	int xpos = (i*numparaion)+1;
	int ypos = (i*numparaion)+2;
	int sigxp = (i*numparaion)+3;
	int sigxm = (i*numparaion)+4;
	int sigyp = (i*numparaion)+5;
	int sigym = (i*numparaion)+6;

	ionsdat[step][i].get_peakhigh(tmp4);
	tmp4 = tmp4;
	nhigh[A] = tmp4*100.;
	nhigh[A] = 100000.;
	nlow[A] = 0.;
	param[A] = tmp4;
	if (et_mat[int(param[ypos])][int(param[xpos])]==0.){
	  param[A] = 0.5;
	}
	else {
	  param[A] = et_mat[int(param[ypos])][int(param[xpos])]*10.;
	}
	ionsdat[step][i].get_tpos(tmp4);
	nhigh[xpos] = tmp4 + tolposxpos;
	if (nhigh[xpos]>507.){
	  nhigh[xpos]=507.;
	}
	nlow[xpos] = tmp4 - tolnegxpos;
	if (nlow[xpos]< 5.){
	  nlow[xpos]=5.;
	}
	param[xpos] = tmp4;
       
	ionsdat[step][i].get_epos(tmp4);
	nhigh[ypos] = tmp4 + tolposypos;
	if (nhigh[ypos]>123.){
	  nhigh[ypos] = 123.;
	}
	nlow[ypos] = tmp4 - tolnegypos;
	if (nlow[ypos] < 5.){
	  nlow[ypos] = 5.;
	}
	param[ypos] = tmp4;
	  
	ionsdat[step][i].get_sigtp(tmp4);
	nhigh[sigxp] = 5.;
	nlow[sigxp] = .2;
	param[sigxp] = tmp4;
	  
	ionsdat[step][i].get_sigtm(tmp4);
	nhigh[sigxm] = 5.;
	nlow[sigxm] = .2;
	param[sigxm] = tmp4;
	  
	ionsdat[step][i].get_sigep(tmp4);
	nhigh[sigyp] = 5.;
	nlow[sigyp] = .2;
	param[sigyp] = tmp4;
	  
	ionsdat[step][i].get_sigem(tmp4);
	nhigh[sigym] = 5.;
	nlow[sigym] = .2;
	param[sigym] = tmp4;
	  
      }

      // loop : parameter of ions that are to be fitted are read in/ are set.  

      for (int i = numberionsfixed[step]; i < numberions[step];i++){
	int A = (i*numparaion);
	int xpos = (i*numparaion)+1;
	int ypos = (i*numparaion)+2;

	ionsdat[step][i].get_peakhigh(tmp4);
	tmp4 = tmp4*100.;
	nhigh[A] = tmp4 * 1000.;
	nlow[A] = 0.;
	param[A] = tmp4;
	  
	ionsdat[step][i].get_tpos(tmp4);
	nhigh[xpos] = tmp4 + tolposxpos;
	if (nhigh[xpos]>507.){
	  nhigh[xpos]=507.;
	}
	nlow[xpos] = tmp4 - tolnegxpos;
	if (nlow[xpos]< 5.){
	  nlow[xpos]=5.;
	}
	param[xpos] = tmp4;
       
	ionsdat[step][i].get_epos(tmp4);
	nhigh[ypos] = tmp4 + tolposypos;
	if (nhigh[ypos]>123.){
	  nhigh[ypos] = 123.;
	}
	nlow[ypos] = tmp4 - tolnegypos;
	if (nlow[ypos] < 5.){
	  nlow[ypos] = 5.;
	}
	param[ypos] = tmp4;
	for (int k = 3; k < numparaion ; k++){
	  nhigh[(i*numparaion)+k] = sig0 + 10.;
	  nlow[(i*numparaion)+k] = 0.2;
	}
      }
      

      boxrates(et_mat,param);
	
      vint paraorder(numberions[step],0);
	
      paraorder=sort(param);
      cout << thisprogram << "paraorder = ";
      for (int m=0;m<numberions[step];m++){
	cout << paraorder[m] << ",";
      }
      cout << endl;

      vint parause(numberions[step]*numparaion,0);




      if (dbglvl >= 1){
	for (int i = 0; i < numberions[step]*numparaion; i++){
	  cout << "param[" << i << "]= " << param[i] << endl;
	}
      }
      vdouble dyda(numberions[step]*numparaion,0.);

      if (dbglvl >= 1){
	cout << "numberions = " << numberions[step] << endl;
      }
      cout << thisprogram << "step " << step+1 << endl;
      int lowerbound=0;
      if (fitparafile){
	lowerbound=0;
      }
      if (!fitparafile){
	lowerbound=numberionsfixed[step];
      }
      for (int it = 0;it < 2;it++){                                  	   // loop : number of iterations
	if (fitmode==0){
	  for (int m = lowerbound; m < numberions[step]; m++){  // loop : number of ions to be fitted
	    for (int n = 0;n < numparaion; n++){                           // loop : number of parameters per ions
	      if (useparameter[n]!=0){
		for (int k = 0; k < numberions[step]*numparaion;k++){
		  parause[k] = 0;
		}

		if (n==0){
		  parause[(paraorder[m]*numparaion)]=1;
		}                             // parameter to be fitted is set
		if (n==1){
		  parause[(paraorder[m]*numparaion)+1]=1;
		}                             // parameter to be fitted is set
		if (n==2){
		  parause[(paraorder[m]*numparaion)+2]=1;
		}                             // parameter to be fitted is set
		if (n>2){
		  parause[(paraorder[m]*numparaion)+n]=1;
		}                             // parameter to be fitted is set

		// used parameters are displayed
		for (int l=0;l<numberions[step]*numparaion;l++){
		  if (parause[l]){
		    cout << thisprogram << "fitting param[" << l << "]" << endl;
		  }
		}
		if (dbglvl >= 1){
		  cout << thisprogram << "param : " << endl;
	      
		  for (int i = 0; i < int(param.size()); i++){
		    if (parause[i]){
		      cout << thisprogram << param[i] << "  " << nlow[i] << "  " << nhigh[i] << endl;
		    }
		  }
		}

		if (dbglvl >= 1){
		  for (int o = 0; o < numberions[step]*numparaion;o++){
		    if (parause[o]){
		      cout << thisprogram << "parause[" << o << "] = " << parause[o] << endl;
		    }
		  }
		}
	    
		if (dbglvl >= 1){
		  cout << thisprogram << "calling maxlifit" << endl;
		}
		while (!maxlifit(et_mat,param,nlow,nhigh,parause,covar,alpha,merit,func)) cout << thisprogram << "calling maxlifit" << endl;
		// fitted parameters are displayed
		for (int l=0;l<numberions[step]*numparaion;l++){
		  if (parause[l]){
		    cout << thisprogram << "param[" << l << "] = " << param[l] << endl;
		  }
		}

		if (dbglvl >= 1){
		  cout << thisprogram << "leaving maxlifit" << endl;
		}
	      }	    
	    }
	  }
	}
	if (fitmode==1){
	  for (int n = 0;n < numparaion; n++){                           // loop : number of parameters per ions
	    if (useparameter[n]!=0){
	      for (int k = 0; k < numberions[step]*numparaion;k++){
		parause[k] = 0;
	      }
	      for (int m = lowerbound; m < numberions[step]; m++){  // loop : number of ions to be fitted
		parause[(m*numparaion)+n] = 1;                             // parameter to be fitted is set
	      }
	      // used parameters are displayed
	      for (int l=0;l<numberions[step]*numparaion;l++){
		if (parause[l]){
		  cout << thisprogram << "fitting param[" << l << "]" << endl;
		}
	      }


	      if (dbglvl >= 1){
		cout << thisprogram << "param : " << endl;
	      
		for (int i = 0; i < int(param.size()); i++){
		  if (parause[i]){
		    cout << thisprogram << param[i] << "  " << nlow[i] << "  " << nhigh[i] << endl;
		  }
		}
	      }

	      if (dbglvl >= 1){
		for (int m = 0; m < numberions[step]*numparaion;m++){
		  if (parause[m]){
		    cout << thisprogram << "parause[" << m << "] = " << parause[m] << endl;
		  }
		}
	      }
	    
	      if (dbglvl >= 1){
		cout << thisprogram << "calling maxlifit" << endl;
	      }
	      while (!maxlifit(et_mat,param,nlow,nhigh,parause,covar,alpha,merit,func)) cout << thisprogram << "calling maxlifit" << endl;
	      //		maxlifit(et_mat,param,nlow,nhigh,parause,covar,alpha,merit,func);
	      // fitted parameters are displayed
	      while (!maxlifit(et_mat,param,nlow,nhigh,parause,covar,alpha,merit,func)) cout << thisprogram << "calling maxlifit" << endl;
	      for (int l=0;l<numberions[step]*numparaion;l++){
		if (parause[l]){
		  cout << thisprogram << "param[" << l << "] = " << param[l] << endl;
		}
	      }
	      if (dbglvl >= 1){
		cout << thisprogram << "leaving maxlifit" << endl;
	      }
	    }	    
	  }
	}
	if (fitmode==2){
	  for (int n = 0;n < 3; n++){                           // loop : number of parameters per ions
	    for (int k = lowerbound; k < numberions[step];k++){
	      for (int l = 0; l < numberions[step]*numparaion;l++){
		parause[l] = 0; // all parameters are set to notfit
	      }
	      if (n==0){
		if (useparameter[1]!=0){
		  parause[(k*numparaion)+1] = 1;
		}
		if (useparameter[2]!=0){
		  parause[(k*numparaion)+2] = 1;
		}
	      }
	      if (n==1){
		if (useparameter[3]!=0){
		  parause[(k*numparaion)+3] = 1;
		}
		if (useparameter[4]!=0){
		  parause[(k*numparaion)+5] = 1;
		}
	      }
	      if (n==2){
		if (useparameter[5]!=0){
		  parause[(k*numparaion)+4] = 1;
		}
		if (useparameter[6]!=0){
		  parause[(k*numparaion)+6] = 1;
		}
	      }
	      // used parameters are displayed
	      for (int l=0;l<numberions[step]*numparaion;l++){
		if (parause[l]){
		  cout << thisprogram << "fitting param[" << l << "]" << endl;
		}
	      }


	      if (dbglvl >= 1){
		cout << thisprogram << "param : " << endl;
	      
		for (int i = 0; i < int(param.size()); i++){
		  if (parause[i]){
		    cout << thisprogram << param[i] << "  " << nlow[i] << "  " << nhigh[i] << endl;
		  }
		}
	      }

	      if (dbglvl >= 1){
		for (int m = 0; m < numberions[step]*numparaion;m++){
		  if (parause[m]){
		    cout << thisprogram << "parause[" << m << "] = " << parause[m] << endl;
		  }
		}
	      }
	    
	      if (dbglvl >= 1){
		cout << thisprogram << "calling maxlifit" << endl;
	      }
	      while (!maxlifit(et_mat,param,nlow,nhigh,parause,covar,alpha,merit,func)) cout << thisprogram << "calling maxlifit" << endl;
	      //		maxlifit(et_mat,param,nlow,nhigh,parause,covar,alpha,merit,func);
	      // fitted parameters are displayed
	      for (int l=0;l<numberions[step]*numparaion;l++){
		if (parause[l]){
		  cout << thisprogram << "param[" << l << "] = " << param[l] << endl;
		}
	      }

	      if (dbglvl >= 1){
		cout << thisprogram << "leaving maxlifit" << endl;
	      }
	      if (n==0){
		if (useparameter[0]!=0){
		  parause[(k*numparaion)] = 1;
		}
		if (useparameter[1]!=0){
		  parause[(k*numparaion)+1] = 0;
		}
		if (useparameter[2]!=0){
		  parause[(k*numparaion)+2] = 0;
		}
		cout << thisprogram << "fitting param[" << (k*numparaion) << "]" << endl;
		while (!maxlifit(et_mat,param,nlow,nhigh,parause,covar,alpha,merit,func)) cout << thisprogram << "calling maxlifit" << endl;
		//maxlifit(et_mat,param,nlow,nhigh,parause,covar,alpha,merit,func) ;
		// fitted parameters are displayed
		for (int l=0;l<numberions[step]*numparaion;l++){
		  if (parause[l]){
		    cout << thisprogram << "param[" << l << "] = " << param[l] << endl;
		  }
		}
	      }
	    }	    

	  }
	}
	if (fitmode==3){   // all parameters of single ions are set to be fitted simultaniously (only parameters that are set to fit")
	  for (int k = lowerbound; k < numberions[step];k++){
	    for (int l = 0; l < numberions[step]*numparaion;l++){
	      parause[l] = 0; // all parameters are set to notfit
	    }
	    for (int l = 0; l < numparaion;l++){
	      if (useparameter[l]!=0){
		parause[(paraorder[k]*numparaion)+l] = 1;
	      }
	    }
	  
	    // used parameters are displayed
	    for (int l=0;l<numberions[step]*numparaion;l++){
	      if (parause[l]){
		cout << thisprogram << "fitting param[" << l << "]" << endl;
	      }
	    }

	    if (dbglvl >= 1){
	      for (int m = 0; m < numberions[step]*numparaion;m++){
		if (parause[m]){
		  cout << thisprogram << "parause[" << m << "] = " << parause[m] << endl;
		}
	      }
	    }
	    
	    if (dbglvl >= 1){
	      cout << thisprogram << "calling maxlifit" << endl;
	    }
	    while (!maxlifit(et_mat,param,nlow,nhigh,parause,covar,alpha,merit,func)) cout << thisprogram << "calling maxlifit" << endl;
	    //		maxlifit(et_mat,param,nlow,nhigh,parause,covar,alpha,merit,func);
	    // fitted parameters are displayed
	    for (int l=0;l<numberions[step]*numparaion;l++){
	      if (parause[l]){
		cout << thisprogram << "param[" << l << "] = " << param[l] << endl;
	      }
	    }

	    if (dbglvl >= 1){
	      cout << thisprogram << "leaving maxlifit" << endl;
	    }
	  }	    
	}
      }

      cout << thisprogram << "entering normfit" << endl;
      normparam=normfit(param,et_mat,func);
      cout << thisprogram << "leaving normfit" << endl;
      param=normparam;
	
      // fiiting results are written to stdout

      for (int i = 0; i < numberions[step]; i++){
	for (int k = 0; k < numparaion; k++){
	  cout << thisprogram << "param[" << (i*numparaion)+k << "]= " << param[(i*numparaion)+k] << endl;
	}
      }

      // fitting results are written to outputfile 

      for (int i = 0; i < numberions[step]; i++){
	line2 = "";
	ionsdat[step][i].get_name(tmp1);
	ionsdat[step][i].get_velocity(tmp5);
	ionsdat[step][i].get_mass(tmp6);
	ionsdat[step][i].get_charge(tmp7);
	sprintf(line,format,tmp1.c_str(),param[(i*numparaion)+1],param[(i*numparaion)+2],param[(i*numparaion)+3],param[(i*numparaion)+4],param[(i*numparaion)+5],param[(i*numparaion)+6],tmp5,tmp6,tmp7,param[(i*numparaion)]);
	line2 = line;
	fileerg << line2 << endl;
      }

      // all parameters are set to "nofit"

      for (int i = 0;i < numberions[step]*numparaion;i++){
	parause[i] = 0;
      }

    }
  
  }
  fileerg.close();

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
