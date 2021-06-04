#ifndef _my_widget
#define _my_widget

#include"function.h"

#include <QOpenGLWidget>

#include <QKeyEvent>
#include <QPainter>
#include <qnamespace.h>

class myGLWidget:public QOpenGLWidget
{
  Q_OBJECT
  private:
    int func_id;
    QString f_name, mode_name;
    double ax, bx, ay, by;
    int nx, ny, mode, acc_mode;
    double p;
    double x_step, y_step;

  protected:
	virtual void paintGL();
	virtual void initializeGL();
	virtual void resizeGL(int nWidth, int nHeight);
	virtual void keyPressEvent(QKeyEvent* e);

    double **FF;
    double *X, *Y;
    double (*f)(double, double);
    double (*dxf)(double, double);
    double (*dyf)(double, double);
    double (*dxyf)(double, double);

	void setProjectionMatrix();
	void setDefaultCamera();
    void change_func();
    void initGrid();
    void sourceGraph();
    void approximationGraph1();
    void approximationGraph2();

    float	angle_h, angle_v;
	float	camera_p;
    float	aspect;

};

#endif
