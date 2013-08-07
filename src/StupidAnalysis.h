#ifndef STUPIDANALYSIS_H

#define STUPIDANALYSIS_H

#include "AbstractAnalysis.h"

class StupidAnalysis : public AbstractAnalysis
{
public:
    StupidAnalysis();
    StupidAnalysis(const StupidAnalysis &a);

    double analyze(const PointList &list) const;
    StupidAnalysis* clone();
};

Q_DECLARE_METATYPE(StupidAnalysis*)

#endif // STUPIDANALYSIS_H
