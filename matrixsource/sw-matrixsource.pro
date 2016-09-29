#-------------------------------------------------
#
# Project created by QtCreator 2015-09-18T21:52:46
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = sw-matrixsource
TEMPLATE = app

INCLUDEPATH+=include . ../mueb/ ../common/ ./fmod/lowlevel/inc/
LIBS += -L$$PWD/lib ./fmod/lowlevel/lib/x86_64/libfmodL.so ../mueb/libMUEB.a


SOURCES += \
    src/main.cpp \
    src/MatrixPlayerWindow.cpp \
    src/MatrixVideoPlayer.cpp \
    src/MatrixPlayer.cpp \
    src/Q4XLoader.cpp \
    src/PlayerFrame.cpp \
    src/MatrixAudioPlayer.cpp

HEADERS  += \
    src/MatrixAudioPlayer.h \
    src/MatrixPlayer.h \
    src/MatrixPlayerWindow.h \
    src/MatrixVideoPlayer.h \
    src/Q4XLoader.h \
    src/PlayerFrame.h

FORMS    += \
    src/MatrixPlayerWindow.ui

DISTFILES +=
