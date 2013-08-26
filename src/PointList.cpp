#include "PointList.h"

PointList::PointList():
    id_(QString())
{
}

PointList::PointList(const ID &id) :
    id_(id)
{
}

QString PointList::toString() const
{
    QStringList pointsRepresentation;
    foreach(const Point &p, list_)
    {
        pointsRepresentation << QString::number(p);
    }
    return pointsRepresentation.join(",");
}

bool PointList::fuzzyCompare(const PointList &actual, const PointList &expected)
{

    const int sizeActual = actual.count();
    const int sizeExpected = expected.count();

    if(sizeActual != sizeExpected)
    {
        return false;
    }

    for(int i = 0; i < actual.count(); i++)
    {
        bool isCompare = fuzzyComparePoints(actual[i],expected[i])
                && (actual.id() == expected.id());

        if(!isCompare)
        {
            return false;
        }
    }

    return true;

}

bool PointList::fuzzyComparePoints(const Point actual, const Point expected)
{
    const double eps = 0.0001;
    const bool result = (qAbs(actual - expected)  <= eps);
    return result;
}


