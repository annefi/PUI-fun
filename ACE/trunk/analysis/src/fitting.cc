#include "fitting.h"

using namespace std;

bool maxlifit(mdouble &y, vdouble &a, vdouble &a_lo, vdouble &a_hi, vint &ia, mdouble&covar, mdouble&alpha, double &merit, double (*funcs)(int, int , vdouble &, vdouble &, int, int,vint &, double))
{

  string thisprogram = "maxlifit : ";

  int dbglvl = 0;

  double alamda = -1.;
  double omerit; 
  int itst = 0;
  int pass = 0;
  int max_test = 50;
  int max_pass = 10;

  int ma = a.size();
  int mfit = 0;
  for (int j=0;j<ma;j++){
    if (ia[j]){
      mfit++;
    }
  }

  vdouble atry(ma,0.), beta(ma,0.),da(ma,0.);
  dbgvector<vdouble> oneda(mfit,vdouble(1,0.));
  double ochisq;

  merit = 1.e20;

  while (itst < max_test && pass < max_pass) {
    omerit = merit;
    if (dbglvl >= 1){
      cout << thisprogram << "calling mrqmin  " << itst << "  " << pass << endl;
    }
    mrqmin(y, a, a_lo, a_hi, ia, covar, alpha, merit, funcs, alamda,atry,beta,da,oneda,ochisq);
    if (dbglvl >= 1){
      cout << thisprogram << "leaving mrqmin" << endl;
    }
    if (merit == omerit){
      pass++;
    }
    else{
      pass = 0;
      itst++;
    }
    omerit = merit;
  }

  alamda = 0.;
  if (dbglvl >= 1){
    cout << "final call of mrqmin" << endl;
  }
  mrqmin(y, a, a_lo, a_hi, ia, covar, alpha, merit, funcs, alamda,atry,beta,da,oneda,ochisq);
  if (dbglvl >= 1){
    cout << "leaving mrqmin" << endl;
  }
  return true;
}


bool mrqmin(mdouble &y, vdouble &a, vdouble &a_lo, vdouble &a_hi, vint &ia, mdouble &covar, mdouble &alpha, double &chisq, double (*funcs)(int, int, vdouble &, vdouble &, int, int, vint &, double), double &alamda, vdouble &atry, vdouble &beta, vdouble &da, dbgvector<vdouble> &oneda, double &ochisq)
{

  string thisprogram = "mrqmin : ";
  int debuglvl = 0;
  
  int j,k,l;
  int ma = a.size();
  int mfit;
  for (mfit=0,j=0;j<ma;j++){
    if (ia[j]){
      mfit++;
    }
  }
  /*
  // Originally the next three lines are declared as static!!! Perhaps an errorsource  
  static vdouble atry(ma,0.), beta(ma,0.),da(ma,0.);
  static dbgvector<vdouble> oneda(mfit,vdouble(1,0.));
  static double ochisq;
  */
  
  if (alamda < 0.0) {
    alamda=.001;
    if (debuglvl >= 1){
      cout << thisprogram << "entering mrqcof" << endl;
    }
    mrqcof(y,a,ia,alpha,beta,chisq,funcs);
    if (debuglvl >= 1){
      cout << thisprogram << "leaving mrqcof" << endl;
    }
    ochisq=chisq;
    for (j=0;j<ma;j++){
      atry[j]=a[j];
    }
  }
  //  cout << thisprogram << "initialization end" << endl;
  for (j=0;j<mfit;j++) {
    for (k=0;k<mfit;k++) {
      covar[j][k] = alpha[j][k];
    }
  }
  //  cout << thisprogram << "mfit = " << mfit << endl;

  for (j=0;j<mfit;j++) {
    covar[j][j]=alpha[j][j]*(1.0+alamda);
    oneda[j][0]=beta[j];
  }
  
  if (debuglvl >= 1){
    cout << thisprogram << "entering gaussj" << endl;
  }
  gaussj(covar, mfit, oneda);
  if (debuglvl >= 1){
    cout << thisprogram << "leaving gaussj" << endl;
  }
  for (j=0;j<mfit;j++){
    da[j]=oneda[j][0];
  }
  if (alamda == 0.0) {
    covsrt(covar,ia,mfit);
    covsrt(alpha,ia,mfit);
    return true;
  }
  for (j=0,l=0;l<ma;l++){
    if (ia[l]){
      atry[l]=a[l]+da[j++];
    }
  }
  if (debuglvl >= 1){
    cout << thisprogram << "entering mrqcof" << endl;
  }
  mrqcof(y,atry,ia,covar,da,chisq,funcs);
  if (debuglvl >= 1){
    cout << thisprogram << "leaving mrqcof" << endl;
  }
  double normchisq;
  double normochisq;
  double area = (9.*9.)-7;

  normochisq = ochisq / area;
  normchisq = chisq / area;
  //  cout << thisprogram << "normchisq = " << normchisq << endl;
  //  cout << thisprogram << "normochisq = " << normochisq << endl;

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

int param_bounds(vdouble &a, vdouble &a_lo, vdouble &a_hi, vint &ia)
{
  
  string thisprogram = "param_bounds : ";
  
  int n = a.size();
  int value = 1;
  
  for (int i = 0; i<n;i++) {
    if (ia[i] && (a[i] < a_lo[i] || a[i] > a_hi[i])) {
      cout << thisprogram << "in param_bounds: " << i << "\t" << a_lo[i] << "\t" << a[i] << "\t" << a_hi[i] << endl;
      value = 0;
    }
  }
  
  return value;
}


bool mrqcof(mdouble &y, vdouble &a, vint &ia,
	    mdouble &alpha, vdouble &beta, double &chisq,
	    double (*funcs)(int, int, vdouble &, vdouble &, int, int, vint &, double))
{

  string thisprogram = "mrqcof : ";

  //  cout << thisprogram << "entering mrqcof" << endl;

  int mfit=0;
  double ymod,wt;
  double dy;
  double ydim = y.size(0);
  double xdim = y.size(1);

  
  double signo;
  int ma = a.size();
  vdouble dyda(ma,0.);
  

  int numberions = ma / 7;

  
  for (int j=0;j<mfit;j++) {
    for (int k=0;k<mfit;k++) {
      alpha[j][k]=0.0;
    }
    beta[j]=0.0;
  }
  chisq=0.0;

  vint fition(ia.size(),0);


  /*
    for (int n = 0; n < ydim; n++){
    for (int o = 0; o < xdim; o++){
  */

  // cout << thisprogram << "entering mainloop" << endl;
  /*
  for (int n = yleft; n < yright; n++){
    for (int o = xleft; o < xright; o++){
  */
  for (int n = 0; n < ydim; n++){
    for (int o = 0; o < xdim; o++){
      
      //if (y[n][o] != 0){
      if (1){

	ymod = funcs(o,n,a,dyda,ma,numberions,ia,3.);
	// following lines added for normal chisq

	signo = 1;
	/*
	  if (y[n][o] != 0){
	  signo = 1.0/y[n][o];
	  }
	  else{
	  signo = 0.;
	  }
	*/
	dy = y[n][o] - ymod;
      
	// added lines end here 
      
	for (int j=0,l=0;l<ma;l++) {
	  if (ia[l]) {
	    // following line added for normal chisq
	    wt = dyda[l]*signo;

	    j++;
	    for (int k=0,m=0;m<=l;m++) {
	      if (ia[m]){
		//if (ia[m] && ymod > 0 && y[n][o] > 0) {
		//cout << thisprogram << "vor alpha" << endl;
		alpha[j-1][k++] += wt*dyda[m];
		//alpha[j-1][k++] += ((y[n][o]*(dyda[l]/ymod)*dyda[m]/ymod));
		//cout << thisprogram << "nach alpha" << endl;
		//}
		//else{
		//k++;
		//}
	      }
	    }
	    //  	cout << thisprogram << "vor beta" << endl;
	    beta[j-1] += dy*wt;
	    //if (ymod > 0) beta[j-1] += - dyda[l]*(1. - (y[n][o]/ymod));
	    //	cout << thisprogram << "nach beta" << endl;
	  
	  }
	
	}
      }
      chisq += dy*dy*signo;
      //if (ymod>0) chisq += ymod - y[n][o]*log(ymod);//Chi squared version: dy*dy*sig2i;  

    }
  }
  // cout << thisprogram << "leaving mainloop" << endl;
   
  for (int j = 1; j < mfit; j++){
    for (int k = 0; k < j; k++){
      alpha[k][j]=alpha[j][k];
    }
  }

  //  cout << thisprogram << "leaving mrqcof" << endl;

  return true;
}

bool covsrt(mdouble &covar, vint &ia, int mfit)
{

  string thisprogram = "covsrt";
  
  int k;
  int ma = covar[0].size();
  
  //assert(ma == int(covar[0].size()));
  
  for (int i=mfit;i<ma;i++){
    //for (j=0;j<i;j++) covar[i][j]=covar[j][i]=0.0; //original from Robert but I think it's wrong
    for (int j=0;j<=i;j++){
      covar[i][j]=covar[j][i]=0.0;
    }
  }
  k=mfit-1;
  for (int j=ma-1;j>=0;j--) {
    if (ia[j]) {
      for (int i=0;i<ma;i++) {
	swap(covar[i][k],covar[i][j]);
      }
      for (int i=0;i<ma;i++) {
	swap(covar[k][i],covar[j][i]);
      }
      k--;
    }
  }
  return true;
}


void gaussj(mdouble &a, int n, dbgvector<vdouble> &b)
{

  string thisprogram = "gaussj : ";

  //cout << thisprogram << "entering gaussj" << endl;

  int icol = 0;
  int irow = 0;
  double big,dum,pivinv;
  //int n = a[0].size();
  int m = b[0].size();
  vint indxc(n,0); 
  vint ipiv(n,0);  
  vint indxr(n,0); 
  //  cout << thisprogram << "n = " << n << endl;
  //cout << thisprogram << "m = " << m << endl;
  
  for (int i=0;i<n;i++) {
    //    cout << thisprogram << "i = " << i << endl;
    big=0.0;
    for (int j=0;j<n;j++){
      //cout << thisprogram << "j = " << j << endl;
      if (ipiv[j] != 1){
	for (int k=0;k<n;k++) {
	  //  cout << thisprogram << "k = " << k << endl;
	  if (ipiv[k] == 0) {
	    if (fabs(a[j][k]) >= big) {
	      big=fabs(a[j][k]);
	      irow=j;
	      icol=k;
	    }
	  }
	  else if (ipiv[k] > 1){
	    cout << thisprogram << "Singular Matrix-1" <<endl;
	  }
	}  
      }
    }
    // cout << thisprogram << "leaving j-loop" << endl;
    // cout << thisprogram << "icol = " << icol << endl;

    ++(ipiv[icol]);
    //cout << thisprogram << "flag2" << endl;
    if (irow != icol) {
      for (int l=0;l<n;l++) {
	//cout << thisprogram << "1.l = " << l << endl;
	swap(a[irow][l],a[icol][l]);
      }
      for (int l=0;l<m;l++) {
	//cout << thisprogram << "2.l = " << l << endl;
	swap(b[irow][l],b[icol][l]);
      }
      
    }
    indxr[i]=irow;
    indxc[i]=icol;
    if (a[icol][icol] == 0.0) cout << thisprogram << "Singular Matrix-2 at icol = " << icol <<endl;
    pivinv=1.0/a[icol][icol];
    a[icol][icol]=1.0;
    for (int l=0;l<n;l++){
      a[icol][l] *= pivinv;
    }
    for (int l=0;l<m;l++){
      b[icol][l] *= pivinv;
    }
    for (int ll=0;ll<n;ll++){
      if (ll != icol) {
	dum=a[ll][icol];
	a[ll][icol]=0.0;
	for (int l=0;l<n;l++){
	  a[ll][l] -= a[icol][l]*dum;
	}
	for (int l=0;l<m;l++){
	  b[ll][l] -= b[icol][l]*dum;
	}
      }
    }
  }
  for (int l=n-1;l>=0;l--) {
    if (indxr[l] != indxc[l]){
      for (int k=0;k<n;k++){
	swap(a[k][indxr[l]],a[k][indxc[l]]);
      }
    }
  }
  indxc.clear();indxr.clear();ipiv.clear();
}


