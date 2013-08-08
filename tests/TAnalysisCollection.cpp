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

    QTest::newRow("stupid-analysis-collection") << AnalysisCollection(AnalysisList()
                                                                      << new StupidAnalysis(1.0))
                                                << (PointList() << 11.0 << 12.0 << 13.0)
                                                << (AnalysisResult()
                                                    .insertInc(StupidAnalysis().name(), 1.0));

    QTest::newRow("stupid-average-analysis-collection") << AnalysisCollection(AnalysisList()
                                                                              << new StupidAnalysis(1.0) << new AverageAnalysis())
                                                        << (PointList() << 5.0 << 9.0 << 14.0)
                                                        << (AnalysisResult()
                                                            .insertInc(StupidAnalysis().name(), 1.0)
                                                            .insertInc(AverageAnalysis().name(), (5.0 + 9.0 + 14.0)/3.0));
    QTest::newRow("all-analysis-collection") << AnalysisCollection(AnalysisList()
                                                                   << new StupidAnalysis(1.0)
                                                                   << new AverageAnalysis()
                                                                   << new AverageIgnoreNullAnalysis())
                                             << (PointList() << 5.0 << 0.0 << 9.0 << 14.0)
                                             << (AnalysisResult()
                                                 .insertInc(StupidAnalysis().name(), 1.0)
                                                 .insertInc(AverageAnalysis().name(), (5.0 + 0.0 + 9.0 + 14.0) / 4.0)
                                                 .insertInc(AverageIgnoreNullAnalysis().name(), (5.0 + 9.0 + 14.0) / 3.0));

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

void TAnalysisCollection::TestAnalyzeAnalysisAddRemove_data()
{
    QTest::addColumn<AnalysisCollection>("collection");
    QTest::addColumn<int>("length");
    QTest::addColumn<IDList>("nameList");


    QTest::newRow("empty-collection") << AnalysisCollection() << 0 << IDList();

    AnalysisCollection test1;
    StupidAnalysis* stupidAnalysis = new StupidAnalysis;
    test1.addAnalysis(static_cast<AbstractAnalysis*>(stupidAnalysis));

    QTest::newRow("stupid-analysis-collection-added")
            << test1
            << 1
            << (IDList() << "stupid");

    test1.removeAll();

    QTest::newRow("stupid-analysis-collection-removed")
            << test1
            << 0
            << IDList();


    AverageAnalysis* averageAnalysis = new AverageAnalysis;

    test1.addAnalysis(static_cast<AbstractAnalysis*>(stupidAnalysis));
    test1.addAnalysis(static_cast<AbstractAnalysis*>(averageAnalysis));


    QTest::newRow("stupid-avarage-analysis-collection-added")
            << test1
            << 2
            << (IDList() << "stupid" << "average");


    test1.removeAll();

    QTest::newRow("stupid-avarage-analysis-collection-removed")
            << test1
            << 0
            << IDList();

    delete stupidAnalysis;
    delete averageAnalysis;

}

void TAnalysisCollection::TestAnalyzeAnalysisAddRemove()
{
    QFETCH(AnalysisCollection, collection);
    QFETCH(int, length);
    QFETCH(IDList, nameList);

    const int actualLength = collection.length();
    const int expectedLength = length;

    QCOMPARE(actualLength, expectedLength);

    const IDList actualNames = collection.getNameList();
    const IDList expectedNames = nameList;

    QCOMPARE(actualNames, expectedNames);
}
