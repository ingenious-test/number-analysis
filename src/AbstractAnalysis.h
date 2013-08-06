#ifndef ABSTRACTANALYSIS_H

#define ABSTRACTANALYSIS_H

#include <QtCore>

typedef double Point;
typedef QList<Point> PointList;

Q_DECLARE_METATYPE(PointList)

class AbstractAnalysis
{
    friend class AverageAnalisys;
    friend class AverangeIgnoreNullAnalisys;
    friend class StupidAnalysis;

public:
    static double listSum(const PointList &list);

    virtual double analyze(const PointList &list) const = 0;

protected:
    AbstractAnalysis();
};

#endif // ABSTRACTANALYSIS_H
