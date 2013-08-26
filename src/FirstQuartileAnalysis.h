#ifndef FIRSTQUARTILEANALYSIS_H

#define FIRSTQUARTILEANALYSIS_H

#include "MedianAnalysis.h"

class FirstQuartileAnalysis : public AbstractAnalysis
{
public:
    FirstQuartileAnalysis();
    FirstQuartileAnalysis(const FirstQuartileAnalysis &a);


    double analyze(const PointList &values) const;
    FirstQuartileAnalysis* clone();
};

#endif // FIRSTQUARTILEANALYSIS_H
