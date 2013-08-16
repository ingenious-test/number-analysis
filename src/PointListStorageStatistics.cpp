#include "PointListStorageStatistics.h"

PointListStorageStatistics::PointListStorageStatistics()
{
}

void PointListStorageStatistics::appendStatistics(const IDStatistics &id, const StatisticsValue &value)
{
    if(contains(id))
    {
        removeStatistics(id);
    }

    statistics_.insert(id, value);
}

void PointListStorageStatistics::removeStatistics(const IDStatistics &id)
{
    if(contains(id))
    {
        statistics_.remove(id);
    }
}


const int PointListStorageStatistics::size() const
{
    return statistics_.size();
}

bool PointListStorageStatistics::contains(const IDStatistics &id) const
{
    return statistics_.contains(id);
}
