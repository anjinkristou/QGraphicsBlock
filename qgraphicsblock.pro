#-------------------------------------------------
#
# Project created by QtCreator 2013-03-13T19:12:29
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qgraphicsblock
TEMPLATE = app

include(qgraphicsblock.pri)

INCLUDEPATH += test

SOURCES += test/main.cpp\
        test/MainWindow.cpp

HEADERS  += test/MainWindow.h

FORMS    += test/MainWindow.ui
