#ifndef SQLPOINTLISTREADER_H

#define SQLPOINTLISTREADER_H

#include "SqlPointListInterface.h"
#include "AbstractPointListReader.h"
#include "StatisticsCollection.h"

class SqlPointListReader :
        public AbstractPointListReader,
        public SqlPointListInterface
{
public:
    SqlPointListReader(const QString &dataBaseName, const QString &tableName);
    ~SqlPointListReader();

    bool prepareQueries();

    PointList read(const ID &item);
    IDList readAllItems();

    void appendStatistics(AbstractStatictics* statistics);
    void appendStatistics(const StatisticsList& statisticsList);

    PointListStorageStatistics statistics();

private:
    QSqlQuery readPointsByID_;
    QSqlQuery readAllPointsIDs_;

    StatisticsList statisticsCollection;

};

#endif // SQLPOINTLISTREADER_H
