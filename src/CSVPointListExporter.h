#ifndef CSVPOINTLISTEXPORTER_H

#define CSVPOINTLISTEXPORTER_H

#include "SqlPointListReader.h"

class CSVPointListExporter
{
public:
    CSVPointListExporter(const QString &sourseDataBaseFile,
                         const QString &sourseTableName,
                         const QString &targetFileName);

    void exportFromDataBase();
};

#endif // CSVPOINTLISTEXPORTER_H
