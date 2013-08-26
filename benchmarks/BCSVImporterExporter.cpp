#include "BCSVImporterExporter.h"

BCSVImporterExporter::BCSVImporterExporter(const int seqCount, const int pointsCount) :
    seqCount_(seqCount),
    pointsCount_(pointsCount)
{

}

void BCSVImporterExporter::run()
{
    const QString dataBaseName = "csvbenchmarck.db";
    const QString tableName = "points";
    const QString importFileName = "csvbenchmarck_import.csv";
    const QString exportFileName = "csvbenchmarck_export.csv";

    if(QFile::exists(dataBaseName))
    {
        if(!QFile::remove(dataBaseName))
        {
            qWarning() << "can't remove data base";
            return;
        }
    }

    if(QFile::exists(importFileName))
    {
        if(!QFile::remove(importFileName))
        {
            qWarning() << "can't remove import file";
        }
    }

    if(QFile::exists(exportFileName))
    {
        if(!QFile::remove(exportFileName))
        {
            qWarning() << "can't remove export file";
        }
    }


    QFile importFile(importFileName);

    if(!importFile.open(QFile::WriteOnly | QIODevice::Text))
    {
        qWarning() << importFileName << "not open to write";
        return;
    }

    QTextStream textStream(&importFile);
    for(int i = 0; i < seqCount_; i++)
    {
        const PointList pointList = PointList();
        for(int j = 0; j < pointsCount_; j++)
        {
            textStream << QString("id%1").arg(i) << ";" << j;

            const bool isLast = ((i + 1) == seqCount_)
                    && ((j + 1) == pointsCount_);

            if(!isLast)
            {
                textStream << '\n';
            }
        }
    }

    importFile.flush();
    importFile.close();

    qWarning() << "Sequence count: " << seqCount_;
    qWarning() << "Points count: " << pointsCount_;
    qWarning() << "Import file size: " << QFileInfo(importFileName).size() / 1024 << "kb";

    CSVPointListValidator csvValidator;
    const QTime validationTime(QTime::currentTime());
    if(!csvValidator.validation(importFileName))
    {
        qWarning() << importFileName << "not valid";
    }
    qWarning() << "Validation time: " << validationTime.secsTo(QTime::currentTime()) << "s";

    CSVPointListImporter csvImporter(importFileName, dataBaseName, tableName);

    const QTime importTime(QTime::currentTime());
    if(!csvImporter.import())
    {
        qWarning() << importFileName << "not imported";
    }
    qWarning() << "Import time: " << importTime.secsTo(QTime::currentTime()) << "s";
    qWarning() << "Database size: " << QFileInfo(dataBaseName).size() / 1024 << "kb";



    CSVPointListExporter csvExporter(dataBaseName, tableName, exportFileName);

    const QTime exportTime(QTime::currentTime());
    csvExporter.exportFromDataBase();
    qWarning() << "Export time: " << exportTime.secsTo(QTime::currentTime()) << "s";
    qWarning() << "Export file size: "  << QFileInfo(exportFileName).size() / 1024 << "kb";
}
