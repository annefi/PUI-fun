#include <math.h>

void mmqbyhand(double eq, double pav, int tch, int ech, 
	       double *mm, double *mq){
  
  double u,v,w,lnm,lnmq;  // tmp variables 
  double dtch, dech;

  /* mass */
  u = log((double)tch) - 1.632172; // Toff = 0, TDAC = -6.632172
  v = log((double)ech) + 0.873459; // Eoff = 0, EDAC = 0.873459

  lnm = 148.183121 + 
    v * (-38.264587 + 12.013794 * u + 2.051758 * v) + 
    u * (-76.847427 + 1.865540 * u * u);

  /* mass/charge */
  u = log((double)tch) - 1.632172; //same but included for parallel with libhef
  w = log(eq + pav);

  lnmq = -375.813843 +
    34.595764 * w +
    69.191528 * u;

/*   *mq = exp(lnmq); */
/*   *mm = exp(lnm); */

/*   *mq = lnmq - 29.21; // arb. offset */
/*   *mm = lnm - 55.49;  // arb. offset */

  *mq = lnmq;
  *mm = lnm;

  if (*mq != 0.0 && *mm !=0.0){
    //printf("mmqbyhand -D- lnmq=%f *mq=%f lnm=%f *mm=%f\n",lnmq,*mq,lnm,*mm);
  }

  return;
}
