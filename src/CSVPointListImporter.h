#ifndef CSVPOINTLISTIMPORTER_H

#define CSVPOINTLISTIMPORTER_H

#include "AbstractAnalysis.h"

class ParsedPoint
{
public:
    ParsedPoint() :
        id(),
        value(0.0)
    {
    }

    ParsedPoint(const ID &id, const Point value) :
        id(id),
        value(value)
    {
    }

    bool operator ==(const ParsedPoint &p) const
    {
        return false;
    }

    ID id;
    Point value;
};

class CSVPointListImporter
{
public:
    CSVPointListImporter(const QString &sourceFileName,
                         const QString &targetFileName,
                         const QString &targetTableName);

    void import();

    static ParsedPoint parseLine(const QString &line);
};

#endif // CSVPOINTLISTIMPORTER_H
