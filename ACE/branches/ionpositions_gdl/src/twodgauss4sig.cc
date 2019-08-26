#include "twodgauss4sig.h"

using namespace std;


double twodgauss4sig(int x,int y, vdouble &param, vdouble &deriv, int numpar, int numion, vint &iparam, double range)
{

  string thisprogram = "twodgauss4sig : ";

  double sumgauss = 0.;
  double normalize = 0.;
  double peakhigh = 0.;
  double exponent = 0.;
  double singlegaussvalue = 0.;

  range = 3.;

  for (int k = 0; k < numion * 7; k++){
    deriv[k] = 0.;
  }

  // Schleife über alle peaks zur Berechnung des Funktionswertes
  for (int i = 0; i < numion;i++){


    int A = (i*7);
    int x0 = (i*7)+1;
    int y0 = (i*7)+2;
    int sigxp = (i*7)+3;
    int sigxm = (i*7)+4;
    int sigyp = (i*7)+5;
    int sigym = (i*7)+6;

    double dx = double(x)-param[x0];
    double dy = double(y)-param[y0];
    

    if ((dx <= range * param[sigxp]) && (dx >= -(range * param[sigxm])) && (dy <= range * param[sigyp]) && (dy >= -(range * param[sigym]))){

      //Berechnung des Funktionswertes des iten peaks 

      // normalize = normalization of i. 2D-Gaussian
      normalize = (1./((param[sigyp]*param[sigxp])+(param[sigym]*param[sigxp])+(param[sigyp]*param[sigxm])+(param[sigym]*param[sigxm])));
    
      normalize = (2./PI) * normalize;

      // peakhigh = Peakhigh of i. 2D-Gaussian
      peakhigh = normalize * param[A];

      // exponent = Position dependent normalize of 2D-Gaussian
      exponent = -((pow(dx,2))/(2.*pow(param[sigxp],2))) * heavyside(-dx) -((pow(dx,2))/(2.*pow(param[sigxm],2))) * heavyside(dx) -((pow(dy,2))/(2.*pow(param[sigyp],2))) * heavyside(-dy) -((pow(dy,2))/(2.*pow(param[sigym],2))) * heavyside(dy);

      // singlegaussvalue = Value of i. 2D-Gaussian
      singlegaussvalue = peakhigh * exp(exponent);

      // sumgauss = Sum over 2D-Gaussians
      sumgauss += singlegaussvalue;  

      //Berechnung der Ableitugen nach den Parametern des iten Peaks
    
      deriv[A] = normalize * exp(exponent);

      deriv[x0] = (heavyside(-dx)*(dx/(pow(param[sigxp],2))) + heavyside(dx)*(dx/(pow(param[sigxm],2)))) * singlegaussvalue;
      deriv[y0] = (heavyside(-dy)*(dy/(pow(param[sigyp],2))) + heavyside(dy)*(dy/(pow(param[sigym],2)))) * singlegaussvalue;

      deriv[sigxp] = -singlegaussvalue*(1./(param[sigxp]+param[sigxm]));
      deriv[sigxm] = -singlegaussvalue*(1./(param[sigxp]+param[sigxm]));
      deriv[sigyp] = -singlegaussvalue*(1./(param[sigyp]+param[sigym]));
      deriv[sigym] = -singlegaussvalue*(1./(param[sigyp]+param[sigym]));

      deriv[sigxp] += heavyside(-dx)*(((pow(dx,2))/(pow(param[sigxp],3))) * singlegaussvalue); 
      deriv[sigxm] += heavyside(dx)*(((pow(dx,2))/(pow(param[sigxm],3))) * singlegaussvalue);
      deriv[sigyp] += heavyside(-dy)*(((pow(dy,2))/(pow(param[sigyp],3))) * singlegaussvalue); 
      deriv[sigym] += heavyside(dy)*(((pow(dy,2))/(pow(param[sigym],3))) * singlegaussvalue);
      
    }
  }
  //  cout << thisprogram << "sumgauss = " << sumgauss << endl;
  return sumgauss;
}  
 
  
