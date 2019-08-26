//  ************************************************
//  *                                              *
//  * file:      test.cpp                          *
//  *                                              *
//  * author:    
//  *            bob wimmer                        *
//  *            <wimmer@physik.uni-kiel.de>       *
//  *                                              *
//  * version:   0.00                              *
//  *                                              *
//  * rev. date: 3.11.2003                         *
//  *                                              *
//  * skeleton for tests. uses same makefile as    *
//  * getdata5_xy.cpp                              *
//  *                                              *
//  *                                              *
//  *                                              *
//  ************************************************/

//using namespace std;

#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>
#include <cstdio>
//#include <grace_np.h>
//#include "readedb.h"
//#include "fit.h"
//#include "mod_speed.h"
//#include "pha.h"
//#include "ion_fmodel.h"
//#include "mynr.h"
//#include "bernedb.h"

#include <assert.h>

//poidev, page 294
double poidev(double xm, long *idum);
//mrqmin, page 685
double ran_1(long *idum);
void mrqmin(vector<double> &x, vector<double> &y, vector<double> &sig, vector<double> &a, vector<double> &a_lo, vector<double> &a_hi, vector<int> &ia,
	vector<vector<double> >&covar, vector<vector<double> >&alpha, double &chisq,
	    void (*funcs)(double, vector<double> &, double *, vector<double> &, int), double &alamda, int &newit);
//mrqcof, page 687
void mrqcof(vector<double> &x, vector<double> &y, vector<double> &sig, vector<double> &a, vector<int> &ia,
        vector<vector<double> > &alpha, vector<double> &beta, double &chisq,
	    void (*funcs)(double, vector<double> &, double *, vector<double> &, int));
//gaussj, page 39
void gaussj(vector<vector<double> > &a, int n, vector<vector<double> > &b);
//covsrt, page 675
void covsrt(vector<vector<double> > &covar, vector<int> &ia, int mfit);
//void nrerror(string err);
void test_lin(double x, vector<double> &para, double *ymod, vector<double> &dyda, int ma);
void fgauss(double x, vector<double> &para, double *ymod, vector<double> &dyda, int ma);
void maxlifit(vector<double> &x, vector<double> &y, vector<double> &sig, vector<double> &a, vector<double> &a_lo, vector<double> &a_hi, vector<int> &ia,
	vector<vector<double> >&covar, vector<vector<double> >&alpha, double &merit,
	void (*funcs)(double , vector<double> &, double *, vector<double> &, int), int &newit);
double gammln(double xx);
double logfak(double x);
int param_bounds(vector<double> &a, vector<double> &a_lo, vector<double> &a_hi, vector<int> &ia);
void get_mod_mer(vector<double> &x,vector<double> &a, double &mod_merit, void (*funcs)(double, vector<double> &, double *, vector<double> &, int));
const double PI=3.141592653;
long idum = (-1689753);

int main (void)
{
  cout << endl << endl << endl<< "This is a test programme for ACE/SWICS/SWIMS Software" << endl;
  int ma = 7;
  vector<double> data, sum_data;
  vector<double> sig;
  vector<double> x;
  vector<double> para(ma,0.), sum_para(ma,0.), para_lo(ma,0.), para_hi(ma,0.), para_in(ma,0.);
  vector<double> dyda(ma,0.);
  void (*point_test_lin)(double x, vector<double> &para, double *ymod, vector<double> &dyda, int ma) = test_lin;
  void (*point_fgauss)(double x, vector<double> &para, double *ymod, vector<double> &dyda, int ma) = fgauss;
  int max_sim = 100;
  double ymod = 0.9999;
  const char *filename="para_stat.dat";
  ofstream para_stat(filename, ios::out | ios::trunc);
  if (!para_stat.is_open())
    {
      cout << "File-Error: " << filename;
      return false;
    }
  for (int sim = 0 ; sim < max_sim; sim++)
    {
//  int sim = 0;
//       cout << "-----------------------------------------------------------" << endl;
//       cout << "before loop sim = " << sim << endl;
      x.clear();
      data.clear();
      sig.clear();
//       para[0] = 0.002;
//       para[1] = 0.1;
      para[0] = 1.7;
      para[1] = 1.2;
      para[2] = 220.;
      para[3] = 20.;
      para[4] = 1.2;
      para[5] = 270.;
      para[6] = 20.;
      para_in = para;
      para_lo[0] = 0.1;
      para_lo[1] = 0.5;
      para_lo[2] = 100.;
      para_lo[3] = 10.;
      para_lo[4] = 0.5;
      para_lo[5] = 100.;
      para_lo[6] = 10.;
      para_hi[0] = 10.5;
      para_hi[1] = 9.5;
      para_hi[2] = 490.;
      para_hi[3] = 40.;
      para_hi[4] = 9.5;
      para_hi[5] = 490.;
      para_hi[6] = 40.;
      for (int i = 0; i < 500; i++)
	{
	  //cout << i << " ";
	  x.push_back(double(i));
	  //cout << x[i] << " " << endl;
	  fgauss(x[i],para,&ymod,dyda,ma);
	  //test_lin(x[i],para,&ymod,dyda,ma);
	  //cout << " " << ymod << endl;
	  //cout << x[i] << " " << ymod << " " << para[0] << " " << para[1] << " " << dyda[0] << " " << dyda[1] << " " << ma;
	  double aux2 = poidev(ymod, &idum);
	  //cout <<  " " << aux2  << endl;
	  data.push_back(aux2);
	  sig.push_back(max(double(1.),sqrt(aux2)));
	}
//       cout << "end of data generation, ";
      if (sim == 0) sum_data = data;
      for (int i = 0; sim > 0, i < 500; i++) sum_data[i] += data[i];
      vector<int> ia(para.size(),0);
      vector<vector<double> > alpha(para.size(),vector<double>(para.size(),0.));
      vector<vector<double> > covar(para.size(),vector<double>(para.size(),0.));
      //give fitting routine wrong initial parameters, after all, it needs to do something...
      double merit = 1.e6;
      para[0] = 0.5;
      para[1] = 1.5;
      para[2] = 305.;
      para[3] = 15.;
      para[4] = 9.5;
      para[5] = 195.;
      para[6] = 29.;
      ia[0]=1; ia[1]=1; ia[2]=1; ia[3]=1; ia[4]=1; ia[5]=1; ia[6]=1; //tell routine which parameters to fit (1) and not to fit (0)
      int iter = 1;
      //maxlifit(x, data, sig, para, ia, covar, alpha, merit, point_test_lin, iter);
      maxlifit(x, data, sig, para, para_lo, para_hi, ia, covar, alpha, merit, point_fgauss, iter);
      //cout << "merit = " << merit << ", para[0] = " << para[0] << ", para[1] = " << para[1] << ", para[2] = " << para[2] << ", para[3] = " <<para[3] << ", para[4] = " <<para[4] << ", para[5] = " <<para[5]<< endl;
      ia[0]=1; ia[1]=0; ia[2]=1; ia[3]=0; ia[4]=0; ia[5]=1; ia[6]=0; //tell routine which parameters to fit (1) and not to fit (0)
      iter = 1;
      //maxlifit(x, data, sig, para, ia, covar, alpha, merit, point_test_lin, iter);
      maxlifit(x, data, sig, para, para_lo, para_hi, ia, covar, alpha, merit, point_fgauss, iter);
      //cout << "merit = " << merit << ", para[0] = " << para[0] << ", para[1] = " << para[1] << ", para[2] = " << para[2] << ", para[3] = " <<para[3] << ", para[4] = " <<para[4] << ", para[5] = " <<para[5]<< endl;
      ia[0]=1; ia[1]=1; ia[2]=1; ia[3]=0; ia[4]=1; ia[5]=1; ia[6]=0;//tell routine which parameters to fit (1) and not to fit (0)
      iter = 1;
      //maxlifit(x, data, sig, para, ia, covar, alpha, merit, point_test_lin, iter);
      maxlifit(x, data, sig, para, para_lo, para_hi, ia, covar, alpha, merit, point_fgauss, iter);
      //cout << "merit = " << merit << ", para[0] = " << para[0] << ", para[1] = " << para[1] << ", para[2] = " << para[2] << ", para[3] = " <<para[3] << ", para[4] = " <<para[4] << ", para[5] = " <<para[5]<< endl;
      ia[0]=0; ia[1]=0; ia[2]=1; ia[3]=1; ia[4]=0; ia[5]=1; ia[6]=1; //tell routine which parameters to fit (1) and not to fit (0)
      iter = 1;
      //maxlifit(x, data, sig, para, ia, covar, alpha, merit, point_test_lin, iter);
      maxlifit(x, data, sig, para, para_lo, para_hi, ia, covar, alpha, merit, point_fgauss, iter);
      //cout << "merit = " << merit << ", para[0] = " << para[0] << ", para[1] = " << para[1] << ", para[2] = " << para[2] << ", para[3] = " <<para[3] << ", para[4] = " <<para[4] << ", para[5] = " <<para[5]<< endl;
      ia[0]=0; ia[1]=1; ia[2]=0; ia[3]=1; ia[4]=1; ia[5]=0; ia[6]=1; //tell routine which parameters to fit (1) and not to fit (0)
      iter = 1;
      //maxlifit(x, data, sig, para, ia, covar, alpha, merit, point_test_lin, iter);
      maxlifit(x, data, sig, para, para_lo, para_hi, ia, covar, alpha, merit, point_fgauss, iter);
      //cout << "merit = " << merit << ", para[0] = " << para[0] << ", para[1] = " << para[1] << ", para[2] = " << para[2] << ", para[3] = " <<para[3] << ", para[4] = " <<para[4] << ", para[5] = " <<para[5]<< endl;
       ia[0]=0; ia[1]=0; ia[2]=0; ia[3]=1; ia[4]=0; ia[5]=0; ia[6]=1; //tell routine which parameters to fit (1) and not to fit (0)
      iter = 1;
      //maxlifit(x, data, sig, para, ia, covar, alpha, merit, point_test_lin, iter);
      maxlifit(x, data, sig, para, para_lo, para_hi, ia, covar, alpha, merit, point_fgauss, iter);
      //cout << "merit = " << merit << ", para[0] = " << para[0] << ", para[1] = " << para[1] << ", para[2] = " << para[2] << ", para[3] = " <<para[3] << ", para[4] = " <<para[4] << ", para[5] = " <<para[5]<< endl;
      ia[0]=0; ia[1]=1; ia[2]=0; ia[3]=0; ia[4]=1; ia[5]=0; ia[6]=0; //tell routine which parameters to fit (1) and not to fit (0)
      iter = 1;
      //maxlifit(x, data, sig, para, ia, covar, alpha, merit, point_test_lin, iter);
      maxlifit(x, data, sig, para, para_lo, para_hi, ia, covar, alpha, merit, point_fgauss, iter);
      //cout << "merit = " << merit << ", para[0] = " << para[0] << ", para[1] = " << para[1] << ", para[2] = " << para[2] << ", para[3] = " <<para[3] << ", para[4] = " <<para[4] << ", para[5] = " <<para[5]<< endl;
       ia[0]=0; ia[1]=0; ia[2]=1; ia[3]=0; ia[4]=0; ia[5]=1; ia[6]=0; //tell routine which parameters to fit (1) and not to fit (0)
      iter = 1;
      //maxlifit(x, data, sig, para, ia, covar, alpha, merit, point_test_lin, iter);
      maxlifit(x, data, sig, para, para_lo, para_hi, ia, covar, alpha, merit, point_fgauss, iter);
      //cout << "merit = " << merit << ", para[0] = " << para[0] << ", para[1] = " << para[1] << ", para[2] = " << para[2] << ", para[3] = " <<para[3] << ", para[4] = " <<para[4] << ", para[5] = " <<para[5]<< endl;
      ia[0]=1; ia[1]=1; ia[2]=1; ia[3]=1; ia[4]=0; ia[5]=0; ia[6]=0; //tell routine which parameters to fit (1) and not to fit (0)
      iter = 1;
      //maxlifit(x, data, sig, para, ia, covar, alpha, merit, point_test_lin, iter);
      maxlifit(x, data, sig, para, para_lo, para_hi, ia, covar, alpha, merit, point_fgauss, iter);
      //cout << "merit = " << merit << ", para[0] = " << para[0] << ", para[1] = " << para[1] << ", para[2] = " << para[2] << ", para[3] = " <<para[3] << ", para[4] = " <<para[4] << ", para[5] = " <<para[5]<< endl;
      ia[0]=0; ia[1]=0; ia[2]=0; ia[3]=0; ia[4]=1; ia[5]=1; ia[6]=1; //tell routine which parameters to fit (1) and not to fit (0)
      iter = 1;
      //maxlifit(x, data, sig, para, ia, covar, alpha, merit, point_test_lin, iter);
      maxlifit(x, data, sig, para, para_lo, para_hi, ia, covar, alpha, merit, point_fgauss, iter);
      //cout << "merit = " << merit << ", para[0] = " << para[0] << ", para[1] = " << para[1] << ", para[2] = " << para[2] << ", para[3] = " <<para[3] << ", para[4] = " <<para[4] << ", para[5] = " <<para[5]<< endl;
     ia[0]=1; ia[1]=1; ia[2]=1; ia[3]=1; ia[4]=1; ia[5]=1; ia[6]=1; //tell routine which parameters to fit (1) and not to fit (0)
      iter = 1;
      //maxlifit(x, data, sig, para, ia, covar, alpha, merit, point_test_lin, iter);
      maxlifit(x, data, sig, para, para_lo, para_hi, ia, covar, alpha, merit, point_fgauss, iter);
      cout << sim << " merit = " << merit << ", para[0] = " << para[0] << ", para[1] = " << para[1] << ", para[2] = " << para[2] << ", para[3] = " <<para[3] << ", para[4] = " <<para[4] << ", para[5] = " <<para[5]<< endl;
      for (int i = 0 ; i < para.size(); i++) sum_para[i] += para[i];
      //cout << sum_para[0]/(sim+1) << ", " << sum_para[1]/(sim+1) << endl;
      para_stat << sim << "\t";
      for (int i = 0 ; i < para.size(); i++) para_stat << para[i] << "\t";
      para_stat << merit << endl;
    }
  cout << "average parameters are: " << endl;
  cout << "input \t\t fitted \t\t ratio\n";
  for (int i = 0; i < ma; i++) 
    {
      cout << para_in[i] << "\t\t" << sum_para[i]/max_sim << "\t\t" << para_in[i]/sum_para[i]*max_sim << endl;
      para[i] = sum_para[i]/max_sim;
    }
  const char *filename1="test.dat";
  ofstream test(filename1, ios::out | ios::trunc);
  if (!test.is_open())
    {
      cout << "File-Error: " << filename1;
      return false;
    }
  for (int i = 0; i < 500; i++) 
    {
      //test_lin(x[i],para,&ymod,dyda,ma);
      double aux;
      fgauss(x[i],para_in,&aux,dyda,ma);
      fgauss(x[i],para,&ymod,dyda,ma);
      test << x[i] << " " << sum_data[i]/max_sim << " " <<  ymod << " " <<  aux << endl;
    }
}
void fgauss(double x, vector<double> &para, double *ymod, vector<double> &dyda, int ma)
{
	int i;
	double fac,ex,arg;

	*ymod=para[0];  //constant background
	dyda[0] = 1.;  //constant background
	for (i=1;i<ma-1;i+=3) {
		arg=(x-para[i+1])/para[i+2];
		ex=exp(-arg*arg);
		fac=para[i]*ex*2.0*arg;
		*ymod += para[i]*ex;
		dyda[i]=ex;
		dyda[i+1]=fac/para[i+2];
		dyda[i+2]=fac*arg/para[i+2];
	}
}
void test_lin(double x, vector<double> &para, double *ymod, vector<double> &dyda, int ma)
{
  //cout << "in test_lin " << endl;
//   dyda.clear();
//   dyda.push_back(x);
//   dyda.push_back(1.);
  *ymod = para[0]*x + para[1];
  if (*ymod <= 0.) 
    {
      dyda[0] = 0.;
      dyda[1] = 0.;
      *ymod = 0.;
    }
  else
    {
      dyda[0] = x;
      dyda[1] = 1.;
    }
  //cout << "mod("<<x<<") = " << *ymod;// << endl;
}
double poidev(double xm, long *idum)
{
	double gammln(double xx);
	double ran_1(long *idum);
	static double sq,alxm,g,oldm=(-1.0);
	double em,t,y;
	//cout << " xm = " << xm << " and ";
	if (xm < 12.0) {
		if (xm != oldm) {
			oldm=xm;
			g=exp(-xm);
		}
		em = -1;
		t=1.0;
		do {
			++em;
			t *= ran_1(idum);
			//cout << t << ", " << ran_1(idum)<< endl;
		} while (t > g);
	} else {
		if (xm != oldm) {
			oldm=xm;
			sq=sqrt(2.0*xm);
			alxm=log(xm);
			g=xm*alxm-gammln(xm+1.0);
		}
		do {
			do {
				y=tan(PI*ran_1(idum));
				//cout << y << endl;
				em=sq*y+xm;
			} while (em < 0.0);
			em=floor(em);
			t=0.9*(1.0+y*y)*exp(em*alxm-gammln(em+1.0)-g);
		} while (ran_1(idum) > t);
	}
	//cout << "in poidev em is " << em << endl;
	return max(double(0.),em);
}
#define IA 16807
#define IM 2147483647
#define AM (1.0/IM)
#define IQ 127773
#define IR 2836
#define NTAB 32
#define NDIV (1+(IM-1)/NTAB)
#define EPS 1.2e-7
#define RNMX (1.0-EPS)

double ran_1(long *idum)
{
	int j;
	long k;
	static long iy=0;
	static long iv[NTAB];
	double temp;

	if (*idum <= 0 || !iy) {
		if (-(*idum) < 1) *idum=1;
		else *idum = -(*idum);
		for (j=NTAB+7;j>=0;j--) {
			k=(*idum)/IQ;
			*idum=IA*(*idum-k*IQ)-IR*k;
			if (*idum < 0) *idum += IM;
			if (j < NTAB) iv[j] = *idum;
		}
		iy=iv[0];
	}
	k=(*idum)/IQ;
	*idum=IA*(*idum-k*IQ)-IR*k;
	if (*idum < 0) *idum += IM;
	j=iy/NDIV;
	iy=iv[j];
	iv[j] = *idum;
	if ((temp=AM*iy) > RNMX) return RNMX;
	else return temp;
}
#undef IA
#undef IM
#undef AM
#undef IQ
#undef IR
#undef NTAB
#undef NDIV
#undef EPS
#undef RNMX
void maxlifit(vector<double> &x, vector<double> &y, vector<double> &sig, vector<double> &a, vector<double> &a_lo, vector<double> &a_hi, vector<int> &ia,
	vector<vector<double> >&covar, vector<vector<double> >&alpha, double &merit,
	void (*funcs)(double, vector<double> &, double *, vector<double> &, int), int &newit)
{
  //cout << " in maxlifit: " << endl ;
  double merit0 = 0.;
  double merit1 = 0.;
  int ndata = x.size();
  //cout << "ndata = " << ndata << endl;
  //for (int i = 0; i < ndata; i ++) cout << x[i] << ", " << y[i] << endl;//merit0 += logfak(y[i]);
  for (int i = 0; i < ndata; i ++) merit0 += logfak(y[i]);
  //cout << " passed 1st loop " << endl;
  double alamda = -1.;
  merit = 1.e10;
  double omerit = merit;
  int itst = 0;
  int max_test = 5;
  //cout << "ia[0] = " << ia[0] << " and ia[1] = " << ia[1] << ", and newit = " << newit << endl;
  double mod_merit = 0.;
  while (itst < max_test)
    {
      omerit = merit;
      //cout << "calling mrqmin: " << itst << " with parameters " << a[0] << ", " << a[1] << ", " << a[2]<< ", " << a[3] << " , omerit = " << omerit << ", and old mod_merit = " << mod_merit <<endl;
      mrqmin(x, y, sig, a, a_lo, a_hi, ia, covar, alpha, merit1, funcs, alamda, newit);
      //cout << "and now newit = " << newit << endl;
      merit = merit0 + merit1;
      //cout <<" merit function is: merit0 = " << merit0 << ", merit1 = " <<merit1 << ", sum = " << merit << ", and omerit is " << omerit <<endl;; 
      //now we  have new model parameters and a value for the probability of the model to fit the data. Let's see whether it's any good by
      //simulating a data set with these model parameters and then comparing the merit function with the true data.
      get_mod_mer(x,a,mod_merit,funcs);
      //cout << "model merit function is " << mod_merit << endl;
      if (merit > omerit) itst = 0;
      else if (merit > 0.95*omerit && merit <= omerit && merit < 2*mod_merit) itst++;
      //else if (merit > 0.95*omerit && merit <= omerit ) itst++;
      //if (merit == omerit) itst = max_test;
    }
  alamda = 0.;
  //cout << "Last call to mrqmin." << endl;
  mrqmin(x, y, sig, a, a_lo, a_hi, ia, covar, alpha, merit1, funcs, alamda, newit);
  merit = merit0 + merit1;
  //cout <<" merit function is " << merit << ", and omerit is " << omerit <<endl;; 
}

double logfak(double x)
{
  double aux = 0.;
  if (x < 10)
    {
      for (int i = int(x); i >= 1; i --) aux += log(double(i));
    }
  else
    {
      aux = x*log(x)-x+0.5*log(2.*PI*x)+1./12./x - 1./360.*pow(x,-3.) + 1./1260.*pow(x,-5.) - 1./1680*pow(x,-7.);
      aux += 8.4175084e-5*pow(x,-9.) - 2.3010323e-4*pow(x,-11.);
    }
  return aux;
}
void get_mod_mer(vector<double> &x,vector<double> &a, double &mod_merit, void (*funcs)(double, vector<double> &, double *, vector<double> &, int))
{
  int n = x.size();
  int ma = a.size();
  vector<double> dyda(ma,0.);
  double ymod = 0.;
  mod_merit = 0.;        
  for (int i = 0; i < n; i++)
    {
      funcs(x[i],a,&ymod,dyda,ma);
      double aux2 = poidev(ymod, &idum);
      //cout << i << ", " << ymod << ", " << aux2 << ", " <<  mod_merit <<endl;
      mod_merit += logfak(aux2) + ymod - aux2*log(ymod);
    }
}
// //svdcmp, page 67, double arrays are replaced by vectors
// void svdcmp(double **a, int m, int n, double w[], double **v)
// {
// translates as: 
// void svdcmp(vector<vector<double> > &a,vector<double> &w, vector<vector<double> >&v)
// {
//   int flag,i,its,j,jj,k,l,nm;
//   double anorm,c,f,g,h,s,scale,x,y,z;
//   int m = a.size()-1;
//   int n = v.size()-1;
//   vector<double> rv1(n);
// So need to translate mrqmin (p. 685) to vector-language
// void mrqmin(double x[], double y[], double sig[], int ndata, double a[], int ia[],
// 	int ma, double **covar, double **alpha, double *chisq,
// 	void (*funcs)(double, double [], double *, double [], int), double *alamda)
// {
// 	void covsrt(double **covar, int ma, int ia[], int mfit);
// 	void gaussj(double **a, int n, double **b, int m);
// 	void mrqcof(double x[], double y[], double sig[], int ndata, double a[],
// 		int ia[], int ma, double **alpha, double beta[], double *chisq,
// 		void (*funcs)(double, double [], double *, double [], int));
void mrqmin(vector<double> &x, vector<double> &y, vector<double> &sig, vector<double> &a, vector<double> &a_lo, vector<double> &a_hi, vector<int> &ia,
	    vector<vector<double> >&covar, vector<vector<double> >&alpha, double &chisq,
	    void (*funcs)(double, vector<double> &, double *, vector<double> &, int), double &alamda, int &newit)
{
  void covsrt(vector<vector<double> >&covar, vector<int> &ia, int mfit);
  void gaussj(vector<vector<double> >&a, int n, vector<vector<double> >&b);
  void mrqcof(vector<double> &x, vector<double> &y, vector<double> &sig, vector<double> &a,
	      vector<int> &ia, vector<vector<double> >&alpha, vector<double> &beta, double &chisq,
	      void (*funcs)(double, vector<double> &, double *, vector<double> &, int));
  int j,k,l;
  int ma = a.size();
  int mfit;
  for (mfit=0,j=0;j<ma;j++)
    if (ia[j]) mfit++;
  static double ochisq;
  static vector<double> atry(ma,0.), beta(ma,0.),da(ma,0.);
  static vector<vector<double> > oneda(mfit,vector<double>(1,0.));
//   if (newit == 1)
//     {
//       cout << "re-initializing oneda to dimension " << mfit << " because newit = " << newit;
//       newit = 1;
//       cout << " and now resetting newit to " << newit << endl;
//       oneda.clear();
//       static vector<vector<double> > oneda(mfit,vector<double>(1,0.));
//       for (int i = 0; i<mfit;i++) cout << "oneda: " << oneda[i][0] << ", " << endl;
//       cout << "oneda[0].size() = " << oneda[0].size() << endl;
//     }
//   //cout << "in mrqmin: ma, beta[0], mfit = " << ma << ", " << beta[0] << ", " << mfit << ", and newit = " << newit << endl;
  int ndata = x.size();
  
  if (alamda < 0.0) {
    //cout <<"before loop 1" << endl;
    //cout << "in loop, j, mfit = " << j << ", " << mfit << endl;
    alamda=.001;
    //cout << "calling mrqcof" << endl;
    mrqcof(x,y,sig,a,ia,alpha,beta,chisq,funcs);
    //cout << "returned from mrqcof, chisq = " << chisq << ", beta = " << beta[0] << ", "<< beta[1] << endl;
    ochisq=chisq;
    for (j=0;j<ma;j++) atry[j]=a[j];
  }
  for (j=0;j<mfit;j++) 
    {
      for (k=0;k<mfit;k++) 
	{
	  covar[j][k] = alpha[j][k];
	  //cout << alpha[j][k] << "  ";
	}
      //cout << endl;
    }
  //cout << "before loop for covar " << oneda.size() << endl;
  for (j=0;j<mfit;j++) {
//     for (k=0;k<mfit;k++) covar[j][k]=alpha[j][k];
    covar[j][j]=alpha[j][j]*(1.0+alamda);
    oneda[j][0]=beta[j];
    //cout << j << " " << oneda[j][0] << ", " << covar.size() << ", " << oneda[0].size() << endl;
  }
  //cout << "end of covar loop, calling gaussj:" << covar[1][1]<<endl;
//   covar[0][0] = 1.; covar[0][1] = 1.; covar[1][0] = 2.; covar[1][1] = 1.;
//   oneda[0][0] = 1.; oneda[1][0] = 3.;
  gaussj(covar, mfit, oneda);
  //cout << "solution: oneda[0][0] = " << oneda[0][0] << ", oneda[1][0] = " << oneda[1][0] << endl;
  for (j=0;j<mfit;j++) da[j]=oneda[j][0];
  if (alamda == 0.0) {
    covsrt(covar,ia,mfit);
    covsrt(alpha,ia,mfit);
    return;
  }
  for (j=0,l=0;l<ma;l++)
    if (ia[l]) atry[l]=a[l]+da[j++];
  //cout << "Calling mrqcof again" << endl;
  mrqcof(x,y,sig,atry,ia,covar,da,chisq,funcs);
  //cout << "returned from mrqcof again, alambda = " << alamda << ", chisq = " << chisq << ", beta = " << beta[0] << ", "<< beta[1]<< endl;
  //cout << param_bounds(atry,a_lo,a_hi,ia) << "\t chisq = " << chisq << "\t ochisq = " << ochisq << endl;
  if (chisq < ochisq && param_bounds(atry,a_lo,a_hi,ia)) {
    alamda *= 0.1;
    ochisq=chisq;
    //cout << "in chisq < ochisq loop" << endl;
     for (j=0;j<mfit;j++) {
       for (k=0;k<mfit;k++) alpha[j][k]=covar[j][k];
       beta[j]=da[j];
     }
//    alpha = covar;
//    beta = da;
     //cout << "-: " << da[0] << ", " << beta[0] <<endl;
    //    for (l=0;l<ma;l++) a[l]=atry[l];
    a = atry;
  } else {
    alamda *= 10.0;
    chisq=ochisq;
  }
  //assert (newit != 0);
  //cout << "end of mrqmin: newit is " << newit << endl;
}

int param_bounds(vector<double> &a, vector<double> &a_lo, vector<double> &a_hi, vector<int> &ia)
{
  int n = a.size();
  int value = 1;
  for (int i = 0; i<n;i++) 
    {
      if (ia[i]=1 && (a[i] < a_lo[i] || a[i] > a_hi[i])) 
	{
	  cout << i << "\t" << a_lo[i] << "\t" << a[i] << "\t" << a_hi[i] << endl;
	  value = 0;
	}
    }
  return value;
}

void mrqcof(vector<double> &x, vector<double> &y, vector<double> &sig, vector<double> &a, vector<int> &ia,
        vector<vector<double> > &alpha, vector<double> &beta, double &chisq,
	void (*funcs)(double, vector<double> &, double *, vector<double> &, int))
{
  //cout << "in mrqcof para are: " << a[0] << " and " << a[1] << endl;
	int i,j,k,l,m,mfit=0;
	double ymod,wt,sig2i;
	int ndata = x.size();
        int ma = a.size();
        vector<double> dyda(ma,0.);
// 	cout << "before 1st loop" << endl;
	for (j=0;j<ma;j++)
		if (ia[j]) mfit++;
	//cout << "before 2nd loop" << endl;
	//cout << alpha[0][0] << endl;//" " << alpha[mfit-1][mfit-1] << endl;
	for (j=0;j<mfit;j++) {
		for (k=0;k<mfit;k++) alpha[j][k]=0.0;
		beta[j]=0.0;
	}
	//cout << "passed second (compound) loop" << endl;
	//cout << alpha[0][0] << endl;//" " << alpha[mfit-1][mfit-1] << endl;
//  	cout << "before 2nd loop" << endl;
	chisq=0.0;
	for (i=0;i<ndata;i++) 
	  {
	    funcs(x[i],a,&ymod,dyda,ma);
	    //cout << "dyda("<<x[i]<<")[0] = " << dyda[0] << ", dyda("<<x[i]<<")[1] = " << dyda[1] << ", sig[i] = " << sig[i] << ", ymod = " << ymod << endl;
	    sig2i=1.0/(sig[i]*sig[i]);
	    //cout << i << ", " << sig[i] << endl;
	    // 		cout << " inside 2nd loop in mrqcof, mfit, ma =" <<mfit << " " << ma <<endl;
	    for (j=0,l=0;l<ma;l++) 
	      {
		if (ia[l]) 
		  {
		    //wt=dyda[l]*sig2i;
		    for (j++,k=0,m=0;m<=l;m++) 
		      {
			//cout << " j, k, l, m, ia(m) = " << j <<" " << k <<" " << l << " " << m << " "  << ia[m] << endl;
			// 				  if (ia[m]) alpha[j][k++] += wt*dyda[m];
			if (ia[m]) alpha[j-1][k++] += y[i]*(dyda[l]/ymod)*(dyda[m]/ymod);
			//cout << "j , k = " << j-1 << " " << k-1 << " " << alpha[j-1][k-1] << " " << y[i] << " " << dyda[l]/ymod << " " << dyda[l] << " " << dyda[m] << endl;
		      }
		    //cout << endl;
		    // 				beta[j] += dy*wt;
		    //cout << j-1 << endl;
		    beta[j-1] += - dyda[l]*(1. - y[i]/ymod);
		  }
	      }
	    chisq += ymod-y[i]*log(ymod);//Chi squared version: dy*dy*sig2i;
	    //if (ymod <= 0. && chisq > 0.) chisq *=1.02;
	    //if (ymod <= 0. && chisq <= 0.) chisq +=1.;
	    //chisq +=1.;
	    //cout << chisq << ", " << ymod <<endl;
	  }
	//  	cout << "passed second  loop" << endl;
	//  	cout << "before 3rd loop" << endl;
	for (j=1;j<mfit;j++)
	  for (k=0;k<j;k++) alpha[k][j]=alpha[j][k];
	//  	cout << "passed third loop" << endl;
 	//cout << "leaving mrqcof, beta = " << beta[0] << ", " << beta[1] <<  ", chisq = " << chisq << endl;
	//free_vector(dyda,1,ma);
}

#define SWAP(a,b) {swap=(a);(a)=(b);(b)=swap;}

void covsrt(vector<vector<double> > &covar, vector<int> &ia, int mfit)
{
	int i,j,k;
	double swap;
	int ma = covar.size();

	assert(ma == covar[0].size());

	for (i=mfit;i<ma;i++)
		for (j=0;j<i;j++) covar[i][j]=covar[j][i]=0.0;
	k=mfit-1;
	for (j=ma-1;j>=0;j--) {
		if (ia[j]) {
		  //cout << "i,j,k, ma, mfit " << i <<", " << j << ", " << k << ", " << ma << ", " << mfit << endl;
			for (i=0;i<ma;i++) SWAP(covar[i][k],covar[i][j])
			for (i=0;i<ma;i++) SWAP(covar[k][i],covar[j][i])
			k--;
		}
	}
}
#undef SWAP


#define SWAP(a,b) {temp=(a);(a)=(b);(b)=temp;}

void gaussj(vector<vector<double> > &a, int n, vector<vector<double> > &b)
{
  //int *indxc,*indxr,*ipiv;
	int i,icol,irow,j,k,l,ll;
	double big,dum,pivinv,temp;
	//int n = a[0].size();
	int m = b[0].size();

//   	cout << "in gaussj: size of a, b is " << n << " by " << a.size() <<", and " << m << " by " << b.size() << endl;
// 	cout << "in gaussj: " << b[0][0] << ", " << b[1][0] << endl;
// 	cout << "in gaussj: " << a[0][0] << ", " << a[1][0] << ", " << a[2][0] << endl;
// 	cout << "in gaussj: " << a[0][1] << ", " << a[1][1] << ", " << a[2][1] << endl;
// 	cout << "in gaussj: " << a[0][2] << ", " << a[1][2] << ", " << a[2][2] << endl;
	vector<int> indxc(n,0); 
	vector<int> ipiv(n,0);  
	vector<int> indxr(n,0); 
	for (i=0;i<n;i++) {
		big=0.0;
		for (j=0;j<n;j++)
			if (ipiv[j] != 1)
				for (k=0;k<n;k++) 
				  {
				    //cout << "1: irow, icol, i, j, k, a[j][k] = " << irow <<", " << icol << ", " << i <<", " << j <<", " << k << ", " << a[j][k] <<endl;
				    if (ipiv[k] == 0) {
				      if (fabs(a[j][k]) >= big) {
					big=fabs(a[j][k]);
					irow=j;
					icol=k;
				      }
				    } else if (ipiv[k] > 1) cout <<"gaussj: Singular Matrix-1" <<endl;
				  }
		//cout << "2: irow, icol, i, j, k = " << irow <<", " << icol << ", " << i <<", " << j <<", " << k << endl;
		++(ipiv[icol]);
		if (irow != icol) {
			for (l=0;l<n;l++) SWAP(a[irow][l],a[icol][l])
			for (l=0;l<m;l++) SWAP(b[irow][l],b[icol][l])
		}
		indxr[i]=irow;
		indxc[i]=icol;
		//cout << "irow, icol = " << irow <<", " << icol << endl;
		if (a[icol][icol] == 0.0) cout<< "gaussj: Singular Matrix-2" <<endl;
		pivinv=1.0/a[icol][icol];
		a[icol][icol]=1.0;
		for (l=0;l<n;l++) a[icol][l] *= pivinv;
		for (l=0;l<m;l++) b[icol][l] *= pivinv;
		for (ll=0;ll<n;ll++)
			if (ll != icol) {
				dum=a[ll][icol];
				a[ll][icol]=0.0;
				for (l=0;l<n;l++) a[ll][l] -= a[icol][l]*dum;
				for (l=0;l<m;l++) b[ll][l] -= b[icol][l]*dum;
			}
	}
	//cout << "swapping loop" << endl;
	for (l=n-1;l>=0;l--) {
		if (indxr[l] != indxc[l])
			for (k=0;k<n;k++)
				SWAP(a[k][indxr[l]],a[k][indxc[l]]);
	}
// 	free_ivector(ipiv,1,n);
// 	free_ivector(indxr,1,n);
// 	free_ivector(indxc,1,n);
	indxc.clear();indxr.clear();ipiv.clear();
	//cout << "end of gaussj reached" << endl;
}
#undef SWAP
// //Print errors
// void nrerror(string err){
//  cerr << "Error in mynr.cpp!\n";
//  cerr << err << endl;
// }
//gammln, page 214
double gammln(double xx){
  static double cof[6]={76.18009172947146,-86.50532032941677,
			24.01409824083091,-1.231739572450155,
			0.1208650973866179e-2,-0.5395239384953e-5};
  double x;
  double y=x=xx;
  double tmp=x+5.5;
  tmp -= (x+0.5)*log(tmp);
  double ser=1.000000000190015;
  for (int j=0;j<=5;j++) ser += cof[j]/++y;
  return -tmp+log(2.5066282746310005*ser/x);
}
