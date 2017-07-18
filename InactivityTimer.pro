#-------------------------------------------------
#
# Project created by QtCreator 2017-07-17T16:24:42
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = InactivityTimer
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    customeventfilter.cpp

HEADERS  += mainwindow.h \
    customeventfilter.h

FORMS    += mainwindow.ui
