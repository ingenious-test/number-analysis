#include "StandardDeviationAnalysis.h"

StandardDeviationAnalysis::StandardDeviationAnalysis() :
     AbstractAnalysis("standard-deviation")
{
}

StandardDeviationAnalysis::StandardDeviationAnalysis(const StandardDeviationAnalysis &a):
AbstractAnalysis("standard-deviation")
{
}

double StandardDeviationAnalysis::analyze(const PointList &values) const
{
    return 0.0;
}

StandardDeviationAnalysis *StandardDeviationAnalysis::clone()
{
    return  new StandardDeviationAnalysis(*this);
}
