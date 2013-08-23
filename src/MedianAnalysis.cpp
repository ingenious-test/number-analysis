#include "MedianAnalysis.h"

MedianAnalysis::MedianAnalysis():
    AbstractAnalysis("median")
{

}

MedianAnalysis::MedianAnalysis(const MedianAnalysis &a):
    AbstractAnalysis("median")
{
}

double MedianAnalysis::analyze(const PointList &values) const
{
    return 0.0;
}

MedianAnalysis *MedianAnalysis::clone()
{
    return new MedianAnalysis(*this);
}
