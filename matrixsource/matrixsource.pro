#-------------------------------------------------
#
# Project created by QtCreator 2015-09-18T21:52:46
#
#-------------------------------------------------

QT       += core gui network
#QMAKE_CXX = clang++
#QMAKE_CXXFLAGS += -std=c++11 -Wall -Wno-narrowing -pedantic -O3 -g

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MatrixSource
TEMPLATE = app

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

# Copy the dynamic library.
win32 {
}
else {
   QMAKE_PRE_LINK=cp ./fmod/lowlevel/lib/x86_64/libfmodL.so .
}

unix|win32: LIBS += -L'C:/Program Files (x86)/FMOD SoundSystem/FMOD Studio API Windows/api/lowlevel/lib/' -lfmodL64_vc

INCLUDEPATH += 'C:/Program Files (x86)/FMOD SoundSystem/FMOD Studio API Windows/api/lowlevel/inc'
DEPENDPATH += 'C:/Program Files (x86)/FMOD SoundSystem/FMOD Studio API Windows/api/lowlevel/inc'

win32:!win32-g++: PRE_TARGETDEPS += 'C:/Program Files (x86)/FMOD SoundSystem/FMOD Studio API Windows/api/lowlevel/lib/fmodL64_vc.lib'
else:unix|win32-g++: PRE_TARGETDEPS += 'C:/Program Files (x86)/FMOD SoundSystem/FMOD Studio API Windows/api/lowlevel/lib/libfmodL64_vc.a'
