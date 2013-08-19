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

PointListStorageStatistics MocPointListReader::statistics()
{
    PointListStorageStatistics storageStatistics;

    storageStatistics << PointListStatistics("First", 1)
                      << PointListStatistics("Second", "2")
                      << PointListStatistics("Third",
                                             QVariant::fromValue(QStringList()
                                                                 << QString("1")
                                                                 << QString("2")
                                                                 << QString("3")));

    return storageStatistics;
}
