#-------------------------------------------------
#
# Project created by QtCreator 2013-08-06T11:32:25
#
#-------------------------------------------------

QT       += core gui

TARGET = number-analysis


CONFIG(app){
    message("bulding app")
    TEMPLATE = app
}

CONFIG(test){
    QT += testlib
    message("bulding tests")
    DEFINES += TEST
}

SOURCES += main.cpp\
        mainwindow.cpp \
    src/StupidAnalysis.cpp \
    src/AverangeAnalisys.cpp \
    tests/TAnalysis.cpp \
    src/AverangeIgnoreNullAnalisys.cpp \
    src/AbstractAnalysis.cpp

HEADERS  += mainwindow.h \
    src/StupidAnalysis.h \
    src/AverangeAnalisys.h \
    tests/TAnalysis.h \
    src/AverangeIgnoreNullAnalisys.h \
    src/AbstractAnalysis.h
