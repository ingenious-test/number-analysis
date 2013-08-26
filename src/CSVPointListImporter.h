#ifndef CSVPOINTLISTIMPORTER_H

#define CSVPOINTLISTIMPORTER_H

#include "AbstractAnalysis.h"
#include "SqlPointListWriter.h"
#include "CSVPointListValidator.h"

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
        return (this->id == p.id) && (this->value == p.value);
    }

    bool operator !=(const ParsedPoint &p) const
    {
        return !(*this == p);
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

    bool import();

    static ParsedPoint parseLine(const QString &line);

private:
    const QString &sourceFileName_;
    const QString &targetFileName_;
    const QString &targetTableName_;
};

#endif // CSVPOINTLISTIMPORTER_H
