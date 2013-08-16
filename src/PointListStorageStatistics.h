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

    void appendStatistics(const IDStatistics &id, const StatisticsValue &value);
    void removeStatistics(const IDStatistics &id);

    const int size() const;
    bool contains(const IDStatistics &id) const;

private:
    QHash<IDStatistics, StatisticsValue> statistics_;

};

#endif // POINTLISTSTORAGESTATISTICS_H
