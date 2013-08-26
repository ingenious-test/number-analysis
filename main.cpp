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
#include "tests/TCSVPointListValidator.h"
#include "tests/TCSVPointListExporter.h"

#include "benchmarks/BAnalysisCollections.h"
#include "benchmarks/BSqlPointListInterface.h"
#include "benchmarks/BSqlPointListReadWrite.h"
#include "benchmarks/BStatisticsCollection.h"
#include "benchmarks/BCSVImporterExporter.h"

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

    qDebug() << "\n";

    TAnalysisCollection tAnalysisCollection;
    QTest::qExec(&tAnalysisCollection);

    qDebug() << "\n";

    TAnalysisTableModel tAnalysisTableModel;
    QTest::qExec(&tAnalysisTableModel);

    qDebug() << "\n";

    TItemListModel tItemListModel;
    QTest::qExec(&tItemListModel);

    qDebug() << "\n";

    TSqlPointListReader tSqlPointListReader;
    QTest::qExec(&tSqlPointListReader);

    qDebug() << "\n";

    TPointListGenerator tPointListGenerator;
    QTest::qExec(&tPointListGenerator);

    qDebug() << "\n";

    TPointListStorageStatistics tPointListStorageStatistics;
    QTest::qExec(&tPointListStorageStatistics);

    qDebug() << "\n";

    TCSVPointListImporter tCSVPointListImporter;
    QTest::qExec(&tCSVPointListImporter);

    qDebug() << "\n";

    TCSVPointListValidator tCSVPointListValidator;
    QTest::qExec(&tCSVPointListValidator);

    qDebug() << "\n";

    TCSVPointListExporter tCSVPointListExporter;
    QTest::qExec(&tCSVPointListExporter);
#ifdef STRESS 
   /* qWarning() << "\n" << "Analysis collection benchmark" << "\n";

    BAnalysisCollections bAnalysisCollections(0);
    bAnalysisCollections.run();

    qWarning() << "\r\n" << "SqlInterface benchmark"  << "\n";;

    BSqlPointListInterface bSqlPointListInterface(0);
    bSqlPointListInterface.run();

    qWarning() << "\r\n" << "SqlPointListReadWrite benchmark"  << "\n";

    BSqlPointListReadWrite bSqlPointListReadWrite(0);
    bSqlPointListReadWrite.runWrite();
    bSqlPointListReadWrite.runRead();

    qWarning() << "\r\n" << "StaticCollection benchmark"  << "\n";;

    BStatisticsCollection  bStatisticsCollection;
    bStatisticsCollection.generateDatabase(0, 0);
    bStatisticsCollection.statistics();*/

    qWarning() << "\r\n" << "CSV import, export and validation benchmarck"  << "\n";

    BCSVImporterExporter  bCSVImporterExporter(10000, 100);
    bCSVImporterExporter.run();
#endif  

    QDir::setCurrent(currentDir);
#endif

#ifndef TEST
    AnalysisWindow analysisWindow;
    analysisWindow.show();
#endif
    
    return a.exec();

}
