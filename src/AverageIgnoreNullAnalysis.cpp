#include "AverageIgnoreNullAnalysis.h"

AverageIgnoreNullAnalysis::AverageIgnoreNullAnalysis() :
    AbstractAnalysis("average-ignore-null")
{
}

AverageIgnoreNullAnalysis::AverageIgnoreNullAnalysis(const AverageIgnoreNullAnalysis &a):
    AbstractAnalysis("average-ignore-null")
{
}

double AverageIgnoreNullAnalysis::analyze(const PointList &values) const
{
    if(values.isEmpty())
    {
        return 0;
    }

    const double sum = AbstractAnalysis::listSum(values);
    int length = 0;

    foreach(const Point value, values)
    {
        if(value != 0)
        {
            length++;
        }
    }

    const double result = sum / static_cast<double>(length);

    return result;
}

AverageIgnoreNullAnalysis *AverageIgnoreNullAnalysis::clone()
{
    return new AverageIgnoreNullAnalysis(*this);
}
