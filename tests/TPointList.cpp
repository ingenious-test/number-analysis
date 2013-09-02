#include "TPointList.h"

TPointList::TPointList()
{

}

void TPointList::TestToList_data()
{
    QTest::addColumn< QList<int> >("indexes");
    QTest::addColumn< QList<Point> >("points");
    QTest::addColumn< QList<Point> >("result");

    QTest::newRow("first") <<  (QList<int>()
                                << 2 << 4 << 5)
                            << (QList<Point>()
                                << Point(3.0)
                                << Point(5.21)
                                << Point(2.0))
                            << (QList<Point>()
                                << Point(0.0)
                                << Point(0.0)
                                << Point(3.0)
                                << Point(3.0)
                                << Point(5.21)
                                << Point(2.0));
}

void TPointList::TestToList()
{
    QFETCH(QList<int>, indexes);
    QFETCH(QList<Point>, points);
    QFETCH(QList<Point>, result);

    if(indexes.count() != points.count())
    {
        QFAIL("incorrect testing data");
    }


    PointList pointList;
    for(int i = 0; i < indexes.count(); i++)
    {
        const int ind = indexes.at(i);
        const Point value = points.at(i);
        pointList.insert(ind, value);
    }

    const QList<Point> actualResult = pointList.points();
    const QList<Point> expectedResult = result;

    QCOMPARE(actualResult, expectedResult);
}
