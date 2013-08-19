#include "TPointListStorageStatistics.h"

TPointListStorageStatistics::TPointListStorageStatistics()
{
}

void TPointListStorageStatistics::TestAddRemoveStatistic_data()
{
    QTest::addColumn<IDStatisticsList>("statisticNames");
    QTest::addColumn<QVariantList>("statisticValue");

    QTest::newRow("empty") << IDStatisticsList() << QVariantList();

    QTest::newRow("one-string")
            << (IDStatisticsList() << IDStatistics("First"))
            << (QVariantList() << QString("0000000001"));

    QTest::newRow("one-stringlist")
            << (IDStatisticsList() << IDStatistics("First"))
            << (QVariantList() << (QStringList() << QString("1") << QString("2")));
}

void TPointListStorageStatistics::TestAddRemoveStatistic()
{
    QFETCH(IDStatisticsList, statisticNames);
    QFETCH(QVariantList, statisticValue);

    PointListStorageStatistics statistics;

    for(int i = 0; i < statisticNames.size(); i++)
    {
        statistics << PointListStatistics(statisticNames.at(i), statisticValue.at(i));
    }


    const int actualStatisticsSize = statistics.size();
    const int expectedStatisticsSize = statisticNames.size();

    QCOMPARE(actualStatisticsSize, expectedStatisticsSize);

    for(int i = 0; i < statisticNames.size(); i++)
    {
        const bool isContains = statistics.contains(statisticNames.at(i));
        QVERIFY(isContains);

        const QVariant actualStatisticsValue = statistics.value(statisticNames.at(i));
        const QVariant expectedValue = statisticValue.at(i);
        QCOMPARE(actualStatisticsValue, expectedValue);
    }
}
