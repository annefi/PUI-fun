#include "twodgauss.h"

using namespace std;


double twodgauss(int x,int y, vdouble &param, vdouble &deriv, int numpar, int numion, vint &iparam, double range)
{

  string thisprogram = "twodgauss : ";

  double sumgauss = 0.;
  double normalize = 0.;
  double peakhigh = 0.;
  double exponent = 0.;
  double singlegaussvalue = 0.;

  for (int k = 0; k < numion * 7; k++){
    deriv[k] = 0.;
  }

  // Schleife über alle peaks zur Berechnung des Funktionswertes
  for (int i = 0; i < numion;i++){


    int A = (i*7);
    int x0 = (i*7)+1;
    int y0 = (i*7)+2;
    int sig = (i*7)+3;
    int ind4 = (i*7)+4;
    int ind5 = (i*7)+5;
    int ind6 = (i*7)+6;

    double dx = double(x)-param[x0];
    double dy = double(y)-param[y0];
    

    //Berechnung des Funktionswertes des iten peaks 

    // normalize = normalization of i. 2D-Gaussian
    normalize = 1./(pow(param[sig],2));
    
    normalize = normalize/(2.*PI);
    
    // peakhigh = Peakhigh of i. 2D-Gaussian
    peakhigh = normalize * param[A];
    
    // exponent = Position dependent normalize of 2D-Gaussian
    exponent = -((pow(dx,2))/(2.*pow(param[sig],2)))- ((pow(dy,2))/(2.*pow(param[sig],2)));

    // singlegaussvalue = Value of i. 2D-Gaussian
    singlegaussvalue = peakhigh * exp(exponent);

    // sumgauss = Sum over 2D-Gaussians
    sumgauss += singlegaussvalue;  

    //Berechnung der Ableitugen nach den Parametern des iten Peaks
    
    deriv[A] = normalize * exp(exponent);
    
    deriv[x0] = (dx/(pow(param[sig],2))) * singlegaussvalue;
    deriv[y0] = (dy/(pow(param[sig],2))) * singlegaussvalue;
    
    deriv[sig] = -singlegaussvalue*(2./(param[sig]));
    
    deriv[sig] += ((pow(dx,2))/(pow(param[sig],3))) * singlegaussvalue  + ((pow(dy,2))/(pow(param[sig],3))) * singlegaussvalue; 

  }
  //  cout << thisprogram << "sumgauss = " << sumgauss << endl;
  return sumgauss;
}  
 
  
