#ifndef STUPIDANALYSIS_H

#define STUPIDANALYSIS_H

#include "AbstractAnalysis.h"

class StupidAnalysis : public AbstractAnalysis
{
public:
    StupidAnalysis(const double value);

    double analyze(const QList<double> &list) const;

private:
    double value_;
};

#endif // STUPIDANALYSIS_H
