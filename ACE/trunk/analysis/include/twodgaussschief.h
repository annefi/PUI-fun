#ifndef TWODGAUSSSCHIEF_H
#define TWODGAUSSSCHIEF_H

#include "analysis.h"
#include <vector>
#include <math.h>
#include <heavyside.h>

double twodgaussschief(int x,int y, vdouble &param, vdouble &deriv, int numpar, int numion, vint &iparam, double range);

#endif
