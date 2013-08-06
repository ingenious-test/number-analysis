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

QString AbstractAnalysis::name()
{
    return name_;
}

AbstractAnalysis::AbstractAnalysis(const QString &name) :
    name_(name)
{

}
