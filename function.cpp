#include "function.h"
#include<math.h>
#include<string>
#include<QtGlobal>

#define EPS 1.e-5

double f_0(double x, double y) { Q_UNUSED(x); Q_UNUSED(y); return 1; }
double f_1(double x, double y) { Q_UNUSED(y); return x; }
double f_2(double x, double y) { Q_UNUSED(x); return y; }
double f_3(double x, double y) { return x + y; }
double f_4(double x, double y) { return sqrt(x*x + y*y); }
double f_5(double x, double y) { return x*x + y*y; }
double f_6(double x, double y) { return exp(x*x - y*y); }
double f_7(double x, double y) { return 1/(25*(x*x + y*y) + 1); }
