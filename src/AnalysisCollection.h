#ifndef ANALYSISCOLLECTION_H

#define ANALYSISCOLLECTION_H

#include "AbstractAnalysis.h"

class AnalysisResult : public QHash<QString, double>
{
public:
    AnalysisResult& insertInc(const ID &name, const double &value)
    {
        insert(name, value);
        return *this;
    }
};
Q_DECLARE_METATYPE(AnalysisResult)

typedef QList<AbstractAnalysis*> AnalysisList;
Q_DECLARE_METATYPE(AnalysisList)

class AnalysisCollection
{
public:
    AnalysisCollection();
    AnalysisCollection(AnalysisList analyzes);

    ~AnalysisCollection();

    AnalysisResult analyze(const PointList &list) const;

    AnalysisCollection& addAnalysis(AbstractAnalysis *analysis);

    void removeAnalysis(const QString &name);
    void removeAll();

    const IDList getNameList();

    const int size();

    AnalysisCollection* clone();


private:
    QHash<QString, AbstractAnalysis*> analysisTable_;


};

#endif // ANALYSISCOLLECTION_H
