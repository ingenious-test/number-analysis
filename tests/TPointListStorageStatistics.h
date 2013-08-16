#ifndef TPOINTLISTSTORAGESTATISTICS_H

#define TPOINTLISTSTORAGESTATISTICS_H

#include <QTest>

#include "../src/PointListStorageStatistics.h"
#include "../src/Metatypes.h"

class TPointListStorageStatistics : public QObject
{
    Q_OBJECT
public:
    TPointListStorageStatistics();

private slots:
    void TestAddRemoveStatistic_data();
    void TestAddRemoveStatistic();
};

#endif // TPOINTLISTSTORAGESTATISTICS_H
