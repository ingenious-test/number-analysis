#include "TSqlPointListReader.h"

TSqlPointListReader::TSqlPointListReader()
{
}

void TSqlPointListReader::TestWriteRead_data()
{
    QTest::addColumn<IDList>("items");
    QTest::addColumn<SequencePointList>("points");
    QTest::addColumn<IDList>("allItems");
    QTest::addColumn<SequencePointList>("allPoints");




    QTest::newRow("empty") << IDList()
                           << SequencePointList()
                           << IDList()
                           << SequencePointList();

    QTest::newRow("one-item-with-one-point")
            << (IDList() << ID("id1"))
            << (SequencePointList() << (PointList() << Point(1.0)))
            << (IDList() << ID("id1"))
            << (SequencePointList() << (PointList() << Point(1.0)));

    QTest::newRow("one-item-with-two-point")
            << (IDList()<< ID("id1"))
            << (SequencePointList() << (PointList() << Point(1.0) << Point(2.0)))
            << (IDList() << ID("id1"))
            << (SequencePointList() << (PointList() << Point(1.0) << Point(2.0)));

    QTest::newRow("one-item-with-ten-point")
            << (IDList() << ID("id1"))
            << (SequencePointList()
                << (PointList()
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
            << (IDList() << ID("id1"))
            << (SequencePointList()
                << (PointList()
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
            << (IDList() << ID("id1") << ID("id2"))
            << (SequencePointList()
                << (PointList()
                    << Point(4.9)
                    << Point(6.8)
                    << Point(11.0))
                << (PointList()
                    << Point(14.01)
                    << Point(12.3)
                    << Point(3.3)
                    << Point(8.1)))
            << (IDList() << ID("id1") << ID("id2"))
            << (SequencePointList()
                << (PointList()
                    << Point(4.9)
                    << Point(6.8)
                    << Point(11.0))
                << (PointList()
                    << Point(14.01)
                    << Point(12.3)
                    << Point(3.3)
                    << Point(8.1)));

    QTest::newRow("three-item-with-one-point")
            << (IDList() << ID("id1") << ID("id2") << ID("id3"))
            << (SequencePointList()
                << (PointList() << Point(41.29) << Point(4.3))
                << (PointList()
                    << Point(1.25)
                    << Point(3.4)
                    << Point(8.34)
                    << Point(15.6)
                    << Point(38.009))
                << (PointList() << Point(2.44) << Point(5.8)))
            << (IDList() << ID("id1") << ID("id2") << ID("id3"))
            << (SequencePointList()
                << (PointList() << Point(41.29) << Point(4.3))
                << (PointList()
                    << Point(1.25)
                    << Point(3.4)
                    << Point(8.34)
                    << Point(15.6)
                    << Point(38.009))
                << (PointList() << Point(2.44) << Point(5.8)));


    QTest::newRow("two-duplicate-items-with-one-point")
            << (IDList() << ID("id1") << ID("id1") << ID("id2"))
            << (SequencePointList()
                << (PointList() << Point(1.0))
                << (PointList() << Point(2.0))
                << (PointList() << Point(2.5)))
            << (IDList() << ID("id1") << ID("id2"))
            << (SequencePointList()
                << (PointList() << Point(1.0))
                << (PointList() << Point(2.5)));

    QTest::newRow("two-doubled-duplicate-items-with-one-point")
            << (IDList()
                << ID("id1")
                << ID("id1")
                << ID("id2")
                << ID("id3")
                << ID("id2"))
            << (SequencePointList()
                << (PointList() << Point(1.3))
                << (PointList() << Point(6.7))
                << (PointList() << Point(12.1))
                << (PointList() << Point(14.58))
                << (PointList() << Point(3.33)))
            << (IDList() << ID("id1") << ID("id2") << ID("id3"))
            << (SequencePointList()
                << (PointList() << Point(1.3))
                << (PointList() << Point(12.1))
                << (PointList() << Point(14.58)));

    QTest::newRow("two-doubled-duplicate-items-with-one-or-two-points1")
            << (IDList() << ID("id1") << ID("id1"))
            << (SequencePointList()
                << (PointList() << Point(1.3) << Point(-1.0))
                << (PointList() << Point(6.7)))
            << (IDList() << ID("id1"))
            << (SequencePointList()
                << (PointList() << Point(1.3) << Point(-1.0)));

    QTest::newRow("two-doubled-duplicate-items-with-one-or-two-points2")
            << (IDList() << ID("id1") << ID("id1"))
            << (SequencePointList()
                << (PointList() << Point(1.3))
                << (PointList() << Point(6.7) << Point(-1.0)))
            << (IDList() << ID("id1"))
            << (SequencePointList()
                << (PointList() << Point(1.3)));
}

void TSqlPointListReader::TestWriteRead()
{
    QFETCH(IDList, items);
    QFETCH(SequencePointList, points);
    QFETCH(IDList, allItems);
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

    SqlPointListWriter* writer  = new SqlPointListWriter(dataBaseName, tableName);
    for(int i = 0; i < items.size(); i++)
    {
        writer->write(items.at(i), points.at(i));
    }
    delete writer;

    QVERIFY(QFile::exists(dataBaseName));

    SqlPointListReader* reader = new SqlPointListReader(dataBaseName, tableName);

    const IDList actualAllItems = reader->readAllItems();
    const IDList expectedAllItems = allItems;

    SequencePointList seqFromDataBase;
    foreach (const ID& item, actualAllItems)
    {
        seqFromDataBase.append(reader->read(item));
    }

    delete reader;

    QCOMPARE(actualAllItems, expectedAllItems);

    const SequencePointList actualPoints = seqFromDataBase;
    const SequencePointList expectedPoints = allPoints;

    bool isCompare = seqPointListFuzzyCompare(actualPoints,expectedPoints);
    if(!isCompare)
    {
        QFAIL(QString("Compare values are not the same. \nActual:\n"
                      + sequencePointListToString(actualPoints)
                      + "\nExpected:\n"
                      + sequencePointListToString(expectedPoints)).toStdString().c_str());
    }
}

void TSqlPointListReader::TestStatistics_data()
{
    QTest::addColumn<IDList>("items");
    QTest::addColumn<SequencePointList>("points");
    QTest::addColumn<IDStatistics>("statisticsID");
    QTest::addColumn<QVariant>("statisticsValue");

    QTest::newRow("max-sequence-length-id")
            << (IDList() << "First" << "Second" << "Third")
            << (SequencePointList()
                << (PointList() << Point(1.0) << Point(2.0))
                << (PointList() << Point(1.0) << Point(2.0)  << Point(3.0))
                << (PointList() << Point(1.0)))
            << "max-sequence-length-id"
            << QVariant::fromValue(QString("Second"));

    QTest::newRow("max-sequence-length")
            << (IDList() << "First" << "Second" << "Third")
            << (SequencePointList()
                << (PointList() << Point(1.0) << Point(2.0))
                << (PointList() << Point(1.0) << Point(2.0)  << Point(3.0))
                << (PointList() << Point(1.0)))
            << "max-sequence-length"
            << QVariant::fromValue(3);

    QTest::newRow("min-sequence-length-id")
            << (IDList() << "First" << "Second" << "Third")
            << (SequencePointList()
                << (PointList() << Point(1.0) << Point(2.0))
                << (PointList() << Point(1.0) << Point(2.0)  << Point(3.0))
                << (PointList() << Point(1.0)))
            << "min-sequence-length-id"
            << QVariant::fromValue(QString("Third"));

    QTest::newRow("min-sequence-length")
            << (IDList() << "First" << "Second" << "Third")
            << (SequencePointList()
                << (PointList() << Point(1.0) << Point(2.0))
                << (PointList() << Point(1.0) << Point(2.0)  << Point(3.0))
                << (PointList() << Point(1.0)))
            << "min-sequence-length"
            << QVariant::fromValue(1);

    QTest::newRow("average-sequence-length")
            << (IDList() << "First" << "Second" << "Third" << "Four")
            << (SequencePointList()
                << (PointList() << Point(1.0))
                << (PointList() << Point(1.0) << Point(2.0)  << Point(3.0))
                << (PointList() << Point(1.0))
                << (PointList() << Point(1.0) << Point(2.0)  << Point(3.0) << Point(4.0)))
            << "average-sequence-length"
            << QVariant::fromValue(2.25);

    QTest::newRow("five-top-sequence-length")
            << (IDList() << "First" << "Second" << "Third" << "Four" << "Five" << "Six")
            << (SequencePointList()
                << (PointList() << Point(1.0))
                << (PointList() << Point(1.0) << Point(2.0)  << Point(3.0))
                << (PointList() << Point(1.0) << Point(2.0))
                << (PointList() << Point(1.0) << Point(2.0)  << Point(3.0) << Point(4.0))
                << (PointList() << Point(1.0) << Point(2.0)  << Point(3.0) << Point(4.0))
                << (PointList() << Point(1.0) << Point(2.0)  << Point(3.0) << Point(4.0)))
            << "five-top-sequence-length"
            << QVariant::fromValue(QStringList() << "Five" << "Four" << "Six" << "Second" << "Third");

    QTest::newRow("average-null-count-points")
            << (IDList() << "First" << "Second" << "Third")
            << (SequencePointList()
                << (PointList() << Point(0.0) << Point(0.0) << Point(1.0) << Point(0.0))
                << (PointList() << Point(1.0) << Point(0.0)  << Point(1.0) << Point(1.0) << Point(0.0))
                << (PointList() << Point(1.0) << Point(1.0) << Point(1.0) << Point(1.0) << Point(1.0) << Point(1.0)))
            << "average-null-count-points"
            << QVariant::fromValue(5.0 / 3.0);

    QTest::newRow("average-none-null-count-points")
            << (IDList() << "First" << "Second" << "Third")
            << (SequencePointList()
                << (PointList() << Point(0.0) << Point(0.0) << Point(1.0) << Point(0.0))
                << (PointList() << Point(1.0) << Point(0.0)  << Point(1.0) << Point(1.0) << Point(0.0))
                << (PointList() << Point(1.0) << Point(1.0) << Point(1.0) << Point(1.0) << Point(1.0) << Point(1.0)))
            << "average-none-null-count-points"
            << QVariant::fromValue(10.0 / 3.0);


    QTest::newRow("percent-null-count-points")
            << (IDList() << "First" << "Second" << "Third")
            << (SequencePointList()
                << (PointList() << Point(0.0) << Point(0.0) << Point(1.0) << Point(0.0))
                << (PointList() << Point(1.0) << Point(0.0)  << Point(1.0) << Point(1.0) << Point(0.0))
                << (PointList() << Point(1.0) << Point(1.0) << Point(1.0) << Point(1.0) << Point(1.0) << Point(1.0)))
            << "percent-null-count-points"
            << QVariant::fromValue((5.0 / 15.0) * 100.0);

    QTest::newRow("percent-none-null-count-points")
            << (IDList() << "First" << "Second" << "Third")
            << (SequencePointList()
                << (PointList() << Point(0.0) << Point(0.0) << Point(1.0) << Point(0.0))
                << (PointList() << Point(1.0) << Point(0.0)  << Point(1.0) << Point(1.0) << Point(0.0))
                << (PointList() << Point(1.0) << Point(1.0) << Point(1.0) << Point(1.0) << Point(1.0) << Point(1.0)))
            << "percent-none-null-count-points"
            << QVariant::fromValue((10.0 / 15.0) * 100.0);

    QTest::newRow("max-point")
            << (IDList() << "First" << "Second" << "Third")
            << (SequencePointList()
                << (PointList() << Point(3.5) << Point(6.1) << Point(8.9) << Point(3.6))
                << (PointList() << Point(10.9) << Point(11.6)  << Point(2.3) << Point(1.1) << Point(1.8))
                << (PointList() << Point(13.3) << Point(12.0) << Point(10.0) << Point(1.0) << Point(2.0) << Point(3.0)))
            << "max-point"
            << QVariant::fromValue(13.3);

    QTest::newRow("min-point")
            << (IDList() << "First" << "Second" << "Third")
            << (SequencePointList()
                << (PointList() << Point(3.5) << Point(6.1) << Point(8.9) << Point(3.6))
                << (PointList() << Point(10.9) << Point(11.6)  << Point(2.3) << Point(1.1) << Point(1.8))
                << (PointList() << Point(13.3) << Point(12.0) << Point(10.0) << Point(1.0) << Point(2.0) << Point(3.0)))
            << "min-point"
            << QVariant::fromValue(1.0);

    QTest::newRow("five-top-points-value")
            << (IDList() << "First" << "Second" << "Third")
            << (SequencePointList()
                << (PointList() << Point(3.5) << Point(3.5) << Point(3.5) << Point(3.6)  << Point(3.6) << Point(0.2))
                << (PointList() << Point(1.9) << Point(1.9)  << Point(2.3) << Point(1.1) << Point(1.1) << Point(3.1))
                << (PointList() << Point(1.9) << Point(2.3) << Point(1.9) << Point(3.5) << Point(2.3) << Point(3.5)  << Point(1.8)))
            << "five-top-points-value"
            << QVariant::fromValue(QStringList() << "3.5" << "1.9" << "2.3" << "1.1" << "3.6");
}

void TSqlPointListReader::TestStatistics()
{
    QFETCH(IDList, items);
    QFETCH(SequencePointList, points);
    QFETCH(IDStatistics, statisticsID);
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
    for(int i = 0; i < items.size(); i++)
    {
        writer.write(items.at(i), points.at(i));
    }

    SqlPointListReader reader(dataBaseName, tableName);
    PointListStorageStatistics storageStatistics = reader.statistics();

    const QVariant actualStatisticValue = storageStatistics.value(statisticsID);
    const QVariant expectedStatisticValue = statisticsValue;

    QCOMPARE(actualStatisticValue, expectedStatisticValue);
}
