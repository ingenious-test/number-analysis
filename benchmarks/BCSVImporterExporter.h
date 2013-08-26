#ifndef BCSVIMPORTEREXPORTER_H
#define BCSVIMPORTEREXPORTER_H

#include "../src/SequencePointList.h"
#include "../src/CSVPointListImporter.h"
#include "../src/CSVPointListExporter.h"

class BCSVImporterExporter
{
public:
    BCSVImporterExporter(const int seqCount, const int pointsCount);
    void run();

private:
    int seqCount_;
    int pointsCount_;
};

#endif // BCSVIMPORTEREXPORTER_H
