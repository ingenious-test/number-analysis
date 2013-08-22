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

    QCOMPARE(CSVPointListImporter::parseLine(line), parsedPoint);
}

void TCSVPointListImporter::TestImportSinglePointList_data()
{
    QTest::addColumn<QStringList>("data");
    QTest::addColumn<ID>("item");
    QTest::addColumn<PointList>("expectedPointList");

    QTest::newRow("empty-data") << QStringList()
                                << ID("id1")
                                << PointList();

    QTest::newRow("single-line-data1") << (QStringList() << "id1;0.0")
                                       << ID("id1")
                                       << (PointList() << 0.0);

    QTest::newRow("single-line-data2") << (QStringList() << "id1;1.0")
                                       << ID("id1")
                                       << (PointList() << 1.0);

    QTest::newRow("single-line-data3") << (QStringList() << "id2;1.0")
                                       << ID("id2")
                                       << (PointList() << 1.0);

    QTest::newRow("two-lines-data") << (QStringList() << "id2;1.0" << "id2;2.0")
                                    << ID("id2")
                                    << (PointList() << 1.0 << 2.0);
}

void TCSVPointListImporter::TestImportSinglePointList()
{
    QFETCH(QStringList, data);
    QFETCH(ID, item);
    QFETCH(PointList, expectedPointList);

    const QString sourceFileName = QString(QTest::currentDataTag()) + "TestImportSinglePointLis.csv";
    const QString targetDataBaseName = QString(QTest::currentDataTag()) + "TestImportSinglePointLis.db";
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

    CSVPointListImporter importer(sourceFileName,
                                  targetDataBaseName,
                                  tableName);
    importer.import();

    SqlPointListReader reader(targetDataBaseName, tableName);
    reader.open();

    QCOMPARE(reader.read(item), expectedPointList);
}
