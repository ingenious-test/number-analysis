#include "AnalysisCollection.h"

AnalysisCollection::AnalysisCollection()
{
}

AnalysisCollection::AnalysisCollection(AnalysisList analyzes)
{
    foreach(AbstractAnalysis* item, analyzes)
    {
        addAnalysis(item);
    }
}

AnalysisCollection::~AnalysisCollection()
{
    removeAll();
}

AnalysisResult AnalysisCollection::analyze(const PointList &list) const
{
    if(list.isEmpty())
    {
        return AnalysisResult();
    }

    if(analysisList_.empty())
    {
        return AnalysisResult();
    }

    AnalysisResult analysisResult;

    foreach(AbstractAnalysis* item, analysisList_)
    {
       analysisResult.insert(item->name(), item->analyze(list));
    }

    return analysisResult;
}

bool AnalysisCollection::isAdded(AbstractAnalysis *analysis)
{
    foreach(AbstractAnalysis* item, analysisList_)
    {
        if(item->name() == analysis->name()) return true;
    }

    return false;
}

void AnalysisCollection::addAnalysis(AbstractAnalysis *analysis)
{
    if(!isAdded(analysis))
    {
        analysisList_.append(analysis->clone());
    }
}

void AnalysisCollection::removeAnalysis(const int i)
{
    bool isValid_ = (i > 1) && (i < analysisList_.length());
    if(isValid_)
    {
        analysisList_.removeAt(i);
    }
}

void AnalysisCollection::removeAll()
{
    for(int i; i < analysisList_.length(); i++)
    {
        delete analysisList_.at(i);
    }

    analysisList_.clear();
}

const IDList AnalysisCollection::getNameList()
{
    IDList list;

    foreach(AbstractAnalysis* item, analysisList_)
    {
        list.append(item->name());
    }

    return list;
}

const int AnalysisCollection::length()
{
    return analysisList_.length();
}
