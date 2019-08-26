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

#include "errordatagen.h"


using namespace std;

long idum = (-168990);
vdouble normgauss;


int main ()
{
  //Variable declaration
  //  int dim=1000;
  const int numparaion = 7;
  ion iondat;
  vion ionsdat(vion(0));
  const char* format = "error_data_%s_step%i_%.0f_%.1f_%s.dat";
  
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
  
  int numberions;

  mdouble gauss;

  mdouble data(ydim,xdim);

  vdouble auxparagaus; // used to initialise para
  
  mdouble paragaus; // parameters of Gausian distribution for each ion 

  //  bool (*function) (int ,int , vdouble &, vdouble &, double *, vdouble &, int , int) = twodgauss4sig;
    

  string listname="./paralist.in";
  ifstream filelistin(listname.c_str());
  int numberparafiles=0;
  filelistin >> tmp3;
  numberparafiles=tmp3;
  
  for (int file=0;file < numberparafiles;file++){

    // parameterfile is read
  
    string filenameergin; 
    filelistin >> tmp1;
    filenameergin=tmp1;
    ifstream fileergin(filenameergin.c_str());
    // read header 
    fileergin >> tmp1;
    string ionname=tmp1;
    fileergin >> tmp2;
    int ionstep=tmp2;
    fileergin >> tmp2;
    int ionnumbersteps=tmp2;
    fileergin >> tmp5;
    double ionpeakh=tmp5;
    fileergin >> tmp5;
    double ionfrac=tmp5;
    fileergin >> tmp1;

    fileergin >> tmp1 >> tmp1 >> tmp1 >> tmp1 >> tmp1 >> numberions;
    cout << "numberions = "<< numberions << endl;
    fileergin >> tmp1 >> tmp1 >> tmp1 >> tmp1 >> tmp1 >> tmp1 >> tmp1 >> tmp1 >> tmp1 >> tmp1 >> tmp1;
    tmp2 = 0; 
    while (tmp2 < numberions){
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
      ionsdat.push_back(iondat);
    }

    // Loop for Datageneration
  

    for (int ion = 1;ion <numberions;ion++){
      string name;
      ionsdat[ion].get_name(name);
      char tmpfilenamedata[200];
      string filenamedata;
      sprintf(tmpfilenamedata,format,ionname.c_str(),ionstep,ionpeakh,ionfrac,name.c_str());
      //      string filenamedata="error_data_"+string(ionname)+"_step"+string(ionstep)+"_"+string(ionpeakh)+"_"+string(ionfrac)+"_"+name+".dat";
      filenamedata=tmpfilenamedata;
      ofstream file2(filenamedata.c_str());
      file2 << name << std::endl;  
      file2 << filenameergin << std::endl;
      file2 << "*****" << std::endl;

      cout << "opening " << filenamedata << endl;

      vdouble param(2*numparaion,0.);
      vdouble paragauss(2*numparaion,0.);

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

      for (int step = 0;step < dim; step++){
	//    idum -= step;
	for (int i = 0; i < ydim; i++){
	  for (int j = 0; j < xdim; j++){
	    data[i][j] = 0;
	  }
	}
    
	vdouble sum(2,0.);
    
	//	cout << "step : " << step << endl;
    
	for (int ionnr=0;ionnr<2;ionnr++){
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
	  //	  cout << "testsum = " << testsum << endl;

	  for (int n = 0; n < ydim; n++){
	    for (int o = 0; o < xdim; o++){
	      iondistr[n][o] = iondistr[n][o]/testsum;
	      testsum2+=iondistr[n][o];
	    }
	  }
	  //	  cout << "testsum2 = " << testsum2 << endl;
      
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
	  //	  cout << "sumdata = " << sumdata << endl;
	} 
	file2 << ydim << "   " << xdim << endl;
	for (int i = 0; i < ydim; i++){
	  for (int k = 0; k < xdim; k++){
	    file2 << data[i][k] << "  ";
	  }
	  file2 << endl;
      
	}

      }
      file2.close();

      // End of data generation.
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
