#include "MocPointListReader.h"

MocPointListReader::MocPointListReader(const IDList &items)
{
    foreach(const ID &item, items)
    {
        table_.insert(item, PointList());
    }
}

PointList MocPointListReader::read(const ID &id)
{
    return table_.value(id, PointList());
}

IDList MocPointListReader::readAllItems()
{
    return table_.keys();
}
