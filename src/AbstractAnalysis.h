#ifndef ABSTRACTANALYSIS_H

#define ABSTRACTANALYSIS_H

#include <QtCore>

class AbstractAnalysis
{
    friend class AverageAnalisys;
    friend class AverangeIgnoreNullAnalisys;
    friend class StupidAnalysis;

public:
    static double listSum(const QList<double> list);

    virtual double analyze(const QList<double> &list) const = 0;

protected:
    AbstractAnalysis();
};

#endif // ABSTRACTANALYSIS_H
