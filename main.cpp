#include <QtGui/QApplication>


#ifdef TEST
#include <iostream>
#include "tests/TAnalysis.h"
#include "tests/TAnalysisCollection.h"
#include"tests/TAnalysisTableModel.h"
#endif

#ifndef TEST
#include "mainwindow.h"
#endif


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

#ifndef TEST
    MainWindow w;
    w.show();
#endif
    
    return a.exec();

}
