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
  int max_test = 25;
  int max_pass = 10;
  int allzero=1;

  int ma = a.size();
  int mfit = 0;
  for (int j=0;j<ma;j++){
    if (ia[j]){
      mfit++;
    }
  }
  if (mfit==0) return true;

  for (int i=0;i<y.size(0);i++){
    for (int j=0;j<y.size(1);j++){
      if (y[i][j]>0.){
	allzero=0;
      }
    }
  }
  if (allzero){
    for (int i=0;i<a.size();i++){
      if (ia[i]){
	a[i]=0.;
      }
    }
    return true;
  }

  vdouble atry(ma,0.), beta(ma,0.),da(ma,0.);
  vector<vdouble> oneda(mfit,vdouble(1,0.));
  double ochisq;

  merit = 1.e20;

  while (itst < max_test && pass < max_pass) {
    omerit = merit;
    if (dbglvl >= 1){
      cout << thisprogram << "calling mrqmin  " << itst << "  " << pass << endl;
    }
    if (!mrqmin(y, a, a_lo, a_hi, ia, covar, alpha, merit, funcs, alamda,atry,beta,da,oneda,ochisq)) return false;
    
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
  if (!mrqmin(y, a, a_lo, a_hi, ia, covar, alpha, merit, funcs, alamda,atry,beta,da,oneda,ochisq)) return false;
  if (dbglvl >= 1){
    cout << "leaving mrqmin" << endl;
  }
  return true;
}


bool mrqmin(mdouble &y, vdouble &a, vdouble &a_lo, vdouble &a_hi, vint &ia, mdouble &covar, mdouble &alpha, double &chisq, double (*funcs)(int, int, vdouble &, vdouble &, int, int, vint &, double), double &alamda, vdouble &atry, vdouble &beta, vdouble &da, vector<vdouble> &oneda, double &ochisq)
{

  string thisprogram = "mrqmin : ";
  int dbglvl = 0;  
  int j,k,l;
  int ma = a.size();
  int mfit;
  vint parachange(ia.size(),0);

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
    alamda=0.1;
    if (dbglvl >= 1){
      cout << thisprogram << "entering mrqcof" << endl;
    }
    if (!mrqcof(y,a,ia,alpha,beta,chisq,funcs)) return false;
    if (dbglvl >= 1){
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
  
  if (dbglvl >= 1){
    cout << thisprogram << "entering gaussj" << endl;
  }
  gaussj(covar, mfit, oneda);
  if (dbglvl >= 1){
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
      if (atry[l]<-0.0){
	atry[l]=0.0001;
	if (dbglvl >= 1){

	  cout << thisprogram << "atry[" << l << "] negative ->  atry[" << l << "] = 0.0" << endl;
	}
      }
    }
  }
  if (dbglvl >= 1){
    cout << thisprogram << "entering mrqcof" << endl;
  }
  if (!mrqcof(y,atry,ia,covar,da,chisq,funcs)){
    for (int i=0; i<ma; i++){
      if (atry[i]==-0.0) a[i]=-0.0;
    }
    return false;
  }
  if (dbglvl >= 1){
    cout << thisprogram << "leaving mrqcof" << endl;
  }
  double normchisq;
  double normochisq;

  normochisq = ochisq / 1.;
  normchisq = chisq / 1.;
  //  cout << thisprogram << "normchisq = " << normchisq << endl;
  //  cout << thisprogram << "normochisq = " << normochisq << endl;

  parachange=ia;
  //  if (chisq < ochisq && param_bounds(atry,a_lo,a_hi,ia)) {
  if (chisq < ochisq){
    //  if (chisq < ochisq && param_bounds(atry,a_lo,a_hi,ia,parachange)){
    //    param_bounds(atry,a_lo,a_hi,ia,parachange);
    alamda *= 0.1;
    ochisq=chisq;
    for (j=0;j<mfit;j++) {
      for (k=0;k<mfit;k++) alpha[j][k]=covar[j][k];
      beta[j]=da[j];
    }
    a=atry;
    /*
      for (int j=0;j<ia.size();j++){
      if (parachange[j]==1) a[j] = atry[j];
      if (parachange[j]==2) a[j] = a_lo[j];
      if (parachange[j]==3) a[j] = a_hi[j];
      }
    */
      
  } else {
    alamda *= 10.0;
    chisq=ochisq;
  }

  return true;
}

int param_bounds(vdouble &a, vdouble &a_lo, vdouble &a_hi, vint &ia, vint &parachange)
{
  
  string thisprogram = "param_bounds : ";
  
  int n = a.size();
  int value = 1;
  
  for (int i = 0; i<n;i++) {
    if (ia[i] && (a[i] < a_lo[i] || a[i] > a_hi[i]) && a[i]!=-1.) {
      cout << thisprogram << "in param_bounds: " << i << "\t" << a_lo[i] << "\t" << a[i] << "\t" << a_hi[i] << endl;
      value=0;
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
  int dbglvl=0;
  double ymod,wt;
  double dy;
  double ydim = y.size(0);
  double xdim = y.size(1);
  bool returnval=true;
  
  double signo;
  int ma = a.size();
  vdouble dyda(ma,0.);
  for (int i=0;i<ia.size();i++){
    if (ia[i]) mfit++;
  }
  

  int numberions = ma / 7;

  
  for (int j=0;j<mfit;j++) {
    for (int k=0;k<mfit;k++) {
      alpha[j][k]=0.0;
    }
    beta[j]=0.0;
  }
  chisq=0.0;

  for (int n = 0; n < ydim; n++){
    for (int o = 0; o < xdim; o++){
      
      if (1){//poissonian statistics
	//      if (y[n][o] != 0){//gaussian statistics
	ymod = funcs(o,n,a,dyda,ma,numberions,ia,3.);

	//	signo = 1;//gaussian statistics
	/*
	  if (y[n][o] != 0){
	  signo = 1.0/y[n][o];
	  }
	  else{
	  signo = 0.;
	  }
	*/
	//	dy = y[n][o] - ymod;//gaussian statistic
      
	// added lines end here 
	if (ymod > 0.){
	  for (int j=0,l=0;l<ma;l++) {
	    if (ia[l]) {
	      //	      wt = dyda[l]*signo;//poissonian statistics
	      j++;
	      for (int k=0,m=0;m<=l;m++) {
		//      if (ia[m]) alpha[j-1][k++] += wt*dyda[m];//gaussian statistics
		if (ia[m]) alpha[j-1][k++] += y[n][o]*(dyda[l]/ymod)*(dyda[m]/ymod);//poisson statistics
	      }
	      //beta[j-1] += dy*wt;//gaussian statistics
	      beta[j-1] += - dyda[l]*(1. - (y[n][o]/ymod));//poisson statistics
	    }
	
	  }
	}
      }
    //chisq += dy*dy*signo;//gaussian statistics
      if (ymod>0.) chisq += ymod - y[n][o]*log(ymod);//poisson statistics
    }
  }
  //  cout << "mfit = " << mfit << endl;
  //  cout << "alpha = " << endl;
  
  int numnonzero=0;
  for (int j=0;j<mfit;j++){
    if (alpha[j][j]==0.){
      returnval=false;
      alpha[j][j]=1.;
      int l=0;
      for (int k=0;k<ia.size();k++){
	if (ia[k]){
	  if (l==numnonzero) {
	    ia[k]=0;
	    a[k]=-0.0;
	    if (dbglvl >= 1){
	      cout << thisprogram << "param[" << k << "] = " << a[k] << endl;
	    }
	    l++;
	  }
	  else{
	    l++;
	  }
	}
      }
    }
    else{
      numnonzero++;
    }
  }

  /*
  for (int j=0;j<mfit;j++){
    for (int k=0;k<mfit;k++){
      cout << alpha[j][k] << " ";
    }
    cout << endl;
  }
  */
  // cout << thisprogram << "leaving mainloop" << endl;
  for (int j = 1; j < mfit; j++){
    for (int k = 0; k < j; k++){
      alpha[k][j]=alpha[j][k];
    }
  }

  //  cout << thisprogram << "leaving mrqcof" << endl;

  return returnval;
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


void gaussj(mdouble &a, int n, vector<vdouble> &b)
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
	    cerr << thisprogram << "Singular Matrix-1" <<endl;
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
    if (a[icol][icol] == 0.0) cerr << thisprogram << "Singular Matrix-2 at icol = " << icol <<endl;
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


double logfak(double x)
{
  double aux = 0.;
  if (x < 10) {
    for (int i = int(x); i >= 1; i --) aux += log(double(i));
  }
  else {
    aux = x*log(x)-x+0.5*log(2.*PI*x)+1./12./x - 1./360.*pow(x,-3.) + 1./1260.*pow(x,-5.) - 1./1680*pow(x,-7.);
    aux += 8.4175084e-5*pow(x,-9.) - 2.3010323e-4*pow(x,-11.);
  }
  return aux;
}


/*
calculates chisquare in the range of a given ion with a given set parameters for all ions.
*/
double calcchisq(mdouble &y,vdouble &param,int ion,double (*funcs)(int, int , vdouble &, vdouble &, int, int,vint &, double)){

  double chisq=0.0;
  double ymod;
  int ma = param.size();
  vdouble dyda(ma,0.);
  vint ia(ma,0);
  int numberions = ma / 7;
  int dbglvl=0;
  double range=3.;
  int xlb=int(param[ion*7+1]-range*param[ion*7+4]);
  int xrb=int(param[ion*7+1]+range*param[ion*7+3]+1.);
  int ylb=int(param[ion*7+2]-range*param[ion*7+6]);
  int yrb=int(param[ion*7+2]+range*param[ion*7+5]+1.);
  if (xlb<0){
    xlb=0;
  }
  if (xrb>511){
    xrb=511;
  }
  if (ylb<0){
    ylb=0;
  }
  if (yrb>127){
    yrb=127;
  }
  if (dbglvl>=1){
    cout << "xlb = " << xlb << endl;
    cout << "xrb = " << xrb << endl;
    cout << "ylb = " << ylb << endl;
    cout << "yrb = " << yrb << endl;
  }
  for (int n = ylb; n <= yrb ; n++){
    for (int o = xlb; o <= xrb; o++){
      
      //poissonian statistics
      ymod = funcs(o,n,param,dyda,ma,numberions,ia,3.);
      //calculating 
      if (ymod>0.) chisq += (ymod - y[n][o]*log(ymod)+logfak(y[n][o]));//poisson statistics
      //      if (ymod>0.) chisq += (ymod-y[n][o])*(ymod-y[n][o])/sqrt(ymod);
    }
  }
  return chisq;
}


/*
calculates and returns error of given ion. The mean of the + and - error are returned if the - error exeeds 0 only the + error is returned!
*/
double calcerror(mdouble &y,vdouble &param,int ion,double (*funcs)(int, int , vdouble &, vdouble &, int, int,vint &, double)){
  double errp=0.;
  double errm=0.;
  double error=0.;
  double chisqmin=calcchisq(y,param,ion,funcs);
  double deltachisq=0.;
  vdouble errorpar=param;
  while (deltachisq<1.){
    errorpar[ion*7]+=1.;
    double chisq=calcchisq(y,errorpar,ion,funcs);
    deltachisq=chisq-chisqmin;
  }
  deltachisq=0.;
  errorpar[ion*7]-=1.;
  while (deltachisq<1.){
    errorpar[ion*7]+=0.1;
    double chisq=calcchisq(y,errorpar,ion,funcs);
    deltachisq=chisq-chisqmin;
  }
  errp=errorpar[ion*7]-param[ion*7];
  errorpar=param;
  deltachisq=0.;
  while (deltachisq<1. && errorpar[ion*7]>=1.){
    errorpar[ion*7]-=1.;
    double chisq=calcchisq(y,errorpar,ion,funcs);
    deltachisq=chisq-chisqmin;
  }
  if (deltachisq<1.){
    errm=0.;
  }
  else{
    deltachisq=0.;
    errorpar[ion*7]+=1.;
    while (deltachisq<1. && errorpar[ion*7]>=1.){
      errorpar[ion*7]-=0.1;
      double chisq=calcchisq(y,errorpar,ion,funcs);
      deltachisq=chisq-chisqmin;
    }
    errm=param[ion*7]-errorpar[ion*7];
  }

  if (errm==0.){
    error=errp;
  }
  else{
    error=(errp+errm)/2.;
  }
  return error;
}


/*
function checks if there is at least a single count in the peakarea.
*/
bool scanion(mdouble &y,vdouble &param,int ion){
  double range=3.;
  double sum=0.;
  int xlb=int(param[ion*7+1]-range*param[ion*7+4]);
  int xrb=int(param[ion*7+1]+range*param[ion*7+3]+1.);
  int ylb=int(param[ion*7+2]-range*param[ion*7+6]);
  int yrb=int(param[ion*7+2]+range*param[ion*7+5]+1.);
  if (xlb<0){
    xlb=0;
  }
  if (xrb>511){
    xrb=511;
  }
  if (ylb<0){
    ylb=0;
  }
  if (yrb>127){
    yrb=127;
  }
  for (int n = ylb; n <= yrb ; n++){
    for (int o = xlb; o <= xrb; o++){
      sum+=y[n][o];
    }
  }
  if (sum==0.){
    return false;
  }
  else{
    return true;
  }
}

/*
returns vector that contains the errors for all ions that are in param.
*/
vdouble calcerrors(mdouble &y,vdouble &param,double (*funcs)(int, int , vdouble &, vdouble &, int, int,vint &, double)){
  vdouble errors(param.size()/7,0.);
  for (int ion=0;ion < param.size()/7;ion++){
    if (scanion(y,param,ion)){
      errors[ion]=calcerror(y,param,ion,funcs);
    }
    else{
      errors[ion]=0.;
    }
  }
  return errors;
}

