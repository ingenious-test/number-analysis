#ifndef STANDARDDEVIATIONANALYSIS_H

#define STANDARDDEVIATIONANALYSIS_H

#include "AbstractAnalysis.h"
#include "AverageAnalysis.h"

class StandardDeviationAnalysis : public AbstractAnalysis
{
public:
    StandardDeviationAnalysis();

    StandardDeviationAnalysis(const StandardDeviationAnalysis &a);


    double analyze(const PointList &values) const;
    StandardDeviationAnalysis* clone();
};

#endif // STANDARDDEVIATIONANALYSIS_H
