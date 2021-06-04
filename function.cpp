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

/*попробовать, если будет время
template <typename T1, typename T2>
double multM2x2(T1 m1, T2 m2, double buf[2][2])
{
    buf[0][0] = m1[0][0]*m2[0][0] + m1[0][1]*m2[1][0];
    buf[0][1] = m1[0][0]*m2[0][1] + m1[0][1]*m2[1][1];
    buf[1][0] = m1[1][0]*m2[0][0] + m1[1][1]*m2[1][0];
    buf[1][1] = m1[1][0]*m2[0][1] + m1[1][1]*m2[1][1];
}*/

void multM2x2(double m1[2][2], double m2[2][2], double buf[2][2])
{
    buf[0][0] = m1[0][0]*m2[0][0] + m1[0][1]*m2[1][0];
    buf[0][1] = m1[0][0]*m2[0][1] + m1[0][1]*m2[1][1];
    buf[1][0] = m1[1][0]*m2[0][0] + m1[1][1]*m2[1][0];
    buf[1][1] = m1[1][0]*m2[0][1] + m1[1][1]*m2[1][1];
}

void multM2x2(double m1[2][2], double **m2, double buf[2][2])
{
    buf[0][0] = m1[0][0]*m2[0][0] + m1[0][1]*m2[1][0];
    buf[0][1] = m1[0][0]*m2[0][1] + m1[0][1]*m2[1][1];
    buf[1][0] = m1[1][0]*m2[0][0] + m1[1][1]*m2[1][0];
    buf[1][1] = m1[1][0]*m2[0][1] + m1[1][1]*m2[1][1];
}

void multM2x2(double **m1, double m2[2][2], double buf[2][2])
{
    buf[0][0] = m1[0][0]*m2[0][0] + m1[0][1]*m2[1][0];
    buf[0][1] = m1[0][0]*m2[0][1] + m1[0][1]*m2[1][1];
    buf[1][0] = m1[1][0]*m2[0][0] + m1[1][1]*m2[1][0];
    buf[1][1] = m1[1][0]*m2[0][1] + m1[1][1]*m2[1][1];
}

void multM2x2(double m1[2][2], double m2[2][2], double **buf)
{
    buf[0][0] = m1[0][0]*m2[0][0] + m1[0][1]*m2[1][0];
    buf[0][1] = m1[0][0]*m2[0][1] + m1[0][1]*m2[1][1];
    buf[1][0] = m1[1][0]*m2[0][0] + m1[1][1]*m2[1][0];
    buf[1][1] = m1[1][0]*m2[0][1] + m1[1][1]*m2[1][1];
}

void multM2x2(double m1[2][2], double **m2, double **buf)
{
    buf[0][0] = m1[0][0]*m2[0][0] + m1[0][1]*m2[1][0];
    buf[0][1] = m1[0][0]*m2[0][1] + m1[0][1]*m2[1][1];
    buf[1][0] = m1[1][0]*m2[0][0] + m1[1][1]*m2[1][0];
    buf[1][1] = m1[1][0]*m2[0][1] + m1[1][1]*m2[1][1];
}

void multM2x2(double **m1, double m2[2][2], double **buf)
{
    buf[0][0] = m1[0][0]*m2[0][0] + m1[0][1]*m2[1][0];
    buf[0][1] = m1[0][0]*m2[0][1] + m1[0][1]*m2[1][1];
    buf[1][0] = m1[1][0]*m2[0][0] + m1[1][1]*m2[1][0];
    buf[1][1] = m1[1][0]*m2[0][1] + m1[1][1]*m2[1][1];
}


double Pf1(double x, double x1, double y, double y1, double C[4][4])
{
    double sum = 0;
    for (int i=0; i<4; i++)
    {
        for (int j=0; j<4; j++)
        {
            sum += C[i][j]*pow(x-x1, i)*pow(y-y1, j);
        }
    }

    return sum;
}


//coeffsErmit(X, Y, FF, coeffs, i, j);
void coeffsErmit(double *X, double *Y, double ****FF, double C[2][2][2][2], int i, int j)
{
    double Ax1[2][2], Ax2[2][2], Ay1T[2][2], Ay2T[2][2]; //speaking ugly names
    double buf1[2][2], buf2[2][2], buf3[2][2];
    double h;

    C[0][0][0][0] = FF[i][j][0][0];    C[0][0][0][1] = FF[i][j][0][1];
    C[0][0][1][0] = FF[i][j][1][0];    C[0][0][1][1] = FF[i][j][1][1];

    h = X[i+1] - X[i];
    Ax1[0][0] = -(3/(h*h));      Ax1[0][1] = -(2/(h));
    Ax1[1][0] = (2/(h*h*h));     Ax1[0][1] = (1/(h*h));

    Ax2[0][0] = (3/(h*h));       Ax2[0][1] = -(1/(h));
    Ax2[1][0] = -(2/(h*h*h));    Ax2[0][1] = (1/(h*h));


    h = Y[j+1] - Y[j];

    Ay1T[0][0] = -(3/(h*h));    Ay1T[0][1] = (2/(h*h*h));
    Ay1T[1][0] = -(2/(h));      Ay1T[0][1] = (1/(h*h));

    Ay2T[0][0] = (3/(h*h));     Ay2T[0][1] = -(2/(h*h*h));
    Ay2T[1][0] = -(1/(h));      Ay2T[0][1] = (1/(h*h));

    multM2x2(FF[i][j],   Ay1T, C[0][1]);
    multM2x2(FF[i][j+1], Ay2T, buf2);

    C[0][1][0][0] += buf2[0][0];    C[0][1][0][1] += buf2[0][1];
    C[0][1][1][0] += buf2[1][0];    C[0][1][1][1] += buf2[1][1];

    multM2x2(Ax1, FF[i][j], C[1][0]);
    multM2x2(Ax2, FF[i+1][j], buf1);

    buf1[0][0] = C[1][0][0][0] = buf1[0][0] + C[1][0][0][0];
    buf1[0][1] = C[1][0][0][1] = buf1[0][1] + C[1][0][0][1];
    buf1[1][0] = C[1][0][1][0] = buf1[1][0] + C[1][0][1][0];
    buf1[0][1] = C[1][0][1][1] = buf1[1][1] + C[1][0][1][1];

    multM2x2(buf1, Ay1T, buf3);
    multM2x2(Ax1, buf2, buf1);

    C[1][1][0][0] = buf3[0][0] + buf1[0][0];
    C[1][1][0][1] = buf3[0][1] + buf1[0][1];
    C[1][1][1][0] = buf3[1][0] + buf1[1][0];
    C[1][1][1][1] = buf3[1][1] + buf1[1][1];

    multM2x2(Ax2, FF[i+1][j+1], buf1);
    multM2x2(buf1, Ay2T, buf2);

    C[1][1][0][0] += buf2[0][0];
    C[1][1][0][1] += buf2[0][1];
    C[1][1][1][0] += buf2[1][0];
    C[1][1][1][1] += buf2[1][1];
}



void generateA(double *A, double h)
{
    for (int i=0; i<8; i++)
    {
        A[i] = 0;
    }
    A[0] = 1;
    A[5] = 1;
    A[8] = -(3/(h*h));     A[9] = -(2/(h));
    A[10] = (3/(h*h));     A[11] = -(1/(h));
    A[12] = (2/(h*h*h));     A[13] = (1/(h*h));
    A[14] = -(2/(h*h*h));    A[15] = (1/(h*h));
}



void supeRcoeffsErmit(double *X, double *Y, double **FF, double C[4][4], int ii, int jj, double *Ax, double *AyT, double *F)
{
    double hx, hy;

    for (int i=0; i<4; i++)
        for (int j=0; j<4; j++)
            F[4*i+j] = 0;

    hx = X[ii+1] - X[ii];
    hy = Y[jj+1] - Y[jj];
    generateA(Ax, hx);
    generateA(AyT, hy);

    for (int i=0; i<4; i++)
        for (int j=0; j<4; j++)
            for (int k=0; k<4; k++)
                F[4*i+j] += Ax[4*i+k]*FF[2*ii + k][2*jj + j];

    for (int i=0; i<4; i++)
        for (int j=0; j<4; j++)
        {
            C[i][j] = 0;
            for (int k=0; k<4; k++)
                C[i][j] += F[4*i+k]*AyT[k+4*j];
        }



}
