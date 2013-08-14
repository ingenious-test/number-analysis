#include "BAnalysisCollections.h"

BAnalysisCollections::BAnalysisCollections(const int nRuns) :
    nRuns_(nRuns)
{
}

void BAnalysisCollections::run()
{
    for(int i = 0; i < nRuns_; ++i)
    {
        AnalysisCollection collection;

        StupidAnalysis *analysis = new StupidAnalysis(0.0);

        collection.addAnalysis(analysis);

        delete analysis;

        collection.analyze(PointList());

        qDebug() << QString("iteration : " + QString::number(i)).toLocal8Bit();
    }
}
