#include "PointList.h"

PointList::PointList():
    id_(QString())
{
}

PointList::PointList(const ID &id) :
    id_(id)
{
}

QList<Point> PointList::points() const
{
    QList<Point> result;
    QHashIterator<int, Point>  iterator(points_);
    while (iterator.hasNext())
    {
        iterator.next();

        const int delta = (result.count() > 0 ? result.count() - 1 : 0) - iterator.key();

        if(delta > 0)
        {
            const Point lastPoint = result.last();
            for(int i = 0; i < delta; i++)
            {
                result.append(lastPoint);
            }
        }

        result.append(iterator.value());
    }
    return result;
}

const Point &PointList::at(const int i) const
{
    if(points_.contains(i))
    {
        return points_.value(i);
    }
    else
    {
        qWarning() << "Point at" << i << "not contains";
    }
    return Point(0.0);
}

void PointList::append(const Point &point)
{
    const int lastInd = points_.count();
    setPointAt(lastInd, point);
}

void PointList::setPointAt(const int ind, const Point &point)
{
    if(ind < 0)
    {
        qWarning() << "Index must be more than or equal zero";
        return;
    }

    if(points_.contains(ind))
    {
        points_.remove(ind);
    }

    points_.insert(ind, point);
}

QString PointList::toString() const
{
    QStringList pointsRepresentation;
    foreach(const Point &p, points_)
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


