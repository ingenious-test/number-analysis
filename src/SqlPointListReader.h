#ifndef SQLPOINTLISTREADER_H

#define SQLPOINTLISTREADER_H

#include <QSqlQuery>
#include <QSqlError>

#include "AbstractPointListReader.h"

class SqlPointListReader : public AbstractPointListReader
{
public:
    SqlPointListReader(const QString &dataBaseName);

    virtual PointList read(const ID &item);
    virtual IDList readAllItems();

private:
    QString dataBaseName_;
};

#endif // SQLPOINTLISTREADER_H
