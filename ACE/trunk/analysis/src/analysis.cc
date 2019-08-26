//  ************************************************
//  *                                              *
//  * file:      analysis.cpp                      *
//  *                                              *
//  * author:                                      *
//  *            Lars Berger                       *
//  *            <berger@physik.uni-kiel.de>       *
//  *                                              *
//  * version:   1.00                              *
//  *                                              *
//  * rev. date: 28.02.2006                        *
//  *                                              *
//  *                                              *
//  *                                              *
//  *                                              *
//  *                                              *
//  *                                              *
//  *                                              *
//  ************************************************/

#include "analysis.h"

int XDIM = 512;
int YDIM = 128;

using namespace std;

int main()
{
  // Variable declaration

  const int numparaion = 7;

  string tmp1 = ""; // Dummies 

  int tmp2 = 0; // Dummies

  double tmp3 = 0.;
  double tmp4 = 0.; // Dummies
  double tmp5 = 0.;
  double tmp6 = 0.;
  double tmp7 = 0.;
  double tmp8 = 0.;

  double range = 3.;
  double merit = 0.;

  string thisprogram = "main : ";
  int dbglvl = 1;

  ion iondat;
  
  vint numberions(60,0); // Number of Ions to fit for Each E/q step
  mdouble et_mat_in;
  mdouble et_mat_tmp;
  mdouble et_mat;
  mdouble alpha;
  mdouble covar;
  
  double (*func) (int ,int , vdouble &, vdouble &, int , int, vint &, double) = twodgauss4sig;  // Function used for fitting
  
  // Initialization
  
  et_mat_in = mdouble(YDIM*2,XDIM*2);
  et_mat_tmp = mdouble(YDIM*2,XDIM);
  et_mat= mdouble(YDIM,XDIM);  
  
  if (dbglvl >= 1){
    cout << thisprogram << "opened ion_para.dat" << endl;
  }

  // Open files for in and output
  string filenamepara = "ion_para.dat";
  ifstream filepara(filenamepara.c_str());

  string filenameerg = "results.dat";
  ofstream fileerg(filenameerg.c_str());

  //string filename=("/home/ivar/berger/projects/SWICS/trunk/databinning/axlv2_sumwhol_asp_06.0-07.0_bin.dat");
  string filename=("/data/ivar/work/VerhältnisseRobert/america/runs/heidelberg/2005001_12min/axlv2_et_slices_001_956.dat");
  cout << thisprogram << "opened " << filename << endl;
  
  ifstream file2(filename.c_str());

  const char* format = "%10.2f%10.2f\n";
  char line[30];
  string line2;
  
  // Finish reading ion_pos.dat
  
  for (int step = 0; step < 60;step++){
    
    filepara >> tmp1 >> tmp1 >> tmp1 >> tmp1 >> tmp1 >> numberions[step];
    vdouble nlow(numberions[step]*numparaion,0.),nhigh(numberions[step]*numparaion,0.);
    vdouble param(numberions[step]*numparaion,double(0));
    vstring names(numberions[step]);
    vdouble velocity(numberions[step]);
    
    filepara >> tmp1 >> tmp1 >> tmp1 >> tmp1 >> tmp1 >> tmp1 >> tmp1 >> tmp1 >> tmp1 >> tmp1 >> tmp1;
    for (int i = 0; i < numberions[step]; i++){
      filepara >> tmp1 ;
      names[i] = tmp1;
      for (int k = 1; k < numparaion; k++){
	filepara >> param[(i*numparaion)+k];
      }
      filepara >> velocity[i];;
      filepara >> tmp1 >> tmp1 >> tmp1;
    }

    fileerg << "Step : " << step+1 << "  Numberions : " << numberions[step] << endl;
    fileerg << "Ion        Velocity" << endl;


 
    /* 
    // For already binned data
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
    */
    //for (int l = 0; l < (step+1); l++){
    file2 >> tmp1 >> tmp1 >> tmp1 >> tmp1 >> tmp1 >> tmp1 >> tmp1;
    cout << tmp1 << endl;
    file2 >> tmp1 >> tmp1;
    cout << tmp1 << endl;
    file2 >> tmp1 >> tmp1 >> tmp1 >> tmp1;
    cout << tmp1 << endl;
    file2 >> tmp1 >> tmp1;
    cout << tmp1 << endl;
    //alternative for already binned data
    //file2 >> tmp2 >> tmp2;
    //	cout << tmp2 << endl;
    for (int i = 0; i < XDIM*2; i++){
      for (int k = 0; k < YDIM*2; k++){
	file2 >> tmp3;
	et_mat_in[k][i] = double(tmp3);
      }
    }
    //}
    for (int i = 1; i < XDIM; i++){
      for (int k = 0; k < YDIM*2; k++){
	et_mat_tmp[k][i] = et_mat_in[k][i*2]+et_mat_in[k][(i*2)-1];
      }
    }

    for (int i = 0; i < XDIM; i++){
      for (int k = 1; k < YDIM; k++){
	et_mat[k][i] = et_mat_tmp[(k*2)][i]+et_mat_tmp[(k*2)-1][i];
      }
    }

 
    for (int i = 0; i < XDIM; i++){
      et_mat[0][i] = 0.;
    }

    if (dbglvl >= 1){
      cout << thisprogram << "Finished reading data, step " << step + 1 << endl;
    }

    if (numberions[step] > 0){
      
      
      alpha = mdouble(numberions[step],numberions[step]);
      covar = mdouble(numberions[step],numberions[step]);

      for (int i = 0; i < numberions[step];i++){
	param[(i*numparaion)] = 50;
	nhigh[(i*numparaion)] = param[(i*numparaion)] * 1000000.;
	nlow[(i*numparaion)] = 0.;
	  
      }
      
      vint parause(numberions[step]*numparaion,0);

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

	for (int m = 0; m < numberions[step]; m++){

	  for (int k = 0; k < numberions[step]*numparaion;k++){
	    parause[k] = 0;
	  }

	  parause[(m*numparaion)] = 1;
	    
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
	  maxlifit(et_mat,param,nlow,nhigh,parause,covar,alpha,merit,func);
	  //	maxlifit(testdata,param,nlow,nhigh,parause,covar,alpha,merit,func);
	  if (dbglvl >= 1){
	    cout << thisprogram << "leaving maxlifit" << endl;
	  }

	  if (dbglvl >= 1){
	    cout << thisprogram << "param : " << endl;
	      
	    for (int i = 0; i < int(param.size()); i++){
	      if (parause[i]){
		cout << thisprogram << param[i] << "  " << nlow[i] << "  " << nhigh[i] << endl;
	      }
	    }
	  }
	}
      }
      
	
      for (int i = 0; i < numberions[step]; i++){
	sprintf(line,format,param[(i*numparaion)],velocity[i]);
	line2 = line;
	fileerg << line2;
      }
      
      for (int i = 0; i < numberions[step]; i++){
	for (int k = 0; k < numparaion; k++){
	  cout << thisprogram << "param[" << (i)+k << "]= " << param[(i)+k] << endl;
	}
      }
      
      for (int i = 0;i < numberions[step];i++){
	parause[i] = 1;
      }
      
      
    
      for (int i = 0;i < numberions[step];i++){
	parause[i] = 0;
	cout << param[(i*numparaion)] << endl;
      }
      
      string filename6=("mod_data.dat");
  
      ofstream file(filename6.c_str());

      file << "Y-Cut" << endl;
      file << "9" << endl;
      for (int i = 0;i < 9;i++){
	ymod = func(int(param[1]),(int(param[2])+i-4),param,dyda,numberions[step],numberions[step],parause,range);
	file  << ymod << "  " << et_mat[(int(param[2])+i-4)][int(param[1])] << endl;
      }
      file << endl;

      file << "X-Cut" << endl;
      file << "9" << endl;
      for (int i = 0;i < 9;i++){
	ymod = func((int(param[1])+i-4),int(param[2]),param,dyda,numberions[step],numberions[step],parause,range);
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
	  ymod = func(i,j,param,dyda,numberions[step],numberions[step],parause,range);
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
	  ymod = func(i,j,param,dyda,numberions[step],numberions[step],parause,range);
	  file23 << ymod << "  "; 
	}
	file23 << endl;
      }

      file23.close();
	
    }
  
  }
  filepara.close();
  if (dbglvl >= 1){
    cout << thisprogram << "closed ion_para.dat" << endl;
  }
  file2.close();


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
