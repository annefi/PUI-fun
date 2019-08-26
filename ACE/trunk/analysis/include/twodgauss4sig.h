#ifndef TWODGAUSS4SIG_H
#define TWODGAUSS4SIG_H

#include "analysis.h"
#include <vector>
#include <math.h>
#include <heavyside.h>

double twodgauss4sig(int x,int y, vdouble &param, vdouble &deriv, int numpar, int numion, vint &iparam, double range);

#endif
