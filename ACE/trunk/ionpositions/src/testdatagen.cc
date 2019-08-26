//  ************************************************
//  *                                              *
//  * file:      testdatagen.cc                    *
//  *                                              *
//  * author:                                      *
//  *            Lars Berger                       *
//  *            <berger@physik.uni-kiel.de>       *
//  *                                              *
//  * version:   1.00                              *
//  *                                              *
//  * rev. date: 21.11.2006                        *
//  *                                              *
//  * Generates synthetic data                     *
//  *                                              *
//  *                                              *
//  *                                              *
//  *                                              *
//  *                                              *
//  ************************************************/

#include "testdatagen.h"


using namespace std;

long idum = (-168990);
vdouble normgauss;


int main ()
{
  //Variable declaration
  int dim=1000;
  const int numparaion = 7;
  ion iondat;
  dbgvector<vion> ionsdat(dim,vion(0));
  
  string tmp1=""; // Dummies 
  int tmp2=0; // Dummies
  double tmp4=0; // Dummies
  double tmp3=0;
  double tmp5 = 0.;
  double tmp6 = 0.;
  double tmp7 = 0.;
  double tmp8 = 0.;
  double tmp9 = 0.;
  double tmp10 = 0.;
  double tmp11 = 0.;
  double tmp12 = 0.;
  string tmp13 = "";

  // Variables for datageneration
  
  vint numberions(dim,0);

  mdouble gauss;

  mdouble data(ydim,xdim);

  vdouble auxparagaus; // used to initialise para
  
  mdouble paragaus; // parameters of Gausian distribution for each ion 

  //  bool (*function) (int ,int , vdouble &, vdouble &, double *, vdouble &, int , int) = twodgauss4sig;
    
  // parameterfile is read
  
  string filenameergin; 
  filenameergin="./o8n7c6para30_1000.dat";
  ifstream fileergin(filenameergin.c_str());

  for (int i = 0; i < dim; i++){
    fileergin >> tmp1 >> tmp1 >> tmp1 >> tmp1 >> tmp1 >> numberions[i];
    cout << "numberions[" << i << "] = "<< numberions[i] << endl;
    fileergin >> tmp1 >> tmp1 >> tmp1 >> tmp1 >> tmp1 >> tmp1 >> tmp1 >> tmp1 >> tmp1 >> tmp1 >> tmp1;
    tmp2 = 0; 
    while (tmp2 < numberions[i]){
      fileergin >> tmp1 >> tmp3 >> tmp4 >> tmp5 >> tmp6 >> tmp7 >> tmp8 >> tmp9 >> tmp10 >> tmp11 >> tmp12; 
      iondat = ion(0.);
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

  // Loop for Datageneration
  
  string filenamedata="o8n7c6_data30_1000.dat";
  ofstream file2(filenamedata.c_str());
  file2 << "ACE/SWICS counts for day(s) 2007_029_17.57.12 - 2007_029_18.57.12" << std::endl;
  file2 << "Cycles  : 5" << std::endl;
  file2 << "Aspang  : 5.75" << std::endl;
  file2 << "SWSpeed : 649.35" << std::endl;
  file2 << "*****" << std::endl;

  cout << "opening " << filenamedata << endl;

  for (int step = 0;step < dim; step++){
    //    idum -= step;
    
    for (int i = 0; i < ydim; i++){
      for (int j = 0; j < xdim; j++){
	data[i][j] = 0;
      }
    }
    
    vdouble sum(numberions[step],0.);
    vint nreal(numberions[step],0);
    vdouble param(numberions[step]*numparaion,0.);
    vdouble paragauss(numparaion,0.);

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
      param[A] = tmp4; // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

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
    
    cout << "step : " << step << endl;
    
    for (int ionnr=0;ionnr<numberions[step];ionnr++){
      mdouble iondistr(ydim,xdim);
      vdouble dyda(numparaion,0.);
      vint ia(numparaion,1);
      double testsum=0.;
      double testsum2=0.;
      // parameters for single ion are created
      for (int i=0;i<numparaion;i++){
	paragauss[i]=param[(ionnr*numparaion)+i];
      }
      paragauss[0]=1.;
      
      // distribution for ion ionnr is calculated

      for (int n = 0; n < ydim; n++){
	for (int o = 0; o < xdim; o++){
	  iondistr[n][o] = twodgauss4sig(o,n,paragauss,dyda,numparaion,1,ia,3.);
	  testsum+=iondistr[n][o];
	}
      }
      for (int n = 0; n < ydim; n++){
	for (int o = 0; o < xdim; o++){
	  iondistr[n][o] = iondistr[n][o]/testsum;
	  testsum2+=iondistr[n][o];
	}
      }
      
      //cout << "ion " << ionnr << " : sum1 = " << testsum << " , sum2 = " << testsum2 << endl;
      vdouble ran(int(param[ionnr*7]),0.);
      ran_urand(ran);

      for (int count=0;count < param[ionnr*7];count++){
	//	cout << "randomnumber = " << ran << endl;
	for (int n = 0; n < ydim; n++){
	  for (int o = 0; o < xdim; o++){
	    if (ran[count]<=iondistr[n][o]){
	      data[n][o]+=1;
	      ran[count]=3.;
	    }
	    else{
	      ran[count]-=iondistr[n][o];
	    }
	  }
	  
	}
      }
      int sumdata=0;
      for (int n = 0; n < ydim; n++){
	for (int o = 0; o < xdim; o++){
	  sumdata+=int(data[n][o]);
	}
      }
      cout << "sumdata = " << sumdata << endl;
    }
    file2 << ydim << "   " << xdim << endl;
    for (int i = 0; i < ydim; i++){
      for (int k = 0; k < xdim; k++){
	file2 << data[i][k] << "  ";
      }
      file2 << endl;
    }



    // End of data generation.
    
 
    
    
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
