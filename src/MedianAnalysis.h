#ifndef MEDIANANALYSIS_H

#define MEDIANANALYSIS_H

#include "AbstractAnalysis.h"

class MedianAnalysis : public AbstractAnalysis
{
public:
    MedianAnalysis();
    MedianAnalysis(const MedianAnalysis &a);

    double analyze(const PointList &values) const;
    MedianAnalysis* clone();

};

#endif // MEDIANANALYSIS_H
