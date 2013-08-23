#include "TCSVPointListExporter.h"

TCSVPointListExporter::TCSVPointListExporter()
{

}

void TCSVPointListExporter::TestExportPointList_data()
{
    QTest::addColumn<SequencePointList>("pointList");
    QTest::addColumn<QStringList>("result");

    QTest::newRow("empty") << SequencePointList()
                           << QStringList();

    QTest::newRow("one-item-with-one-point")
            << (SequencePointList() << (PointList("id1") << Point(1.0)))
            << (QStringList() << QString("id1;1.0"));

    QTest::newRow("one-item-with-two-point")
            << (SequencePointList()
                << (PointList("id1")
                    << Point(1.0)
                    << Point(2.0)))
            << (QStringList() << QString("id1;1.0") << QString("id1;2.0"));

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
            << (QStringList()
                << QString("id1;1.1")
                << QString("id1;2.2")
                << QString("id1;4.4")
                << QString("id1;8.8")
                << QString("id1;16.16")
                << QString("id1;32.32")
                << QString("id1;64.64")
                << QString("id1;128.128")
                << QString("id1;256.256")
                << QString("id1;512.512"));

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
                    << Point(8.1)))
            << (QStringList()
                    << QString("id1;4.9")
                    << QString("id1;6.8")
                    << QString("id1;11.0")
                    << QString("id2;14.01")
                    << QString("id2;12.3")
                    << QString("id2;3.3")
                    << QString("id2;8.1"));

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
                    << Point(5.8)))
            << (QStringList()
                << QString("id1;41.29")
                << QString("id1;4.3")
                << QString("id2;1.25")
                << QString("id2;3.4")
                << QString("id2;8.34")
                << QString("id2;15.6")
                << QString("id2;38.009")
                << QString("id3;2.44")
                << QString("id3;5.8"));
}

void TCSVPointListExporter::TestExportPointList()
{
    QFETCH(SequencePointList, pointList);
    QFETCH(QStringList, result);


    const QString sourseDataBaseName = QString(QTest::currentDataTag()) +  QTest::currentTestFunction() + ".db";
    const QString tableName = "Points";
    const QString targetFileName = QString(QTest::currentDataTag()) + QTest::currentTestFunction() + ".csv";


    if(QFile::exists(targetFileName))
    {
        if(!QFile::remove(targetFileName))
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
    writer.open();
    writer.write(pointList);

    QVERIFY(QFile::exists(sourseDataBaseName));


    CSVPointListExporter exporter(sourseDataBaseName,
                                  tableName,
                                  targetFileName);
    exporter.exportFromDataBase();

    QVERIFY(QFile::exists(targetFileName));

    QFile file(targetFileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qWarning() << targetFileName << " not open";
        return;
    }

    QStringList fileData;
    while (!file.atEnd())
    {
        fileData.append(file.readLine());
    }


    const QStringList actualData = fileData;
    const QStringList expectedData = result;
}
