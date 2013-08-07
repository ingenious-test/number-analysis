#include "StupidAnalysis.h"

StupidAnalysis::StupidAnalysis() :
    AbstractAnalysis("stupid")
{

}

StupidAnalysis::StupidAnalysis(const StupidAnalysis &a)
    :
       AbstractAnalysis("stupid")
{

}

double StupidAnalysis::analyze(const PointList &list) const
{
    return listSum(list);
}

StupidAnalysis *StupidAnalysis::clone()
{
    return new StupidAnalysis(*this);
}
