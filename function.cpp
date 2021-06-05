#include "function.h"
#include<math.h>
#include<string>
#include<QtGlobal>


#define MIN(a, b) ((a) > (b) ? (b) : (a))
#define MAX(a, b) ((a) < (b) ? (b) : (a))
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
/*
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
}*/


double difdif(double f1, double f2, double x1, double x2)
{
    return (f2-f1)/(x2-x1);
}


double Pf
(double x, double x1, double y, double y1, double C[4][4])
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


void coeffsErmit(double *X, double *Y, double **FF, double C[4][4], int ii, int jj, double *Ax, double *AyT, double *F)
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


void coeffsSlpine1d(int n, double *X, double *F, double *b, double x00, double xn1, double fx00, double fxn1)
{
    double *m = new double[3*(n+1)];
    double k;
    Q_UNUSED(fx00);
    Q_UNUSED(fxn1);

    m[0] = (X[1] - x00)*(X[1] - x00);
    m[1] = (x00 - X[1])*(x00 - X[0]);
    m[2] = 0;
    b[0] = difdif(F[0], F[1], X[0], X[1])*(x00 - X[0])*(x00 - X[0])*(2*(x00 - X[0])-3*(X[1]-X[0])) +
            (fx00-F[0])*(X[1]-X[0])*(X[1]-X[0]);

    m[3*n]     = 0;
    m[3*n + 1] = (xn1 - X[n])*(xn1 - X[n]);
    m[3*n + 2] = (xn1 - X[n-1])*(xn1 - X[n]);
    b[n] = difdif(F[n-1], F[n], X[n-1], X[n])*(xn1 - X[n-1])*(xn1 - X[n-1])*(2*(xn1 - X[n-1])-3*(X[n]-X[n-1]))+
            (fxn1-F[n-1])*(X[n]-X[n-1])*(X[n]-X[n-1]);


    for (int i=1; i<n; i++)
    {
        m[3*i]     = X[i-1] - X[i];
        m[3*i + 1] = 2*(X[i+1] - X[i-1]);
        m[3*i + 2] = X[i] - X[i-1];
        b[i] = 3 * difdif(F[i-1], F[i], X[i-1], X[i]) * (X[i+1] - X[i]) + 3 * difdif(F[i], F[i+1], X[i], X[i+1]) * (X[i] - X[i-1]);
    }

    for (int i=0; i<n; i++)
    {
        k = m[3*(i+1)]/m[3*i + 1];
        m[3*(i+1)+1] -= k*m[3*i + 2];
        b[i+1] -= k*b[i];
    }


    b[n] = b[n]/m[3*n+2];
    for (int i=n; i>0; i--)
    {
        b[i-1] = (b[i-1]-m[3*(i-1)+2]*b[i])/m[3*(i-1) + 1];
    }

}


void derivOperator(int nx, int ny, double *X, double *Y, double **FF)
{
    double *F;
    double *b;
    F = new double[MAX(nx, ny) - 1];
    b = new double[MAX(nx, ny) - 1];

    for (int j=0; j<ny+1; j++)
    {
        for (int i=1; i < nx; i++)
        {
            F[i-1] = FF[2*i][2*j];
        }
        coeffsSlpine1d(nx - 2, X+1, F, b, X[0], X[nx], FF[0][2*j], FF[2*nx][2*j]);
        for (int i=1; i < nx; i++)
        {
            FF[2*i+1][2*j] = b[i-1];
        }
    }

    for (int i=0; i<nx+1; i++)
    {
        for (int j=1; j < ny; j++)
        {
            F[j-1] = FF[2*i][2*j];
        }
        coeffsSlpine1d(ny - 2, Y+1, F, b, Y[0], Y[ny], FF[2*i][0], FF[2*i][2*ny]);
        for (int j=1; j < ny; j++)
        {
            FF[2*i][2*j+1] = b[j-1];
        }
    }

    for (int i=0; i<nx+1; i++)
    {
        for (int j=1; j < ny; j++)
        {
            F[j-1] = FF[2*i+1][2*j];
        }
        coeffsSlpine1d(ny - 2, Y+1, F, b, Y[0], Y[ny], FF[2*i+1][0], FF[2*i+1][2*ny]);
        for (int j=1; j < ny; j++)
        {
            FF[2*i+1][2*j+1] = b[j-1];
        }
    }

}


/*
 begin of version with +border outside
void derivOperator(int nx, int ny, double *X, double *Y, double **FF, double (*f)(double, double))
{
    double *F;
    double *b;
    F = new double[MAX(nx, ny) + 1];
    b = new double[MAX(nx, ny) + 1];
    double x_step = (X[nx]-X[0])/(nx),
           y_step = (Y[ny]-Y[0])/(ny);
    double x00 = X[0] - x_step, xn1 = X[nx] + x_step,
           y00 = Y[0] - y_step, yn1 = Y[nx] + y_step;
    double f00, fn1;

    for (int j=0; j<ny+1; j++)
    {
        f00 = f(x00, Y[j]);
        fn1 = f(xn1, Y[j]);
        for (int i=0; i < nx + 1; i++)
        {
            F[i] = FF[2*i][2*j];
        }
        coeffsSlpine1d(ny, X, F, b, x00, xn1, f00, fn1);
        for (int i=0; i < nx + 1; i++)
        {
            FF[2*i+1][2*j] = b[i];
        }
    }

    for (int i=0; i<nx+1; i++)
    {
        f00 = f(X[i], y00);
        fn1 = f(X[i], yn1);
        for (int j=0; j < ny + 1; j++)
        {
            F[i] = FF[2*i][2*j];
        }
        coeffsSlpine1d(nx, X, F, b, x00, xn1, f00, fn1);
        for (int j=0; j < ny + 1; j++)
        {
            FF[2*i][2*j+1] = b[j];
        }
    }

}
*/
