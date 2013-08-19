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

    PointListStorageStatistics statistics();

private:
    QSqlQuery readPointsByID_;
    QSqlQuery readAllPointsIDs_;

    //statistics querys
    QSqlQuery statisticsMaxSequenceLengthId;
    QSqlQuery statisticsMinSequenceLengthId;
    QSqlQuery statisticsAverageSequenceLength;
    QSqlQuery statisticsAverageNullCountPoints;

};

#endif // SQLPOINTLISTREADER_H
