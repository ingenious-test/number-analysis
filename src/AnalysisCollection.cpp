#include "AnalysisCollection.h"

AnalysisCollection::AnalysisCollection()
{
}

AnalysisCollection::AnalysisCollection(QList<AbstractAnalysis *> analyzes)
{
}

AnalysisResult AnalysisCollection::analyze(const PointList &list) const
{
    return AnalysisResult();
}
