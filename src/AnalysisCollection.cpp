#include "AnalysisCollection.h"

AnalysisCollection::AnalysisCollection()
{   
}

AnalysisCollection::AnalysisCollection(AnalysisList analyzes)
{
    foreach(AbstractAnalysis* item, analyzes)
    {
        addAnalysis(item->clone());
    }
}

AnalysisCollection::AnalysisCollection(const AnalysisCollection &collection)
{
    foreach(AbstractAnalysis* item, collection.analysisTable_.values())
    {
        addAnalysis(item->clone());
    }
}


AnalysisCollection::~AnalysisCollection()
{
    removeAll();
}

AnalysisResult AnalysisCollection::analyze(const PointList &list) const
{
    AnalysisResult analysisResult;

    foreach(AbstractAnalysis* item, analysisTable_.values())
    {
        analysisResult.insert(item->name(), item->analyze(list));
    }

    return analysisResult;
}

AnalysisCollection& AnalysisCollection::addAnalysis(AbstractAnalysis *analysis)
{
    const QString name = analysis->name();

    if(analysisTable_.contains(name))
    {
        removeAnalysis(name);
    }

    analysisTable_.insert(name, analysis->clone());

    return *this;
}

void AnalysisCollection::removeAnalysis(const QString &name)
{
    if(analysisTable_.contains(name))
    {
        delete analysisTable_[name];
        analysisTable_.remove(name);
    }
    else
    {
        qWarning("incorrect index");
    }
}

void AnalysisCollection::removeAll()
{
    foreach(const QString &name, analysisTable_.keys())
    {
        removeAnalysis(name);
    }
}

const IDAnalysisList AnalysisCollection::getNameList() const
{    
    return analysisTable_.keys();
}

const int AnalysisCollection::size() const
{
    return analysisTable_.size();
}

AnalysisCollection *AnalysisCollection::clone()
{
    return new AnalysisCollection(*this);
}
