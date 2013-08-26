#include "TAnalysis.h"


TAnalysis::TAnalysis()
{
}

void TAnalysis::TestAbstractAnalysis_data()
{
    QTest::addColumn<AbstractAnalysis*>("analysis");
    QTest::addColumn<IDAnalysis>("analysisID");

    QTest::newRow("average") << static_cast<AbstractAnalysis*>(new AverageAnalysis) << "average";
    QTest::newRow("average-with-ignore-null")
            << static_cast<AbstractAnalysis*>(new AverageIgnoreNullAnalysis)
            << "average-ignore-null";
    QTest::newRow("stupid") << static_cast<AbstractAnalysis*>(new StupidAnalysis) << "stupid";
}

void TAnalysis::TestAbstractAnalysis()
{
    QFETCH(AbstractAnalysis*, analysis);
    QFETCH(IDAnalysis, analysisID);

    QCOMPARE(analysis->id(), analysisID);

    delete analysis;
}

void TAnalysis::TestListSum_data()
{
    QTest::addColumn< PointList >("list");
    QTest::addColumn<double>("sum");

    QTest::newRow("empty-list") << PointList()
                                << 0.0;

    QTest::newRow("single-element") << (PointList() << 1.0)
                                    << 1.0;

    QTest::newRow("two-elements") << (PointList() << 1.0 << 1.0)
                                  << 2.0;

    QTest::newRow("negative-element") << (PointList() << 1.0 << -1.0)
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

    QTest::newRow("one-value") << (PointList() << 23.0)
                               << 23.0;

    QTest::newRow("one-doubled-value") << (PointList()<< 3.5)
                                       << 3.5;

    QTest::newRow("one-negative-value") << (PointList() << -3.0)
                                        << -3.0;


    QTest::newRow("two-value") << (PointList() << 11.0 << 44.0)
                               << (11.0 + 44.0) / 2.0;

    QTest::newRow("two-doubled-value") << (PointList() << 12.3 << 4.5)
                                       << (12.3 + 4.5) / 2.0;

    QTest::newRow("two-negative-value") << (PointList() << -1.0 << 4.0)
                                        << (-1.0 + 4.0) / 2.0;

    QTest::newRow("three-value") << (PointList() << 4.0 << 19.0 <<51.0)
                                 << (4.0 + 19.0 + 51.0) / 3.0;

    QTest::newRow("three-doubled-value") << (PointList() << 4.5 << 19.3 << 13.2)
                                         << (4.5 + 19.3 + 13.2) / 3.0;

    QTest::newRow("three-negative-value") << (PointList() << -4.0 << 1.0 << 5.0)
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
    QTest::addColumn<double>("result");

    QTest::newRow("empty") << PointList() << 0.0;

    QTest::newRow("null") << (PointList() << 0.0 << 0.0 << 0.0) << 0.0;

    QTest::newRow("one-value") << (PointList() << 23.0) << 23.0;
    QTest::newRow("one-doubled-value") << (PointList() << 3.5) << 3.5;
    QTest::newRow("one-negative-value") << (PointList() << -3.0) << -3.0;


    QTest::newRow("two-value") << (PointList()
                                   << 11.0
                                   << 44.0)
                               << (11.0 + 44.0) / 2.0;
    QTest::newRow("two-doubled-value") << (PointList()
                                           << 12.3
                                           << 4.5)
                                       << (12.3 + 4.5) / 2.0;

    QTest::newRow("two-negative-value") << (PointList()
                                            << -1.0
                                            << 4.0)
                                        << (-1.0 + 4.0) / 2.0;

    QTest::newRow("three-value") << (PointList()
                                     << 4.0
                                     << 19.0
                                     << 51.0)
                                 << (4.0 + 19.0 + 51.0) / 3.0;
    QTest::newRow("three-doubled-value") << (PointList()
                                             << 4.5
                                             << 19.3
                                             << 13.2)
                                         << (4.5 + 19.3 + 13.2) / 3.0;
    QTest::newRow("three-negative-value") << (PointList()
                                              << -4.0
                                              << 1.0
                                              << 5.0)
                                          << (-4.0 + 1.0 + 5.0) / 3.0;

    QTest::newRow("three-with-null-value") << (PointList()
                                               << -4.0
                                               << 0.0
                                               << 5.0)
                                           << (-4.0 + 5.0) / 2.0;

    QTest::newRow("four-with-null-value") << (PointList()
                                              << 5.0
                                              << 0.0
                                              << 10.0
                                              <<0.0)
                                          << (5.0 + 10.0) / 2.0;

    QTest::newRow("five-with-null-value") << (PointList()
                                              << 15.0
                                              << 0.0
                                              << 9.0
                                              << 0.0
                                              << 4.0)
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

void TAnalysis::TestStandardDeviation_data()
{
    QTest::addColumn< PointList >("values");
    QTest::addColumn<double>("result");

    QTest::newRow("empty") << PointList() << 0.0;

    QTest::newRow("one-value") << (PointList() << 23.0) << 0.0;

    QTest::newRow("two-values") << (PointList() << -3.0 << 12.0)
                                << 15.0/qSqrt(2.0); // Значения с сайта калькулятора http://www.wolframalpha.com/

    QTest::newRow("three-values") << (PointList() << 0.0 << 4.0 << 7.0)
                                  << qSqrt(37.0 / 3.0); // Значения с сайта калькулятора http://www.wolframalpha.com/

    QTest::newRow("three-values") << (PointList() << 60.0 << 77.0 << 34.0 << 98.0)
                                  << qSqrt(8795.0 / 3.0) / 2.0; //Значения с сайта калькулятора http://www.wolframalpha.com/

    QTest::newRow("four-values") << (PointList()
                                     << -20.6
                                     << -17.2
                                     << -21.0
                                     << -42.1
                                     << -18.5)
                                 << 10.3028;    //Значения с сайта калькулятора http://www.wolframalpha.com/
}

void TAnalysis::TestStandardDeviation()
{
    QFETCH(PointList, values);
    QFETCH(double, result);

    StandardDeviationAnalysis analysis;

    const double actualResult = analysis.analyze(values);
    const double expectedResult = result;

    FUZZY_COMPARE(actualResult, expectedResult);
}

void TAnalysis::TestMedian_data()
{
    QTest::addColumn< PointList >("values");
    QTest::addColumn<double>("result");

    QTest::newRow("empty") << PointList() << 0.0;

    QTest::newRow("one-value") << (PointList() << Point(26.0)) << 26.0;

    QTest::newRow("four-value-sorted") << (PointList()
                                           << Point(1.0)
                                           << Point(2.0)
                                           << Point(3.0)
                                           << Point(4.0))
                                       << 5.0 / 2.0; //Значения с сайта калькулятора http://www.wolframalpha.com/

    QTest::newRow("four-value-unsorter") << (PointList()
                                             << Point(23.0)
                                             << Point(-5.0)
                                             << Point(0.0)
                                             << Point(31.0))
                                         << 23.0 / 2.0; //Значения с сайта калькулятора http://www.wolframalpha.com/

    QTest::newRow("five-value-sorted") << (PointList()
                                           << Point(1.0)
                                           << Point(2.0)
                                           << Point(3.0)
                                           << Point(4.0)
                                           << Point(5.0))
                                       << 3.0; //Значения с сайта калькулятора http://www.wolframalpha.com/

    QTest::newRow("five-value-unsorted") << (PointList()
                                             << Point(-3.0)
                                             << Point(13.0)
                                             << Point(17.5)
                                             << Point(15.0)
                                             << Point(-4.5))
                                         << 13.0; //Значения с сайта калькулятора http://www.wolframalpha.com/
}

void TAnalysis::TestMedian()
{
    QFETCH(PointList, values);
    QFETCH(double, result);

    MedianAnalysis analysis;

    const double actualResult = analysis.analyze(values);
    const double expectedResult = result;

    FUZZY_COMPARE(actualResult, expectedResult);
}

void TAnalysis::TestFirstAndThirdQuartile_data()
{
    QTest::addColumn< PointList >("values");
    QTest::addColumn<double>("firstQuartileResult");
    QTest::addColumn<double>("thirdQuartileResult");

    QTest::newRow("empty") << PointList() << 0.0 << 0.0;

    QTest::newRow("one-value") << (PointList() << Point(26.0)) << 26.0 << 26.0;

    QTest::newRow("four-value-sorted") << (PointList()
                                           << Point(1.0)
                                           << Point(2.0)
                                           << Point(3.0)
                                           << Point(4.0))
                                       << (1.0 + 2.0) / 2.0
                                       <<  (3.0 + 5.0) / 2.0;

    QTest::newRow("four-value-unsorter") << (PointList()
                                             << Point(23.0)
                                             << Point(-5.0)
                                             << Point(0.0)
                                             << Point(31.0))
                                         << (0.0 + -5.0) / 2.0
                                         <<  (23.0 + 31.0) / 2.0;

    QTest::newRow("five-value-sorted") << (PointList()
                                           << Point(1.0)
                                           << Point(2.0)
                                           << Point(3.0)
                                           << Point(4.0)
                                           << Point(5.0))
                                       << (1.0 + 2.0 + 3.0) / 3.0
                                       <<  (3.0 + 4.0 + 5.0) / 3.0;

    QTest::newRow("five-value-unsorted") << (PointList()
                                             << Point(-3.0)
                                             << Point(13.0)
                                             << Point(17.5)
                                             << Point(15.0)
                                             << Point(-4.5))
                                         << (-3.0 + -4.5 + 13.0) / 3.0
                                         <<  (13.0 + 15.0 + 17.5) / 3.0;
}

void TAnalysis::TestFirstAndThirdQuartile()
{
    QFETCH(PointList, values);
    QFETCH(double, firstQuartileResult);
    QFETCH(double, thirdQuartileResult);

    FirstQuartileAnalysis firstQuartile;
    ThirdQuartileAnalysis thirdQuartile;

    const double actualFirstQuartileResult = firstQuartile.analyze(values);
    const double expectedFirstQuartileResult = firstQuartileResult;

    FUZZY_COMPARE(actualFirstQuartileResult, expectedFirstQuartileResult);

    const double actualThirdQuartileResult = thirdQuartile.analyze(values);
    const double expectedThirdQuartileResult = thirdQuartileResult;

    FUZZY_COMPARE(actualThirdQuartileResult, expectedThirdQuartileResult);
}
