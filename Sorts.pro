#-------------------------------------------------
#
# Project created by QtCreator 2015-10-19T14:34:07
#
#-------------------------------------------------

QT       += core gui

#CONFIG += c++14
QMAKE_CXXFLAGS += -std=gnu++1y
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Sorts
TEMPLATE = app


SOURCES += main.cpp\
        sortsmainwindow.cpp \
    sortspresenter.cpp \
    sortsgenerator.cpp

HEADERS  += sortsmainwindow.h \
    sortspresenter.h \
    sortssorts.h \
    sortsprofiler.h \
    sortsgenerator.h \
    sortsworker.h

FORMS    += sortsmainwindow.ui
