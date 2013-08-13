#ifndef ABSTRACTPOINTLISTREADER_H

#define ABSTRACTPOINTLISTREADER_H

#include "../src/AbstractAnalysis.h"

class AbstractPointListReader
{
public:
    AbstractPointListReader();

    virtual PointList read(const ID &id) = 0;
    virtual IDList readAllItems() = 0;
};

#endif // ABSTRACTPOINTLISTREADER_H
