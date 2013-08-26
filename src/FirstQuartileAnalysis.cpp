#include "FirstQuartileAnalysis.h"

FirstQuartileAnalysis::FirstQuartileAnalysis() :
    AbstractAnalysis("first-quartile")
{
}

FirstQuartileAnalysis::FirstQuartileAnalysis(const FirstQuartileAnalysis &a):
    AbstractAnalysis("first-quartile")
{
}

double FirstQuartileAnalysis::analyze(const PointList &values) const
{
    return 0;
}

FirstQuartileAnalysis *FirstQuartileAnalysis::clone()
{
    return new FirstQuartileAnalysis(*this);
}
