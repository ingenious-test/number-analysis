#include "AverangeIgnoreNullAnalisys.h"

AverangeIgnoreNullAnalisys::AverangeIgnoreNullAnalisys()
{
}

double AverangeIgnoreNullAnalisys::analyze(const QList<double> &values) const
{
    if(values.isEmpty())
    {
        return 0;
    }

    const double sum = AbstractAnalysis::listSum(values);
    int length = 0;

    foreach(const double value, values)
    {
        if(value != 0)
        {
            length++;
        }
    }

    const double result = sum / static_cast<double>(length);

    return result;
}
