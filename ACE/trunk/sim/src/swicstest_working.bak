//  ************************************************
//  *                                              *
//  * file:      swicstest.cpp                     *
//  *                                              *
//  * author:                                      *
//  *            Lars Berger                       *
//  *            <berger@physik.uni-kiel.de>       *
//  *                                              *
//  * version:   1.00                              *
//  *                                              *
//  * rev. date: 17.02.2005                        *
//  *                                              *
//  * Generates synthetic data and tests analyse-  *
//  * method.                                      *
//  *                                              *
//  *                                              *
//  *                                              *
//  *                                              *
//  ************************************************/

#include "swicstest.h"


using namespace std;

long idum = (-168990);
vector<double> normgauss;


int main ()
{
  //Variable deklaration
  

  int numberions = 2;
  int numparagaus = (5 * numberions) + 1; // determines number of ions. 
  // 1 parameter Background 
  // 5 parameters per ion : Amplitude,TO,SigmaT,E0,SigmaT
  
  // parameter of vdf1 and vdf2
  
  double merit0;
  double summe;
  double kappa1;           
  double kappa2;           
  double dens1;            
  double dens2;            
  double vth1;             
  double vth2;             
  double vsw1;
  double vsw2;
  double tmp;
  double tmp2;
  double tmp3;
  double a1;
  double a2;
  double b1;
  double b2;
  double x;


  // Variables for datageneration


  vector<double> auxcovar;
  vector<vector<double> > covar;
  vector<vector<double> > alpha;
  
  vector<double> sum;
  vector<double> auxmat;
  vector<vector<double> > contmat;

  vector<int> nlow;
  vector<int> nhigh;
  vector<int> nspill;
  vector<int> nreal;
  vector<int> boxrates;
  vector<int> nprob;
  vector<int> parause;
  vector<double> nspilldbl;
  vector<double> nhighdbl;
  vector<double> nlowdbl;

  vector<double> auxprob;
  vector<vector<double> > auxprob2;
  vector<vector<vector<double> > > prob;
  vector<vector<vector<double> > > sumprob;
  
  vector<int> auxbox1;
  vector<vector<int> > auxbox2;
  vector<vector<vector<int> > >  box;

  vector<vector<double> > gauss;
  vector<double> auxgauss;
    

  vector<double> auxdatadbl;
  vector<vector<double> > datadbl;
 
  for (int i = 0; i < 1024; i++){
    auxdatadbl.push_back(0.);
  }
  for (int i = 0; i < 256; i++){
    datadbl.push_back(auxdatadbl);
  }

  for (int i = 0; i < 1024; i++){
    auxgauss.push_back(0.);
  }
  for (int i = 0; i < 256; i++){
    gauss.push_back(auxgauss);
  }
  

  vector<double> auxparagaus; // used to initialise para
  vector<int> auxdata1; // used to initialize data
  vector<vector<int> > auxdata2; //used to initialize data
  
  vector<vector<double> > paragaus; // parameters of Gausian distribution for each ion 
  vector<vector<vector<int> > > data; // generated data
  vector<double> auxsig1;
  vector<vector<double> > auxsig2;
  vector<vector<vector<double> > > sigdata;

  vector<double> vdf1; // Velocity distribution function of ion1
  vector<double> vdf2; // Velocity distribution function of ion2

  bool (*function) (int ,int , vector<double> &, vector<double> &, double *, vector<double> &, int , int) = twodgauss;
    

  // Fuctions


  //  void fgauss(double x, vector<double> &para, double *ymod, vector<double> &dyda, int ma);
  
  // void two_gauss(double x, vector<double> &para, double *ymod, vector<double> &dyda, int ma);
 
  // void many_peaks(double x, vector<double> &para, double *ymod, vector<double> &dyda, int ma);
  
  // void test_lin(double x, vector<double> &para, double *ymod, vector<double> &dyda, int ma);
  
 // double poidev(double xm, long *idum);
  
 // double ran_1(long *idum);
  
  
  // Initialisation

  for (int i = 0;i < numberions; i++) normgauss.push_back(0.);
  for (int i = 0;i < numberions; i++) auxcovar.push_back(0.);
  for (int i = 0;i < numberions; i++) covar.push_back(auxcovar);
  for (int i = 0;i < numberions; i++) alpha.push_back(auxcovar);
  
    
  for (int i = 0;i < 1024; i++) auxprob.push_back(0.);
  for (int i = 0;i < 256 ; i++) auxprob2.push_back(auxprob);
  for (int i = 0;i < numberions; i++) prob.push_back(auxprob2);
  for (int i = 0;i < numberions; i++) sumprob.push_back(auxprob2);
  
  auxmat.push_back (0.);
  auxmat.push_back (0.);
  
  contmat.push_back(auxmat);
  contmat.push_back(auxmat);
  
  //contmat[0][0] = 8./3.;
  //contmat[0][1] = -4./3.;
  //contmat[1][0] = -4./3.;
  //contmat[1][1] = 8./3.;
  
  
  kappa1 = 2.99;           
  kappa2 = 2.99;           
  dens1 = 980000;            
  dens2 = 47000;            
  vth1 = 100;            
  vth2 = 114;             
  vsw1 = 599;
  vsw2 = 626;  
  
  for (int i = 0; i < numberions; i++){
    nspill.push_back(0);
    nreal.push_back(0);
    boxrates.push_back(0);
    sum.push_back(0.);  
    nprob.push_back(0);
    nspilldbl.push_back(0.);
    nlowdbl.push_back(0.);
    nhighdbl.push_back(0.);
    parause.push_back(1);
    nlow.push_back(0);
    nhigh.push_back(0);
      
  }
  
  for (int i = 0; i < numparagaus; i++){
    auxparagaus.push_back(0.);
  }
  for (int i = 0; i < 60; i++){
    paragaus.push_back(auxparagaus);
  }
  for (int i = 0; i < 60; i++){
    vdf1.push_back(0.);
    vdf2.push_back(0.);
  }
  
  for (int i = 0; i < 1024; i++) auxdata1.push_back(0);
  for (int i = 0; i < 256 ; i++) auxdata2.push_back(auxdata1);
  for (int i = 0; i < 60  ; i++) data.push_back(auxdata2);    
  for (int i = 0; i < 1024; i++) auxsig1.push_back(0.);
  for (int i = 0; i < 256 ; i++) auxsig2.push_back(auxsig1);
  for (int i = 0; i < 60  ; i++) sigdata.push_back(auxsig2);
  
  auxbox1.push_back(0);
  auxbox1.push_back(0);
  auxbox2.push_back(auxbox1);
  auxbox2.push_back(auxbox1);
  box.push_back(auxbox2);
  box.push_back(auxbox2);
  
  // Initialisation for testing the position and errors are considered equal
  // for each E/Q-Step. 
  
  for (int i = 0; i < 60; i++){
    paragaus[i][0] = 1. ;    // Background
    paragaus[i][1] = 100.;     // Number ion 1
    paragaus[i][2] = 200.;   // T0 ion1
    paragaus[i][3] = 5.;     // sigmaT ion1 
    paragaus[i][4] = 60.;    // Eo ion1
    paragaus[i][5] = 7.;     // sigmaE ion1
    paragaus[i][6] = 50.;    // Number ion2
    paragaus[i][7] = 205.;   // T0 ion2
    paragaus[i][8] = 8.;     // sigmaT ion2
    paragaus[i][9] = 65.;    // E0 ion2
    paragaus[i][10] = 12.;    // sigmaE ion2
  }
  
  box[0][0][0] = int(paragaus[0][2]-paragaus[0][3]);
  box[0][0][1] = int(paragaus[0][4]-paragaus[0][5]);
  box[0][1][0] = int(paragaus[0][2]+paragaus[0][3]);
  box[0][1][1] = int(paragaus[0][4]+paragaus[0][5]);
  box[1][0][0] = int(paragaus[0][7]-paragaus[0][8]);
  box[1][0][1] = int(paragaus[0][9]-paragaus[0][10]);
  box[1][1][0] = int(paragaus[0][7]+paragaus[0][8]);
  box[1][1][1] = int(paragaus[0][9]+paragaus[0][10]);
  
  
  /*
****************************************
vdfs are derived

tmp = gammln(kappa1+1.)-gammln(kappa1-.05);
tmp = exp(tmp);
a1 = 1. / pow(kappa1,.05);
a1 = a1 * dens1;
a1 = a1 / vth1;
a1 = a1 / sqrt(PI);
a1 = a1 * tmp;
b1 = kappa1*pow(vth1,2);
tmp = gammln(kappa2+1.)-gammln(kappa2-.05);
tmp = exp(tmp);
a2 = 1. / pow(kappa2,.05);
a2 = a2 * dens2;
a2 = a2 / vth2;
a2 = a2 / sqrt(PI);
a2 = a2 * tmp;    
b2 = kappa2*pow(vth2,2);

for (int i = 0; i < 60; i++){
x = (double(i) * 50.);
vdf1[i] = a1 * 1/pow((1+(pow((x-vsw1),2)/b1)),kappa1);
//    cout << vdf1[i] << endl;
//    sum+=vdf1[i];
}

//  cout << sum << endl;

  */
  
  for (int m = 0;m < 1; m++){
    idum = (-168990);
    idum -= m;
    merit0 = 0.;
    
    for (int i = 0; i < 256; i++){
      for (int j = 0; j < 1024; j++){
	data[0][i][j] = 0;
      }
    }

    // Generation of Data
    
    sum[0] = 0.;
    sum[1] = 0.;
    nreal[0] = 0;
    nreal[1] = 0;
    
    for (int i = 0; i < 256; i++){
      for (int j = 0; j < 1024 ; j++){
	tmp2 = paragaus[0][2]-double(j);
	tmp2 = tmp2 / paragaus[0][3];
	tmp2 = tmp2*tmp2;
	tmp2 = tmp2 / 2.;
	tmp3 = paragaus[0][4]-double(i);
	tmp3 = tmp3 / paragaus[0][5];
	tmp3 = tmp3*tmp3;
	tmp3 = tmp3 / 2.;
	//      cout << tmp2 << "   " << tmp3 << endl;
	tmp = exp(-tmp2)*exp(-tmp3);
	sum[0] += tmp;
      }
    }
    normgauss[0] = sum[0];
    cout << "normgauss = " << normgauss[0] << endl;
    sum[0] = paragaus[0][1] / sum[0];
    normgauss[0] = sum[0];
    
    for (int i = 0; i < 256; i++){
      for (int j = 0; j < 1024 ; j++){
	tmp2 = paragaus[0][7]-double(j);
	tmp2 = tmp2 / paragaus[0][8];
	tmp2 = tmp2*tmp2;
	tmp2 = tmp2 / 2.;
	tmp3 = paragaus[0][9]-double(i);
	tmp3 = tmp3 / paragaus[0][10];
	tmp3 = tmp3*tmp3;
	tmp3 = tmp3 / 2.;
	//      cout << tmp2 << "   " << tmp3 << endl;
	tmp = exp(-tmp2)*exp(-tmp3);
	sum[1] += tmp;
      }
    }
    sum[1] = paragaus[0][6] / sum[1];
    normgauss[1] = sum[1];

    for (int i = 0; i < 256; i++){
      for (int j = 0; j < 1024 ; j++){
	tmp2 = paragaus[0][2]-double(j);
	tmp2 = tmp2 / paragaus[0][3];
	tmp2 = tmp2*tmp2;
	tmp2 = tmp2 / 2.;
	tmp3 = paragaus[0][4]-double(i);
	tmp3 = tmp3 / paragaus[0][5];
	tmp3 = tmp3*tmp3;
	tmp3 = tmp3 / 2.;
	tmp = exp(-tmp2)*exp(-tmp3);
	tmp = sum[0] * tmp;
	//if (i >= box[0][0][1] && i <= box[0][1][1] && j >= box[0][0][0] && j <= box[0][1][0]) testsum += tmp;
	tmp = poidev(tmp,&idum);	
	data[0][i][j] += int(tmp);
	nreal[0] += int(tmp); 
      }
    }
    
    for (int i = 0; i < 256; i++){
      for (int j = 0; j < 1024 ; j++){
	tmp2 = paragaus[0][7]-double(j);
	tmp2 = tmp2 / paragaus[0][8];
	tmp2 = tmp2*tmp2;
	tmp2 = tmp2 / 2.;
	tmp3 = paragaus[0][9]-double(i);
	tmp3 = tmp3 / paragaus[0][10];
	tmp3 = tmp3*tmp3;
	tmp3 = tmp3 / 2.;
	tmp = exp(-tmp2)*exp(-tmp3);
	tmp = sum[1] * tmp;
	//    if (i >= box[1][0][1] && i <= box[1][1][1] && j >= box[1][0][0] && j <= box[1][1][0]) testsum2 += tmp;
	tmp = poidev(tmp,&idum);
	data[0][i][j] += int(tmp);
	nreal[1] += int(tmp);
      }
    }
    for (int i = 0; i < 256; i++){
      for (int j = 0; j < 1024 ; j++){
	sigdata[0][i][j] = sqrt(double(data[0][i][j]));
      }
    }			

    
    //  for (int i = 100; i < 350; i++) cout << data[0][60][i] << endl;
    cout << "N1  N2" << endl;
    cout << nreal[0] << "  " << nreal[1] << endl;
    
    // End of data generation.
    
    boxrates[0] = 0;
    boxrates[1] = 0;
    nspill[0] = 0;
    nspill[1] = 0;
    nlow[0] = 0;
    nlow[1] = 0;
    nhigh[0] = 1000000;
    nhigh[1] = 1000000;
    
    
    for (int i = box[0][0][1]; i <= box[0][1][1]; i++){
      for (int j = box[0][0][0]; j <= box[0][1][0]; j++){
	boxrates[0] += int(data[0][i][j]);
      }
    }
    
    for (int i = box[1][0][1]; i <= box[1][1][1]; i++){
      for (int j = box[1][0][0]; j <= box[1][1][0]; j++){
	boxrates[1] += int(data[0][i][j]);
      }
    }
    
    
    // Contaminationmatrix is calculated
    
    
    
    
    for (int i = 0; i < 2; i++){
      for (int k = 0;k < 2; k++){
	contmat[i][k] = 0.;
      }
    }
    
    for (int l = 0; l < 2; l++){
      for (int k = 0; k < 2; k++){
	summe = 0.;
	for (int i = 0; i < 256; i++){
	  for (int j = 0; j < 1024 ; j++){
	    tmp2 = paragaus[0][((k+1)*5)-3]-double(j);
	    tmp2 = tmp2 / paragaus[0][((k+1)*5)-2];
	    tmp2 = tmp2*tmp2;
	    tmp2 = tmp2 / 2.;
	    tmp3 = paragaus[0][((k+1)*5)-1]-double(i);
	    tmp3 = tmp3 / paragaus[0][((k+1)*5)];
	    tmp3 = tmp3*tmp3;
	    tmp3 = tmp3 / 2.;
	    //      cout << tmp2 << "   " << tmp3 << endl;
	    tmp = exp(-tmp2)*exp(-tmp3);
	    gauss[i][j] = tmp;
	    summe += tmp;
	  }
	}
	summe = 1 / summe; 
	tmp = 0.;
	for (int i = 0; i < 256; i++){
	  for (int j = 0; j < 1024 ; j++){
	    gauss[i][j] = gauss[i][j] * summe;
	    tmp += gauss[i][j];
	  }
	}
	for (int i  = box[l][0][1];i <= box[l][1][1]; i++){
	  for (int j = box[l][0][0];j <= box[l][1][0]; j++){
	    contmat[l][k] += gauss[i][j];
	  }
	}
      }
    }
    
    //cout << contmat[0][0] << "  " << contmat[0][1] << endl;
    //cout << contmat[1][0] << "  " << contmat[1][1] << endl;
    
    // Invert contmat
    
    Matrix<double> contaminmat;
    contaminmat = Matrix<double>(numberions,numberions);
    contaminmat[0][0] = contmat[0][0];
    contaminmat[0][1] = contmat[0][1];
    contaminmat[1][0] = contmat[1][0];
    contaminmat[1][1] = contmat[1][1];
    
    
    //cout << "calculate invert contaminmat\n";
    Matrix<double> inv=contaminmat;
    //cout.put('.'); cout.flush();
    matrix_invert(inv);
    //cout << "done\n";
    ofstream file("/home/ivar/berger/projects/dpgtagung/programs/invcontmat.dat");
    if (!file.is_open()) {
      cout << "File-Error: invcontmat.dat\n";
    }
    else {
      for (unsigned int s = 0; s < numberions; s++){
	for (unsigned int t = 0; t < numberions; t++){   
	  file << inv[s][t];
	  file << " ";
	}
	file << endl;
      }
    }
    file.close();
    
    //cout << inv[0][0] << "  " << inv[0][1] << endl;
    //cout << inv[1][0] << "  " << inv[1][1] << endl;
    
    tmp = (inv[0][0] * double(boxrates[0])) + (inv[0][1] * double(boxrates[1]));
    nspill[0] = int(tmp);
    
    tmp = (inv[1][0] * double(boxrates[0])) + (inv[1][1] * double(boxrates[1]));
    nspill[1] = int(tmp); 
    
    
    
    cout << "B1  B2" << endl;
    cout << boxrates[0] << "  " << boxrates[1] << endl;
    //  cout << "B/N" << endl;
    //  cout << (double(boxrates[0])/double(nreal[0])) << "  " << (double(boxrates[1])/double(nreal[1])) << endl;
    cout << "Nspill1  Nspill2" << endl;
    cout << nspill[0] << "   " << nspill[1] << endl;
    
    
    
    // Calculate Nprob (Steiger et.al)
    
    summe = 0.;
    sum[0] = 0.;
    sum[1] = 0.;
  
    for (int i = 0; i < 256; i++){
	for (int j = 0; j < 1024 ; j++){	  
	  sumprob[0][i][j] = 0.;
	}
      }

  
    for (int k = 0; k < numberions; k++){
      for (int i = 0; i < 256; i++){
	for (int j = 0; j < 1024 ; j++){
	  tmp2 = paragaus[0][((k+1)*5)-3]-double(j);
	  tmp2 = tmp2 / paragaus[0][((k+1)*5)-2];
	  tmp2 = tmp2*tmp2;
	  tmp2 = tmp2 / 2.;
	  tmp3 = paragaus[0][((k+1)*5)-1]-double(i);
	  tmp3 = tmp3 / paragaus[0][((k+1)*5)];
	  tmp3 = tmp3*tmp3;
	  tmp3 = tmp3 / 2.;
	  //      cout << tmp2 << "   " << tmp3 << endl;
	  tmp = exp(-tmp2)*exp(-tmp3);
	  gauss[i][j] = tmp;
	  //sum[k] += tmp;
	}
      }
      
      sum[k] = sqrt(paragaus[0][(k+1)*5-2] * paragaus[0][(k+1)*5]);
      sum[k] = sum[k] * 2. * PI;
      sum[k] = 1 / sum[k];
      
      
      // sum[k] = 1 / sum[k]; 
      
      for (int i = 0; i < 256; i++){
	for (int j = 0; j < 1024 ; j++){
	  gauss[i][j] = gauss[i][j] * sum[k];
	  sumprob[0][i][j] += double(nspill[k]) * gauss[i][j];
	}
      }
    }
    for (int k = 0;k < numberions; k++){
      for (int i = 0; i < 256; i++){
	for (int j = 0; j < 1024; j++){
	  tmp2 = paragaus[0][((k+1)*5)-3]-double(j);
	  tmp2 = tmp2 / paragaus[0][((k+1)*5)-2];
	  tmp2 = tmp2*tmp2;
	  tmp2 = tmp2 / 2.;
	  tmp3 = paragaus[0][((k+1)*5)-1]-double(i);
	  tmp3 = tmp3 / paragaus[0][((k+1)*5)];
	  tmp3 = tmp3*tmp3;
	  tmp3 = tmp3 / 2.;
	  //      cout << tmp2 << "   " << tmp3 << endl;
	  tmp = exp(-tmp2)*exp(-tmp3);
	  prob[k][i][j] = (double(nspill[k]) * tmp * sum[k]) / sumprob[0][i][j];
	  
	}
      }
    }
    
    //  cout << prob[0][60][200] << "  " << prob[1][60][200];
    //  cout << summe << endl;
    
    nprob[0] = 0;
    nprob[1] = 0;
    
    for (int i = 0;i < 256; i++){
      for (int j = 0;j < 1024; j++){
	for (int l = 0;l < data[0][i][j]; l++){
	  tmp = ran_1(&idum);
	  if (tmp <= prob[0][i][j]){
	    nprob[0]++;
	  }
	  else{
	    tmp -= prob[0][i][j];
	    if (tmp <= prob[1][i][j]) nprob[1]++;
	  }
	}
      }
    }
    
    cout << "Nprob1  Nprob2" << endl;
    cout << nprob[0] << "   " << nprob[1] << endl;
  }  

  for (int i = 0; i < 256; i++){
    for (int j = 0; j < 1024; j ++){
      datadbl[i][j] = double(data[0][i][j]);
    }
  }

  for (int k = 0; k < numberions; k++){
    nspilldbl[k] = double(nspill[k]);
    nlowdbl[k] = double(nlow[k]);
    nhighdbl[k] = double(nhigh[k]);
  }

  //cout << "normgauss = " << normgauss [0] << endl;
  cout << "calling maxlifit" << endl;
  //  function = &twodgauss;
  maxlifit(datadbl,datadbl,sigdata[0],paragaus[0],nspilldbl,nlowdbl,nhighdbl,parause,covar,alpha,merit0,function,numberions);
  cout << nspilldbl[0] << "  " << nspilldbl[1] << endl;

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
