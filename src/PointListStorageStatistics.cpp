#include "PointListStorageStatistics.h"

PointListStorageStatistics::PointListStorageStatistics()
{
}

void PointListStorageStatistics::appendStatistics(const PointListStatistics &statistics)
{
    if(contains(statistics.id()))
    {
        removeStatistics(statistics.id());
    }

    statistics_.insert(statistics.id(), statistics.value());
}

void PointListStorageStatistics::removeStatistics(const IDStatistics &id)
{
    if(contains(id))
    {
        statistics_.remove(id);
    }
}

const QVariant PointListStorageStatistics::value(const IDStatistics &id)
{
    return statistics_.value(id);
}

const QStringList PointListStorageStatistics::toString()
{
    QStringList result;
    QHashIterator<IDStatistics, QVariant> value(statistics_);
    while (value.hasNext()) {
        value.next();
        QString text;

        const QString typeName = QString(value.value().typeName());

        if(typeName == "QStringList")
        {
            text = value.key() + " - " + qvariant_cast<QStringList>(value.value()).join(",");
        }
        else
        {
            text = value.key() + " - " + value.value().toString();
        }



        result << text;
    }

    return result;
}


const int PointListStorageStatistics::size() const
{
    return statistics_.size();
}

bool PointListStorageStatistics::contains(const IDStatistics &id) const
{
    return statistics_.contains(id);
}
