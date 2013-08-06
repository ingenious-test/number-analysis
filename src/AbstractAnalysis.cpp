#include "AbstractAnalysis.h"

double AbstractAnalysis::listSum(const PointList &list)
{
    double sum = 0.0;
    foreach(const Point e, list)
    {
        sum += e;
    }
    return sum;
}

AbstractAnalysis::AbstractAnalysis()
{
}
