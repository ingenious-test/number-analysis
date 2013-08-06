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
    src/AverageAnalysis.cpp \
    tests/TAnalysis.cpp \
    src/AverageIgnoreNullAnalysis.cpp \
    src/AbstractAnalysis.cpp \
    tests/TAnalysisCollection.cpp \
    src/AnalysisCollection.cpp

HEADERS  += mainwindow.h \
    src/StupidAnalysis.h \
    tests/TAnalysis.h \
    src/AbstractAnalysis.h \
    tests/TAnalysisCollection.h \
    src/AnalysisCollection.h \
    tests/TestingUtilities.h \
    src/AverageIgnoreNullAnalysis.h \
    src/AverageAnalysis.h
