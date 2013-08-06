#ifndef TANALYSIS_H

#define TANALYSIS_H

#include <QTest>

#include "../src/StupidAnalysis.h"
#include "../src/AverangeAnalisys.h"

class TAnalysis : public QObject
{
    Q_OBJECT
public:
    TAnalysis();

private slots:
    void TestStupidAnalysis_data();
    void TestStupidAnalysis();

    void TestAverangeAnalysis_data();
    void TestAverangeAnalysis();
};

#endif // TANALYSIS_H
