#include "TSqlPointListReader.h"

TSqlPointListReader::TSqlPointListReader()
{
}

void TSqlPointListReader::TestWriteRead_data()
{
    QTest::addColumn<ID>("item");
    QTest::addColumn<PointList>("points");

    QTest::newRow("empty-point-list") << ID("id1") << PointList();
}

void TSqlPointListReader::TestWriteRead()
{
    QFETCH(ID, item);
    QFETCH(PointList, points);

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

    SqlPointListReader reader(dataBaseName);

    const PointList actualPoints = reader.read(item);
    const PointList expectedPoints = points;

    QCOMPARE(actualPoints, expectedPoints);
}
