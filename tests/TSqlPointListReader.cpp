#include "TSqlPointListReader.h"

TSqlPointListReader::TSqlPointListReader()
{
}

void TSqlPointListReader::TestWriteRead_data()
{
    QTest::addColumn<SequencePointList>("points");
    QTest::addColumn<SequencePointList>("allPoints");




    QTest::newRow("empty") << SequencePointList()
                           << SequencePointList();

    QTest::newRow("one-item-with-one-point")
            << (SequencePointList() << (PointList("id1") << Point(1.0)))
            << (SequencePointList() << (PointList("id1") << Point(1.0)));

    QTest::newRow("one-item-with-two-point")
            << (SequencePointList() << (PointList("id1") << Point(1.0) << Point(2.0)))
            << (SequencePointList() << (PointList("id1") << Point(1.0) << Point(2.0)));

    QTest::newRow("one-item-with-ten-point")
            << (SequencePointList()
                << (PointList("id1")
                    << Point(1.1)
                    << Point(2.2)
                    << Point(4.4)
                    << Point(8.8)
                    << Point(16.16)
                    << Point(32.32)
                    << Point(64.64)
                    << Point(128.128)
                    << Point(256.256)
                    << Point(512.512)))
            << (SequencePointList()
                << (PointList("id1")
                    << Point(1.1)
                    << Point(2.2)
                    << Point(4.4)
                    << Point(8.8)
                    << Point(16.16)
                    << Point(32.32)
                    << Point(64.64)
                    << Point(128.128)
                    << Point(256.256)
                    << Point(512.512)));

    QTest::newRow("two-item-with-one-point")
            << (SequencePointList()
                << (PointList("id1")
                    << Point(4.9)
                    << Point(6.8)
                    << Point(11.0))
                << (PointList("id2")
                    << Point(14.01)
                    << Point(12.3)
                    << Point(3.3)
                    << Point(8.1)))
            << (SequencePointList()
                << (PointList("id1")
                    << Point(4.9)
                    << Point(6.8)
                    << Point(11.0))
                << (PointList("id2")
                    << Point(14.01)
                    << Point(12.3)
                    << Point(3.3)
                    << Point(8.1)));

    QTest::newRow("three-item-with-one-point")
            << (SequencePointList()
                << (PointList("id1") << Point(41.29) << Point(4.3))
                << (PointList("id2")
                    << Point(1.25)
                    << Point(3.4)
                    << Point(8.34)
                    << Point(15.6)
                    << Point(38.009))
                << (PointList("id3") << Point(2.44) << Point(5.8)))
            << (SequencePointList()
                << (PointList("id1") << Point(41.29) << Point(4.3))
                << (PointList("id2")
                    << Point(1.25)
                    << Point(3.4)
                    << Point(8.34)
                    << Point(15.6)
                    << Point(38.009))
                << (PointList("id3") << Point(2.44) << Point(5.8)));


    QTest::newRow("two-duplicate-items-with-one-point")
            << (SequencePointList()
                << (PointList("id1") << Point(1.0))
                << (PointList("id1") << Point(2.0))
                << (PointList("id2") << Point(2.5)))
            << (SequencePointList()
                << (PointList("id1") << Point(1.0))
                << (PointList("id2") << Point(2.5)));

    QTest::newRow("two-doubled-duplicate-items-with-one-point")
            << (SequencePointList()
                << (PointList("id1") << Point(1.3))
                << (PointList("id1") << Point(6.7))
                << (PointList("id2") << Point(12.1))
                << (PointList("id3") << Point(14.58))
                << (PointList("id2") << Point(3.33)))
            << (SequencePointList()
                << (PointList("id1") << Point(1.3))
                << (PointList("id2") << Point(12.1))
                << (PointList("id3") << Point(14.58)));

    QTest::newRow("two-doubled-duplicate-items-with-one-or-two-points1")
            << (SequencePointList()
                << (PointList("id1") << Point(1.3) << Point(-1.0))
                << (PointList("id1") << Point(6.7)))
            << (SequencePointList()
                << (PointList("id1") << Point(1.3) << Point(-1.0)));

    QTest::newRow("two-doubled-duplicate-items-with-one-or-two-points2")
            << (SequencePointList()
                << (PointList("id1") << Point(1.3))
                << (PointList("id1") << Point(6.7) << Point(-1.0)))
            << (SequencePointList()
                << (PointList("id1") << Point(1.3)));
}

void TSqlPointListReader::TestWriteRead()
{
    QFETCH(SequencePointList, points);
    QFETCH(SequencePointList, allPoints);

    const QString dataBaseName = QString(QTest::currentDataTag()) + "TestWriteRead.db";
    const QString tableName = "Points";

    if(QFile::exists(dataBaseName))
    {
        if(!QFile::remove(dataBaseName))
        {
            QFAIL("can't remove testing database");
        }
    }

    SqlPointListWriter writer(dataBaseName, tableName);
    writer.open();
    for(int i = 0; i < points.count(); i++)
    {
        writer.write(points.at(i));
    }

    QVERIFY(QFile::exists(dataBaseName));

    SqlPointListReader reader(dataBaseName, tableName);
    reader.open();

    const IDList allItems = reader.readAllItems();

    SequencePointList seqFromDataBase;
    foreach (const ID& item, allItems)
    {
        seqFromDataBase.append(reader.read(item));
    }



    const SequencePointList actualPoints = seqFromDataBase;
    const SequencePointList expectedPoints = allPoints;

    bool isCompare = SequencePointList::fuzzyCompare(actualPoints,expectedPoints);
    if(!isCompare)
    {
        QFAIL(QString("Compare values are not the same. \nActual:\n"
                      + actualPoints.toString()
                      + "\nExpected:\n"
                      + expectedPoints.toString()).toStdString().c_str());
    }
}

void TSqlPointListReader::TestStatistics_data()
{;
    QTest::addColumn<SequencePointList>("points");
    QTest::addColumn<AbstractStatictics*>("statistics");
    QTest::addColumn<QVariant>("statisticsValue");

    QTest::newRow("max-sequence-length-id")
            << (SequencePointList()
                << (PointList("First") << Point(1.0) << Point(2.0))
                << (PointList("Second") << Point(1.0) << Point(2.0)  << Point(3.0))
                << (PointList("Third") << Point(1.0)))
            << static_cast<AbstractStatictics*>(new MaxSequenceLengthIdStatistics)
            << QVariant::fromValue(QString("Second"));

    QTest::newRow("max-sequence-length")
            << (SequencePointList()
                << (PointList("First") << Point(1.0) << Point(2.0))
                << (PointList("Second") << Point(1.0) << Point(2.0)  << Point(3.0))
                << (PointList("Third") << Point(1.0)))
            << static_cast<AbstractStatictics*>(new MaxSequenceLengthStatistics)
            << QVariant::fromValue(3);

    QTest::newRow("min-sequence-length-id")
            << (SequencePointList()
                << (PointList("First") << Point(1.0) << Point(2.0))
                << (PointList("Second") << Point(1.0) << Point(2.0)  << Point(3.0))
                << (PointList("Third") << Point(1.0)))
            << static_cast<AbstractStatictics*>(new MinSequenceLengthIdStatistics)
            << QVariant::fromValue(QString("Third"));

    QTest::newRow("min-sequence-length")
            << (SequencePointList()
                << (PointList("First") << Point(1.0) << Point(2.0))
                << (PointList("Second") << Point(1.0) << Point(2.0)  << Point(3.0))
                << (PointList("Third") << Point(1.0)))
            << static_cast<AbstractStatictics*>(new MinSequenceLengthStatistics)
            << QVariant::fromValue(1);

    QTest::newRow("average-sequence-length")
            << (SequencePointList()
                << (PointList("First") << Point(1.0))
                << (PointList("Second" ) << Point(1.0) << Point(2.0)  << Point(3.0))
                << (PointList("Third") << Point(1.0))
                << (PointList("Four") << Point(1.0) << Point(2.0)  << Point(3.0) << Point(4.0)))
            << static_cast<AbstractStatictics*>(new AverageSequenceLengthStatistics)
            << QVariant::fromValue(2.25);

    QTest::newRow("five-top-sequence-length")
            << (SequencePointList()
                << (PointList("First") << Point(1.0))
                << (PointList("Second") << Point(1.0) << Point(2.0)  << Point(3.0))
                << (PointList("Third") << Point(1.0) << Point(2.0))
                << (PointList("Four") << Point(1.0) << Point(2.0)  << Point(3.0) << Point(4.0))
                << (PointList("Five") << Point(1.0) << Point(2.0)  << Point(3.0) << Point(4.0))
                << (PointList("Six") << Point(1.0) << Point(2.0)  << Point(3.0) << Point(4.0)))
            << static_cast<AbstractStatictics*>(new FiveTopSequenceLengthStatistics)
            << QVariant::fromValue(QStringList() << "Five" << "Four" << "Six" << "Second" << "Third");

    QTest::newRow("average-null-count-points")
            << (SequencePointList()
                << (PointList("First") << Point(0.0) << Point(0.0) << Point(1.0) << Point(0.0))
                << (PointList("Second") << Point(1.0) << Point(0.0)  << Point(1.0) << Point(1.0) << Point(0.0))
                << (PointList("Third") << Point(1.0) << Point(1.0) << Point(1.0) << Point(1.0) << Point(1.0) << Point(1.0)))
            << static_cast<AbstractStatictics*>(new AverageNullCountPointsStatistics)
            << QVariant::fromValue(5.0 / 3.0);

    QTest::newRow("average-none-null-count-points")
            << (SequencePointList()
                << (PointList("First") << Point(0.0) << Point(0.0) << Point(1.0) << Point(0.0))
                << (PointList("Second") << Point(1.0) << Point(0.0)  << Point(1.0) << Point(1.0) << Point(0.0))
                << (PointList("Third") << Point(1.0) << Point(1.0) << Point(1.0) << Point(1.0) << Point(1.0) << Point(1.0)))
            << static_cast<AbstractStatictics*>(new AverageNoneNullCountPointsStatistics)
            << QVariant::fromValue(10.0 / 3.0);


    QTest::newRow("percent-null-count-points")
            << (SequencePointList()
                << (PointList("First") << Point(0.0) << Point(0.0) << Point(1.0) << Point(0.0))
                << (PointList("Second") << Point(1.0) << Point(0.0)  << Point(1.0) << Point(1.0) << Point(0.0))
                << (PointList("Third") << Point(1.0) << Point(1.0) << Point(1.0) << Point(1.0) << Point(1.0) << Point(1.0)))
            << static_cast<AbstractStatictics*>(new PercentNullCountPointsStatistics)
            << QVariant::fromValue((5.0 / 15.0) * 100.0);

    QTest::newRow("percent-none-null-count-points")
            << (SequencePointList()
                << (PointList("First") << Point(0.0) << Point(0.0) << Point(1.0) << Point(0.0))
                << (PointList("Second") << Point(1.0) << Point(0.0)  << Point(1.0) << Point(1.0) << Point(0.0))
                << (PointList("Third") << Point(1.0) << Point(1.0) << Point(1.0) << Point(1.0) << Point(1.0) << Point(1.0)))
            << static_cast<AbstractStatictics*>(new PercentNoneNullCountPointsStatistics)
            << QVariant::fromValue((10.0 / 15.0) * 100.0);

    QTest::newRow("max-point")
            << (SequencePointList()
                << (PointList("First") << Point(3.5) << Point(6.1) << Point(8.9) << Point(3.6))
                << (PointList("Second") << Point(10.9) << Point(11.6)  << Point(2.3) << Point(1.1) << Point(1.8))
                << (PointList("Third") << Point(13.3) << Point(12.0) << Point(10.0) << Point(1.0) << Point(2.0) << Point(3.0)))
            << static_cast<AbstractStatictics*>(new MaxPointStatistics)
            << QVariant::fromValue(13.3);

    QTest::newRow("min-point")
            << (SequencePointList()
                << (PointList("First") << Point(3.5) << Point(6.1) << Point(8.9) << Point(3.6))
                << (PointList("Second") << Point(10.9) << Point(11.6)  << Point(2.3) << Point(1.1) << Point(1.8))
                << (PointList("Third") << Point(13.3) << Point(12.0) << Point(10.0) << Point(1.0) << Point(2.0) << Point(3.0)))
            << static_cast<AbstractStatictics*>(new MinPointStatistics)
            << QVariant::fromValue(1.0);

    QTest::newRow("five-top-points-value")
            << (SequencePointList()
                << (PointList("First") << Point(3.5) << Point(3.5) << Point(3.5) << Point(3.6)  << Point(3.6) << Point(0.2))
                << (PointList("Second") << Point(1.9) << Point(1.9)  << Point(2.3) << Point(1.1) << Point(1.1) << Point(3.1))
                << (PointList("Third") << Point(1.9) << Point(2.3) << Point(1.9) << Point(3.5) << Point(2.3) << Point(3.5)  << Point(1.8)))
            << static_cast<AbstractStatictics*>(new FiveTopPointsValueStatistics)
            << QVariant::fromValue(QStringList() << "3.5" << "1.9" << "2.3" << "1.1" << "3.6");

    QTest::newRow("sequence-with-repeat-count")
            << (SequencePointList()
                << (PointList("First" ) << Point(1.0) << Point(2.0) << Point(3.0) << Point(4.0)  << Point(5.0) << Point(6.0))
                << (PointList("Second") << Point(1.0) << Point(1.0)  << Point(2.0) << Point(3.0) << Point(3.0) << Point(3.0))
                << (PointList("Third") << Point(1.0) << Point(2.0) << Point(2.0) << Point(3.0) << Point(4.0) << Point(5.0)))
            << static_cast<AbstractStatictics*>(new SequenceWithRepeatCountStatistics)
            << QVariant::fromValue(2);

    QTest::newRow("inc-sequences-count")
            << (SequencePointList()
                << (PointList("First" ) << Point(1.0) << Point(2.0) << Point(3.0) << Point(4.0)  << Point(5.0) << Point(6.0))
                << (PointList("Second") << Point(1.0) << Point(1.0)  << Point(2.0) << Point(3.0) << Point(3.0) << Point(3.0))
                << (PointList("Third") << Point(1.0) << Point(2.0) << Point(5.0) << Point(7.0) << Point(10.0) << Point(15.0)))
            << static_cast<AbstractStatictics*>(new IncSequenceCountStatistics)
            << QVariant::fromValue(2);

    QTest::newRow("dec-sequences-count")
            << (SequencePointList()
                << (PointList("First") << Point(1.0) << Point(2.0) << Point(3.0) << Point(4.0)  << Point(5.0) << Point(6.0))
                << (PointList("Second") << Point(10.0) << Point(7.0)  << Point(5.0) << Point(3.0) << Point(2.0) << Point(1.0))
                << (PointList("Third") << Point(4.0) << Point(3.0) << Point(2.0) << Point(1.0) << Point(0.0) << Point(-1.0))
                << (PointList("Four") << Point(1.0) << Point(1.0)  << Point(2.0) << Point(3.0) << Point(3.0) << Point(3.0)))
            << static_cast<AbstractStatictics*>(new DecSequenceCountStatistics)
            << QVariant::fromValue(2);
}

void TSqlPointListReader::TestStatistics()
{
    QFETCH(SequencePointList, points);
    QFETCH(AbstractStatictics*, statistics);
    QFETCH(QVariant, statisticsValue);

    const QString dataBaseName = QString(QTest::currentDataTag()) + "TestWriteRead.db";
    const QString tableName = "Points";

    if(QFile::exists(dataBaseName))
    {
        if(!QFile::remove(dataBaseName))
        {
            QFAIL("can't remove testing database");
        }
    }

    SqlPointListWriter writer(dataBaseName, tableName);
    writer.open();
    for(int i = 0; i < points.count(); i++)
    {
        writer.write(points.at(i));
    }

    SqlPointListReader reader(dataBaseName, tableName);
    reader.appendStatistics(statistics);
    reader.open();

    PointListStorageStatistics storageStatistics = reader.statistics();

    statistics->open(dataBaseName, tableName);


    const QVariant actualStatisticValue = statistics->exec();
    const QVariant expectedStatisticValue = statisticsValue;

    QCOMPARE(actualStatisticValue, expectedStatisticValue);

    const QVariant actualStatisticReaderValue = storageStatistics.value(statistics->name());
    const QVariant expectedStatisticReaderValue = statisticsValue;

    QCOMPARE(actualStatisticReaderValue, expectedStatisticReaderValue);
}
