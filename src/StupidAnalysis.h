#ifndef STUPIDANALYSIS_H

#define STUPIDANALYSIS_H

#include "AbstractAnalysis.h"

class StupidAnalysis : public AbstractAnalysis
{
public:
    StupidAnalysis();
    StupidAnalysis(const Point value);
    StupidAnalysis(const StupidAnalysis &a);

    double analyze(const PointList &list) const;
    StupidAnalysis* clone();


private:
    Point value_;
};

Q_DECLARE_METATYPE(StupidAnalysis*)

#endif // STUPIDANALYSIS_H
