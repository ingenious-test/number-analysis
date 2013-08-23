#include "TCSVPointListImporter.h"

TCSVPointListImporter::TCSVPointListImporter()
{
}

void TCSVPointListImporter::TestParseLine_data()
{
    QTest::addColumn<QString>("line");
    QTest::addColumn<ParsedPoint>("parsedPoint");

    QTest::newRow("null-value") << "id1;0.0"
                                << ParsedPoint(ID("id1"), 0.0);

    QTest::newRow("positive-value") << "id1;1.0"
                                    << ParsedPoint(ID("id1"), 1.0);

    QTest::newRow("negative-value") << "id1;-1.0"
                                    << ParsedPoint(ID("id1"), -1.0);
}

void TCSVPointListImporter::TestParseLine()
{
    QFETCH(QString, line);
    QFETCH(ParsedPoint, parsedPoint);

    const ParsedPoint actualParsedPoint = CSVPointListImporter::parseLine(line);
    const ParsedPoint expectedParsedPoint = parsedPoint;


    if(actualParsedPoint != expectedParsedPoint)
    {
        QFAIL(QString("Compare values are not the same\nActual:\nid: "
              + actualParsedPoint.id
              + "\nvalue: " + actualParsedPoint.value
              + "\n\nExpected:\nid: "
              + expectedParsedPoint.id
              + "\nvalue: " + expectedParsedPoint.value).toStdString().c_str());
    }
}

void TCSVPointListImporter::TestImportPointList_data()
{
    QTest::addColumn<QStringList>("data");
    QTest::addColumn<SequencePointList>("pointList");

    QTest::newRow("empty-data") << QStringList()
                                << (SequencePointList());

    QTest::newRow("single-line-data1") << (QStringList() << "id1;0.0")
                                       << (SequencePointList()
                                           << (PointList(ID("id1")) << 0.0));

    QTest::newRow("single-line-data2") << (QStringList() << "id1;1.0")
                                       << (SequencePointList()
                                           << (PointList(ID("id1")) << 1.0));

    QTest::newRow("single-line-data3") << (QStringList() << "id2;1.0")
                                       << (SequencePointList()
                                           << (PointList(ID("id2")) << 1.0));

    QTest::newRow("two-lines-data") << (QStringList() << "id2;1.0" << "id2;2.0")
                                    << (SequencePointList()
                                        << (PointList(ID("id2")) << 1.0 << 2.0));

    QTest::newRow("four-lines-data-correct") << (QStringList() << "id1;-13.0" << "id2;1.0" << "id2;2.0")
                                    << (SequencePointList()
                                        << (PointList(ID("id1")) << -13.0)
                                        << (PointList(ID("id2")) << 1.0 << 2.0));

    QTest::newRow("four-lines-data-incorrect") << (QStringList() << "id1;3.5" << "id2;1.0" << "id1;2.0")
                                    << (SequencePointList()
                                        << (PointList(ID("id1")) << 3.5)
                                        << (PointList(ID("id2")) << 1.0));
}

void TCSVPointListImporter::TestImportPointList()
{
    QFETCH(QStringList, data);
    QFETCH(SequencePointList, pointList);

    const QString sourceFileName = QString(QTest::currentDataTag()) + QTest::currentTestFunction() + ".csv";
    const QString targetDataBaseName = QString(QTest::currentDataTag()) +  QTest::currentTestFunction() + ".db";
    const QString tableName = "Points";

    if(QFile::exists(sourceFileName))
    {
        if(!QFile::remove(sourceFileName))
        {
            QFAIL("can't remove testing source file");
        }
    }

    if(QFile::exists(targetDataBaseName))
    {
        if(!QFile::remove(targetDataBaseName))
        {
            QFAIL("can't remove testing data base");
        }
    }

    QFile sourceFile(sourceFileName);
    if(!sourceFile.open(QFile::WriteOnly))
    {
        QFAIL("can't open testing source file for writing");
    }
    QTextStream sourceFileStream(&sourceFile);
    sourceFileStream << data.join("\n");
    sourceFile.flush();
    sourceFile.close();

    CSVPointListImporter importer(sourceFileName,
                                  targetDataBaseName,
                                  tableName);
    importer.import();

    SqlPointListReader reader(targetDataBaseName, tableName);
    reader.open();

    SequencePointList pointsFromDataBase;
    const IDList items = reader.readAllItems();
    foreach(const ID& item, items)
    {
        pointsFromDataBase << reader.read(item);
    }


    const SequencePointList actualPointList = pointsFromDataBase;
    const SequencePointList expectedPointList = pointList;

    bool isCompare = SequencePointList::fuzzyCompare(actualPointList,expectedPointList);
    if(!isCompare)
    {
        QFAIL(QString("Compare values are not the same. \nActual:\n"
                      + actualPointList.toString()
                      + "\nExpected:\n"
                      + expectedPointList.toString()).toStdString().c_str());
    }
}
