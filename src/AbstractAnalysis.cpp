#include "AbstractAnalysis.h"

double AbstractAnalysis::listSum(const QList<double> list)
{
    double sum = 0.0;
    foreach(const double e, list)
    {
        sum += e;
    }
    return sum;
}

AbstractAnalysis::AbstractAnalysis()
{
}
