QT += opengl
win32:LIBS += -lOpenGL32

HEADERS += glwidget.h \
    function.h
SOURCES += main.cpp \
	   glwidget.cpp \
    function.cpp
