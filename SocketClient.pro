#-------------------------------------------------
#
# Project created by QtCreator 2013-02-18T10:05:37
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SocketClient
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    clientconnection.cpp

HEADERS  += mainwindow.h \
    clientconnection.h

FORMS    += mainwindow.ui
