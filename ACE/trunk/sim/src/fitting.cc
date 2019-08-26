#include "fitting.h"

using namespace std;

#define IA 16807
#define IM 2147483647
#define AM (1.0/IM)
#define IQ 127773
#define IR 2836
#define NTAB 32
#define NDIV (1+(IM-1)/NTAB)
#define FIT_EPS 1.2e-7 
  // EPS collides with ../lib/libmymath/mynr.h and is only used in the next line???
#define RNMX (1.0-FIT_EPS)


bool maxlifit(Matrix<double> &y, vector<double> &para, vector<double> &a, vector<double> &a_lo, vector<double> &a_hi, vector<int> &ia, Matrix<double>&covar, Matrix<double>&alpha, double &merit, bool (*funcs)(int, int , vector<double> &, vector<double> &, double *, vector<double> &, int, int), int &newit)
{

  //for (int i = 0; i < 256; i++){
  //  for (int j = 0; j < 1024; j++){
  //    if (y[i][j]) cout << y[i][j] << endl;
  //  }
  //} 

  double merit0 = 0.;
  double merit1 = 0.;
  // cout << ydim << "   " << xdim << endl;
  for (int i = 0; i < ydim; i ++){
    for (int j = 0; j < xdim; j ++){
      //     cout << i << "  " << j << endl;
      merit0 += logfak(y[i][j]);
    }
  }
  double alamda = -1.;
  merit = 1.e10;
  double omerit = merit;
  int itst = 0;
  int max_test = 5;
  int max_pass = 20;
  int pass = 0;
  double mod_merit = 0.;
  //cout << "entering while loop" << endl; 
  while (itst < max_test && pass < max_pass) {
    omerit = merit;
    //cout << "calling mrqmin" << itst << "  " << pass << endl;
    mrqmin(y, para, a, a_lo, a_hi, ia, covar, alpha, merit1, funcs, alamda, newit);
    //cout << "leaving mrqmin" << endl;
    //cout << "merit0 = " << merit0 << "  merit1 = " << merit1 << endl;
    merit = merit0 + merit1;
    //cout << "entering get_mod_mer" << endl;
    get_mod_mer(para,a,mod_merit,funcs);
    //cout << "leaving get_mod_mer" << endl;
    if (merit > omerit) itst = 0;
    else if (merit > 0.95*omerit && merit <= omerit && merit < 2*mod_merit) itst++;
    pass++;
    //else if (merit > 0.95*omerit && merit <= omerit ) itst++;
    //if (merit == omerit) itst = max_test;
  }
  //cout << "leaving while loop" << endl;
  alamda = 0.;
  //cout << "calling mrqmin" << endl;
  mrqmin(y, para, a, a_lo, a_hi, ia, covar, alpha, merit1, funcs, alamda, newit);
  //cout << "leaving mrqmin" << endl;
  merit = merit0 + merit1;
  return true;
}


double logfak(double x)
{
  double aux = 0.;
  if (x < 10) {
    for (int i = int(x); i >= 1; i --) aux += log(double(i));
  } else {
    aux = x*log(x)-x+0.5*log(2.*PI*x)+1./12./x - 1./360.*pow(x,-3.) + 1./1260.*pow(x,-5.) - 1./1680*pow(x,-7.);
    aux += 8.4175084e-5*pow(x,-9.) - 2.3010323e-4*pow(x,-11.);
  }
  return aux;
}


bool get_mod_mer(vector<double> &para,vector<double> &a, double &mod_merit, bool (*funcs)(int, int, vector<double> &, vector<double> &,double *, vector<double> &, int, int))
{
  double tmp;
  double tmp2;
  double tmp3;
  int ma = a.size();
  vector<double> dydam(ma,0.);
  double ymod = 0.;
  mod_merit = 0.;
  
  for (int k = 0; k < ma; k++){
    normgauss[k] = 0.;
    for (int i = 0; i < ydim; i++){
      for (int j = 0; j < xdim ; j++){
	tmp2 = para[((k+1)*5)-3]-double(j);
	tmp2 = tmp2 / para[(k+1)*5-2];
	tmp2 = tmp2*tmp2;
	tmp2 = tmp2 / 2.;
	tmp3 = para[((k+1)*5)-1]-double(i);
	tmp3 = tmp3 / para[(k+1)*5];
	tmp3 = tmp3*tmp3;
	tmp3 = tmp3 / 2.;
	tmp = exp(-tmp2)*exp(-tmp3);
	normgauss[k]+= tmp;
      }
    }
  }
  /*
  cout << "entering funcs-loop  " << normgauss[0] << endl;
  cout << "nspill = " << a[0] << endl;
  cout << "sigmaT = " << para[3] << endl;
  cout << "sigmaE = " << para[5] << endl;
  */

  for (int i = 0; i < ydim; i++) {
    for (int j = 0; j < xdim; j++){
      
      funcs(i,j,para,a,&ymod,dydam,ma,numberions);
      //    cout << i << "  " << j << " ymod = " << ymod << endl;
      double aux2 = poidev(ymod, &idum);
      mod_merit += logfak(aux2) + ymod - aux2*log(ymod);
    }
  }
  return true;
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


bool mrqmin(Matrix<double> &y, vector<double> &para, vector<double> &a, vector<double> &a_lo, vector<double> &a_hi, vector<int> &ia, Matrix<double> &covar, Matrix<double> &alpha, double &chisq, bool (*funcs)(int, int, vector<double> &, vector<double> &, double *, vector<double> &, int, int), double &alamda, int &newit)
{
  //  void covsrt(vector<vector<double> >&covar, vector<int> &ia, int mfit);
  //  void gaussj(vector<vector<double> >&a, int n, vector<vector<double> >&b);
  //  void mrqcof(vector<vector<double> >&field, vector<vector<double> >&y, vector<vector<double> >&sig, vector<double> &a,
  //	      vector<int> &ia, vector<vector<double> >&alpha, vector<double> &beta, double &chisq,
  //	      void (*funcs)(double, vector<double> &, double *, vector<double> &, int));

  //for (int i = 0; i < 256; i++){
  //  for (int j = 0; j < 1024; j++){
  //    if (y[i][j]) cout << "mrqmin: ydata = " << y[i][j] << endl;
  //  }
  //}


  int j,k,l;
  int ma = a.size();
  int mfit;
  for (mfit=0,j=0;j<ma;j++)
    if (ia[j]) mfit++;
  //cout << "mrqmin: mfit = " << mfit << endl;
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
  //  cout << "in mrqmin: ma, beta[0], mfit, ia[1] = " << ma << ", " << beta[0] << ", " << mfit << "\t" << ia[1] << ", and newit = " << newit << endl;
  //for (int i = 0; i < ma; i++) cout << "in mrqmin index is " << i << "\t and ia[index] is " << ia[i] << endl;
  
  if (alamda < 0.0) {
    alamda=.001;
    //cout << "entering mrqcof" << endl;
    mrqcof(y,para,a,ia,alpha,beta,chisq,funcs);
    //cout << "leaving mrqcof" << endl;
    ochisq=chisq;
    for (j=0;j<ma;j++) atry[j]=a[j];
  }
  for (j=0;j<mfit;j++) {
    for (k=0;k<mfit;k++) {
      covar[j][k] = alpha[j][k];
    }
  }
  for (j=0;j<mfit;j++) {
    covar[j][j]=alpha[j][j]*(1.0+alamda);
    oneda[j][0]=beta[j];
  }
  gaussj(covar, mfit, oneda);
  for (j=0;j<mfit;j++){
    da[j]=oneda[j][0];
    //cout << "da = " << da[j] << endl;
  }
  if (alamda == 0.0) {
    covsrt(covar,ia,mfit);
    covsrt(alpha,ia,mfit);
    return true;
  }
  for (j=0,l=0;l<ma;l++){
    if (ia[l]) atry[l]=a[l]+da[j++];
  }
  mrqcof(y,para,atry,ia,covar,da,chisq,funcs);
  //cout << atry[0] << "  " << atry[1] << endl;
  //cout << "end of mrqmin" << endl;

  if (chisq < ochisq && param_bounds(atry,a_lo,a_hi,ia)) {
    alamda *= 0.1;
    ochisq=chisq;
    for (j=0;j<mfit;j++) {
      for (k=0;k<mfit;k++) alpha[j][k]=covar[j][k];
      beta[j]=da[j];
    }
    a = atry;
  } else {
    alamda *= 10.0;
    chisq=ochisq;
  }
  return true;
}

int param_bounds(vector<double> &a, vector<double> &a_lo, vector<double> &a_hi, vector<int> &ia)
{
  int n = a.size();
  int value = 1;
  
  for (int i = 0; i<n;i++) {
    if (ia[i] && (a[i] < a_lo[i] || a[i] > a_hi[i])) {
      cout << "in param_bounds: " << i << "\t" << a_lo[i] << "\t" << a[i] << "\t" << a_hi[i] << endl;
      value = 0;
    }
  }
  
  return value;
}


bool mrqcof(Matrix<double> &y, vector<double> &para, vector<double> &a, vector<int> &ia,
	    Matrix<double> &alpha, vector<double> &beta, double &chisq,
	    bool (*funcs)(int, int, vector<double> &, vector<double> &, double *, vector<double> &, int, int))
{
  //for (int i = 0; i < 256; i++){
  //  for (int j = 0; j < 1024; j++){
  //    if (y[i][j]) cout << "mrqcof: ydata = " << y[i][j] << endl;
  //  }
  //}



  int i,j,k,l,m,mfit=0;
  double ymod,wt,sig2i;
  double tmp;
  double tmp2;
  double tmp3;
  int ma = a.size();
  vector<double> dyda(ma,0.);
  for (j=0;j<ma;j++){
    if (ia[j]) mfit++;
  }
  //cout << "mrqcof: mfit = " << mfit << endl;
  for (j=0;j<mfit;j++) {
    for (k=0;k<mfit;k++) alpha[j][k]=0.0;
    beta[j]=0.0;
  }
  chisq=0.0;

  for (int k = 0; k < ma; k++){
    normgauss[k] = 0.;
    for (int i = 0; i < ydim; i++){
      for (int j = 0; j < xdim ; j++){
	tmp2 = para[((k+1)*5)-3]-double(j);
	tmp2 = tmp2 / para[(k+1)*5-2];
	tmp2 = tmp2*tmp2;
	tmp2 = tmp2 / 2.;
	tmp3 = para[((k+1)*5)-1]-double(i);
	tmp3 = tmp3 / para[(k+1)*5];
	tmp3 = tmp3*tmp3;
	tmp3 = tmp3 / 2.;
	tmp = exp(-tmp2)*exp(-tmp3);
	normgauss[k]+= tmp;
      }
    }
    //    sum2[k] = param2[k] / sum2[k];
  }
  
  //cout << "normgauss = " << normgauss[0] << endl;
  for (int n = 0; n < ydim; n++){
    for (int o = 0; o < xdim; o++){
      funcs(n,o,para,a,&ymod,dyda,ma,numberions);
      //if (y[n][o] > 0) cout << n << "  " << o << "  " << "ymod = " << ymod << endl;
      //cout << n << "  " << o << "  " << "ydat = " << y[n][o] << endl;
      //if (ymod>0.1) cout << "mrqcof: ymod = " << ymod << endl;
      for (j=0,l=0;l<ma;l++) {
	if (ia[l]) {
	  for (j++,k=0,m=0;m<=l;m++) {
	    //if (ia[m] && ymod > 0) alpha[j-1][k++] += sig2i *dyda[l]*dyda[m];
	    if (ia[m] && ymod > 0) alpha[j-1][k++] += y[n][o]*(dyda[l]/ymod)*(dyda[m]/ymod);
	  }
	}
	if (ymod > 0) beta[j-1] += - dyda[l]*(ymod - y[n][o])/ymod;
	//if (ymod > 0) beta[j-1] += - dyda[l]*(1. - (y[n][o]/ymod));
	/*
	if (y[n][o] > 0) {
	cout << "yd = " << y[n][o] << endl;
	cout << "ym = " << ymod << endl;
	cout << "yd/ym = " << (1. - y[n][o]/ymod) << endl; 
	cout << "dyda = " << dyda[l] << endl; 
	cout << "beta" << (j-1) << " = " << beta[j-1] << endl; 
	}
	*/
      }
      if (ymod>0) chisq += ymod-y[n][o]*log(ymod)+logfak(y[n][o]);//Chi squared version: dy*dy*sig2i;  
    }
    
    //chisq += ymod-y[n][o]*log(ymod);//Chi squared version: dy*dy*sig2i;
    
  }

  /*  for (j = 0; j < ma; j++){
      cout << "beta" << (j) << " = " << beta[j] << endl;
      }
  */
  for (j = 1; j < mfit; j++){
    for (k = 0; k < j; k++){
      alpha[k][j]=alpha[j][k];
    }
  }
  return true;
}

bool covsrt(Matrix<double> &covar, vector<int> &ia, int mfit)
{
  int i,j,k;
  int ma = covar[0].size();
  
  assert(ma == covar[0].size());
  
  for (i=mfit;i<ma;i++)
    for (j=0;j<i;j++) covar[i][j]=covar[j][i]=0.0;
  k=mfit-1;
  for (j=ma-1;j>=0;j--) {
    if (ia[j]) {
      for (i=0;i<ma;i++) {
	swap(covar[i][k],covar[i][j]);
	for (i=0;i<ma;i++) {
	  swap(covar[k][i],covar[j][i]);
	}
      }
      k--;
    }
  }
  return true;
}


bool gaussj(Matrix<double> &a, int n, vector<vector<double> > &b)
{
  int i,icol,irow,j,k,l,ll;
  double big,dum,pivinv,temp;
  //int n = a[0].size();
  int m = b[0].size();
  vector<int> indxc(n,0); 
  vector<int> ipiv(n,0);  
  vector<int> indxr(n,0); 
  for (i=0;i<n;i++) {
    big=0.0;
    for (j=0;j<n;j++)
      if (ipiv[j] != 1)
	for (k=0;k<n;k++) {
	  if (ipiv[k] == 0) {
	    if (fabs(a[j][k]) >= big) {
	      big=fabs(a[j][k]);
	      irow=j;
	      icol=k;
	    }
	  }
	  else if (ipiv[k] > 1) cout <<"gaussj: Singular Matrix-1" <<endl;
	}
    ++(ipiv[icol]);
    if (irow != icol) {
      for (l=0;l<n;l++) {
	swap(a[irow][l],a[icol][l]);
	for (l=0;l<m;l++) {
	  swap(b[irow][l],b[icol][l]);
	}
      }
    }
    indxr[i]=irow;
    indxc[i]=icol;
    if (a[icol][icol] == 0.0) cout<< "gaussj: Singular Matrix-2 at icol = " << icol <<endl;
    pivinv=1.0/a[icol][icol];
    a[icol][icol]=1.0;
    for (l=0;l<n;l++) a[icol][l] *= pivinv;
    for (l=0;l<m;l++) b[icol][l] *= pivinv;
    for (ll=0;ll<n;ll++){
      if (ll != icol) {
	dum=a[ll][icol];
	a[ll][icol]=0.0;
	for (l=0;l<n;l++) a[ll][l] -= a[icol][l]*dum;
	for (l=0;l<m;l++) b[ll][l] -= b[icol][l]*dum;
      }
    }
  }
  for (l=n-1;l>=0;l--) {
    if (indxr[l] != indxc[l])
      for (k=0;k<n;k++)
	swap(a[k][indxr[l]],a[k][indxc[l]]);
  }
  indxc.clear();indxr.clear();ipiv.clear();
}


