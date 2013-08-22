#include "AbstractAnalysis.h"

AbstractAnalysis::AbstractAnalysis(const IDAnalysis &id) :
    id_(id)
{

}

double AbstractAnalysis::listSum(const PointList &list)
{
    double sum = 0.0;
    foreach(const Point e, list.points())
    {
        sum += e;
    }
    return sum;
}

bool AbstractAnalysis::isValid() const
{
    return !id_.isEmpty();
}


IDAnalysis AbstractAnalysis::id() const
{
    return id_;
}
