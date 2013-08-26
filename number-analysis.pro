#-------------------------------------------------
#
# Project created by QtCreator 2013-08-06T11:32:25
#
#-------------------------------------------------

QT       += core gui
QT       += sql
QT       += testlib

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
    src/SqlPointListWriter.cpp \
    src/SqlPointListInterface.cpp \
    benchmarks/BSqlPointListInterface.cpp \
    benchmarks/BSqlPointListReadWrite.cpp \
    src/DatabaseGenerator.cpp \
    tests/TPointListGenerator.cpp \
    src/PointListGenerator.cpp \
    tests/TPointListStorageStatistics.cpp \
    src/PointListStorageStatistics.cpp \
    src/PointListStorageStatisticsDialog.cpp \
    benchmarks/BStatisticsCollection.cpp \
    src/CSVPointListImporter.cpp \
    tests/TCSVPointListImporter.cpp \
    tests/TCSVPointListValidator.cpp \
    src/CSVPointListValidator.cpp \
    tests/TCSVPointListExporter.cpp \
    src/CSVPointListExporter.cpp \
    src/MedianAnalysis.cpp \
    src/PointList.cpp \
    src/SequencePointList.cpp \
    benchmarks/BCSVImporterExporter.cpp \
    src/FirstQuartileAnalysis.cpp \
    src/ThirdQuartileAnalysis.cpp

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
    src/SqlPointListWriter.h \
    src/SqlPointListInterface.h \
    benchmarks/BSqlPointListInterface.h \
    benchmarks/BSqlPointListReadWrite.h \
    src/DatabaseGenerator.h \
    tests/TPointListGenerator.h \
    src/PointListGenerator.h \
    tests/TPointListStorageStatistics.h \
    src/PointListStorageStatistics.h \
    src/Metatypes.h \
    src/PointListStorageStatisticsDialog.h \
    src/StatisticsCollection.h \
    benchmarks/BStatisticsCollection.h \
    src/CSVPointListImporter.h \
    tests/TCSVPointListImporter.h \
    tests/TCSVPointListValidator.h \
    src/CSVPointListValidator.h \
    tests/TCSVPointListExporter.h \
    src/CSVPointListExporter.h \
    src/MedianAnalysis.h \
    src/PointList.h \
    src/SequencePointList.h \
    benchmarks/BCSVImporterExporter.h \
    src/FirstQuartileAnalysis.h \
    src/ThirdQuartileAnalysis.h
