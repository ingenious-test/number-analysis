#ifndef ABSTRACTANALYSIS_H

#define ABSTRACTANALYSIS_H

#include <QtCore>

typedef QString IDAnalysis;
typedef QList<IDAnalysis> IDAnalysisList;

typedef QString ID;
typedef QList<ID> IDList;
Q_DECLARE_METATYPE(IDList)

typedef double Point;
typedef QList<Point> PointList;
Q_DECLARE_METATYPE(PointList)
typedef QList<PointList> SequencePointList;
Q_DECLARE_METATYPE(SequencePointList)


class AbstractAnalysis
{
    friend class AverageAnalysis;
    friend class AverageIgnoreNullAnalysis;
    friend class StupidAnalysis;

public:
    static double listSum(const PointList &list);

    virtual double analyze(const PointList &list) const = 0;
    virtual AbstractAnalysis* clone() = 0;

    virtual bool isValid();

    IDAnalysis id();

protected:
    AbstractAnalysis(const IDAnalysis &id);

private:
    IDAnalysis id_;
};

Q_DECLARE_METATYPE(AbstractAnalysis*)

#endif // ABSTRACTANALYSIS_H
