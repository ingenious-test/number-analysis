#include "TAnalysis.h"


TAnalysis::TAnalysis()
{
}

void TAnalysis::TestListSum_data()
{
    QTest::addColumn< QList<double> >("list");
    QTest::addColumn<double>("sum");

    QTest::newRow("empty-list") << QList<double>()
                                << 0.0;

    QTest::newRow("single-element") << (QList<double>() << 1.0)
                                    << 1.0;

    QTest::newRow("two-elements") << (QList<double>() << 1.0 << 1.0)
                                  << 2.0;

    QTest::newRow("negative-element") << (QList<double>() << 1.0 << -1.0)
                                      << 0.0;
}

void TAnalysis::TestListSum()
{
    QFETCH(QList<double>, list);
    QFETCH(double, sum);

    QCOMPARE(AbstractAnalysis::listSum(list), sum);
}

void TAnalysis::TestStupidAnalysis_data()
{
    QTest::addColumn<double>("value");
    QTest::addColumn<double>("result");

    QTest::newRow("zero-value") << 0.0 << 0.0;
    QTest::newRow("non-zero-value") << 1.0 << 1.0;
    QTest::newRow("negative-value") << -1.0 << -1.0;
}

void TAnalysis::TestStupidAnalysis()
{
    QFETCH(double, value);
    QFETCH(double, result);

    StupidAnalysis analysis(value);

    const double actualResult = analysis.analyze(QList<double>());
    const double expectedResult = result;

    QCOMPARE(actualResult, expectedResult);
}

void TAnalysis::TestAverangeAnalysis_data()
{
    QTest::addColumn< QList<double> >("values");
    QTest::addColumn<double>("result");

    QTest::newRow("empty") << QList<double>() << 0.0;
    QTest::newRow("one-value") << (QList<double>()  << 23.0) << 23.0;
    QTest::newRow("one-doubled-value") << (QList<double>()  << 3.5) << 3.5;
    QTest::newRow("one-negative-value") << (QList<double>()  << -3.0) << -3.0;


    QTest::newRow("two-value") << (QList<double>() << 11.0 << 44.0) << (11.0 + 44.0) / 2.0;
    QTest::newRow("two-doubled-value") << (QList<double>() << 12.3 << 4.5) << (12.3 + 4.5) / 2.0;
    QTest::newRow("two-negative-value") << (QList<double>() << -1.0 << 4.0) << (-1.0 + 4.0) / 2.0;

    QTest::newRow("three-value") << (QList<double>() << 4.0 << 19.0 << 51.0) << (4.0 + 19.0 + 51.0) / 3.0;
    QTest::newRow("three-doubled-value") << (QList<double>() << 4.5 << 19.3 << 13.2) << (4.5 + 19.3 + 13.2) / 3.0;
    QTest::newRow("three-negative-value") << (QList<double>() << -4.0 << 1.0 << 5.0) << (-4.0 + 1.0 + 5.0) / 3.0;


}

void TAnalysis::TestAverangeAnalysis()
{
    QFETCH(QList<double>, values);
    QFETCH(double, result);

    AverangeAnalisys analysis;

    const double actualResult = analysis.analyze(values);
    const double expectedResult = result;

    QCOMPARE(actualResult, expectedResult);

}

void TAnalysis::TestAverangeIgnoreNullAnalysis_data()
{
    QTest::addColumn< QList<double> >("values");
    QTest::addColumn<double>("result");

    QTest::newRow("empty") << QList<double>() << 0.0;
    QTest::newRow("one-value") << (QList<double>()  << 23.0) << 23.0;
    QTest::newRow("one-doubled-value") << (QList<double>()  << 3.5) << 3.5;
    QTest::newRow("one-negative-value") << (QList<double>()  << -3.0) << -3.0;


    QTest::newRow("two-value") << (QList<double>() << 11.0 << 44.0) << (11.0 + 44.0) / 2.0;
    QTest::newRow("two-doubled-value") << (QList<double>() << 12.3 << 4.5) << (12.3 + 4.5) / 2.0;
    QTest::newRow("two-negative-value") << (QList<double>() << -1.0 << 4.0) << (-1.0 + 4.0) / 2.0;

    QTest::newRow("three-value") << (QList<double>() << 4.0 << 19.0 << 51.0) << (4.0 + 19.0 + 51.0) / 3.0;
    QTest::newRow("three-doubled-value") << (QList<double>() << 4.5 << 19.3 << 13.2) << (4.5 + 19.3 + 13.2) / 3.0;
    QTest::newRow("three-negative-value") << (QList<double>() << -4.0 << 1.0 << 5.0) << (-4.0 + 1.0 + 5.0) / 3.0;

    QTest::newRow("three-with-null-value") << (QList<double>() << -4.0 << 0.0 << 5.0) << (-4.0 + 5.0) / 2.0;
    QTest::newRow("four-with-null-value") << (QList<double>() << 5.0 << 0.0 << 10.0 << 0.0) << (5.0 + 10.0) / 2.0;
    QTest::newRow("five-with-null-value") << (QList<double>() << 15.0 << 0.0 << 9.0 << 0.0 << 4.0) << (15.0 + 9.0 + 4.0) / 3.0;
}

void TAnalysis::TestAverangeIgnoreNullAnalysis()
{
    QFETCH(QList<double>, values);
    QFETCH(double, result);

    AverangeIgnoreNullAnalisys analysis;

    const double actualResult = analysis.analyze(values);
    const double expectedResult = result;

    QCOMPARE(actualResult, expectedResult);
}
