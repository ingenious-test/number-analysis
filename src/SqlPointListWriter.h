#ifndef SQLPOINTLISTWRITER_H

#define SQLPOINTLISTWRITER_H

#include <QSqlQuery>
#include <QSqlError>

#include "AbstractAnalysis.h"

class SqlPointListWriter
{
public:
    SqlPointListWriter(const QString &dataBaseName);

    void write(const ID &item, const PointList &points);

private:
    const QString dataBaseName_;

    void error(const QString& errorString);
};

#endif // SQLPOINTLISTWRITER_H
