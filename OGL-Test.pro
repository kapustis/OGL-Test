#-------------------------------------------------
#
# Project created by QtCreator 2018-09-14T08:38:05
#
#-------------------------------------------------

QT += core gui widgets
QT += opengl

TARGET = OGL-Test
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets


#-------- REMOTE TARGET PATH - need for run from QtCreator -------
#target.path =/root
#INSTALLS += target
#-----------------------------------------------------------------

CONFIG += c++11

win32: LIBS += -lopengl32

TARGET = OGL-Test
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
	simpleobject3d.cpp \
	group3d.cpp \
	camera3d.cpp \
	skybox.cpp \
        material.cpp \
        materiallibrary.cpp \
        objectengine3d.cpp \
    light.cpp


HEADERS  += widget.h \
        simpleobject3d.h \
        transformational.h \
        group3d.h \
        camera3d.h \
        skybox.h \
        material.h \
        materiallibrary.h \
        objectengine3d.h \
    light.h

DISTFILES +=

RESOURCES += \
    shaders.qrc \
    textures.qrc \
    model.qrc
