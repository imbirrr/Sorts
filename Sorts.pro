#-------------------------------------------------
#
# Project created by QtCreator 2015-10-19T14:34:07
#
#-------------------------------------------------

QT       += core gui

CONFIG += c++14

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Sorts
TEMPLATE = app


SOURCES += main.cpp\
        sortsmainwindow.cpp \
    sortspresenter.cpp \
    sortssorts.cpp \
    sortsprofiler.cpp \
    sortsgenerator.cpp

HEADERS  += sortsmainwindow.h \
    sortspresenter.h \
    sortssorts.h \
    sortsprofiler.h \
    sortsgenerator.h

FORMS    += sortsmainwindow.ui
