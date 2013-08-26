#include "SequencePointList.h"

SequencePointList::SequencePointList()
{
}

bool SequencePointList::isValid() const
{
    foreach(const PointList pointList, sequencesPoints())
    {
        const bool isValidList = pointList.isValid();
        if(!isValidList)
        {
            return false;
        }
    }

    return true;
}

QString SequencePointList::toString() const
{
    QString stringRepresentation;

    foreach(const PointList &pl, sequencsePoints_)
    {
        stringRepresentation += pl.id() + "(" + pl.toString() + ")\n";
    }

    return stringRepresentation;
}

bool SequencePointList::fuzzyCompare(const SequencePointList &actual, const SequencePointList &expected)
{
    const int sizeActual = actual.count();
    const int sizeExpected = expected.count();

    if(sizeActual != sizeExpected)
    {
        return false;
    }

    for(int i = 0; i < actual.count(); i++)
    {
        bool isCompare = PointList::fuzzyCompare(actual[i], expected[i]);
        if(!isCompare)
        {
            return false;
        }
    }

    return true;
}

bool SequencePointList::contains(const ID &id)
{
    foreach(const PointList& pointList, sequencesPoints())
    {
        if(pointList.id() == id)
        {
            return true;
        }
    }

    return false;
}

IDList SequencePointList::getPointListIDs()
{
    IDList idList;
    foreach(const PointList& pointList, sequencesPoints())
    {
        idList << pointList.id();
    }
    return idList;
}
