#include "MocPointListReader.h"

MocPointListReader::MocPointListReader(const IDList &items)
{
    foreach(const ID &item, items)
    {
        table_.insert(item, PointList());
    }
}

PointList MocPointListReader::read(const ID &item)
{
    return table_.value(item, PointList());
}

IDList MocPointListReader::readAllItems()
{
    return table_.keys();
}
