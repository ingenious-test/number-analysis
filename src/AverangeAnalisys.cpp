#include "AverangeAnalisys.h"

AverangeAnalisys::AverangeAnalisys()
{
}

double AverangeAnalisys::analyze(const QList<double> &values)
{
    if(values.isEmpty())
    {
        return 0;
    }

    double sum = 0.0;

    foreach(const double value, values)
    {
        sum += value;
    }

    const double result = sum / static_cast<double>(values.length());

    return result;
}
