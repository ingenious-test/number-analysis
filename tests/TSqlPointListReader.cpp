#include "TSqlPointListReader.h"

TSqlPointListReader::TSqlPointListReader()
{
}

void TSqlPointListReader::TestWriteRead_data()
{
    QTest::addColumn<ID>("item");
    QTest::addColumn<PointList>("points");
    QTest::addColumn<IDList>("allItems");

    QTest::newRow("empty-point-list") << ID("id1")
                                      << PointList()
                                      << IDList();

    QTest::newRow("single-point-list") << ID("id1")
                                       << (PointList() << Point(0.0))
                                       << (IDList() << ID("id1"));

    QTest::newRow("two-point-list") << ID("id1")
                                    << (PointList() << Point(1.0) << Point(2.0))
                                    << (IDList() << ID("id1"));

    QTest::newRow("ten-point-list") << ID("id1")
                                    << (PointList()
                                        << Point(1.1)
                                        << Point(2.2)                                           << Point(0.0)
                                        << Point(4.4)
                                        << Point(8.8)
                                        << Point(16.16)
                                        << Point(32.32)
                                        << Point(64.64)
                                        << Point(128.128)
                                        << Point(256.256)
                                        << Point(512.512))
                                    << (IDList() << ID("id1"));;
}

void TSqlPointListReader::TestWriteRead()
{
    QFETCH(ID, item);
    QFETCH(PointList, points);
    QFETCH(IDList, allItems);

    const QString dataBaseName = QString(QTest::currentDataTag()) + "TestWriteRead.db";

    if(QFile::exists(dataBaseName))
    {
        if(!QFile::remove(dataBaseName))
        {
            QFAIL("can't remove testing database");
        }
    }

    SqlPointListWriter writer(dataBaseName);

    writer.write(item, points);

    QVERIFY(QFile::exists(dataBaseName));

    SqlPointListReader reader(dataBaseName);

    const IDList actualAllItems = reader.readAllItems();
    const IDList expectedAllItems = allItems;

    QCOMPARE(actualAllItems, expectedAllItems);

    const PointList actualPoints = reader.read(item);
    const PointList expectedPoints = points;

    QCOMPARE(actualPoints, expectedPoints);
}
