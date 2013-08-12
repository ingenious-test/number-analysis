#include "AbstractAnalysis.h"

AbstractAnalysis::AbstractAnalysis(const IDAnalysis &id) :
    id_(id)
{

}

double AbstractAnalysis::listSum(const PointList &list)
{
    double sum = 0.0;
    foreach(const Point e, list)
    {
        sum += e;
    }
    return sum;
}

bool AbstractAnalysis::isValid()
{
    return !id_.isEmpty();
}


IDAnalysis AbstractAnalysis::id()
{
    return id_;
}
