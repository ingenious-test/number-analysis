#include "TAnalysis.h"


TAnalysis::TAnalysis()
{
}

void TAnalysis::TestAbstractAnalysis_data()
{
    QTest::addColumn<AbstractAnalysis*>("analysis");
    QTest::addColumn<QString>("name");

    QTest::newRow("average") << static_cast<AbstractAnalysis*>(new AverageAnalysis) << "average";
    QTest::newRow("average-with-ignore-null")
            << static_cast<AbstractAnalysis*>(new AverageIgnoreNullAnalysis)
            << "average-ignore-null";
    QTest::newRow("stupid") << static_cast<AbstractAnalysis*>(new StupidAnalysis) << "stupid";
}

void TAnalysis::TestAbstractAnalysis()
{
    QFETCH(AbstractAnalysis*, analysis);
    QFETCH(QString, name);

    QCOMPARE(analysis->name(), name);

    delete analysis;
}

void TAnalysis::TestListSum_data()
{
    QTest::addColumn< PointList >("list");
    QTest::addColumn<double>("sum");

    QTest::newRow("empty-list") << PointList()
                                << 0.0;

    QTest::newRow("single-element") << PointList().appendInc(1.0)
                                    << 1.0;

    QTest::newRow("two-elements") << PointList().appendInc(1.0).appendInc(1.0)
                                  << 2.0;

    QTest::newRow("negative-element") << PointList().appendInc(1.0).appendInc(-1.0)
                                      << 0.0;
}

void TAnalysis::TestListSum()
{
    QFETCH(PointList, list);
    QFETCH(double, sum);

    FUZZY_COMPARE(AbstractAnalysis::listSum(list), sum);
}

void TAnalysis::TestStupidAnalysis_data()
{
    QTest::addColumn<Point>("value");
    QTest::addColumn<double>("result");

    QTest::newRow("zero-value") << 0.0 << 0.0;
    QTest::newRow("non-zero-value") << 1.0 << 1.0;
    QTest::newRow("negative-value") << -1.0 << -1.0;
}

void TAnalysis::TestStupidAnalysis()
{
    QFETCH(Point, value);
    QFETCH(double, result);

    StupidAnalysis analysis(value);

    const double actualResult = analysis.analyze(PointList());
    const double expectedResult = result;

    FUZZY_COMPARE(actualResult, expectedResult);
}

void TAnalysis::TestAverageAnalysis_data()
{
    QTest::addColumn< PointList >("values");
    QTest::addColumn<double>("result");

    QTest::newRow("empty") << PointList() << 0.0;

    QTest::newRow("one-value") << PointList()
                                  .appendInc(23.0)
                               << 23.0;

    QTest::newRow("one-doubled-value") << PointList()
                                          .appendInc(3.5)
                                       << 3.5;

    QTest::newRow("one-negative-value") << PointList()
                                           .appendInc(-3.0)
                                        << -3.0;


    QTest::newRow("two-value") << PointList()
                                  .appendInc(11.0)
                                  .appendInc(44.0)
                               << (11.0 + 44.0) / 2.0;

    QTest::newRow("two-doubled-value") << PointList()
                                          .appendInc(12.3)
                                          .appendInc(4.5)
                                       << (12.3 + 4.5) / 2.0;

    QTest::newRow("two-negative-value") << PointList()
                                           .appendInc(-1.0)
                                           .appendInc(4.0)
                                        << (-1.0 + 4.0) / 2.0;

    QTest::newRow("three-value") << PointList()
                                    .appendInc(4.0)
                                    .appendInc(19.0)
                                    .appendInc(51.0)
                                 << (4.0 + 19.0 + 51.0) / 3.0;

    QTest::newRow("three-doubled-value") << PointList()
                                            .appendInc(4.5)
                                            .appendInc(19.3)
                                            .appendInc(13.2)
                                         << (4.5 + 19.3 + 13.2) / 3.0;

    QTest::newRow("three-negative-value") << PointList()
                                             .appendInc(-4.0)
                                             .appendInc(1.0)
                                             .appendInc(5.0)
                                          << (-4.0 + 1.0 + 5.0) / 3.0;


}

void TAnalysis::TestAverageAnalysis()
{
    QFETCH(PointList, values);
    QFETCH(double, result);

    AverageAnalysis analysis;

    const double actualResult = analysis.analyze(values);
    const double expectedResult = result;

    FUZZY_COMPARE(actualResult, expectedResult);

}

void TAnalysis::TestAverageIgnoreNullAnalysis_data()
{
    QTest::addColumn< PointList >("values");
    QTest::addColumn<Point>("result");

    QTest::newRow("empty") << PointList() << 0.0;
    QTest::newRow("one-value") << PointList().appendInc(23.0) << 23.0;
    QTest::newRow("one-doubled-value") << PointList().appendInc(3.5) << 3.5;
    QTest::newRow("one-negative-value") << PointList().appendInc( -3.0) << -3.0;


    QTest::newRow("two-value") << PointList()
                                  .appendInc(11.0)
                                  .appendInc(44.0)
                               << (11.0 + 44.0) / 2.0;
    QTest::newRow("two-doubled-value") << PointList()
                                          .appendInc(12.3)
                                          .appendInc(4.5)
                                       << (12.3 + 4.5) / 2.0;

    QTest::newRow("two-negative-value") << PointList()
                                           .appendInc(-1.0)
                                           .appendInc(4.0)
                                        << (-1.0 + 4.0) / 2.0;

    QTest::newRow("three-value") << PointList().appendInc(4.0)
                                    .appendInc(19.0)
                                    .appendInc(51.0)
                                 << (4.0 + 19.0 + 51.0) / 3.0;
    QTest::newRow("three-doubled-value") << PointList().appendInc(4.5)
                                            .appendInc(19.3)
                                            .appendInc(13.2)
                                         << (4.5 + 19.3 + 13.2) / 3.0;
    QTest::newRow("three-negative-value") << PointList().appendInc(-4.0)
                                             .appendInc(1.0)
                                             .appendInc(5.0)
                                          << (-4.0 + 1.0 + 5.0) / 3.0;

    QTest::newRow("three-with-null-value") << PointList()
                                              .appendInc(-4.0)
                                              .appendInc(0.0)
                                              .appendInc(5.0)
                                           << (-4.0 + 5.0) / 2.0;

    QTest::newRow("four-with-null-value") << PointList()
                                             .appendInc(5.0)
                                             .appendInc(0.0)
                                             .appendInc(10.0)
                                             .appendInc(0.0)
                                          << (5.0 + 10.0) / 2.0;

    QTest::newRow("five-with-null-value") << PointList()
                                             .appendInc(15.0)
                                             .appendInc(0.0)
                                             .appendInc(9.0)
                                             .appendInc(0.0)
                                             .appendInc(4.0)
                                          << (15.0 + 9.0 + 4.0) / 3.0;
}

void TAnalysis::TestAverageIgnoreNullAnalysis()
{
    QFETCH(PointList, values);
    QFETCH(double, result);

    AverageIgnoreNullAnalysis analysis;

    const double actualResult = analysis.analyze(values);
    const double expectedResult = result;

    FUZZY_COMPARE(actualResult, expectedResult);
}
