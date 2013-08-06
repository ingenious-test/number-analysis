#include "StupidAnalysis.h"

StupidAnalysis::StupidAnalysis(const double value) :
    value_(value)
{
}

double StupidAnalysis::analyze()
{
    return value_;
}
