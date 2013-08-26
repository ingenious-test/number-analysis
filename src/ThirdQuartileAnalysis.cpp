#include "ThirdQuartileAnalysis.h"

ThirdQuartileAnalysis::ThirdQuartileAnalysis() :
    AbstractAnalysis("third-quartile")
{
}

ThirdQuartileAnalysis::ThirdQuartileAnalysis(const ThirdQuartileAnalysis &a):
    AbstractAnalysis("third-quartile")
{
}

double ThirdQuartileAnalysis::analyze(const PointList &values) const
{
    return 0;
}

ThirdQuartileAnalysis *ThirdQuartileAnalysis::clone()
{
    return new ThirdQuartileAnalysis(*this);
}
