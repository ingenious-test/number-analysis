#include "TPointListStorageStatistics.h"

TPointListStorageStatistics::TPointListStorageStatistics()
{
}

void TPointListStorageStatistics::TestAddRemoveStatistic_data()
{
    QTest::addColumn<IDStatisticsList>("statisticNames");
    QTest::addColumn<StatisticsValueList>("statisticValue");

    QTest::newRow("empty") << IDStatisticsList() << StatisticsValueList();
}

void TPointListStorageStatistics::TestAddRemoveStatistic()
{
    QFETCH(IDStatisticsList, statisticNames);
    QFETCH(StatisticsValueList, statisticValue);

    PointListStorageStatistics statistics;

    for(int i = 0; i < statisticNames.size(); i++)
    {
        statistics.appendStatistic(statisticNames.at(i), statisticValue.at(i));
    }


    const int actualStatisticsSize = statistics.size();
    const int expectedStatisticsSize = statisticNames.size();

    QCOMPARE(actualStatisticsSize, expectedStatisticsSize);

    for(int i = 0; i < statisticNames.size(); i++)
    {
        const bool isContains = statistics.contains(statisticNames.at(i));
        QVERIFY(isContains);
    }
}
