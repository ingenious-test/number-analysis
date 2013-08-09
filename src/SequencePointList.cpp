#include "SequencePointList.h"

SequencePointList::SequencePointList():
    QList<PointList>()
{
}

SequencePointList &SequencePointList::appendInc(ID id, PointList &pointList)
{
    pointList.setID(id);
    append(pointList);
    return *this;
}

void SequencePointList::append(ID id, const PointList &pointList)
{
    append(PointList(id,pointList));
}

void SequencePointList::append(const PointList &pointList)
{
    if(pointList.isSetID())
    {
        int index = containsID(pointList.id());
        if(index > -1)
        {
            removeAt(index);
            qWarning() << "PointList with id '" + pointList.id() + "' removed";
        }
        QList<PointList>::append(pointList);
    }
}

int SequencePointList::containsID(const ID& id)
{
    for(int i = 0; i < size(); i++)
    {
        if(at(i).id() == id)
        {
            return i;
        }
    }

    return -1;
}
