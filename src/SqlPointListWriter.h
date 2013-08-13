#ifndef SQLPOINTLISTWRITER_H

#define SQLPOINTLISTWRITER_H

#include "AbstractAnalysis.h"

class SqlPointListWriter
{
public:
    SqlPointListWriter(const QString &dataBaseName);

    void write(const ID &item, const PointList &points);
};

#endif // SQLPOINTLISTWRITER_H
