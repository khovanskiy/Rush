#-------------------------------------------------
#
# Project created by QtCreator 2014-02-21T16:05:02
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Server
TEMPLATE = app


SOURCES += \
    server-main.cpp \
    vector2d.cpp \
    console.cpp \
    server.cpp \
    event.cpp \
    eventdispatcher.cpp \
    gamemodelobject.cpp \
    networkclient.cpp \
    api.cpp

HEADERS  += \
    ../background.h \
    vector2d.h \
    console.h \
    server.h \
    event.h \
    eventdispatcher.h \
    eventhandler.h \
    gamemodelobject.h \
    networkclient.h \
    api.h
