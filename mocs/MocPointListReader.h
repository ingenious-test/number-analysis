#ifndef MOCPOINTLISTREADER_H

#define MOCPOINTLISTREADER_H

#include "../src/AbstractPointListReader.h"

class MocPointListReader : public AbstractPointListReader
{
public:
    MocPointListReader();

    PointList read(const ID &id);
    IDList readAllItems();

private:
    QHash<ID, PointList> table_;
};

#endif // MOCPOINTLISTREADER_H
