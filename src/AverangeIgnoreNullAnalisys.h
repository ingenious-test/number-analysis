#ifndef AVERANGEIGNORENULLANALISYS_H

#define AVERANGEIGNORENULLANALISYS_H

#include "AbstractAnalysis.h"

class AverangeIgnoreNullAnalisys : public AbstractAnalysis
{
public:
    AverangeIgnoreNullAnalisys();

    double analyze(const QList<double> &values) const;
};

#endif // AVERANGEIGNORENULLANALISYS_H
