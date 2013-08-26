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
    if(!targetFile.open(QFile::WriteOnly | QIODevice::Text))
    {
        qWarning() << targetFileName_ << "can't open for writing";
    }

    QTextStream targetFileStream(&targetFile);
    const IDList idList = reader.readAllItems();

    for(int i = 0; i < idList.count(); i++)
    {
        const ID& id = idList.at(i);
        const PointList pointList = reader.read(id);
        for(int j = 0; j < pointList.count(); j++)
        {
            const Point& point = pointList.at(j);
            targetFileStream << pointList.id() << ";" << point;

            const bool isLast = ((i + 1) == idList.count())
                    && ((j + 1) == pointList.count());

            if(!isLast)
            {
                targetFileStream << '\n';
            }
        }
    }

    targetFile.flush();
    targetFile.close();
}
