#include "glwidget.h"

#include <stdio.h>
#include <math.h>
#include <QtWidgets/QMessageBox>
#include <sstream>

#define MIN(a, b) ((a) > (b) ? (b) : (a))
#define MAX(a, b) ((a) < (b) ? (b) : (a))

#define X_RESOLUTION 128
#define Y_RESOLUTION 128
#define DEFAULT_A -10
#define DEFAULT_B 10
#define DEF_N 8
#define MODES 4

#define ANGLE_DIFF	(5)
#define POSITION_DIFF	(0.1)

void myGLWidget::initializeGL()
{
	glClearColor(1.0, 1.0, 1.0, 1.0);

	setDefaultCamera();

    if(got_args < 1)
    {
        ax = DEFAULT_A;    bx = DEFAULT_B;
        ay = DEFAULT_A;    by = DEFAULT_B;
    }

    if (got_args < 2)
    {
        nx = DEF_N;
        ny = DEF_N;
    }

    untigrid = 1;
    mode = 0;
    acc_mode = 0;
    orig_mode = 1;

    func_max = (by - ay)/10;
    func_id = 0;
    x_step = (bx - ax) / X_RESOLUTION;
    y_step = (by - ay) / Y_RESOLUTION;

    p = 0.1;

    change_func();
}

int myGLWidget::parse_command_line(int argc, char *argv[])
{
    got_args = 0;
    if (argc == 1)
        return 0;

    if (argc == 2)
        return -1;

    if (sscanf(argv[1], "%lf", &ax) != 1 || sscanf(argv[2], "%lf", &bx) != 1 || bx - ax < 1.e-6 ||
            sscanf(argv[3], "%lf", &ay) != 1 || sscanf(argv[4], "%lf", &by) != 1 || by - ay < 1.e-6)
        return -2;
    else
        got_args += 1;

    if (argc > 4)
    {
        if ((sscanf(argv[5], "%d", &nx) != 1 || (sscanf(argv[6], "%d", &ny) != 1)) || nx <= 4 || ny <= 4)
        {
            return -2;
        }
        got_args += 1;
    }

    return 0;
}

double myGLWidget::fp(double x, double y)
{
    double x0 = (bx+ax)/2,
           y0 = (by+ay)/2,
           delta = ((bx-ax)/X_RESOLUTION + (by-ay)/Y_RESOLUTION)*2;
    if (p && (fabs(x - x0) + fabs(y - y0) < delta))
    {
        return f(x, y) + p*func_max;
    }
    else
    {
        return f(x, y);
    }
}

void myGLWidget::setProjectionMatrix()
{
    GLfloat view[16] = {0}, projection[16] = {0}, tmp[16] = {0};

    GLfloat  vnear = 5, vtop = 2, vbottom = -vtop, vright = vtop * aspect, vleft = -vright;

//	bottom = -top;
//	right = top * aspect;
//	left = -right;

    projection[0] = 2 * vnear / (vright - vleft);
    projection[8] = (vright + vleft) / (vright - vleft);
    projection[5] = 2 * vnear / (vtop - vbottom);
    projection[9] = (vtop + vbottom) / (vtop - vbottom);
    projection[10] = - 1;
    projection[14] = - 2 * vnear;
    projection[11] = -1;

    GLfloat	cam_x, cam_y, cam_z;
    cam_x = 0;
    cam_y = 0;
    cam_z = camera_p;

    view[0] = 1;
    view[6] = -1;
    view[9] = 1;
    view[15] = 1;

    view[12] = -cam_x;
    view[13] = -cam_y;
    view[14] = -cam_z;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glRotated(angle_h, 0, 0, 1);
    glGetFloatv(GL_PROJECTION_MATRIX, tmp);

    glLoadMatrixf(projection);
    glMultMatrixf(view);

    glRotated(angle_h, 0, 0, 1);
    glRotated(angle_v, tmp[0], tmp[4], tmp[8]);
}

void myGLWidget::setDefaultCamera()
{
    camera_p = 2*MAX((bx-ax), (by-ay));
    angle_h = 45;
    angle_v = 20;
    aspect = 1.0 * width() / height();
}

void myGLWidget::resizeGL(int nWidth, int nHeight)
{
    glViewport(0, 0, nWidth, nHeight);
    aspect = 1.0 * nWidth / nHeight;
    update();
}

void myGLWidget::change_func()
{
    func_id = (func_id + 1) % 7;

    switch (func_id) {
    case 0:
        f_name = "f (x) = 1";
        f = f_0;
        dxf = Dxf_0;
        dyf = Dyf_0;
        dxyf = DxDyf_0;
        break;
    case 1:
        f_name = "f (x) = x";
        f = f_1;
        dxf = Dxf_1;
        dyf = Dyf_1;
        dxyf = DxDyf_1;
        break;
    case 2:
        f_name = "f (x) = y";
        f = f_2;
        dxf = Dxf_2;
        dyf = Dyf_2;
        dxyf = DxDyf_2;
        break;
    case 3:
        f_name = "f (x) = x+y";
        f = f_3;
        dxf = Dxf_3;
        dyf = Dyf_3;
        dxyf = DxDyf_3;
        break;
    case 4:
        f_name = "f (x) = |(x, y)|";
        f = f_4;
        dxf = Dxf_4;
        dyf = Dyf_4;
        dxyf = DxDyf_4;
        break;
    case 5:
        f_name = "f (x) = |(x, y)|^2";
        f = f_5;
        dxf = Dxf_5;
        dyf = Dyf_5;
        dxyf = DxDyf_5;
        break;
    case 6:
        f_name = "exp(x*x - y*y)";
        f = f_6;
        dxf = Dxf_6;
        dyf = Dyf_6;
        dxyf = DxDyf_6;
        break;
    case 7:
        f_name = "f (x) = 1/(25*(x*x + y*y) + 1)";
        f = f_7;
        dxf = Dxf_7;
        dyf = Dyf_7;
        dxyf = DxDyf_7;
        break;
    }

    update();
}

void myGLWidget::keyPressEvent(QKeyEvent* e)
{
    switch (e->key()) {
    case Qt::Key_C:
        setDefaultCamera();
        break;
    case Qt::Key_Up:
        angle_v = MIN(angle_v + 5.0, 80);
        break;
    case Qt::Key_Down:
        angle_v = MAX(angle_v - 5.0, -80);
        break;
    case Qt::Key_Left:
        angle_h -= 5.0;
        break;
    case Qt::Key_Right:
        angle_h += 5.0;
        break;
    case Qt::Key_Plus:
        camera_p = MAX(camera_p - 0.1, 6);
        break;
    case Qt::Key_Minus:
        camera_p += 0.1;
        break;

    case Qt::Key_D:
        debugOut();
        break;
    case Qt::Key_1:
        change_func();
        untigrid = 1;
        break;
    case Qt::Key_4:     //increase acc
        if (nx < 128 && ny < 128)
        {
            nx*=2;
            ny*=2;
        }
        untigrid = 1;
        break;
    case Qt::Key_5:     //decrease acc
        if (nx > 8 && ny > 8)
        {
            nx/=2;
            ny/=2;
        }
        untigrid = 1;
        break;
    case Qt::Key_6:     //increase disturb
        p+=0.1;
        untigrid = 1;
        break;
    case Qt::Key_7:     //decrease disturb
        p-=0.1;
        untigrid = 1;
        break;
    case Qt::Key_9:
        acc_mode = (acc_mode + 1) % 2;
        break;
    case Qt::Key_0:
        mode = (mode + 1) % MODES;
        break;
    case Qt::Key_Q:
        orig_mode = (orig_mode + 1) % 2;
        break;
    }

    update();
}

void myGLWidget::initGrid()
{
    double x_delta = (bx-ax)/nx,
           y_delta = (by-ay)/ny;
    FF  = new double *[2*(nx+1)];
    FF2 = new double *[2*(nx+1)];
    X  = new double [nx+1];
    Y  = new double [ny+1];

    for (int i=0; i < nx+1; i++)
    {
        FF[2*i]     = new double [2*(ny + 1)];
        FF[2*i + 1] = new double [2*(ny + 1)];
        FF2[2*i]     = new double [2*(ny + 1)];
        FF2[2*i + 1] = new double [2*(ny + 1)];
        for (int j=0; j < ny+1; j++)
        {
            X[i] = ax + i*x_delta;
            Y[j] = ay + j*y_delta;
            FF[2*i][2*j]      = fp(X[i], Y[j]);
            FF2[2*i][2*j]     = fp(X[i], Y[j]);
            FF[2*i+1][2*j]   = dxf(X[i], Y[j]);
            FF[2*i][2*j+1]   = dyf(X[i], Y[j]);
            FF[2*i+1][2*j+1] = dxyf(X[i], Y[j]);
        }
    }
}

void myGLWidget::sourceGraph()
{
    glBegin(GL_QUADS);

    glColor3d(1.0,0.0,0.0);

    for (double x = ax; x - bx < x_step; x+=x_step)
        for (double y = ay; y - by < y_step; y+=y_step) {
            double	z;

            glColor3d((bx - x) / (bx - ax), (y - ay) / (by - ay), 0.0);

            z = fp(x, y);
            glVertex3d(x, y, z);

            z = fp(x + x_step, y);
            glVertex3d(x + x_step, y, z);

            z = fp(x + x_step, y + y_step);
            glVertex3d(x + x_step, y + y_step, z);

            z = fp(x, y + y_step);
            glVertex3d(x, y + y_step, z);
        }

    glEnd();

}

void myGLWidget::approximationGraph1()
{
    //double x1, x2, y1, y2;
    bool hardDebug = 0;
    double coeffs[4][4];
    double	z1, z2, z3, z4;
    double	z10, z20, z30, z40;
    double *Ax, *AyT, *F;


    F = new double[16];
    Ax = new double[16];
    AyT = new double[16];

    glBegin(GL_QUADS);

    glColor3d(1.0,0.0,0.0);
    for (int i=0; i < nx;  i++)
    {
        for (int j=0; j < ny; j++)
        {
            coeffsErmit(X, Y, FF, coeffs, i, j, Ax, AyT, F);

            if (hardDebug && (nx*ny < 10))
            {
                out.precision(3);
                out.str("");
                out << "\n i, j: " << i << j << "\n";
                out << "\n Ax:\n";
                for (int k=0; k < 4; k++)
                {
                    for (int l=0; l < 4; l++)
                    {
                        out << std::fixed <<  Ax[k*4 + l] << "    ";
                    }
                    out << "\n";
                }
                out << "\n AyT:\n";
                for (int k=0; k < 4; k++)
                {
                    for (int l=0; l < 4; l++)
                    {
                        out << std::fixed <<  AyT[k*4 + l] << "    ";
                    }
                    out << "\n";
                }
                out << "\n coeffs:\n";
                for (int k=0; k < 4; k++)
                {
                    for (int l=0; l < 4; l++)
                    {
                        out << std::fixed <<  coeffs[k][l] << "    ";
                    }
                    out << "\n";
                }
                QMessageBox::warning(0, "Coeffs", QString::fromStdString(out.str()));

            }

            for (double x = X[i]; x - X[i+1] < x_step; x+=x_step)
                for (double y = Y[j]; y - Y[j+1] < y_step; y+=y_step)
                {
                    glColor3d(0.3, 0.3, 0.1);


                    z1 = Pf(x, X[i],           y, Y[j],          coeffs);
                    z2 = Pf(x + x_step, X[i],  y, Y[j],          coeffs);
                    z3 = Pf(x + x_step, X[i],  y + y_step, Y[j], coeffs);
                    z4 = Pf(x, X[i],           y + y_step, Y[j], coeffs);


                    glVertex3d(x, y, z1);
                    glVertex3d(x + x_step, y, z2);
                    glVertex3d(x + x_step, y + y_step, z3);
                    glVertex3d(x, y + y_step, z4);

                    if (acc_mode)
                    {
                        z10 = f(x, y);
                        z20 = f(x + x_step, y);
                        z30 = f(x + x_step, y+y_step);
                        z40 = f(x, y+y_step);

                        glVertex3d(x, y, z1 - z10);
                        glVertex3d(x + x_step, y, z2 - z20);
                        glVertex3d(x + x_step, y + y_step, z3 - z30);
                        glVertex3d(x, y + y_step, z4 - z40);
                    }

                }
        }
    }


    glEnd();
}

void myGLWidget::approximationGraph2()
{
    //double x1, x2, y1, y2;
    bool hardDebug = 0;
    double coeffs[4][4];
    double	z1, z2, z3, z4;
    double	z10, z20, z30, z40;
    double *Ax, *AyT, *F;

    F = new double[16];
    Ax = new double[16];
    AyT = new double[16];

    //derivOperator(nx, ny, X, Y, FF2);
    //debugOut();
    glBegin(GL_QUADS);

    glColor3d(1.0,0.0,0.0);
    for (int i=1; i < nx-1;  i++)
    {
        for (int j=1; j < ny-1; j++)
        {
            coeffsErmit(X, Y, FF2, coeffs, i, j, Ax, AyT, F);

            if (hardDebug && ((nx-1)*(ny-1) < 10))
            {
                out.precision(3);
                out.str("");
                out << "\n i, j: " << i << j << "\n";
                out << "\n Ax:\n";
                for (int k=0; k < 4; k++)
                {
                    for (int l=0; l < 4; l++)
                    {
                        out << std::fixed <<  Ax[k*4 + l] << "    ";
                    }
                    out << "\n";
                }
                out << "\n AyT:\n";
                for (int k=0; k < 4; k++)
                {
                    for (int l=0; l < 4; l++)
                    {
                        out << std::fixed <<  AyT[k*4 + l] << "    ";
                    }
                    out << "\n";
                }
                out << "\n coeffs:\n";
                for (int k=0; k < 4; k++)
                {
                    for (int l=0; l < 4; l++)
                    {
                        out << std::fixed <<  coeffs[k][l] << "    ";
                    }
                    out << "\n";
                }
                QMessageBox::warning(0, "Coeffs", QString::fromStdString(out.str()));

            }

            for (double x = X[i]; x - X[i+1] < x_step; x+=x_step)
                for (double y = Y[j]; y - Y[j+1] < y_step; y+=y_step)
                {
                    glColor3d(0.3, 0.8, 0.1);


                    z1 = Pf(x, X[i],           y, Y[j],          coeffs);
                    z2 = Pf(x + x_step, X[i],  y, Y[j],          coeffs);
                    z3 = Pf(x + x_step, X[i],  y + y_step, Y[j], coeffs);
                    z4 = Pf(x, X[i],           y + y_step, Y[j], coeffs);


                    glVertex3d(x, y, z1);
                    glVertex3d(x + x_step, y, z2);
                    glVertex3d(x + x_step, y + y_step, z3);
                    glVertex3d(x, y + y_step, z4);

                    if (acc_mode)
                    {
                        z10 = f(x, y);
                        z20 = f(x + x_step, y);
                        z30 = f(x + x_step, y+y_step);
                        z40 = f(x, y+y_step);

                        glVertex3d(x, y, z1 - z10);
                        glVertex3d(x + x_step, y, z2 - z20);
                        glVertex3d(x + x_step, y + y_step, z3 - z30);
                        glVertex3d(x, y + y_step, z4 - z40);
                    }
                }
        }
    }


    glEnd();
}

void myGLWidget::debugOut()
{
    std::stringstream out;
    out.precision(3);
    //out << "Matrix i, j: " << i << j << "\n";
    for (int k=0; k < 2*(nx+1); k++)
    {
        for (int l=0; l < 2*(ny+1); l++)
        {
            out << std::fixed <<  FF[k][l] << "    ";
        }
        out << "\n";
    }
    QMessageBox::warning(0, "Matrix", QString::fromStdString(out.str()));
}

void myGLWidget::paintGL()
{
    QPainter painter(this);
	setProjectionMatrix();

	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    glEnable(GL_DEPTH_TEST);

    if (untigrid)
    {
        initGrid();
        derivOperator(nx, ny, X, Y, FF2);
        untigrid = 0;
    }

    //исходный график
    if (orig_mode)
        sourceGraph();
    if (mode == 1 || mode == 3)
        approximationGraph1();
    if (mode == 2 || mode == 3)
        approximationGraph2();

    painter.beginNativePainting();
    painter.setPen("blue");
    painter.drawText(0, 20, f_name);

    painter.drawText(0,   40, "ax, bx:");
    painter.drawText(50,  40, QString::number(ax, 'g', 3));
    painter.drawText(100, 40, QString::number(bx, 'g', 3));

    painter.drawText(0,   60, "ay, by:");
    painter.drawText(50,  60, QString::number(ay, 'g', 3));
    painter.drawText(100, 60, QString::number(by, 'g', 3));


    painter.drawText(0,   80, "nx ny:");
    painter.drawText(50,  80, QString::number(nx));
    painter.drawText(100, 80, QString::number(ny));

    /*
    painter.drawText(0, 60, "min, max:");
    painter.drawText(70,   60, QString::number(func_min, 'g', 3));
    painter.drawText(120,  60, QString::number(func_max, 'g', 3));
*/

    painter.drawText(0,  100, "mode:");
    painter.drawText(50, 100, QString::number(mode));

    painter.drawText(0,  120, "acc_mode:");
    painter.drawText(100,120, QString::number(acc_mode));

    painter.drawText(0,  140, "p:");
    painter.drawText(50, 140, QString::number(p));

    painter.drawText(0,  160, "camera:");
    painter.drawText(70, 160, QString::number(camera_p));
    glDisable(GL_DEPTH_TEST);
}
