#include "analyse_data.h"

/*
  Revision controlled by SVN:
  $Id: analyse_data.cc 8033 2009-11-23 14:28:46Z berger $
*/

int XDIM = 512;
int YDIM = 128;
int DIM=60;

using namespace std;

//int main()
int main(int argc, char* argv[])
{
  // Variable declaration

  const int numparaion = 7;
  const double sig0 = 2.;
  string tmp1; // Dummies 
  int tmp2; // Dummies
  double tmp4; // Dummies
  double tmp3;
  double merit = 0.;

  char version[]="$Id: analyse_data.cc 8033 2009-11-23 14:28:46Z berger $";
  string thisprogram = "analyse_data : ";
  string filenamelist ="";
  //string filenamedata ="";
  string filenamedata=argv[1];
  string filenameergin = "";
  string filenameionpos= "";
  string filenameerg = "";

  int dbglvl = 1;

  ion iondat;
  
  vint numberions(DIM,0); // Complete number of Ions for Each E/q step
  vint numberparam(DIM,0); // Number of Parameters for Each E/q step
  vector<vion> ionsdat(DIM,vion(0));
  mdouble et_mat;
  mdouble alpha;
  mdouble covar;
  
  double (*func) (int ,int , vdouble &, vdouble &, int , int, vint &, double) = twodgauss4sig;  // Function used for fitting
  
  char line[200];
  string line2;
  const char* format = "%-10s%8.2f%8.2f%8.2f%8.2f%8.2f%8.2f%8.2f%8.2f%8.2f%16.2f%12.2f%12.2f";

  
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

  printf("analyse_data -I- analyses ACE/SWICS Lv0 data. produces Lv1 data,\n");
  printf("          built %s %s\n",__DATE__,__TIME__);
  printf("          from %s\n",version);

  // Read ion_pos.in -> several settings are done
  
  string filenameionposin = "analyse_data.in";
  cout << "Reading " << filenameionposin << endl;
  ifstream fileionposin(filenameionposin.c_str());

  // name of data file is read
  fileionposin >> filenamelist;
  getline(fileionposin,tmp13);
  cout << "filelist : " << filenamelist << endl;

  // local dbglvl is set
  fileionposin >> dbglvl;
  getline(fileionposin,tmp13);
  cout << "dbglvl : " << dbglvl << endl;

  // lower and upper limit for steps to be fitted
  fileionposin >> lowerstep;
  getline(fileionposin,tmp13);
  cout << "lowerstep = " << lowerstep << endl;

  fileionposin >> upperstep;
  getline(fileionposin,tmp13);
  cout << "upperstep = " << upperstep << endl;

  fileionposin >> fitmode;
  getline(fileionposin,tmp13);
  
  fileionposin.close();

  if (dbglvl >= 1){
    cout << "Finished reading analyse_data.in" << endl;
  }
  
  // Read parameter file "ion_para.dat" (name comes from "ion_pos.in"). These ions are beeing held fixed during the fitting
  filenameergin="ion_para.dat";
  cout << "Reading ion positions from " << filenameergin << endl;
  //  filenameergin="./paramfiles/testdatapara.dat";
  ifstream fileergin(filenameergin.c_str());

  for (int i = 0; i < DIM; i++){
    fileergin >> tmp1 >> tmp1 >> tmp1 >> tmp1 >> tmp1 >> numberions[i];
    //    cout << "numberions[" << i << "] = "<< numberions[i] << endl;
    fileergin >> tmp1 >> tmp1 >> tmp1 >> tmp1 >> tmp1 >> tmp1 >> tmp1 >> tmp1 >> tmp1 >> tmp1 >> tmp1;
    tmp2 = 0; 
    while (tmp2 < numberions[i]){
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
  cout << "Finished reading ion positions from " << filenameergin << endl;
  // Finish reading ion_para.dat

  
  //int numfiles=0;
  //ifstream infilelist(filenamelist.c_str());
  //infilelist >> numfiles;
  //for (int filenr=0;filenr < numfiles;filenr++){
  for (int nf=0;nf<1;nf++){
    //infilelist >> filenamedata;
    filenameerg="erg_"+filenamedata;

    // opening file for output (it is closed after mainloop)
    ifstream datain(filenamedata.c_str());
    if (check_data_file(datain)){
      datain.close();
      ifstream datain(filenamedata.c_str());
      ofstream fileerg(filenameerg.c_str());
      //    ofstream filechisq("chisq.dat");
      copy_header(datain,fileerg);
      for (int i=0;i < lowerstep-1;i++){
	read_data(datain,1,et_mat,0);
      }
      cout << "opening " << filenameerg << endl;

      // mainloop where fitting is done starts here 
      cout << thisprogram << "fitting to " << filenamedata << endl;
      for (int step = lowerstep-1; step < upperstep;step++){

	fileerg << "Step : " << step+1 << "  Numberions = " << numberions[step] << endl;
	fileerg << "Name          xpos    ypos   sigxp   sigxm   sigyp   sigym    vel     mass    charge         fiterg     normerg  signormerg" << endl;
    
	if (numberions[step] > 0){
      
	  read_data(datain,1,et_mat,0);
	  // et_matrix is filtered (DCR and noise is cut away!)
	  filter_data(step,et_mat);

	  if (dbglvl >= 1){
	    cout << thisprogram << "Finished reading data" << endl;
	  }
      
	  alpha = mdouble(numberions[step]*numparaion,numberions[step]*numparaion);
	  covar = mdouble(numberions[step]*numparaion,numberions[step]*numparaion);
	  vdouble param(numberions[step]*numparaion,sig0);

	  // nlow and nhigh are obsolete and not used in fitting.cc but for they are needed in ion_pos.cc are left into fitting.cc 
	  vdouble nlow(numberions[step]*numparaion,0.);
	  vdouble nhigh(numberions[step]*numparaion,0.);


	  // loop : parameters of ions held fixed are read in

	  for (int i = 0; i < numberions[step];i++){
	    int A = (i*numparaion);
	    int xpos = (i*numparaion)+1;
	    int ypos = (i*numparaion)+2;
	    int sigxp = (i*numparaion)+3;
	    int sigxm = (i*numparaion)+4;
	    int sigyp = (i*numparaion)+5;
	    int sigym = (i*numparaion)+6;

	    ionsdat[step][i].get_peakhigh(tmp4);
	    tmp4 = tmp4;
	    param[A] = tmp4;
	    if (et_mat[int(param[ypos])][int(param[xpos])]==0.){
	      param[A] = 0.5;
	    }
	    else {
	      param[A] = et_mat[int(param[ypos])][int(param[xpos])]*10.;
	    }
	    ionsdat[step][i].get_tpos(tmp4);
	    param[xpos] = tmp4;
       
	    ionsdat[step][i].get_epos(tmp4);
	    param[ypos] = tmp4;
	  
	    ionsdat[step][i].get_sigtp(tmp4);
	    param[sigxp] = tmp4;
	  
	    ionsdat[step][i].get_sigtm(tmp4);
	    param[sigxm] = tmp4;
	  
	    ionsdat[step][i].get_sigep(tmp4);
	    param[sigyp] = tmp4;
	  
	    ionsdat[step][i].get_sigem(tmp4);
	    param[sigym] = tmp4;
	  
	  }
	
	  boxrates(et_mat,param);
	
	  vint paraorder(numberions[step],0);
	
	  paraorder=sort(param);
	  /*
	    cout << thisprogram << "paraorder = ";
	    for (int m=0;m<numberions[step];m++){
	    cout << paraorder[m] << ",";
	    }
	    cout << endl;
	  */
	  vint parause(numberions[step]*numparaion,0);

	  if (dbglvl >= 1){
	    for (int i = 0; i < numberions[step]*numparaion; i++){
	      cout << "param[" << i << "]= " << param[i] << endl;
	    }
	  }
	  vdouble dyda(numberions[step]*numparaion,0.);

	  if (dbglvl >= 1){
	    cout << "numberions = " << numberions[step] << endl;
	    cout << thisprogram << "step " << step+1 << endl;
	  }
	  for (int it = 0;it < 2;it++){                                  	   // loop : number of iterations
	    if (it==2){
	      fitmode=1;
	    }
	    if (fitmode==0){
	      for (int m = 0; m < numberions[step]; m++){  // loop : number of ions to be fitted
		for (int k = 0; k < numberions[step];k++){
		  parause[k*numparaion] = 0;
		}
	      
		parause[paraorder[m]*numparaion]=1;

		// used parameters are displayed
		if (dbglvl >= 1){
		  for (int l=0;l<numberions[step]*numparaion;l++){
		    if (parause[l]){
		      cout << thisprogram << "fitting param[" << l << "]" << endl;
		    }
		  }
		}
		if (dbglvl >= 2){
		  for (int o = 0; o < numberions[step]*numparaion;o++){
		    if (parause[o]){
		      cout << thisprogram << "parause[" << o << "] = " << parause[o] << endl;
		    }
		  }
		}
	    
		if (dbglvl >= 1){
		  cout << thisprogram << "calling maxlifit" << endl;
		}
		while (!maxlifit(et_mat,param,nlow,nhigh,parause,covar,alpha,merit,func)){
		  if (dbglvl>=1){
		    cout << thisprogram << "calling maxlifit" << endl;
		  }
		}
		// fitted parameters are displayed
		if (dbglvl >= 2){
		  for (int l=0;l<numberions[step]*numparaion;l++){
		    if (parause[l]){
		      cout << thisprogram << "param[" << l << "] = " << param[l] << endl;
		    }
		  }
		}
		if (dbglvl >= 1){
		  cout << thisprogram << "leaving maxlifit" << endl;
		}
	      }
	    }
	    if (fitmode==1){
	      for (int k = 0; k < numberions[step]*numparaion;k++){
		parause[k] = 0;
	      }
	      for (int m = 0; m < numberions[step]; m++){  // loop : number of ions to be fitted
		parause[(m*numparaion)] = 1;                             // parameter to be fitted is set
	      }
	      // used parameters are displayed
	      if (dbglvl >= 1){
		for (int l=0;l<numberions[step]*numparaion;l++){
		  if (parause[l]){
		    cout << thisprogram << "fitting param[" << l << "]" << endl;
		  }
		}
	      }
	      if (dbglvl >= 2){
		for (int m = 0; m < numberions[step]*numparaion;m++){
		  if (parause[m]){
		    cout << thisprogram << "parause[" << m << "] = " << parause[m] << endl;
		  }
		}
	      }
	    
	      if (dbglvl >= 1){
		cout << thisprogram << "calling maxlifit" << endl;
	      }
	      while (!maxlifit(et_mat,param,nlow,nhigh,parause,covar,alpha,merit,func)){
		if (dbglvl>=1){
		  cout << thisprogram << "calling maxlifit" << endl;
		}
	      }
	      // fitted parameters are displayed
	      if (dbglvl >= 1){
		for (int l=0;l<numberions[step]*numparaion;l++){
		  if (parause[l]){
		    cout << thisprogram << "param[" << l << "] = " << param[l] << endl;
		  }
		}
	      }
	    }
	  }

	  vdouble normparam(numberions[step]*numparaion,0.);

	  if (dbglvl >= 1){
	    cout << thisprogram << "entering normfit" << endl;
	  }
	  normparam=normfit(param,et_mat,func);
	  if (dbglvl >= 1){
	    cout << thisprogram << "leaving normfit" << endl;
	  }
	  if (dbglvl >= 1){
	    cout << thisprogram << "calculate errors" << endl;
	  }
	  vdouble errors(normparam.size()/7,0.);
	  errors=calcerrors(et_mat,normparam,func);
	  if (dbglvl >= 1){
	    cout << thisprogram << "finished calculate errors" << endl;
	  }


	  //	param=normparam;
	
	  // fiiting results are written to stdout
	  if (dbglvl >= 1){
	    for (int i = 0; i < numberions[step]; i++){
	      for (int k = 0; k < numparaion; k++){
		if (k==0){
		  cout << thisprogram << "param[" << (i*numparaion)+k << "]= " << param[(i*numparaion)+k] << " +- " << errors[i] << endl;
		}
		else{
		  cout << thisprogram << "param[" << (i*numparaion)+k << "]= " << param[(i*numparaion)+k] << endl;
		}
	      }
	    }
	  }
	  // fitting results are written to outputfile 

	  for (int i = 0; i < numberions[step]; i++){
	    line2 = "";
	    ionsdat[step][i].get_name(tmp1);
	    ionsdat[step][i].get_velocity(tmp5);
	    ionsdat[step][i].get_mass(tmp6);
	    ionsdat[step][i].get_charge(tmp7);
	    sprintf(line,format,tmp1.c_str(),param[(i*numparaion)+1],param[(i*numparaion)+2],param[(i*numparaion)+3],param[(i*numparaion)+4],param[(i*numparaion)+5],param[(i*numparaion)+6],tmp5,tmp6,tmp7,param[(i*numparaion)],normparam[(i*numparaion)],errors[i]);
	    line2 = line;
	    fileerg << line2 << endl;
	  }

	  // all parameters are set to "nofit"

	  for (int i = 0;i < numberions[step]*numparaion;i++){
	    parause[i] = 0;
	  }
	  /*
	    for (int ion=0;ion < normparam.size()/7;ion++){
	    string name;
	    ionsdat[step][ion].get_name(name);
	    filechisq << name << " " << normparam[ion*7] << " +-" << errors[ion] << endl;
	    }
	  */
	}
  
      }
      fileerg.close();
    //    filechisq.close();
      cout << "Closing " << filenameerg << endl;
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
