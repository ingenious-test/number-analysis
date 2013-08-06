#include "StupidAnalysis.h"

StupidAnalysis::StupidAnalysis(const Point value) :
    value_(value)
{
}

double StupidAnalysis::analyze(const PointList &list) const
{
    return value_;
}
