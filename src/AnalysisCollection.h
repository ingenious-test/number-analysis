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

class AnalysisCollection
{
public:
    AnalysisCollection();
    AnalysisCollection(const AnalysisCollection& collection);
    AnalysisCollection(AnalysisList analyzes);

    ~AnalysisCollection();

    AnalysisResult analyze(const PointList &list) const;

    bool isAdded(AbstractAnalysis *analysis);
    void addAnalysis(AbstractAnalysis *analysis);

    void removeAnalysis(const int i);
    void removeAll();

    const IDList getNameList();

    const int length();

    AnalysisCollection* clone();


private:
    AnalysisList analysisList_;

};
Q_DECLARE_METATYPE(AnalysisCollection)

#endif // ANALYSISCOLLECTION_H
