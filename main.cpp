#include <QtGui/QApplication>
#include <QTextCodec>

#ifdef TEST
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
#include "tests/TPointList.h"
#endif

#ifdef STRESS
#include "benchmarks/BAnalysisCollections.h"
#include "benchmarks/BSqlPointListInterface.h"
#include "benchmarks/BSqlPointListReadWrite.h"
#include "benchmarks/BStatisticsCollection.h"
#include "benchmarks/BCSVImporterExporter.h"
#include "benchmarks/BAnalyzing.h"
#endif


#ifdef APP
#include "AnalysisWindow.h"
#endif

int main(int argc, char *argv[])
{
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));

    QApplication a(argc, argv);

    const QString currentDir = QDir::currentPath();
    const QString testingFilesDir = currentDir + "\\testingFiles\\";

    if(!QDir().exists(testingFilesDir))
    {
        QDir().mkdir(testingFilesDir);
    }

    QDir::setCurrent(testingFilesDir);
#ifdef TEST
    TAnalysis tAnalysis;
    QTest::qExec(&tAnalysis);

    qWarning() << "\n";

    TAnalysisCollection tAnalysisCollection;
    QTest::qExec(&tAnalysisCollection);

    qWarning() << "\n";

    TAnalysisTableModel tAnalysisTableModel;
    QTest::qExec(&tAnalysisTableModel);

    qWarning() << "\n";

    TItemListModel tItemListModel;
    QTest::qExec(&tItemListModel);

    qWarning() << "\n";

    TSqlPointListReader tSqlPointListReader;
    QTest::qExec(&tSqlPointListReader);

    qWarning() << "\n";

    TPointListGenerator tPointListGenerator;
    QTest::qExec(&tPointListGenerator);

    qWarning() << "\n";

    TPointListStorageStatistics tPointListStorageStatistics;
    QTest::qExec(&tPointListStorageStatistics);

    qWarning() << "\n";

    TCSVPointListImporter tCSVPointListImporter;
    QTest::qExec(&tCSVPointListImporter);

    qWarning() << "\n";

    TCSVPointListValidator tCSVPointListValidator;
    QTest::qExec(&tCSVPointListValidator);

    qWarning() << "\n";

    TCSVPointListExporter tCSVPointListExporter;
    QTest::qExec(&tCSVPointListExporter);

    qWarning() << "\n";

    TPointList tPointList;
    QTest::qExec(&tPointList);
#endif

#ifdef STRESS
//    qWarning() << "\n" << "Analysis collection benchmark" << "\n";

//    BAnalysisCollections bAnalysisCollections(10000);
//    bAnalysisCollections.run();

//    qWarning() << "\n" << "SqlInterface benchmark"  << "\n";;

//    BSqlPointListInterface bSqlPointListInterface(10000);
//    bSqlPointListInterface.run();

//    qWarning() << "\n" << "SqlPointListReadWrite benchmark"  << "\n";

//    BSqlPointListReadWrite bSqlPointListReadWrite(10000);
//    bSqlPointListReadWrite.runWriteAll();
//    bSqlPointListReadWrite.runReadAll();

//    bSqlPointListReadWrite.runWrite();
//    bSqlPointListReadWrite.runRead();

//    qWarning() << "\n" << "StaticCollection benchmark"  << "\n";

//    BStatisticsCollection  bStatisticsCollection;
//    bStatisticsCollection.generateDatabase(10000, 100);
//    bStatisticsCollection.statistics();

//    qWarning() << "\n" << "CSV import, export and validation benchmarck"  << "\n";

//    BCSVImporterExporter  bCSVImporterExporter(20000, 200);
//    bCSVImporterExporter.run();

    qWarning() << "\n" << "Analyzing benchmark"  << "\n";

    BAnalyzing  bAnalyzing(100000);
    bAnalyzing.run();

#endif
    QDir::setCurrent(currentDir);


#ifdef APP
    AnalysisWindow analysisWindow;
    analysisWindow.show();  
#endif

    return a.exec();
}
