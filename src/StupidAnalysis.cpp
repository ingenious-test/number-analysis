#include "StupidAnalysis.h"

StupidAnalysis::StupidAnalysis(const double value) :
    value_(value)
{
}

double StupidAnalysis::analyze(const QList<double> &list) const
{
    return value_;
}
