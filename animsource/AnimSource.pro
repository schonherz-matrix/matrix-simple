######################################################################
# Automatically generated by qmake (3.0) Sun Sep 20 15:14:39 2015
######################################################################

TEMPLATE = app
TARGET = AnimSource
QT += core gui widgets
INCLUDEPATH += . ../mueb/ ../common/
QMAKE_CXX = clang++
QMAKE_CXXFLAGS += -std=c++11 -Wall -Wno-narrowing -pedantic -O3 -g
QMAKE_LFLAGS += -lm

# Input
HEADERS += animsender.h animfactory.h mainwindow.h timer.h chessanim.h verticalanim.h solidanim.h
SOURCES += main.cpp animsender.cpp animfactory.cpp mainwindow.cpp timer.cpp chessanim.cpp verticalanim.cpp solidanim.cpp
LIBS += ../mueb/libMUEB.a
