#include "StupidAnalysis.h"

StupidAnalysis::StupidAnalysis() :
    AbstractAnalysis("stupid"),
    value_(0.0)
{

}

StupidAnalysis::StupidAnalysis(const Point value) :
    AbstractAnalysis("stupid"),
    value_(value)
{
}

double StupidAnalysis::analyze(const PointList &list) const
{
    return value_;
}
