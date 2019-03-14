######################################################################
# Automatically generated by qmake (3.0) Sun Sep 20 15:14:39 2015
######################################################################

TEMPLATE = app
TARGET = ColorSource
QT += core gui widgets network
#QMAKE_CXX = clang++
#QMAKE_CXXFLAGS += -std=c++11 -Wall -Wno-narrowing -pedantic -O3 -g
#QMAKE_LFLAGS += -lm

# Input
HEADERS += colorsender.h mainwindow.h timer.h
SOURCES += main.cpp colorsender.cpp mainwindow.cpp timer.cpp

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../mueb/release/ -lmueb
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../mueb/debug/ -lmueb
else:unix: LIBS += -L$$PWD/../mueb/ -lmueb

INCLUDEPATH += $$PWD/../mueb $$PWD/../common
DEPENDPATH += $$PWD/../mueb

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../mueb/release/libmueb.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../mueb/debug/libmueb.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../mueb/release/mueb.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../mueb/debug/mueb.lib
else:unix: PRE_TARGETDEPS += $$PWD/../mueb/libmueb.a
