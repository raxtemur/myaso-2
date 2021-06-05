#include <qapplication.h>
#include <qgl.h>

//#include <QAction>
#include <QMainWindow>
#include <QMenuBar>

#include "glwidget.h"

int main(int argc, char** argv)
{
	QApplication app(argc, argv);

    myGLWidget myglw;

    app.setActiveWindow(&myglw);
    if (myglw.parse_command_line(argc, argv)) {
        qWarning("Wrong input arguments!");
        return -1;
    }
    /*QMenuBar *tool_bar = new QMenuBar(myglw);

    tool_bar->addAction("&Change func", myglw,
                                 SLOT(change_func()));
    tool_bar->addAction("&Change mode", myglw,
                                 SLOT(change_mode()));
    tool_bar->addAction("&N*=2", myglw,
                                 SLOT(increase_accuracy()));
    tool_bar->addAction("&N/=2", myglw,
                                 SLOT(decrease_accuracy()));
    tool_bar->addAction("&p+=0.1", myglw,
                                 SLOT(increase_accuracy()));
    tool_bar->addAction("&p-=0.1", myglw,
                                 SLOT(decrease_accuracy()));
*/
    myglw.show();
	return app.exec();
}
