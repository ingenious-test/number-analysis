#ifndef DATABASEGENERATOR_H

#define DATABASEGENERATOR_H

#include "PointListGenerator.h"
#include "SqlPointListWriter.h"

class DatabaseGenerator
{
public:
    DatabaseGenerator();

    void generateDataBase(const QString& dataBaseName, const QString &tableName);
};

#endif // DATABASEGENERATOR_H
