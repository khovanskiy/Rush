#-------------------------------------------------
#
# Project created by QtCreator 2013-10-18T13:41:38
#
#-------------------------------------------------

QT       += core gui network opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Rush
TEMPLATE = app


SOURCES += main.cpp\
        program.cpp \
    camera.cpp \
    graphiccore.cpp \
    console.cpp \
    bitmap.cpp \
    background.cpp \
    movieclip.cpp \
    mouseevent.cpp \
    mouse.cpp \
    vector2d.cpp \
    interactiveobject.cpp \
    eventdispatcher.cpp \
    stage.cpp \
    keyboard.cpp \
    keyboardevent.cpp \
    event.cpp \
    displayobjectcontainer.cpp \
    displayobject.cpp \
    interface.cpp \
    matrix.cpp

HEADERS  += program.h \
    camera.h \
    graphiccore.h \
    console.h \
    bitmap.h \
    background.h \
    movieclip.h \
    mouseevent.h \
    mouse.h \
    vector2d.h \
    interactiveobject.h \
    function.h \
    eventdispatcher.h \
    stage.h \
    keyboard.h \
    keyboardevent.h \
    event.h \
    displayobjectcontainer.h \
    displayobject.h \
    interface.h \
    matrix.h
