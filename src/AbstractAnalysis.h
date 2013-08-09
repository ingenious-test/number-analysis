#ifndef ABSTRACTANALYSIS_H

#define ABSTRACTANALYSIS_H

#include <QtCore>

typedef QString ID;
typedef double Point;

class PointList : public QList<Point>
{
public:
    PointList& appendInc(const Point &t)
    {
        append(t);
        return *this;
    }

    void setID(const ID& id)
    {

    }
};
Q_DECLARE_METATYPE(PointList)

class SequencePointList : public QList<PointList>
{
public:
    SequencePointList& appendInc( ID id, PointList& pointList)
    {
        pointList.setID(id);
        append(pointList);
        return *this;
    }
};
Q_DECLARE_METATYPE(SequencePointList)

typedef QString IDAnalysis;
typedef QList<IDAnalysis> IDAnalysisList;

Q_DECLARE_METATYPE(IDAnalysisList)

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
