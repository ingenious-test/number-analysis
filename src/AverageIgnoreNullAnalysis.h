#ifndef AVERAGEIGNORENULLANALYSIS_H

#define AVERAGEIGNORENULLANALYSIS_H

#include "AbstractAnalysis.h"

class AverageIgnoreNullAnalysis : public AbstractAnalysis
{
public:
    AverageIgnoreNullAnalysis();
    AverageIgnoreNullAnalysis(const AverageIgnoreNullAnalysis &a);


    double analyze(const PointList &values) const;
    AverageIgnoreNullAnalysis* clone();
};

#endif // AVERAGEIGNORENULLANALYSIS_H
