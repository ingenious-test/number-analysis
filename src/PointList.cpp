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

QString PointList::join(const QString c) const
{
    QString result;

    QListIterator<Point> i(*this);

    while(i.hasNext())
    {
        result += QString::number(i.next());
        if(i.hasNext()) result += c;
    }
    return result;
}
