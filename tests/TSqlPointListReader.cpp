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

    SqlPointListWriter writer(dataBaseName, tableName);
    {
        int index = 0;
        foreach(const ID& item, items)
        {
            writer.write(item, points[index]);
            index++;
        }
    }

    QVERIFY(QFile::exists(dataBaseName));

    SqlPointListReader reader(dataBaseName, tableName);

    const IDList actualAllItems = reader.readAllItems();
    const IDList expectedAllItems = allItems;

    QCOMPARE(actualAllItems, expectedAllItems);

    SequencePointList seqFromDataBase;
    foreach (const ID& item, actualAllItems)
    {
        seqFromDataBase.append(reader.read(item));
    }

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
