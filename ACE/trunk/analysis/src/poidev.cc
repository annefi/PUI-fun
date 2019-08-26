#include "poidev.h"

using namespace std;

double poidev(double xm, long *idum)
{
	double ran_2(long *idum);
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
			t *= ran_2(idum);
			//cout << t << ", " << ran_2(idum)<< endl;
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
				y=tan(PI*ran_2(idum));
				//cout << y << endl;
				em=sq*y+xm;
			} while (em < 0.0);
			em=floor(em);
			t=0.9*(1.0+y*y)*exp(em*alxm-gammln(em+1.0)-g);
		} while (ran_2(idum) > t);
	}
	//cout << "in poidev em is " << em << endl;
	return max(double(0.),em);
}
