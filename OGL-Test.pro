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

# set BUILD_DIR
CONFIG(debug, debug|release) {
BUILD_FLAG = debug_$${QT_VERSION}
} else {
BUILD_FLAG = release_$${QT_VERSION}
}

ARCH_SUFFIX = x32
contains(QT_ARCH, x86_64) {
ARCH_SUFFIX = x64
} else {
ARCH_SUFFIX = x32
}

win32:MAKE_DIR      = OS_WIN_$${ARCH_SUFFIX}
unix:qnx:MAKE_DIR   = OS_QNX_$${ARCH_SUFFIX}

BUILD_DIR           = $${MAKE_DIR}/$${BUILD_FLAG}

DESTDIR             = $$PWD/$${BUILD_DIR}

UI_DIR              = $$PWD/$${BUILD_DIR}/UI
OBJECTS_DIR         = $$PWD/$${BUILD_DIR}/OBJECTS_DIR
MOC_DIR             = $$PWD/$${BUILD_DIR}/MOC
RCC_DIR             = $$PWD/$${BUILD_DIR}/RCC

MAKEFILE            = Makefile_$${QT_VERSION}
message(COPY_BUILD_PATH: $$PWD/$$BUILD_DIR)
#set BUILD_DIR

SOURCES +=  main.cpp\
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

RESOURCES +=    \
            shaders.qrc \
            textures.qrc \
            model.qrc
