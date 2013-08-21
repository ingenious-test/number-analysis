#ifndef BSTATISTICSCOLLECTION_H

#define BSTATISTICSCOLLECTION_H

#include "../src/StatisticsCollection.h"
#include "../src/SqlPointListWriter.h"


class BStatisticsCollection
{
public:
    BStatisticsCollection();
    ~BStatisticsCollection();
    void generateDatabase(const int seqCount, const int pointsCount);
    void statistics();

private:
    const QString dataBaseName_;
    const QString tableName_;
};

#endif // BSTATISTICSCOLLECTION_H
