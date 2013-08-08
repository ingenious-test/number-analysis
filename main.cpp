#include <QtGui/QApplication>

#include <iostream>

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

    std::cout << "\r\n";

    TAnalysisCollection tAnalysisCollection;
    QTest::qExec(&tAnalysisCollection);

    std::cout << "\r\n";

    TAnalysisTableModel tAnalysisTableModel;
    QTest::qExec(&tAnalysisTableModel);
#endif

#ifdef STRESS_TEST
    BAnalysisCollections  bAnalysisCollections(1000000);
    bAnalysisCollections.run();
#endif

#ifndef TEST
    MainWindow w;
    w.show();
#endif
    
    return a.exec();

}
