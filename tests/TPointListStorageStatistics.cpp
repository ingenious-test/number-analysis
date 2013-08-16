#include "TPointListStorageStatistics.h"

TPointListStorageStatistics::TPointListStorageStatistics()
{
}

void TPointListStorageStatistics::TestAddRemoveStatistic_data()
{
    QTest::addColumn<IDStatisticsList>("statisticNames");
    QTest::addColumn<StatisticsValueList>("statisticValue");

    QTest::newRow("empty") << IDStatisticsList() << StatisticsValueList();

    QTest::newRow("one-string")
            << (IDStatisticsList() << IDStatistics("First"))
            << (StatisticsValueList() << QString("0000000001"));

    QTest::newRow("one-stringlist")
            << (IDStatisticsList() << IDStatistics("First"))
            << (StatisticsValueList() << (QStringList() << QString("1") << QString("2")));
}

void TPointListStorageStatistics::TestAddRemoveStatistic()
{
    QFETCH(IDStatisticsList, statisticNames);
    QFETCH(StatisticsValueList, statisticValue);

    PointListStorageStatistics statistics;

    for(int i = 0; i < statisticNames.size(); i++)
    {
        statistics.appendStatistics(statisticNames.at(i), statisticValue.at(i));
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
