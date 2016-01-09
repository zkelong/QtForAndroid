#-------------------------------------------------
#
# Project created by QtCreator 2015-12-15T20:57:31
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QtForAndroid
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    qdebug2logcat.cpp

HEADERS  += mainwindow.h \
    qdebug2logcat.h

FORMS    += mainwindow.ui

CONFIG += mobility
MOBILITY = 

OTHER_FILES += note/*  \

DISTFILES += \
    note/note-1.js \
    note/note-2.js

