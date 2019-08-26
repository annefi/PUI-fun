#ifndef TWODGAUSS_H
#define TWODGAUSS_H

#include "analysis.h"
#include <vector>
#include <math.h>
#include <heavyside.h>

double twodgauss(int x,int y, vdouble &param, vdouble &deriv, int numpar, int numion, vint &iparam, double range);

#endif
