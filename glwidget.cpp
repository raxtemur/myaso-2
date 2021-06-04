#include "glwidget.h"

#include <stdio.h>
#include <math.h>

#define MIN(a, b) ((a) > (b) ? (b) : (a))
#define MAX(a, b) ((a) < (b) ? (b) : (a))

#define X_RESOLUTION 30
#define Y_RESOLUTION 30

void myGLWidget::initializeGL()
{
	glClearColor(1.0, 1.0, 1.0, 1.0);

	setDefaultCamera();

    func_id = -1;

    change_func();
}

void myGLWidget::paintGL()
{
	setProjectionMatrix();

	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

	glEnable(GL_DEPTH_TEST);
/*	glEnable(GL_MULTISAMPLE);
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_POLYGON_SMOOTH);
	glEnable(GL_BLEND);
*/
	glBegin(GL_QUADS);

	double	x_min = -1, x_max = 1,
		y_min = -1, y_max = 1;
    double x_step = (x_max - x_min) / X_RESOLUTION,
           y_step = (y_max - y_min) / Y_RESOLUTION;

	glColor3d(1.0,0.0,0.0);

    for (int i = 0; i < X_RESOLUTION; i++)
        for (int j = 0; j < Y_RESOLUTION; j++) {
			double	x, y, z;

            glColor3d(1.0 * (X_RESOLUTION - i) / X_RESOLUTION, 1.0 * j / Y_RESOLUTION, 0.0);

            x = x_step * i + x_min;
            y = y_step * j + y_min;
            z = f(x, y);
			glVertex3d(x, y, z);
            x = x_step * (i + 1) + x_min;
            y = y_step * j + y_min;
            z = f(x, y);
			glVertex3d(x, y, z);
            x = x_step * (i + 1) + x_min;
            y = y_step * (j + 1) + y_min;
            z = f(x, y);
			glVertex3d(x, y, z);
            x = x_step * i + x_min;
            y = y_step * (j + 1) + y_min;
            z = f(x, y);
			glVertex3d(x, y, z);
		}

	glEnd();

	glDisable(GL_DEPTH_TEST);
}

void myGLWidget::resizeGL(int nWidth, int nHeight)
{
	glViewport(0, 0, nWidth, nHeight);
	aspect = 1.0 * nWidth / nHeight;
	update();
}

#define ANGLE_DIFF	(5)
#define POSITION_DIFF	(0.1)



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

	}

	update();
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
