#include "TCSVPointListExporter.h"

TCSVPointListExporter::TCSVPointListExporter()
{

}

void TCSVPointListExporter::TestExportPointList_data()
{
    QTest::addColumn<QStringList>("result");

    QTest::newRow("empty") << QStringList();

    QTest::newRow("one-item-with-one-point")
            << (QStringList() << QString("id1;1"));

    QTest::newRow("one-item-with-two-point")
            << (QStringList() << QString("id1;1") << QString("id1;2"));

    QTest::newRow("one-item-with-ten-point")
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
            << (QStringList()
                    << QString("id1;4.9")
                    << QString("id1;6.8")
                    << QString("id1;11")
                    << QString("id2;14.01")
                    << QString("id2;12.3")
                    << QString("id2;3.3")
                    << QString("id2;8.1"));

    QTest::newRow("three-items")
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
    QFETCH(QStringList, result);


    const QString sourseDataBaseName = QString(QTest::currentDataTag()) +  QTest::currentTestFunction() + ".db";
    const QString tableName = "Points";
    const QString importFileName = QString(QTest::currentDataTag()) + QTest::currentTestFunction() + "source.csv";
    const QString exportFileName = QString(QTest::currentDataTag()) + QTest::currentTestFunction() + "target.csv";


    if(QFile::exists(importFileName))
    {
        if(!QFile::remove(importFileName))
        {
            QFAIL("can't remove testing source file");
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


    QFile importFile(importFileName);
    if(!importFile.open(QFile::WriteOnly | QIODevice::Text))
    {
        QFAIL("can't open testing source file for writing");
    }
    QTextStream sourceFileStream(&importFile);
    sourceFileStream << result.join("\n");
    importFile.flush();
    importFile.close();


    CSVPointListImporter importer(importFileName, sourseDataBaseName, tableName);
    if(!importer.import())
    {
        QFAIL("can't import testing data base");
    }

    QVERIFY(QFile::exists(sourseDataBaseName));


    CSVPointListExporter exporter(sourseDataBaseName,
                                  tableName,
                                  exportFileName);
    exporter.exportFromDataBase();

    QVERIFY(QFile::exists(exportFileName));

    QFile exportFile(exportFileName);
    if (!exportFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QFAIL(QString(exportFileName + " not open").toStdString().c_str());
    }

    QStringList fileTargetData;
    while (!exportFile.atEnd())
    {
        fileTargetData.append(exportFile.readLine());
    }

    importFile.setFileName(importFileName);
    if (!importFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QFAIL(QString(importFileName + " not open").toStdString().c_str());
    }

    QStringList fileSourceData;
    while (!importFile.atEnd())
    {
        fileSourceData.append(importFile.readLine());
    }


    const QStringList actualData = fileTargetData;
    const QStringList expectedData = fileSourceData;

    QCOMPARE(actualData, expectedData);
}
