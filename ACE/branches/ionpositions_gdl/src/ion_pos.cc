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
  double range = 3.;
  double merit = 0.;
  int tmp0 = 0;

  string thisprogram = "main : ";
  int dbglvl = 1;

  ion iondat;
  
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
  

  // Read ion_pos.dat, created by ion_pos.pro (IDL)
  
  string filenameergin = "ion_para.dat";

  ifstream fileergin(filenameergin.c_str());

  for (int i = 0; i < 60; i++){
    fileergin >> tmp1 >> tmp1 >> tmp1 >> tmp1 >> tmp1 >> numberionsfixed[i];
    cout << numberionsfixed[i] << endl;
    fileergin >> tmp1 >> tmp1 >> tmp1 >> tmp1 >> tmp1 >> tmp1 >> tmp1 >> tmp1 >> tmp1 >> tmp1 >> tmp1;
    tmp2 = 0; 
    while (tmp2 < numberionsfixed[i]){
      fileergin >> tmp1 >> tmp3 >> tmp4 >> tmp5 >> tmp6 >> tmp7 >> tmp8 >> tmp9 >> tmp10 >> tmp11 >> tmp12; 
      //      cout << tmp1 << tmp4 << tmp5 << tmp3 << tmp8 << tmp6 << tmp7 << endl;
      iondat = ion(sig0);
      iondat.put_name(tmp1);
      iondat.put_mass(tmp10);
      iondat.put_charge(tmp11);
      //      cout << "tpos = " << tmp3 << endl;
      iondat.put_tpos(tmp3);
      //      cout << "epos = " << tmp8 << endl;
      iondat.put_epos(tmp4);
      //      cout << "peakhigh = " << tmp6 << endl;
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



  string filename=("ion_pos.dat");
  
  ifstream file(filename.c_str());
  
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
	cout << tmp1 << "  " << tmp13 << endl;
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
	//      cout << "tpos = " << tmp3 << endl;
	iondat.put_tpos(tmp3);
	//      cout << "epos = " << tmp8 << endl;
	iondat.put_epos(tmp8);
	//      cout << "peakhigh = " << tmp6 << endl;
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

  if (dbglvl >= 1){
    cout << thisprogram << "Finished reading ion_pos.dat" << endl;
  }
  // Finish reading ion_pos.dat
  
  /*
  
  // Test fitting with artifical data.
  
  mdouble testdata;
  testdata = mdouble(YDIM,XDIM);
  vdouble testparam(numparaion,0.);
  testparam[0] = 999.;
  testparam[1] = 40.;
  testparam[2] = 40.;
  testparam[3] = 2.;
  testparam[4] = 2.3;
  testparam[5] = 3.;
  testparam[6] = 2.;
  vdouble testdyda(numparaion,0.);
  vint testparause(numparaion,1);
  int testnum1 = numparaion;
  int testnum2 = 1;
  double testrange = 3.;

  //  double (*func) (int ,int , vdouble &, vdouble &, int , int, vint &, double) = twodgauss4sig;  // Function used for fitting

  for (int i = 0; i < YDIM; i++){
  for (int j = 0; j < XDIM; j++){
  testdata[i][j] = func(j,i,testparam,testdyda,testnum1,testnum2,testparause,testrange);
  }
  }
  if (dbglvl >= 1){
  cout << thisprogram << "testdata generated!" << endl;
  }

  */


  string filenameerg = "ion_para.dat";
	  
  ofstream fileerg(filenameerg.c_str());

  for (int step = 0; step < 60;step++){

    numberions[step] = numberions[step] + numberionsfixed[step];
    
    fileerg << "Step : " << step+1 << "  Numberions = " << numberions[step] << endl;
    fileerg << "Name          xpos    ypos   sigxp   sigxm   sigtp   sigtm    vel     mass    charge       peakhigh" << endl;
    
    
    
    //*************************** remove when testing is over!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!    
	//numberions[step] = 1;
	
	if (numberions[step] > 0){
	  
	  filename=("/home/ivar/berger/projects/SWICS/trunk/databinning/axlv2_sumwhol_asp_06.0-07.0_bin.dat");
	//filename=("/home/ivar/berger/work/subversion/amerika/runs/2000138-2005198_accum_aspang/axlv2_sumwhol_asp_06.0-07.0_bin.dat");
	
	ifstream file2(filename.c_str());
      
	for (int l = 0; l < (step+1); l++){
	  file2 >> tmp2 >> tmp2;
	  //	cout << tmp2 << endl;
	  for (int i = 0; i < XDIM; i++){
	    for (int k = 0; k < YDIM; k++){
	      file2 >> tmp3;
	      et_mat[k][i] = double(tmp3);
	    }
	  }
	}
	for (int i = 0; i < XDIM; i++){
	  et_mat[0][i] = 0.;
	}

	if (dbglvl >= 1){
	  cout << thisprogram << "Finished reading data" << endl;
	}
      
	alpha = mdouble(numberions[step]*numparaion,numberions[step]*numparaion);
	covar = mdouble(numberions[step]*numparaion,numberions[step]*numparaion);
	vdouble nlow(numberions[step]*numparaion,0.),nhigh(numberions[step]*numparaion,0.);
      
	vdouble param(numberions[step]*numparaion,sig0);

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
	  nhigh[A] = tmp4;
	  nlow[A] = tmp4;
	  param[A] = tmp4;
	  
	  ionsdat[step][i].get_tpos(tmp4);
	  //	tmp2 = tmp2/2;
	  nhigh[xpos] = tmp4;
	  nlow[xpos] = tmp4;
	  param[xpos] = tmp4;
       
	  ionsdat[step][i].get_epos(tmp4);
       	  nhigh[ypos] = tmp4;
	  nlow[ypos] = tmp4;
	  param[ypos] = tmp4;
	  
	  ionsdat[step][i].get_sigtp(tmp4);
	  nhigh[sigxp] = tmp5;
	  nlow[sigxp] = tmp4;
	  param[sigxp] = tmp4;
	  
	  ionsdat[step][i].get_sigtm(tmp4);
	  nhigh[sigxm] = tmp4;
	  nlow[sigxm] = tmp4;
	  param[sigxm] = tmp4;
	  
	  ionsdat[step][i].get_sigep(tmp4);
	  nhigh[sigyp] = tmp4;
	  nlow[sigyp] = tmp4;
	  param[sigyp] = tmp4;
	  
	  ionsdat[step][i].get_sigem(tmp4);
	  nhigh[sigym] = tmp4;
	  nlow[sigym] = tmp4;
	  param[sigym] = tmp4;
	  
	}
	for (int i = numberionsfixed[step]; i < numberions[step];i++){
	  int A = (i*numparaion);
	  int xpos = (i*numparaion)+1;
	  int ypos = (i*numparaion)+2;
	  int sigxp = (i*numparaion)+3;
	  int sigxm = (i*numparaion)+4;
	  int sigyp = (i*numparaion)+5;
	  int sigym = (i*numparaion)+6;

	  ionsdat[step][i].get_peakhigh(tmp4);
	  tmp4 = tmp4*100.;
	  nhigh[A] = tmp4 * 1000.;
	  nlow[A] = 0.;
	  param[A] = tmp4;
	  
	  ionsdat[step][i].get_tpos(tmp4);
	  //	tmp2 = tmp2/2;
	  nhigh[xpos] = tmp4 + 2.;
	  nlow[xpos] = tmp4 - 2.;
	  param[xpos] = tmp4;
       
	  ionsdat[step][i].get_epos(tmp4);
	  //tmp4 = tmp4/2.;
	  nhigh[ypos] = tmp4 + 2.;
	  nlow[ypos] = tmp4 - 2.;
	  param[ypos] = tmp4;
	  for (int k = 3; k < numparaion ; k++){
	    nhigh[(i*numparaion)+k] = sig0 + 3.;
	    nlow[(i*numparaion)+k] = 0.2;
	  }
	}
      
	/* 
	// following lines for testing only!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
      
	param[0] = testparam[0]+10000.;
	param[1] = testparam[1]+1.;
	param[2] = testparam[2]+2.;
	param[3] = testparam[3]+.3;
	param[4] = testparam[4]+.2;
	param[5] = testparam[5]+.3; 
	param[6] = testparam[6]-.2;
      
	nhigh[0] = double(param[0]) * 10.;
	nhigh[1] = double(param[1]) + 10.;
	nhigh[2] = double(param[2]) + 10.;
	nhigh[3] = double(param[3]) + 10.;
	nhigh[4] = double(param[4]) + 10.;
	nhigh[5] = double(param[5]) + 10.;
	nhigh[6] = double(param[6]) + 10.;
	nlow[0] = 1.;
	nlow[1] = double(param[1]) - 10.;
	nlow[2] = double(param[2]) - 10.;
	nlow[3] = max(1.,double(param[3]) - 10.);
	nlow[4] = double(param[4]) - 10.;
	nlow[5] = max(1.,double(param[5]) - 10.);
	nlow[6] = double(param[6]) - 10.;
      
	*/
      
   
	vint parause(numberions[step]*numparaion,0);
	file.close();

	if (dbglvl >= 1){
	  for (int i = 0; i < numberions[step]*numparaion; i++){
	    cout << "param[" << i << "]= " << param[i] << endl;
	  }
	}
	double ymod;
	vdouble dyda(numberions[step]*numparaion,0.);

	if (dbglvl >= 1){
	  cout << "numberions = " << numberions[step] << endl;
	}
	for (int it = 0;it < 2;it++){
	  //	for (int l = 0; l < numberions[step];l++){


	  for (int m = numberionsfixed[step]; m < numberions[step]; m++){
	    for (int n = 0;n < numparaion; n++){

	      for (int k = 0; k < numberions[step]*numparaion;k++){
		parause[k] = 0;
	      }

	      parause[(m*numparaion)+n] = 1;
	    
	      if (dbglvl >= 1){
		//		cout << thisprogram << "numberions : " << numberions[step] << "   numberparam : " << numberions[step]*numparaion << endl;
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
	      maxlifit(et_mat,param,nlow,nhigh,parause,covar,alpha,merit,func);
	      //	maxlifit(testdata,param,nlow,nhigh,parause,covar,alpha,merit,func);
	      if (dbglvl >= 1){
		cout << thisprogram << "leaving maxlifit" << endl;
	      }
	    
	    }
	  }
	}
	
  

	for (int i = 0; i < numberions[step]; i++){
	  for (int k = 0; k < numparaion; k++){
	    cout << thisprogram << "param[" << (i*numparaion)+k << "]= " << param[(i*numparaion)+k] << endl;
	  }
	}


	for (int i = 0;i < numberions[step]*numparaion;i++){
	  parause[i] = 1;
	}
      
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




	cout << "Y-Cut" << endl;
	for (int i = 0;i < 9;i++){
	  ymod = func(int(param[1]),(int(param[2])+i-4),param,dyda,numberions[step]*numparaion,numberions[step],parause,range);
	  cout << thisprogram << "ymod = " << ymod << endl;
	  cout << thisprogram << "y[" << (int(param[2])+i-4) << "][" << int(param[1]) << "] = " << et_mat[(int(param[2])+i-4)][int(param[1])] << endl;
	  //cout << thisprogram << "y[" << (int(param[2])+i-4) << "][" << int(param[1]) << "] = " << testdata[(int(param[2])+i-4)][int(param[1])] << endl;

	}
	cout << endl;
      
	cout << "X-Cut" << endl;
	for (int i = 0;i < 9;i++){
	  ymod = func((int(param[1])+i-4),int(param[2]),param,dyda,numberions[step]*numparaion,numberions[step],parause,range);
	  cout << thisprogram << "ymod = " << ymod << endl;
	  cout << thisprogram << "y[" << int(param[2]) << "][" << (int(param[1])+i-4) << "] = " << et_mat[int(param[2])][int(param[1]+i-4)] << endl;
	  //cout << thisprogram << "y[" << int(param[2]) << "][" << (int(param[1])+i-4) << "] = " << testdata[int(param[2])][int(param[1]+i-4)] << endl;

	}
	cout << endl;
    
	for (int i = 0;i < numberions[step]*numparaion;i++){
	  parause[i] = 0;
	}
      
	string filename=("mod_data.dat");
  
	ofstream file(filename.c_str());

	file << "Y-Cut" << endl;
	file << "9" << endl;
	for (int i = 0;i < 9;i++){
	  ymod = func(int(param[1]),(int(param[2])+i-4),param,dyda,numberions[step]*numparaion,numberions[step],parause,range);
	  file  << ymod << "  " << et_mat[(int(param[2])+i-4)][int(param[1])] << endl;
	}
	file << endl;

	file << "X-Cut" << endl;
	file << "9" << endl;
	for (int i = 0;i < 9;i++){
	  ymod = func((int(param[1])+i-4),int(param[2]),param,dyda,numberions[step]*numparaion,numberions[step],parause,range);
	  file  << ymod << "  " << et_mat[int(param[2])][int(param[1]+i-4)] << endl;
	}
	file << endl;


	file.close();


	string filename2=("diff.dat");
  
	ofstream file22(filename2.c_str());

	int diffrange = 9;

	file22  << XDIM << " " << YDIM <<  endl;
	for (int i = 0;i < XDIM;i++){
	  for (int j = 0;j < YDIM;j++){
	    ymod = func(i,j,param,dyda,numberions[step]*numparaion,numberions[step],parause,range);
	    //if (ymod) {
	    file22 << (ymod-et_mat[j][i])<< "  "; 
	    /*}
	      else{
	      file22 << "0" << "  "; 
	      }
	    */
	  }
	  file22 << endl;
	}

	file22.close();
      

	string filename3=("testdata.dat");
  
	ofstream file23(filename3.c_str());

	file23  << XDIM << " " << YDIM << endl;
	for (int i = 0;i < XDIM;i++){
	  for (int j = 0;j < YDIM;j++){
	    ymod = func(i,j,param,dyda,numberions[step]*numparaion,numberions[step],parause,range);
	    file23 << ymod << "  "; 
	  }
	  file23 << endl;
	}

	file23.close();
     
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
