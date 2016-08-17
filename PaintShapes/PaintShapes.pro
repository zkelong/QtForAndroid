#-------------------------------------------------
#
# Project created by QtCreator 2016-08-16T21:54:57
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PaintShapes
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    shapefactory.cpp \
    shapeselector.cpp

HEADERS  += widget.h \
    shapefactory.h \
    shapeselector.h \
    shapetype.h
