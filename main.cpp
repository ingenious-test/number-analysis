#include <QtGui/QApplication>

#include "tests/TAnalysis.h"

#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

#ifdef TEST
    TAnalysis tAnalysis;
    QTest::qExec(&tAnalysis);
#endif

#ifndef TEST
    MainWindow w;
    w.show();
#endif
    
    return a.exec();

}
