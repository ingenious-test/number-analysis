#include "TPointListGenerator.h"

TPointListGenerator::TPointListGenerator(QObject *parent):
    QObject(parent)
{

}

void TPointListGenerator::TestGenerator_data()
{
    QTest::addColumn<int>("lenght");
    QTest::addColumn<PointList>("resultPoints");

    QTest::newRow("empty") << 0 << PointList();

    QTest::newRow("two") << 2
                         << (PointList()
                             << Point(1.0)
                             << Point(2.0));

    QTest::newRow("five") << 5
                          << (PointList()
                              << Point(1.0)
                              << Point(2.0)
                              << Point(3.0)
                              << Point(4.0)
                              << Point(5.0));

    QTest::newRow("ten") << 10
                         << (PointList()
                             << Point(1.0)
                             << Point(2.0)
                             << Point(3.0)
                             << Point(4.0)
                             << Point(5.0)
                             << Point(6.0)
                             << Point(7.0)
                             << Point(8.0)
                             << Point(9.0)
                             << Point(10));

}

void TPointListGenerator::TestGenerator()
{
    QFETCH(int, lenght);
    QFETCH(PointList, resultPoints);

    PointListGenerator pointListGenerator;

    const PointList actualPoints = pointListGenerator.generateConst(lenght);
    const PointList expectedPoints = resultPoints;

    bool isCompare = pointListFuzzyCompare(actualPoints,expectedPoints);
    if(!isCompare)
    {
        QFAIL(QString("Compare values are not the same. \nActual:\n"
                      + pointListToString(actualPoints)
                      + "\nExpected:\n"
                      + pointListToString(expectedPoints)).toStdString().c_str());
    }
}

void TPointListGenerator::TestValueGenerator_data()
{
    QTest::addColumn<int>("lenght");
    QTest::addColumn<int>("value");
    QTest::addColumn<PointList>("resultPoints");

    QTest::newRow("empty") << 0 << 0 << PointList();

    QTest::newRow("two-null") << 2
                              << 0
                              << (PointList()
                                  << Point(0.0)
                                  << Point(0.0));

    QTest::newRow("five-three") << 5
                                << 3
                                << (PointList()
                                    << Point(3.0)
                                    << Point(3.0)
                                    << Point(3.0)
                                    << Point(3.0)
                                    << Point(3.0));

    QTest::newRow("ten-six") << 10
                             << 6
                             << (PointList()
                                 << Point(6.0)
                                 << Point(6.0)
                                 << Point(6.0)
                                 << Point(6.0)
                                 << Point(6.0)
                                 << Point(6.0)
                                 << Point(6.0)
                                 << Point(6.0)
                                 << Point(6.0)
                                 << Point(6.0));
}

void TPointListGenerator::TestValueGenerator()
{
    QFETCH(int, lenght);
    QFETCH(int, value);
    QFETCH(PointList, resultPoints);

    PointListGenerator pointListGenerator;

    const PointList actualPoints = pointListGenerator.generateConst(lenght, value);
    const PointList expectedPoints = resultPoints;

    bool isCompare = pointListFuzzyCompare(actualPoints,expectedPoints);
    if(!isCompare)
    {
        QFAIL(QString("Compare values are not the same. \nActual:\n"
                      + pointListToString(actualPoints)
                      + "\nExpected:\n"
                      + pointListToString(expectedPoints)).toStdString().c_str());
    }
}
