#include "twodgaussschief.h"

using namespace std;


double twodgaussschief(int x,int y, vdouble &param, vdouble &deriv, int numpar, int numion, vint &iparam, double range)
{

  string thisprogram = "twodgaussschief : ";

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
    int sigx = (i*7)+3;
    int kx = (i*7)+4;
    int sigy = (i*7)+5;
    int ky = (i*7)+6;

    double kxp = 1. + param[kx];
    double kxm = 1. - param[kx];
    double kyp = 1. + param[ky];
    double kym = 1. - param[ky];

    double dx = double(x)-param[x0];
    double dy = double(y)-param[y0];
    

    //Berechnung des Funktionswertes des iten peaks 

    // normalize = normalization of i. 2D-Gaussian
    normalize = 1./(param[sigy]*param[sigx]);
    
    normalize = normalize/(2.*PI);
    
    // peakhigh = Peakhigh of i. 2D-Gaussian
    peakhigh = normalize * param[A];
    
    // exponent = Position dependent normalize of 2D-Gaussian
    exponent = -((pow(dx,2))/(2.*pow((param[sigx]*kxp),2))) * heavyside(-dx) -((pow(dx,2))/(2.*pow((param[sigx]*kxm),2))) * heavyside(dx) -((pow(dy,2))/(2.*pow((param[sigy]*kyp),2))) * heavyside(-dy) -((pow(dy,2))/(2.*pow((param[sigy]*kym),2))) * heavyside(dy);

    // singlegaussvalue = Value of i. 2D-Gaussian
    singlegaussvalue = peakhigh * exp(exponent);

    // sumgauss = Sum over 2D-Gaussians
    sumgauss += singlegaussvalue;  

    //Berechnung der Ableitugen nach den Parametern des iten Peaks
    
    deriv[A] = normalize * exp(exponent);

    deriv[x0] = (heavyside(-dx)*(dx/(pow((param[sigx]*kxp),2))) + heavyside(dx)*(dx/(pow((param[sigx]*kxm),2)))) * singlegaussvalue;
    deriv[y0] = (heavyside(-dy)*(dy/(pow((param[sigy]*kyp),2))) + heavyside(dy)*(dy/(pow((param[sigy]*kym),2)))) * singlegaussvalue;

    deriv[sigx] = -singlegaussvalue*(1./(param[sigx]));
    deriv[sigy] = -singlegaussvalue*(1./(param[sigy]));

    deriv[sigx] += heavyside(-dx)*(((pow(dx,2))/(param[sigx]*pow((param[sigx]*kxp),2))) * singlegaussvalue) + heavyside(dx)*(((pow(dx,2))/(param[sigx]*pow((param[sigx]*kxm),2))) * singlegaussvalue); 

    deriv[sigy] += heavyside(-dy)*(((pow(dy,2))/(param[sigy]*pow((param[sigy]*kyp),2))) * singlegaussvalue) + heavyside(dy)*(((pow(dy,2))/(param[sigy]*pow((param[sigy]*kym),2))) * singlegaussvalue); 


    deriv[kx] += heavyside(-dx)*(((pow(dx,2))/(pow(kxp*(param[sigx]*kxp),2))) * singlegaussvalue) + heavyside(dx)*(((pow(dx,2))/(pow(kxm*(param[sigx]*kxm),2))) * singlegaussvalue);

    deriv[ky] += heavyside(-dy)*(((pow(dy,2))/(kyp*pow((param[sigy]*kyp),2))) * singlegaussvalue) + heavyside(dy)*(((pow(dy,2))/(kym*pow((param[sigy]*kym),2))) * singlegaussvalue);

  }
  //  cout << thisprogram << "sumgauss = " << sumgauss << endl;
  return sumgauss;
}  
 
  
