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

double Dxf_0(double x, double y){ Q_UNUSED(x); Q_UNUSED(y); return 0; }
double Dxf_1(double x, double y) { Q_UNUSED(x); Q_UNUSED(y); return 1; }
double Dxf_2(double x, double y) { Q_UNUSED(x); Q_UNUSED(y); return 0; }
double Dxf_3(double x, double y) { Q_UNUSED(x); Q_UNUSED(y); return 1; }
double Dxf_4(double x, double y)
{
    if (x*x + y*y > EPS)
        return x/sqrt(x*x + y*y);
    else return 0;
}
double Dxf_5(double x, double y) { Q_UNUSED(y); return 2*x; }
double Dxf_6(double x, double y) { return 2*x*exp(x*x - y*y); }
double Dxf_7(double x, double y) { return -50*x/(25*(x*x + y*y) + 1)/(25*(x*x + y*y) + 1); }

double Dyf_0(double x, double y) { Q_UNUSED(x); Q_UNUSED(y); return 0; }
double Dyf_1(double x, double y) { Q_UNUSED(x); Q_UNUSED(y); return 0; }
double Dyf_2(double x, double y) { Q_UNUSED(x); Q_UNUSED(y); return 1; }
double Dyf_3(double x, double y) { Q_UNUSED(x); Q_UNUSED(y); return 1; }
double Dyf_4(double x, double y)
{
    if (x*x + y*y > EPS)
        return y/sqrt(x*x + y*y);
    else return 0;
}
double Dyf_5(double x, double y) { Q_UNUSED(x); return 2*y; }
double Dyf_6(double x, double y) { return -2*y*exp(x*x - y*y); }
double Dyf_7(double x, double y) { return -50*y/(25*(x*x + y*y) + 1)/(25*(x*x + y*y) + 1); }

double DxDyf_0(double x, double y) { Q_UNUSED(x); Q_UNUSED(y); return 0; }
double DxDyf_1(double x, double y) { Q_UNUSED(x); Q_UNUSED(y); return 0; }
double DxDyf_2(double x, double y) { Q_UNUSED(x); Q_UNUSED(y); return 0; }
double DxDyf_3(double x, double y) { Q_UNUSED(x); Q_UNUSED(y); return 0; }
double DxDyf_4(double x, double y)
{
    if (x*x + y*y > EPS)
        return -x*y/sqrt(x*x + y*y)/(x*x + y*y);
    else return 0;
}
double DxDyf_5(double x, double y) { Q_UNUSED(x); Q_UNUSED(y); return 0; }
double DxDyf_6(double x, double y) { return -4*x*y*exp(x*x - y*y); }
double DxDyf_7(double x, double y) { return 5000*y*x/(25*(x*x + y*y) + 1)/(25*(x*x + y*y) + 1)/(25*(x*x + y*y) + 1); }
