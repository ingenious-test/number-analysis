#-------------------------------------------------
#
# Project created by QtCreator 2013-08-06T11:32:25
#
#-------------------------------------------------

QT       += core gui
QT += testlib
TARGET = number-analysis

CONFIG(app){
    message("bulding app")
    TEMPLATE = app
    DEFINES += APP
}

CONFIG(test){
    message("bulding tests")
    DEFINES += TEST

    CONFIG(stress){
        message("bulding stress-tests")
        DEFINES += STRESS
    }
}

SOURCES += main.cpp\
        AnalysisWindow.cpp \
    src/StupidAnalysis.cpp \
    src/AverageAnalysis.cpp \
    tests/TAnalysis.cpp \
    src/AverageIgnoreNullAnalysis.cpp \
    src/AbstractAnalysis.cpp \
    tests/TAnalysisCollection.cpp \
    src/AnalysisCollection.cpp \
    tests/TAnalysisTableModel.cpp \
    src/AnalysisTableModel.cpp \
    benchmarks/BAnalysisCollections.cpp \
    tests/TItemListModel.cpp \
    src/ItemListModel.cpp \
    src/StandardDeviationAnalysis.cpp \
    src/ItemListView.cpp \
    mocs/MocPointListReader.cpp \
    src/AbstractPointListReader.cpp \
    src/SqlPointListReader.cpp \
    tests/TSqlPointListReader.cpp \
    src/SqlPointListWriter.cpp

HEADERS  += AnalysisWindow.h \
    src/StupidAnalysis.h \
    tests/TAnalysis.h \
    src/AbstractAnalysis.h \
    tests/TAnalysisCollection.h \
    src/AnalysisCollection.h \
    tests/TestingUtilities.h \
    src/AverageIgnoreNullAnalysis.h \
    src/AverageAnalysis.h \
    tests/TAnalysisTableModel.h \
    src/AnalysisTableModel.h \
    benchmarks/BAnalysisCollections.h \
    tests/TItemListModel.h \
    src/ItemListModel.h \
    src/StandardDeviationAnalysis.h \
    src/ItemListView.h \
    mocs/MocPointListReader.h \
    src/AbstractPointListReader.h \
    src/SqlPointListReader.h \
    tests/TSqlPointListReader.h \
    src/SqlPointListWriter.h
