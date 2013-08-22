#include <QtGui/QApplication>

#include <QDebug>
#include <QTextCodec>

#include "tests/TAnalysis.h"
#include "tests/TAnalysisCollection.h"
#include "tests/TAnalysisTableModel.h"
#include "tests/TItemListModel.h"
#include "tests/TSqlPointListReader.h"
#include "tests/TPointListGenerator.h"
#include "tests/TPointListStorageStatistics.h"
#include "tests/TCSVPointListImporter.h"

#include "benchmarks/BAnalysisCollections.h"
#include "benchmarks/BSqlPointListInterface.h"
#include "benchmarks/BSqlPointListReadWrite.h"
#include "benchmarks/BStatisticsCollection.h"

#include "AnalysisWindow.h"

#include "tests/TestingUtilities.h"


int main(int argc, char *argv[])
{
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));

    QApplication a(argc, argv);

#ifdef TEST
    const QString currentDir = QDir::currentPath();
    const QString testingFilesDir = currentDir + "\\testingFiles\\";

    if(!QDir().exists(testingFilesDir))
    {
        QDir().mkdir(testingFilesDir);
    }

    QDir::setCurrent(testingFilesDir);

    TAnalysis tAnalysis;
    QTest::qExec(&tAnalysis);

    qDebug() << "\r\n";

    TAnalysisCollection tAnalysisCollection;
    QTest::qExec(&tAnalysisCollection);

    qDebug() << "\r\n";

    TAnalysisTableModel tAnalysisTableModel;
    QTest::qExec(&tAnalysisTableModel);

    qDebug() << "\r\n";

    TItemListModel tItemListModel;
    QTest::qExec(&tItemListModel);

    qDebug() << "\r\n";

    TSqlPointListReader tSqlPointListReader;
    QTest::qExec(&tSqlPointListReader);

    qDebug() << "\r\n";

    TPointListGenerator tPointListGenerator;
    QTest::qExec(&tPointListGenerator);

    qDebug() << "\r\n";

    TPointListStorageStatistics tPointListStorageStatistics;
    QTest::qExec(&tPointListStorageStatistics);

    qDebug() << "\r\n";

    TCSVPointListImporter tCSVPointListImporter;
    QTest::qExec(&tCSVPointListImporter);
#ifdef STRESS 
    qDebug() << "\r\n";

    BAnalysisCollections bAnalysisCollections(0);
    bAnalysisCollections.run();

    qDebug() << "\r\n";

    BSqlPointListInterface bSqlPointListInterface(0);
    bSqlPointListInterface.run();

    qDebug() << "\r\n";

    BSqlPointListReadWrite bSqlPointListReadWrite(0);
    bSqlPointListReadWrite.runWrite();
    bSqlPointListReadWrite.runRead();

    qDebug() << "\r\n";

    BStatisticsCollection  bStatisticsCollection;
    bStatisticsCollection.generateDatabase(100000, 200);
    bStatisticsCollection.statistics();
#endif  

    QDir::setCurrent(currentDir);
#endif

#ifndef TEST
    AnalysisWindow analysisWindow;
    analysisWindow.show();
#endif
    
    return a.exec();

}
