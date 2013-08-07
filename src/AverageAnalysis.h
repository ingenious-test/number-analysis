#ifndef AVERAGEANALYSIS_H

#define AVERAGEANALYSIS_H

#include "AbstractAnalysis.h"

class AverageAnalysis : public AbstractAnalysis
{
public:
    AverageAnalysis();
    AverageAnalysis(const AverageAnalysis &a);


    double analyze(const PointList &values) const;
    AverageAnalysis* clone();
};

Q_DECLARE_METATYPE(AverageAnalysis*)

#endif // AVERAGEANALYSIS_H
