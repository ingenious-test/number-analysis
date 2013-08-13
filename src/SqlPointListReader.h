#ifndef SQLPOINTLISTREADER_H

#define SQLPOINTLISTREADER_H

#include "AbstractPointListReader.h"

class SqlPointListReader : public AbstractPointListReader
{
public:
    SqlPointListReader(const QString &dataBaseName);

    virtual PointList read(const ID &id);
    virtual IDList readAllItems();
};

#endif // SQLPOINTLISTREADER_H
