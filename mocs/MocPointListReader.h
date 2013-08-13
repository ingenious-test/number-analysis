#ifndef MOCPOINTLISTREADER_H

#define MOCPOINTLISTREADER_H

#include "../src/AbstractPointListReader.h"

class MocPointListReader : public AbstractPointListReader
{
public:
    MocPointListReader(const IDList &items);

    PointList read(const ID &item);
    IDList readAllItems();

private:
    QHash<ID, PointList> table_;
};

#endif // MOCPOINTLISTREADER_H
