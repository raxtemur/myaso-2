#ifndef FUNCTION_H
#define FUNCTION_H

double f_0(double, double);
double f_1(double, double);
double f_2(double, double);
double f_3(double, double);
double f_4(double, double);
double f_5(double, double);
double f_6(double, double);
double f_7(double, double);

double Dxf_0(double, double);
double Dxf_1(double, double);
double Dxf_2(double, double);
double Dxf_3(double, double);
double Dxf_4(double, double);
double Dxf_5(double, double);
double Dxf_6(double, double);
double Dxf_7(double, double);

double Dyf_0(double, double);
double Dyf_1(double, double);
double Dyf_2(double, double);
double Dyf_3(double, double);
double Dyf_4(double, double);
double Dyf_5(double, double);
double Dyf_6(double, double);
double Dyf_7(double, double);

double DxDyf_0(double, double);
double DxDyf_1(double, double);
double DxDyf_2(double, double);
double DxDyf_3(double, double);
double DxDyf_4(double, double);
double DxDyf_5(double, double);
double DxDyf_6(double, double);
double DxDyf_7(double, double);


double Pf(double x, double x1, double y, double y1, double C[4][4]);
//double Pf2(double x, double x1, double x2, double C[2][2][2][2], int i);//C - coeffs

void coeffsErmit(double *X, double *Y, double **FF, double C[4][4], int ii, int jj, double *Ax, double *AyT, double *F);
void derivOperator(int nx, int ny, double *X, double *Y, double **FF);
#endif // FUNCTION_H
