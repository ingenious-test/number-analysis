#include "StandardDeviationAnalysis.h"

StandardDeviationAnalysis::StandardDeviationAnalysis() :
    AbstractAnalysis("standard-deviation")
{
}

StandardDeviationAnalysis::StandardDeviationAnalysis(const StandardDeviationAnalysis &a):
    AbstractAnalysis("standard-deviation")
{
}

double StandardDeviationAnalysis::analyze(const PointList &values) const
{
    if(values.isEmpty())
    {
        return 0.0;
    }

    if(values.count() == 1)
    {
        return 0.0;
    }

    AverageAnalysis averageAnalysis;
    double average = averageAnalysis.analyze(values);

    double sum = 0;
    foreach(Point value, values.points())
    {
        sum += qPow(value - average, 2.0);
    }

    double result = sum / (values.count() - 1.0);
    result = qSqrt(result);

    return result;
}

StandardDeviationAnalysis *StandardDeviationAnalysis::clone()
{
    return  new StandardDeviationAnalysis(*this);
}
