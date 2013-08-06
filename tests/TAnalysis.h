#ifndef TANALYSIS_H

#define TANALYSIS_H

#include <QTest>

#include "../src/AbstractAnalysis.h"
#include "../src/StupidAnalysis.h"
#include "../src/AverangeAnalisys.h"
#include "../src/AverangeIgnoreNullAnalisys.h"

class TAnalysis : public QObject
{
    Q_OBJECT
public:
    TAnalysis();

private slots:
    void TestListSum_data();
    void TestListSum();

    void TestStupidAnalysis_data();
    void TestStupidAnalysis();

    void TestAverangeAnalysis_data();
    void TestAverangeAnalysis();

    void TestAverangeIgnoreNullAnalysis_data();
    void TestAverangeIgnoreNullAnalysis();
};

#endif // TANALYSIS_H
