#ifndef _my_widget
#define _my_widget

#include <sstream>
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
    double p, func_max;
    double x_step, y_step;

    bool untigrid;
    int got_args;
    std::stringstream out;

  public slots:
    void change_func();
    void change_mode();
    int parse_command_line(int argc, char *argv[]);

  protected:
	virtual void paintGL();
	virtual void initializeGL();
	virtual void resizeGL(int nWidth, int nHeight);
	virtual void keyPressEvent(QKeyEvent* e);

    double **FF, **FF2;
    double *X, *Y;
    double (*f)(double, double);
    double (*dxf)(double, double);
    double (*dyf)(double, double);
    double (*dxyf)(double, double);

	void setProjectionMatrix();
    void setDefaultCamera();
    void initGrid();
    void sourceGraph();
    void approximationGraph1();
    void approximationGraph2();
    void debugOut();



    double fp(double x, double y);


    float	angle_h, angle_v;
	float	camera_p;
    float	aspect;

};

#endif
