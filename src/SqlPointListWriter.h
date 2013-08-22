#ifndef SQLPOINTLISTWRITER_H

#define SQLPOINTLISTWRITER_H

#include "SqlPointListInterface.h"
#include "AbstractAnalysis.h"

class SqlPointListWriter : public SqlPointListInterface
{
public:
    SqlPointListWriter(const QString &dataBaseName, const QString& tableName);

    void write(const PointList &points);
    void write(const SequencePointList &seqPoints);


    bool prepareQueries();

private:
    QSqlQuery writePointsByID_;
};

#endif // SQLPOINTLISTWRITER_H
