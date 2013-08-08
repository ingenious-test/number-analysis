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


IDAnalysis AbstractAnalysis::name()
{
    return name_;
}

AbstractAnalysis::AbstractAnalysis(const IDAnalysis &name) :
    name_(name)
{

}
