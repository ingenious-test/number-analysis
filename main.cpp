#include <QtGui/QApplication>

#include <QDebug>
#include <QTextCodec>

#include "tests/TAnalysis.h"
#include "tests/TAnalysisCollection.h"
#include "tests/TAnalysisTableModel.h"
#include "tests/TItemListModel.h"
#include "tests/TSqlPointListReader.h"

#include "benchmarks/BAnalysisCollections.h"
#include "benchmarks/BSqlPointListInterface.h"
#include "benchmarks/BSqlPointListReadWrite.h"

#include "AnalysisWindow.h"

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

#ifdef STRESS 
    qDebug() << "\r\n";

    BAnalysisCollections bAnalysisCollections(0);
    bAnalysisCollections.run();

    qDebug() << "\r\n";

    BSqlPointListInterface bSqlPointListInterface(0);
    bSqlPointListInterface.run();

    qDebug() << "\r\n";

    BSqlPointListReadWrite bSqlPointListReadWrite(10000);
    //bSqlPointListReadWrite.runWrite();
    bSqlPointListReadWrite.runRead();
#endif  

    QDir::setCurrent(currentDir);
#endif

#ifndef TEST
    AnalysisWindow analysisWindow;
    analysisWindow.show();
#endif
    
    return a.exec();

}
