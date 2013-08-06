#ifndef AVERANGEANALISYS_H

#define AVERANGEANALISYS_H

#include "AbstractAnalysis.h"

class AverangeAnalisys : public AbstractAnalysis
{
public:
    AverangeAnalisys();

    double analyze(const PointList &values) const;
};

#endif // AVERANGEANALISYS_H
