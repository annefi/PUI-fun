#include "nrutil.h"

void mprove(a,alud,n,indx,b,x)
float **a,**alud,b[],x[];
int indx[],n;
{
	void lubksb();
	int j,i;
	double sdp;
	float *r;

	r=vector(1,n);
	for (i=1;i<=n;i++) {
		sdp = -b[i];
		for (j=1;j<=n;j++) sdp += a[i][j]*x[j];
		r[i]=sdp;
	}
	lubksb(alud,n,indx,r);
	for (i=1;i<=n;i++) x[i] -= r[i];
	free_vector(r,1,n);
}
