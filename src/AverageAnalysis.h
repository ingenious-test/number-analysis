#ifndef AVERAGEANALYSIS_H

#define AVERAGEANALYSIS_H

#include "AbstractAnalysis.h"

class AverageAnalysis : public AbstractAnalysis
{
public:
    AverageAnalysis();

    double analyze(const PointList &values) const;
};

Q_DECLARE_METATYPE(AverageAnalysis*)

#endif // AVERAGEANALYSIS_H
