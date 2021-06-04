#include "glwidget.h"

#include <stdio.h>
#include <math.h>
#include <QtWidgets/QMessageBox>
#include <sstream>

#define MIN(a, b) ((a) > (b) ? (b) : (a))
#define MAX(a, b) ((a) < (b) ? (b) : (a))

#define X_RESOLUTION 30
#define Y_RESOLUTION 30

#define ANGLE_DIFF	(5)
#define POSITION_DIFF	(0.1)

void myGLWidget::initializeGL()
{
	glClearColor(1.0, 1.0, 1.0, 1.0);

	setDefaultCamera();

    ax = -1;    bx = 1;
    ay = -1;    by = 1;

    nx = 2; ny = 2;

    func_id = 1;
    x_step = (bx - ax) / X_RESOLUTION;
    y_step = (by - ay) / Y_RESOLUTION;

    change_func();
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
    camera_p = 7;
    angle_h = 45;
    angle_v = 20;
    aspect = 1.0 * width() / height();
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
        f_name = "f (x) = x*x";
        f = f_2;
        dxf = Dxf_2;
        dyf = Dyf_2;
        dxyf = DxDyf_2;
        break;
    case 3:
        f_name = "f (x) = x*x*x";
        f = f_3;
        dxf = Dxf_3;
        dyf = Dyf_3;
        dxyf = DxDyf_3;
        break;
    case 4:
        f_name = "f (x) = x*x*x*x";
        f = f_4;
        dxf = Dxf_4;
        dyf = Dyf_4;
        dxyf = DxDyf_4;
        break;
    case 5:
        f_name = "f (x) = exp(x)";
        f = f_5;
        dxf = Dxf_5;
        dyf = Dyf_5;
        dxyf = DxDyf_5;
        break;
    case 6:
        f_name = "f (x) = 1/(25*x*x + 1)";
        f = f_6;
        dxf = Dxf_6;
        dyf = Dyf_6;
        dxyf = DxDyf_6;
        break;
    case 7:
        f_name = "f (x) = 1/(25*x*x + 1)";
        f = f_7;
        dxf = Dxf_7;
        dyf = Dyf_7;
        dxyf = DxDyf_7;
        break;
    }

    update();
}

void myGLWidget::resizeGL(int nWidth, int nHeight)
{
    glViewport(0, 0, nWidth, nHeight);
    aspect = 1.0 * nWidth / nHeight;
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
        camera_p = MAX(camera_p - 0.1, 7);
        break;
    case Qt::Key_Minus:
        camera_p += 0.1;
        break;
    case Qt::Key_1:
        change_func();
        break;
    case Qt::Key_D:
        debugOut();

    }

    update();
}

void myGLWidget::initGrid()
{
    double x_delta = (bx-ax)/nx,
           y_delta = (by-ay)/ny;
    FF = new double *[2*(nx+1)];
    X  = new double [nx+1];
    Y  = new double [ny+1];

    for (int i=0; i < nx+1; i++)
    {
        FF[2*i]     = new double [2*(ny + 1)];
        FF[2*i + 1] = new double [2*(ny + 1)];
        for (int j=0; j < ny+1; j++)
        {
            X[i] = ax + i*x_delta;
            Y[j] = ay + j*y_delta;
            FF[2*i][2*j]     = f(X[i], Y[j]);
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

            z = f(x, y);
            glVertex3d(x, y, z);

            z = f(x + x_step, y);
            glVertex3d(x + x_step, y, z);

            z = f(x + x_step, y + y_step);
            glVertex3d(x + x_step, y + y_step, z);

            z = f(x, y + y_step);
            glVertex3d(x, y + y_step, z);
        }

    glEnd();

}

void myGLWidget::approximationGraph1()
{
    //double x1, x2, y1, y2;
    bool hardDebug = 0;
    double coeffs[4][4];
    double	z1, z2, z3, z4, z;
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
            supeRcoeffsErmit(X, Y, FF, coeffs, i, j, Ax, AyT, F);


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
                    //glColor3d((bx - x) / (bx - ax), (x - ax) / (by - ay), 0.0);
                    glColor3d(0.3, 0.3, 0.1);


                    z1 = Pf1(x, X[i],           y, Y[j],          coeffs);
                    z2 = Pf1(x + x_step, X[i],  y, Y[j],          coeffs);
                    z3 = Pf1(x + x_step, X[i],  y + y_step, Y[j], coeffs);
                    z4 = Pf1(x, X[i],           y + y_step, Y[j], coeffs);


                    glVertex3d(x, y, z1);
                    glVertex3d(x + x_step, y, z2);
                    glVertex3d(x + x_step, y + y_step, z3);
                    glVertex3d(x, y + y_step, z4);
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

    initGrid();
    //исходный график
    sourceGraph();
    approximationGraph1();

    painter.beginNativePainting();
    painter.setPen("blue");
    painter.drawText(10, 20, "Sosi!");

    glDisable(GL_DEPTH_TEST);
}
