#include "MocPointListReader.h"

MocPointListReader::MocPointListReader()
{
    table_.insert(ID("id1"), PointList() << Point(1.0) << Point(2.0));
    table_.insert(ID("id2"), PointList() << Point(42.0) << Point(128.0));
    table_.insert(ID("id3"), PointList() << Point(13.0) << Point(33.0));
}

PointList MocPointListReader::read(const ID &id)
{
    return table_.value(id, PointList());
}

IDList MocPointListReader::readAllItems()
{
    return table_.keys();
}
