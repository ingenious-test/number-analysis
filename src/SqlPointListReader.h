#ifndef SQLPOINTLISTREADER_H

#define SQLPOINTLISTREADER_H

#include "SqlPointListInterface.h"
#include "AbstractPointListReader.h"

class SqlPointListReader :
        public AbstractPointListReader,
        public SqlPointListInterface
{
public:
    SqlPointListReader(const QString &dataBaseName, const QString &tableName);

    bool prepareQueries();

    PointList read(const ID &item);
    IDList readAllItems();

private:
    QSqlQuery readPointsByID_;
    QSqlQuery readAllPointsIDs_;
};

#endif // SQLPOINTLISTREADER_H
