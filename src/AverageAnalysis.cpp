#include "AverageAnalysis.h"

AverageAnalysis::AverageAnalysis():
    AbstractAnalysis("average")
{
}

double AverageAnalysis::analyze(const PointList &values) const
{
    if(values.isEmpty())
    {
        return 0;
    }

    const double sum = AbstractAnalysis::listSum(values);
    const double result = sum / static_cast<double>(values.length());

    return result;
}
