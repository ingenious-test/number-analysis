#ifndef THIRDQUARTILEANALYSIS_H

#define THIRDQUARTILEANALYSIS_H

#include "MedianAnalysis.h"

class ThirdQuartileAnalysis : public AbstractAnalysis
{
public:
    ThirdQuartileAnalysis();
    ThirdQuartileAnalysis(const ThirdQuartileAnalysis &a);


    double analyze(const PointList &values) const;
    ThirdQuartileAnalysis* clone();
};

#endif // THIRDQUARTILEANALYSIS_H
