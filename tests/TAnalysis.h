#ifndef TANALYSIS_H

#define TANALYSIS_H

#include "../src/AbstractAnalysis.h"
#include "../src/StupidAnalysis.h"
#include "../src/AverageAnalysis.h"
#include "../src/AverageIgnoreNullAnalysis.h"
#include "../src/StandardDeviationAnalysis.h"

#include "TestingUtilities.h"

class TAnalysis : public QObject
{
    Q_OBJECT
public:
    TAnalysis();

private slots:
    void TestAbstractAnalysis_data();
    void TestAbstractAnalysis();

    void TestListSum_data();
    void TestListSum();

    void TestStupidAnalysis_data();
    void TestStupidAnalysis();

    void TestAverageAnalysis_data();
    void TestAverageAnalysis();

    void TestAverageIgnoreNullAnalysis_data();
    void TestAverageIgnoreNullAnalysis();

    void TestStandardDeviation_data();
    void TestStandardDeviation();
};

#endif // TANALYSIS_H
