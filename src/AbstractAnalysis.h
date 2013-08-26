#ifndef ABSTRACTANALYSIS_H

#define ABSTRACTANALYSIS_H

#include "SequencePointList.h"

typedef QString IDAnalysis;
typedef QList<IDAnalysis> IDAnalysisList;

class AbstractAnalysis
{
    friend class AverageAnalysis;
    friend class AverageIgnoreNullAnalysis;
    friend class StupidAnalysis;

public:
    static double listSum(const PointList &list);

    virtual double analyze(const PointList &list) const = 0;
    virtual AbstractAnalysis* clone() = 0;

    virtual bool isValid() const;

    IDAnalysis id() const;

protected:
    AbstractAnalysis(const IDAnalysis &id);

private:
    IDAnalysis id_;
};

#endif // ABSTRACTANALYSIS_H
