#include <QtGui/QApplication>

#include <QDebug>
#include "tests/TAnalysis.h"
#include "tests/TAnalysisCollection.h"
#include "tests/TAnalysisTableModel.h"

#include "benchmarks/BAnalysisCollections.h"

#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

#ifdef TEST
    TAnalysis tAnalysis;
    QTest::qExec(&tAnalysis);

    qDebug() << "\r\n";

    TAnalysisCollection tAnalysisCollection;
    QTest::qExec(&tAnalysisCollection);

    qDebug() << "\r\n";

    TAnalysisTableModel tAnalysisTableModel;
    QTest::qExec(&tAnalysisTableModel);

#ifdef STRESS
    BAnalysisCollections bAnalysisCollections(1000000);
    bAnalysisCollections.run();
#endif

#endif


#ifndef TEST
    MainWindow w;
    w.show();
#endif
    
    return a.exec();

}
