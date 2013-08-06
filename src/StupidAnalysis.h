#ifndef STUPIDANALYSIS_H

#define STUPIDANALYSIS_H

#include "AbstractAnalysis.h"

class StupidAnalysis : public AbstractAnalysis
{
public:
    StupidAnalysis(const Point value);

    double analyze(const PointList &list) const;

private:
    Point value_;
};

#endif // STUPIDANALYSIS_H
