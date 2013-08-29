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

    SOURCES += AnalysisWindow.cpp

    HEADERS += AnalysisWindow.h
}

CONFIG(test){
    message("bulding tests")
    DEFINES += TEST

    SOURCES += tests/TAnalysis.cpp \
        tests/TAnalysisCollection.cpp \
        tests/TAnalysisTableModel.cpp \
        tests/TItemListModel.cpp \
        tests/TSqlPointListReader.cpp \
        tests/TPointListGenerator.cpp \
        tests/TPointListStorageStatistics.cpp \
        tests/TCSVPointListImporter.cpp \
        tests/TCSVPointListValidator.cpp \
        tests/TCSVPointListExporter.cpp


    HEADERS += tests/TAnalysis.h \
        tests/TAnalysisCollection.h \
        tests/TestingUtilities.h \
        tests/TAnalysisTableModel.h \
        tests/TItemListModel.h \
        tests/TSqlPointListReader.h \
        tests/TPointListGenerator.h \
        tests/TCSVPointListImporter.h \
        tests/TCSVPointListValidator.h \
        tests/TCSVPointListExporter.h \
        tests/TPointListStorageStatistics.h
}

CONFIG(stress){
    message("bulding stress-tests")
    DEFINES += STRESS

    SOURCES += benchmarks/BAnalysisCollections.cpp \
        benchmarks/BSqlPointListInterface.cpp \
        benchmarks/BSqlPointListReadWrite.cpp \
        benchmarks/BStatisticsCollection.cpp \
        benchmarks/BCSVImporterExporter.cpp

    HEADERS += benchmarks/BAnalysisCollections.h \
        benchmarks/BSqlPointListInterface.h \
        benchmarks/BSqlPointListReadWrite.h \
        benchmarks/BStatisticsCollection.h \
        benchmarks/BCSVImporterExporter.h
}

SOURCES += main.cpp\
    src/StupidAnalysis.cpp \
    src/AverageAnalysis.cpp \
    src/AverageIgnoreNullAnalysis.cpp \
    src/AbstractAnalysis.cpp \
    src/AnalysisCollection.cpp \
    src/AnalysisTableModel.cpp \
    src/ItemListModel.cpp \
    src/StandardDeviationAnalysis.cpp \
    src/ItemListView.cpp \
    mocs/MocPointListReader.cpp \
    src/AbstractPointListReader.cpp \
    src/SqlPointListReader.cpp \
    src/SqlPointListWriter.cpp \
    src/SqlPointListInterface.cpp \
    src/DatabaseGenerator.cpp \
    src/PointListGenerator.cpp \
    src/PointListStorageStatistics.cpp \
    src/PointListStorageStatisticsDialog.cpp \
    src/CSVPointListImporter.cpp \
    src/CSVPointListValidator.cpp \
    src/CSVPointListExporter.cpp \
    src/MedianAnalysis.cpp \
    src/PointList.cpp \
    src/SequencePointList.cpp \
    src/FirstQuartileAnalysis.cpp \
    src/ThirdQuartileAnalysis.cpp

HEADERS  += src/StupidAnalysis.h \
    src/AbstractAnalysis.h \    
    src/AnalysisCollection.h \    
    src/AverageIgnoreNullAnalysis.h \
    src/AverageAnalysis.h \    
    src/AnalysisTableModel.h \
    src/ItemListModel.h \
    src/StandardDeviationAnalysis.h \
    src/ItemListView.h \
    mocs/MocPointListReader.h \
    src/AbstractPointListReader.h \
    src/SqlPointListReader.h \    
    src/SqlPointListWriter.h \
    src/SqlPointListInterface.h \    
    src/DatabaseGenerator.h \    
    src/PointListGenerator.h \
    src/PointListStorageStatistics.h \
    src/Metatypes.h \
    src/PointListStorageStatisticsDialog.h \
    src/StatisticsCollection.h \    
    src/CSVPointListImporter.h \    
    src/CSVPointListValidator.h \    
    src/CSVPointListExporter.h \
    src/MedianAnalysis.h \
    src/PointList.h \
    src/SequencePointList.h \    
    src/FirstQuartileAnalysis.h \
    src/ThirdQuartileAnalysis.h



CONFIG(debug, debug|release) {
    message(building debug)
    DESTDIR = build/debug
    OBJECTS_DIR = build/debug/.obj
    MOC_DIR = build/debug/.moc
    RCC_DIR = build/debug/.rcc
    UI_DIR = build/debug/.u
}
CONFIG(release, debug|release) {
    message(building release)
    DESTDIR = build/release
    OBJECTS_DIR = build/release/.obj
    MOC_DIR = build/release/.moc
    RCC_DIR = build/release/.rcc
    UI_DIR = build/release/.ui
}

win32{

QMAKE_CXXFLAGS += -W \
-Wundef \
#-Wfloat-equal \
#-Wshadow \
-Wunsafe-loop-optimizations \
-Wconversion \
#-Wlogical-op \
#-Wpadded \
#-Winvalid-pch \
-Wdisabled-optimization \
}
