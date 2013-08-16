#ifndef ANALYSISCOLLECTION_H

#define ANALYSISCOLLECTION_H

#include "AbstractAnalysis.h"

class AnalysisResult : public QHash<IDAnalysis, double>
{
public:
    AnalysisResult& insertInc(const IDAnalysis &name, const double &value)
    {
        if(contains(name))
        {
            remove(name);
        }

        insert(name, value);
        return *this;
    }
};


class AnalysisResults : public QHash<ID, AnalysisResult>
{
public:
    AnalysisResults& insertInc(const ID &id, const AnalysisResult &analysisResult)
    {
        if(contains(id))
        {
            remove(id);
        }

        insert(id, analysisResult);
        return *this;
    }
};



typedef QList<AbstractAnalysis*> AnalysisList;


class AnalysisCollection
{
    friend class AnalysisTableModel;

public:
    AnalysisCollection();
    AnalysisCollection(AnalysisList analyzes);

    ~AnalysisCollection();

    AnalysisResult analyze(const PointList &list) const;

    void addAnalysis(AbstractAnalysis *analysis);
    int indexOfAnalysis(const IDAnalysis& idAnalysis);
    void removeAnalysis(const int index);
    void removeAllAnalysis();

    const IDAnalysisList getIDList() const;
    const IDAnalysis getIDAt(const int index) const;

    const int size() const;

    AnalysisCollection* clone();


private:
    AnalysisCollection(const AnalysisCollection& collection);
    AnalysisList analysisTable_;


};

#endif // ANALYSISCOLLECTION_H
