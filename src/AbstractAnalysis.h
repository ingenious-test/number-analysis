#ifndef ABSTRACTANALYSIS_H

#define ABSTRACTANALYSIS_H

#include <QtCore>

typedef double Point;
typedef QList<Point> PointList;

typedef QString IDAnalysis;
typedef QList<IDAnalysis> IDList;

Q_DECLARE_METATYPE(PointList)
Q_DECLARE_METATYPE(IDList)

class AbstractAnalysis
{
    friend class AverageAnalysis;
    friend class AverageIgnoreNullAnalysis;
    friend class StupidAnalysis;

public:
    static double listSum(const PointList &list);

    virtual double analyze(const PointList &list) const = 0;
    virtual AbstractAnalysis* clone() = 0;

    IDAnalysis name();

protected:
    AbstractAnalysis(const IDAnalysis &name);

private:
    IDAnalysis name_;
};

Q_DECLARE_METATYPE(AbstractAnalysis*)

#endif // ABSTRACTANALYSIS_H
