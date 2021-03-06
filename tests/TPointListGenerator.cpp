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

    const PointList actualPoints = pointListGenerator.generateByLenghtConst(lenght);
    const PointList expectedPoints = resultPoints;

    bool isCompare = PointList::fuzzyCompare(actualPoints,expectedPoints);
    if(!isCompare)
    {
        QFAIL(QString("Compare values are not the same. \nActual:\n"
                      + actualPoints.id() + " - "
                      + actualPoints.toString()
                      + "\nExpected:\n"
                      + expectedPoints.id() + " - "
                      + expectedPoints.toString()).toStdString().c_str());
    }
}

void TPointListGenerator::TestValueGenerator_data()
{
    QTest::addColumn<int>("lenght");
    QTest::addColumn<Point>("value");
    QTest::addColumn<PointList>("resultPoints");

    QTest::newRow("empty") << 0 << Point(0.0) << PointList();

    QTest::newRow("two-null") << 2
                              << Point(0.0)
                              << (PointList()
                                  << Point(0.0)
                                  << Point(0.0));

    QTest::newRow("five-three") << 5
                                << Point(3.0)
                                << (PointList()
                                    << Point(3.0)
                                    << Point(3.0)
                                    << Point(3.0)
                                    << Point(3.0)
                                    << Point(3.0));

    QTest::newRow("ten-six") << 10
                             << Point(6.0)
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
    QFETCH(Point, value);
    QFETCH(PointList, resultPoints);

    PointListGenerator pointListGenerator;

    const PointList actualPoints = pointListGenerator.generateByLenghtValue(lenght, value);
    const PointList expectedPoints = resultPoints;

    bool isCompare = PointList::fuzzyCompare(actualPoints,expectedPoints);
    if(!isCompare)
    {
        QFAIL(QString("Compare values are not the same. \nActual:\n"
                      + actualPoints.id() + " - "
                      + actualPoints.toString()
                      + "\nExpected:\n"
                      + expectedPoints.id() + " - "
                      + expectedPoints.toString()).toStdString().c_str());
    }
}

void TPointListGenerator::TestStartEndGenerator_data()
{
    QTest::addColumn<int>("start");
    QTest::addColumn<int>("end");
    QTest::addColumn<PointList>("resultPoints");

    QTest::newRow("empty") << 0 << 0 << (PointList() << 0);

    QTest::newRow("19-21") << 19 << 21 << (PointList()
                                           << 19
                                           << 20
                                           << 21);

    QTest::newRow("10-25") << 10 << 15 << (PointList()
                                           << 10
                                           << 11
                                           << 12
                                           << 13
                                           << 14
                                           << 15);
    QTest::newRow("44-10") << 44 << 10 << PointList();

}

void TPointListGenerator::TestStartEndGenerator()
{
    QFETCH(int, start);
    QFETCH(int, end);
    QFETCH(PointList, resultPoints);

    PointListGenerator pointListGenerator;

    const PointList actualPoints = pointListGenerator.generateStartEnd(start, end);
    const PointList expectedPoints = resultPoints;

    bool isCompare = PointList::fuzzyCompare(actualPoints,expectedPoints);
    if(!isCompare)
    {
        QFAIL(QString("Compare values are not the same. \nActual:\n"
                      + actualPoints.id() + " - "
                      + actualPoints.toString()
                      + "\nExpected:\n"
                      + expectedPoints.id() + " - "
                      + expectedPoints.toString()).toStdString().c_str());
    }
}
