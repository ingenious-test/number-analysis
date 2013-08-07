#include <QtGui/QApplication>

#ifdef TEST
    #include <iostream>
    #include "tests/TAnalysis.h"
    #include "tests/TAnalysisCollection.h"
#else
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
#else
    MainWindow w;
    w.show();
#endif
    
    return a.exec();

}
