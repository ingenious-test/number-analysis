#include "TAnalysisCollection.h"

TAnalysisCollection::TAnalysisCollection()
{
}

void TAnalysisCollection::TestAnalyzeAnalysis_data()
{
    QTest::addColumn<AnalysisCollection>("collection");
    QTest::addColumn<PointList>("list");
    QTest::addColumn<AnalysisResult>("result");

    QTest::newRow("empty-collection") << AnalysisCollection()
                                      << PointList()
                                      << AnalysisResult();

    QTest::newRow("stupid-analysis-collection") << AnalysisCollection(QList<AbstractAnalysis*>()
                                                                      << new StupidAnalysis(1.0))
                                                << PointList()
                                                << (AnalysisResult()
                                                    .insertInc(StupidAnalysis().name(), 1.0));
}

void TAnalysisCollection::TestAnalyzeAnalysis()
{
    QFETCH(AnalysisCollection, collection);
    QFETCH(PointList, list);
    QFETCH(AnalysisResult, result);

    const AnalysisResult actualResult = collection.analyze(list);
    const AnalysisResult expectedResult = result;

    QCOMPARE(actualResult, expectedResult);
}
