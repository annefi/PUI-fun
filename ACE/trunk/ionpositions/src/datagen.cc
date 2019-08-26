//  ************************************************
//  *                                              *
//  * file:      errordatagen2.cc                  *
//  *                                              *
//  * author:                                      *
//  *            Lars Berger                       *
//  *            <berger@physik.uni-kiel.de>       *
//  *                                              *
//  * version:   1.00                              *
//  *                                              *
//  * rev. date: 18.06.2007                        *
//  *                                              *
//  * Generates synthetic data                     *
//  *                                              *
//  *                                              *
//  *                                              *
//  *                                              *
//  *                                              *
//  ************************************************/

#include "datagen.h"

using namespace std;

mdouble datagen(vdouble &param)
{
  
  //Variable declaration
  const int numparaion = 7;
  mdouble data(ydim,xdim);
  //  void (*func) (dbgvector<double> &)=ran_urand;
  // Loop for Datageneration
  for (int i = 0; i < ydim; i++){
    for (int j = 0; j < xdim; j++){
      data[i][j] = 0.;
    }
  }
  vdouble sum(2,0.);

  for (int ionnr=0;ionnr<2;ionnr++){
    mdouble iondistr(ydim,xdim);
    vdouble dyda(numparaion,0.);
    vdouble paragauss(numparaion,0.);
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

    int lowy=int(param[ionnr*7+2]-3.*param[ionnr*7+6])-1;
    int highy=int(param[ionnr*7+2]+3.*param[ionnr*7+5])+1;
    int lowx=int(param[ionnr*7+1]-3.*param[ionnr*7+4])-1;
    int highx=int(param[ionnr*7+1]+3.*param[ionnr*7+3])+1;

    if (lowy<0){
      lowy=0;
    }
    if (highy>128){
      highy=128;
    }
    if (lowx<0){
      lowx=0;
    }
    if (highx>512){
      highx=512;
    }


    for (int count=0;count < param[ionnr*7];count++){
      //	cout << "randomnumber = " << ran << endl;
      for (int n = lowy; n < highy; n++){
	for (int o = lowx; o < highx; o++){
	  if (ran[count]<=iondistr[n][o]){
	    data[n][o]+=1.;
	    ran[count]=3.;
	  }
	  else{
	    ran[count]-=iondistr[n][o];
	  }
	}
	  
      }
    }
    
    /*
      int sumdata=0.;
      for (int n = 0; n < ydim; n++){
      for (int o = 0; o < xdim; o++){
      sumdata+=data[n][o];
      }
      }
      cout << "sumdata = " << sumdata << endl;
    */
  } 
  
  return data;

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
