//-----------------------------------------------------------------------------
/* \file mynr.cpp
 * \version 1.0
 * \author Fredy Dobler (dobler@phim.unibe.ch)
 * \date 1999-2000
 * \brief adapting the function of the book <<Numerical Recipes in C>>

 * Function copied from the book

 * Numerical Recipes in C, Second Edition

 * W. H. Press, S. A. Teukolsky, W. T. Vetterling, B. P. Flannery

 * Cambridge University Press

 * and adapting them to our interface
 */
// -----------------------------------------------------------------------------

#include <iostream>
#include <string>
#include <math.h>
#include "mynr.h"

using namespace std;

static double maxarg1,maxarg2;
#define FMAX(a,b) (maxarg1=(a),maxarg2=(b),(maxarg1) > (maxarg2) ?\
        (maxarg1) : (maxarg2))

static int iminarg1,iminarg2;
#define IMIN(a,b) (iminarg1=(a),iminarg2=(b),(iminarg1) < (iminarg2) ?\
        (iminarg1) : (iminarg2))

#define SIGN(a,b) ((b) >= 0.0 ? fabs(a) : -fabs(a))

double SQR(const double &a) {
  return pow(a,2);
}

//stepfunction
int stepf(double x){
  if (x < 0 ) return 0;
  return 1;
}


///Print errors
void nrerror(string err){
  cerr << "Error in mynr.cpp!\n";
  cerr << err << endl;
}

///Error Funktion: Page 220, (6.2.8)
double myerff(double x){
  return x < 0.0 ? -gammp(0.5,x*x) : gammp(0.5,x*x);
}

///Returns the incomplete gamma function P(a,x)
///Page 218
double gammp(double a, double x){
  double gamser, gammcf, gln;
  if (x<0.0 || a <= 0.0) nrerror("Invalid arguments in routine gammp");
  if (x < (a+1.0)) {
    gser(gamser,a,x,gln);
    return gamser;
  }
  else {
    gcf(gammcf,a,x,gln);
    return 1.0-gammcf;
  }
}

///Returns the incomplete gamma function Q(a,x) := 1 - P(a,x)
///Page 218
double gammq(double a, double x){
  double gamser, gammcf, gln;
  
  if (x<0.0 || a <= 0.0) nrerror("Invalid arguments in routine gammp");
  if (x < (a+1.0)) {
    gser(gamser,a,x,gln);
    return 1.0-gamser;
  }
  else {
    gcf(gammcf,a,x,gln);
    return gammcf;
  }
}


///gser, page 218
void gser(double &gamser, double a, double x, double &gln){
  gln = gammln(a);
  if (x <= 0.0) {
    if (x< 0.0) nrerror("x less than 0 in routine gser");
    gamser=0.0;
    return;
  }
  else {
    double sum, del;
    double ap=a;
    del=sum=1.0/a;
    for (int n=1; n <= ITMAX; n++) {
      ++ap;
      del *= x/ap;
      sum += del;
      if (fabs(del) < fabs(sum)*EPS) {
	gamser=sum*exp(-x+a*log(x)-(gln));
	return;
      }
    }
    nrerror("a too large, ITMAX too small in routine gser");
    return;
  }
}

///gcf, page 219
void gcf(double &gammcf, double a, double x, double &gln) {
  gln = gammln(a);
  double b=x+1.0-a;
  double c=1.0/FPMIN;
  double d=1.0/b;
  double h=d;
  double an,del;
  for (int i=1; i <= ITMAX; i++) {
    an = -i*(i-a);
    b+= 2.0;
    d=an*d+b;
    if(fabs(d) < FPMIN) d=FPMIN;
    c=b+an/c;
    if(fabs(c) < FPMIN) c=FPMIN;
    d=1.0/d;
    del=d*c;
    h *= del;
    if (fabs(del-1.0) < EPS) break;
  }
  if (a > ITMAX) nrerror("a too large, ITMAX too small in gcf");
  gammcf=exp(-x+a*log(x)-(gln))*h;
}

///gammln, page 214
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

///phythag, page 70
double pythag(double a, double b){
	double absa,absb;
	absa=fabs(a);
	absb=fabs(b);
	if (absa > absb) return absa*sqrt(1.0+SQR(absb/absa));
	else return (absb == 0.0 ? 0.0 : absb*sqrt(1.0+SQR(absa/absb)));
}


///svdcmp, page 67, double arrays are replace by vectors and Matrix
void svdcmp(Matrix<double> &a,vector<double> &w, Matrix<double> &v) {
  int flag,i,its,j,jj,k,l,nm;
  double anorm,c,f,g,h,s,scale,x,y,z;
  int m = a.size(0)-1;
  int n = v.size(0)-1;
  vector<double> rv1(n+1);
  g=scale=anorm=0.0;
  for (i=0;i<=n;i++) {
    l=i+1;
    rv1[i]=scale*g;
    g=s=scale=0.0;
    if (i <= m) {
      for (k=i;k<=m;k++) {
	scale += fabs(a[k][i]);  
      }
      if (scale) {
	for (k=i;k<=m;k++) {
	  a[k][i] /= scale;
	  s += a[k][i]*a[k][i];
	}
	f=a[i][i];
	g = -SIGN(sqrt(s),f);
	h=f*g-s;
	a[i][i]=f-g;
	for (j=l;j<=n;j++) {
	  for (s=0.0,k=i;k<=m;k++) s += a[k][i]*a[k][j];
	  f=s/h;
	  for (k=i;k<=m;k++) a[k][j] += f*a[k][i];
	}
	for (k=i;k<=m;k++) a[k][i] *= scale;
      }
    }
    w[i]=scale *g;
    g=s=scale=0.0;
    if (i <= m && i != n) {
      for (k=l;k<=n;k++) scale += fabs(a[i][k]);
      if (scale) {
	for (k=l;k<=n;k++) {
	  a[i][k] /= scale;
	  s += a[i][k]*a[i][k];
	}
	f=a[i][l];
	g = -SIGN(sqrt(s),f);
	h=f*g-s;
	a[i][l]=f-g;
	for (k=l;k<=n;k++) rv1[k]=a[i][k]/h;
	for (j=l;j<=m;j++) {
	  for (s=0.0,k=l;k<=n;k++) s += a[j][k]*a[i][k];
	  for (k=l;k<=n;k++) a[j][k] += s*rv1[k];
	}
	for (k=l;k<=n;k++) a[i][k] *= scale;
      }
    }
    anorm=FMAX(anorm,(fabs(w[i])+fabs(rv1[i])));
  }
  for (i=n;i>=0;i--) {
    if (i < n) {
      if (g) {
	for (j=l;j<=n;j++)
	  v[j][i]=(a[i][j]/a[i][l])/g;
	for (j=l;j<=n;j++) {
	  for (s=0.0,k=l;k<=n;k++) s += a[i][k]*v[k][j];
	  for (k=l;k<=n;k++) v[k][j] += s*v[k][i];
	}
      }
      for (j=l;j<=n;j++) v[i][j]=v[j][i]=0.0;
    }
    v[i][i]=1.0;
    g=rv1[i];
    l=i;
  }
  for (i=IMIN(m,n);i>=0;i--) {
    l=i+1;
    g=w[i];
    for (j=l;j<=n;j++) a[i][j]=0.0;
    if (g) {
      g=1.0/g;
      for (j=l;j<=n;j++) {
	for (s=0.0,k=l;k<=m;k++) s += a[k][i]*a[k][j];
	f=(s/a[i][i])*g;
	for (k=i;k<=m;k++) a[k][j] += f*a[k][i];
      }
      for (j=i;j<=m;j++) a[j][i] *= g;
    } else for (j=i;j<=m;j++) a[j][i]=0.0;
    ++a[i][i];
  }
  for (k=n;k>=0;k--) {
    for (its=1;its<=30;its++) {
      flag=1;
      for (l=k;l>=0;l--) {
	nm=l-1;
	if ((double)(fabs(rv1[l])+anorm) == anorm) {
	  flag=0;
	  break;
	}
	if ((double)(fabs(w[nm])+anorm) == anorm) break;
      }
      if (flag) {
	c=0.0;
	s=1.0;
	for (i=l;i<=k;i++) {
	  f=s*rv1[i];
	  rv1[i]=c*rv1[i];
	  if ((double)(fabs(f)+anorm) == anorm) break;
	  g=w[i];
	  h=pythag(f,g);
	  w[i]=h;
	  h=1.0/h;
	  c=g*h;
	  s = -f*h;
	  for (j=0;j<=m;j++) {
	    y=a[j][nm];
	    z=a[j][i];
	    a[j][nm]=y*c+z*s;
	    a[j][i]=z*c-y*s;
	  }
	}
      }
      z=w[k];
      if (l == k) {
	if (z < 0.0) {
	  w[k] = -z;
	  for (j=0;j<=n;j++) v[j][k] = -v[j][k];
	}
	break;
      }
      if (its == 30) nrerror("no convergence in 30 svdcmp iterations");
      x=w[l];
      nm=k-1;
      y=w[nm];
      g=rv1[nm];
      h=rv1[k];
      f=((y-z)*(y+z)+(g-h)*(g+h))/(2.0*h*y);
      g=pythag(f,1.0);
      f=((x-z)*(x+z)+h*((y/(f+SIGN(g,f)))-h))/x;
      c=s=1.0;
      for (j=l;j<=nm;j++) {
	i=j+1;
	g=rv1[i];
	y=w[i];
	h=s*g;
	g=c*g;
	z=pythag(f,h);
	rv1[j]=z;
	c=f/z;
	s=h/z;
	f=x*c+g*s;
	g = g*c-x*s;
	h=y*s;
	y *= c;
	for (jj=0;jj<=n;jj++) {
	  x=v[jj][j];
	  z=v[jj][i];
	  v[jj][j]=x*c+z*s;
	  v[jj][i]=z*c-x*s;
	}
	z=pythag(f,h);
	w[j]=z;
	if (z) {
	  z=1.0/z;
	  c=f*z;
	  s=h*z;
	}
	f=c*g+s*y;
	x=c*y-s*g;
	for (jj=0;jj<=m;jj++) {
	  y=a[jj][j];
	  z=a[jj][i];
	  a[jj][j]=y*c+z*s;
	  a[jj][i]=z*c-y*s;
	}
      }
      rv1[l]=0.0;
      rv1[k]=f;
      w[k]=x;
    }
  }
}

///invert matricies
void matrix_invert(Matrix<double> &matrix){
  int m=matrix.size(0),n=matrix.size(1);
  Matrix<double> U(matrix),W(m,n),V(m,n);
  fVECTOR W1(m);
  svdcmp(U,W1,V);
  for (unsigned int i=0;i<W1.size();i++){
    if (W1[i]==0)
      W[i][i]=0;  //numerical recipes, p. 52ff
    else
      W[i][i]=1/W1[i];
  }
  U.transpose();
  matrix=W*U;
  matrix=V*matrix;
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

///ran1, p.280
float ran1(long &idum){
	int j;
	long k;
	static long iy=0;
	static long iv[NTAB];
	float temp;

	if (idum <= 0 || !iy) {
		if (-(idum) < 1) idum=1;
		else idum = -(idum);
		for (j=NTAB+7;j>=0;j--) {
			k=(idum)/IQ;
			idum=IA*(idum-k*IQ)-IR*k;
			if (idum < 0) idum += IM;
			if (j < NTAB) iv[j] = idum;
		}
		iy=iv[0];
	}
	k=(idum)/IQ;
	idum=IA*(idum-k*IQ)-IR*k;
	if (idum < 0) idum += IM;
	j=iy/NDIV;
	iy=iv[j];
	iv[j] = idum;
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

///gasdev, p.289
float gasdev(long &idum) {
  float ran1(long &idum);
  static int iset=0;
  static float gset;
  float fac,rsq,v1,v2;

  if (idum < 0) iset=0;
  if  (iset == 0) {
    do {
      v1=2.0*ran1(idum)-1.0;
      v2=2.0*ran1(idum)-1.0;
      rsq=v1*v1+v2*v2;
    } while (rsq >= 1.0 || rsq == 0.0);
    fac=sqrt(-2.0*log(rsq)/rsq);
    gset=v1*fac;
    iset=1;
    return v2*fac;
  } else {
    iset=0;
    return gset;
  }
}

///mygasdev
float mygasdev(long &idum,const double &m1,const double &s1){
  return m1+s1*gasdev(idum);
}

///a special distribution to produce random values
/*! the distribution function is: left of the m1 value a gaussian function with standard deviation s1 and right of m1 a gaussian function with standard deviation s2
 */
float my2gasdev(long &idum,double &value2,const double &m1,const double &s1, const double &s2){
  float ran1(long &idum);
  double rsq,v1,v2;//sq1=pow(s1,2),sq2=pow(s2,2);
  do {
    v2=2.0*ran1(idum)-1.0;
    float a=(s1-s2)/((s1+s2));
    float rn=0;
    if (v2 < a) {
      rn=(v2-a)/(1+a);
    }
    else {
      rn=(v2-a)/(1-a);
    }
    v1=2.0*ran1(idum)-1.0;
    v2=rn;
    rsq=v1*v1+v2*v2;
  } while (rsq >= 1 || rsq == 0.0);
  if (v2 <0 ) {
    value2=m1+v2*s1*sqrt(-2.0*log(rsq)/rsq);
  }
  else {
    value2=m1+v2*s2*sqrt(-2.0*log(rsq)/rsq);
  }
  return m1+v1*s1*sqrt(-2.0*log(rsq)/rsq); 
}
