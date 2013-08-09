#include "PointList.h"

PointList::PointList(ID id) :
    QList<Point>()
{
    id_ = id;
}

PointList::PointList(ID id, const PointList &pointList)
{
    setID(id);
    foreach(Point point, pointList)
    {
        append(point);
    }
}

PointList &PointList::appendInc(const Point &t)
{
    append(t);
    return *this;
}

void PointList::setID(const ID &id)
{
    id_ = id;
}

const ID &PointList::id() const
{
    return id_;
}

bool PointList::isSetID() const
{
    return !id_.isEmpty();
}
