#ifndef _my_widget
#define _my_widget

#include"function.h"

#include <QOpenGLWidget>

#include <QKeyEvent>

#include <qnamespace.h>

class myGLWidget:public QOpenGLWidget
{
  Q_OBJECT

  protected:
	virtual void paintGL();
	virtual void initializeGL();
	virtual void resizeGL(int nWidth, int nHeight);
	virtual void keyPressEvent(QKeyEvent* e);

	void setProjectionMatrix();
	void setDefaultCamera();

	float	angle_h, angle_v;
	float	camera_p;
	float	aspect;
};

#endif
