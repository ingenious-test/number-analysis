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

    virtual PointList read(const ID &item);
    virtual IDList readAllItems();
};

#endif // SQLPOINTLISTREADER_H
