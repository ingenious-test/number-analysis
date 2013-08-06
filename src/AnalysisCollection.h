#ifndef ANALYSISCOLLECTION_H

#define ANALYSISCOLLECTION_H

#include "AbstractAnalysis.h"

class AnalysisResult : public QHash<QString, double>
{
public:
    AnalysisResult& insertInc(const QString &name, const double &value)
    {
        insert(name, value);
        return *this;
    }
};
Q_DECLARE_METATYPE(AnalysisResult)

class AnalysisCollection
{
public:
    AnalysisCollection();
    AnalysisCollection(QList<AbstractAnalysis*> analyzes);

    AnalysisResult analyze(const PointList &list) const;
};
Q_DECLARE_METATYPE(AnalysisCollection)

#endif // ANALYSISCOLLECTION_H
