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

StupidAnalysis::StupidAnalysis(const StupidAnalysis &a)
    :
       AbstractAnalysis("stupid"),
       value_(a.value_)
{

}

double StupidAnalysis::analyze(const PointList &list) const
{
    return value_;
}

StupidAnalysis *StupidAnalysis::clone()
{
    return new StupidAnalysis(*this);
}
