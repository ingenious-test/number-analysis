#include "TCSVPointListExporter.h"

TCSVPointListExporter::TCSVPointListExporter()
{

}

void TCSVPointListExporter::TestExportPointList_data()
{
    QTest::addColumn<SequencePointList>("result");

    QTest::newRow("empty") << SequencePointList();

    QTest::newRow("one-item-with-one-point")
            << (SequencePointList()
                << (PointList("id1") << Point(1.0)));

    QTest::newRow("one-item-with-two-point")
            << (SequencePointList()
                << (PointList("id1")
                    << Point(1.0)
                    << Point(2.0)));

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
                    << Point(512.512)));

    QTest::newRow("two-items")
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

    QTest::newRow("three-items")
            << (SequencePointList()
                << (PointList("id1")
                    << Point(41.29)
                    << Point(4.3))
                << (PointList("id2")
                    << Point(1.25)
                    << Point(3.4)
                    << Point(8.34)
                    << Point(15.6)
                    << Point(38.009))
                << (PointList("id3")
                    << Point(2.44)
                    << Point(5.8)));
}

void TCSVPointListExporter::TestExportPointList()
{
    QFETCH(SequencePointList, result);


    const QString sourseDataBaseName = QString(QTest::currentDataTag()) +  QTest::currentTestFunction() + ".db";
    const QString importDataBaseName = QString(QTest::currentDataTag()) +  QTest::currentTestFunction() + "import-from-csv.db";
    const QString tableName = "Points";
    const QString exportFileName = QString(QTest::currentDataTag()) + QTest::currentTestFunction() + ".csv";


    if(QFile::exists(importDataBaseName))
    {
        if(!QFile::remove(importDataBaseName))
        {
            QFAIL("can't remove testing database file");
        }
    }

    if(QFile::exists(exportFileName))
    {
        if(!QFile::remove(exportFileName))
        {
            QFAIL("can't remove testing target file");
        }
    }

    if(QFile::exists(sourseDataBaseName))
    {
        if(!QFile::remove(sourseDataBaseName))
        {
            QFAIL("can't remove testing data base");
        }
    }


    SqlPointListWriter writer(sourseDataBaseName, tableName);
    if(!writer.open())
    {
        QFAIL(QString("can't open to write " + sourseDataBaseName).toStdString().c_str());
    }
    writer.write(result);


    CSVPointListExporter csvExporter(sourseDataBaseName, tableName, exportFileName);
    csvExporter.exportFromDataBase();
    QVERIFY(QFile::exists(exportFileName));

    CSVPointListImporter csvImporter(exportFileName, importDataBaseName, tableName);
    if(!csvImporter.import())
    {
        QFAIL(QString("can't import " + exportFileName + " to " + importDataBaseName).toStdString().c_str());
    }
    QVERIFY(QFile::exists(exportFileName));


    SqlPointListReader reader(sourseDataBaseName, tableName);
    if(!reader.open())
    {
        QFAIL(QString("can't open to read " + sourseDataBaseName).toStdString().c_str());
    }
    const IDList expectedItems = reader.readAllItems();
    SequencePointList fileSourceData;
    foreach(const ID& item, expectedItems)
    {
        fileSourceData.append(reader.read(item));
    }

    reader.open(importDataBaseName, tableName);
    if(!reader.open())
    {
        QFAIL(QString("can't open to read " + importDataBaseName).toStdString().c_str());
    }

    const IDList actualItems = reader.readAllItems();
    SequencePointList fileTargetData;
    foreach(const ID& item, actualItems)
    {
        fileTargetData.append(reader.read(item));
    }


    QCOMPARE(actualItems, expectedItems);

    const SequencePointList actualData = fileTargetData;
    const SequencePointList expectedData = fileSourceData;

    bool isCompare = SequencePointList::fuzzyCompare(actualData,expectedData);
    if(!isCompare)
    {
        QFAIL(QString("Compare values are not the same. \nActual:\n"
                      + actualData.toString()
                      + "\nExpected:\n"
                      + expectedData.toString()).toStdString().c_str());
    }
}
