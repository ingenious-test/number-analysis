#include "CSVPointListExporter.h"

CSVPointListExporter::CSVPointListExporter(const QString &sourseDataBaseFile,
                                           const QString &sourseTableName,
                                           const QString &targetFileName) :
    sourseDataBaseFile_(sourseDataBaseFile),
    sourseTableName_(sourseTableName),
    targetFileName_(targetFileName)
{
}

void CSVPointListExporter::exportFromDataBase()
{
    if(!QFile::exists(sourseDataBaseFile_))
    {
        qWarning() << sourseDataBaseFile_ << "not exists";
        return;
    }

    SqlPointListReader reader(sourseDataBaseFile_, sourseTableName_);

    if(!reader.open())
    {
        qWarning() << sourseDataBaseFile_ << "not open";
        return;
    }

    QFile targetFile(targetFileName_);
    if(!targetFile.open(QFile::WriteOnly))
    {
        qWarning() << targetFileName_ << "can't open for writing";
    }

    QTextStream targetFileStream(&targetFile);
    const IDList idList = reader.readAllItems();
    foreach(const ID& id, idList)
    {
        const PointList pointList = reader.read(id);
        foreach(const Point& point, pointList.points())
        {
            targetFileStream << pointList.id() << ";" << point << "\n";
        }
    }

    targetFile.flush();
    targetFile.close();
}
