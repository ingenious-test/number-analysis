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
    foreach(AbstractAnalysis* item, collection.analysisTable_)
    {
        addAnalysis(item->clone());
    }
}


AnalysisCollection::~AnalysisCollection()
{
    removeAllAnalysis();
}

AnalysisResult AnalysisCollection::analyze(const PointList &list) const
{
    AnalysisResult analysisResult;

    foreach(AbstractAnalysis* item, analysisTable_)
    {
        analysisResult.insert(item->id(), item->analyze(list));
    }

    return analysisResult;
}

void AnalysisCollection::addAnalysis(AbstractAnalysis *analysis)
{
    if(!analysis->isValid())
    {
        qWarning() << "Not valid analysis";
        return ;
    }

    int index = indexOfAnalysis(analysis->id());

    if(index > -1)
    {
        qWarning() << QString("Analysis %1 already exists").arg(analysis->id());
        return ;
    }

    analysisTable_.append(analysis->clone());
}

int AnalysisCollection::indexOfAnalysis(const IDAnalysis &idAnalysis)
{
    for(int i = 0; i < analysisTable_.size(); i++)
    {
        if(analysisTable_.at(i)->id() == idAnalysis)
        {
            return i;
        }
    }
    return -1;
}


void AnalysisCollection::removeAnalysis(const int index)
{
    bool isValidIndex = (index > -1) && (index < analysisTable_.size());
    if(isValidIndex)
    {
        delete analysisTable_[index];
        analysisTable_.removeAt(index);
    }
    else
    {
        qWarning("incorrect index");
    }
}

void AnalysisCollection::removeAllAnalysis()
{
    for(int i = (analysisTable_.size() - 1); i >= 0 ; i--)
    {
        removeAnalysis(i);
    }
}

const IDAnalysisList AnalysisCollection::getIDList() const
{    
    IDAnalysisList list;

    foreach (AbstractAnalysis* analysis, analysisTable_)
    {
        list.append(analysis->id());
    }

    return list;
}

const int AnalysisCollection::size() const
{
    return analysisTable_.size();
}

AnalysisCollection *AnalysisCollection::clone()
{
    return new AnalysisCollection(*this);
}
