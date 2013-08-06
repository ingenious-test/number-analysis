#ifndef AVERAGEIGNORENULLANALYSIS_H

#define AVERAGEIGNORENULLANALYSIS_H

#include "AbstractAnalysis.h"

class AverageIgnoreNullAnalysis : public AbstractAnalysis
{
public:
    AverageIgnoreNullAnalysis();

    double analyze(const PointList &values) const;
};

Q_DECLARE_METATYPE(AverageIgnoreNullAnalysis*)

#endif // AVERAGEIGNORENULLANALYSIS_H
