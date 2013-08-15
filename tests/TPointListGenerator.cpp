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
                             << 1
                             << 2);

    QTest::newRow("five") << 2
                         << (PointList()
                             << 1
                             << 2
                             << 3
                             << 4
                             << 5);

    QTest::newRow("ten") << 10
                         << (PointList()
                             << 1
                             << 2
                             << 3
                             << 4
                             << 5
                             << 6
                             << 7
                             << 8
                             << 9
                             << 10);
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
