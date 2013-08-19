#ifndef ABSTRACTPOINTLISTREADER_H

#define ABSTRACTPOINTLISTREADER_H

#include "AbstractAnalysis.h"
#include "PointListStorageStatistics.h"

class AbstractPointListReader
{
public:
    AbstractPointListReader();

    virtual ~AbstractPointListReader();

    virtual PointList read(const ID &item) = 0;
    virtual IDList readAllItems() = 0;

    virtual PointListStorageStatistics statistics() = 0;
};

#endif // ABSTRACTPOINTLISTREADER_H
