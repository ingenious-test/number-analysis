#ifndef AVERANGEIGNORENULLANALISYS_H

#define AVERANGEIGNORENULLANALISYS_H

#include "AbstractAnalysis.h"

class AverangeIgnoreNullAnalisys : public AbstractAnalysis
{
public:
    AverangeIgnoreNullAnalisys();

    double analyze(const PointList &values) const;
};

#endif // AVERANGEIGNORENULLANALISYS_H
