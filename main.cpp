#include <QtGui/QApplication>

#include <QDebug>
#include <QTextCodec>

#include "tests/TAnalysis.h"
#include "tests/TAnalysisCollection.h"
#include "tests/TAnalysisTableModel.h"
#include "tests/TItemListModel.h"
#include "tests/TSqlPointListReader.h"

#include "benchmarks/BAnalysisCollections.h"

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

    QDir::setCurrent(currentDir);

#ifdef STRESS
    BAnalysisCollections bAnalysisCollections(1000000);
    bAnalysisCollections.run();
#endif

#endif

#ifndef TEST
    AnalysisWindow analysisWindow;
    analysisWindow.show();
#endif
    
    return a.exec();

}
