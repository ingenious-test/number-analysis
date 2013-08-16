#ifndef POINTLISTSTORAGESTATISTICS_H

#define POINTLISTSTORAGESTATISTICS_H

#include <QtCore>

typedef QString IDStatistics;
typedef QList<IDStatistics> IDStatisticsList;


typedef QVariant StatisticsValue;
typedef QVariantList StatisticsValueList;

class PointListStorageStatistics
{
public:
    PointListStorageStatistics();

    void appendStatistic(const IDStatistics &id, const StatisticsValue &value);
    const int size() const;
    bool contains(const IDStatistics &id) const;


};

#endif // POINTLISTSTORAGESTATISTICS_H
