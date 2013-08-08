#include "TAnalysisCollection.h"

TAnalysisCollection::TAnalysisCollection()
{
}

void TAnalysisCollection::TestAnalyzeAnalysis_data()
{
    QTest::addColumn<AnalysisList>("analyzes");
    QTest::addColumn<PointList>("list");
    QTest::addColumn<AnalysisResult>("result");

    QTest::newRow("empty-collection") << AnalysisList()
                                      << PointList()
                                      << AnalysisResult();

    QTest::newRow("stupid-analysis-collection") << AnalysisList()
                                                   .insertInc(new StupidAnalysis(1.0))
                                                << (PointList())
                                                << (AnalysisResult()
                                                    .insertInc(StupidAnalysis().name(), 1.0));

    QTest::newRow("stupid-average-analysis-collection") << AnalysisList()
                                                           .insertInc(new StupidAnalysis(1.0))
                                                           .insertInc(new AverageAnalysis())
                                                        << (PointList() << 5.0 << 9.0 << 14.0)
                                                        << (AnalysisResult()
                                                            .insertInc(StupidAnalysis().name(), 1.0)
                                                            .insertInc(AverageAnalysis().name(), (5.0 + 9.0 + 14.0)/3.0));
    QTest::newRow("all-analysis-collection") << AnalysisList()
                                                .insertInc(new StupidAnalysis(1.0))
                                                .insertInc(new AverageAnalysis())
                                                .insertInc(new AverageIgnoreNullAnalysis())
                                             << (PointList() << 5.0 << 0.0 << 9.0 << 14.0)
                                             << (AnalysisResult()
                                                 .insertInc(StupidAnalysis().name(), 1.0)
                                                 .insertInc(AverageAnalysis().name(), (5.0 + 0.0 + 9.0 + 14.0) / 4.0)
                                                 .insertInc(AverageIgnoreNullAnalysis().name(), (5.0 + 9.0 + 14.0) / 3.0));

}

void TAnalysisCollection::TestAnalyzeAnalysis()
{
    QFETCH(AnalysisList, analyzes);
    QFETCH(PointList, list);
    QFETCH(AnalysisResult, result);

    AnalysisCollection collection(analyzes);


    foreach(AbstractAnalysis* item, analyzes.values())
    {
        delete item;
    }
    analyzes.clear();

    const AnalysisResult actualResult = collection.analyze(list);
    const AnalysisResult expectedResult = result;

    QCOMPARE(actualResult, expectedResult);

}

void TAnalysisCollection::TestAnalyzeAnalysisAddRemove_data()
{
    QTest::addColumn<AnalysisList>("analyzes");
    QTest::addColumn<int>("length");
    QTest::addColumn<IDList>("nameList");


    QTest::newRow("empty-collection") << AnalysisList() << 0 << IDList();


    QTest::newRow("stupid-analysis-collection")
            << AnalysisList()
               .insertInc(new StupidAnalysis())
            << 1
            << (IDList() << "stupid");

    QTest::newRow("stupid-avarage-analysis-collection-added")
            << AnalysisList()
                .insertInc(new StupidAnalysis())
                .insertInc(new AverageAnalysis())
            << 2
            << (IDList() << "stupid" << "average");

    QTest::newRow("all-analysis-collection-added")
            << AnalysisList()
                .insertInc(new StupidAnalysis())
                .insertInc(new AverageAnalysis())
                .insertInc(new AverageIgnoreNullAnalysis())
            << 3
            << (IDList() << "stupid" << "average" << "average-ignore-null");


}

void TAnalysisCollection::TestAnalyzeAnalysisAddRemove()
{
    QFETCH(AnalysisList, analyzes);
    QFETCH(int, length);
    QFETCH(IDList, nameList);

    AnalysisCollection collection(analyzes);

    foreach(AbstractAnalysis* item, analyzes.values())
    {
        delete item;
    }
    analyzes.clear();

    const int actualLength = collection.size();
    const int expectedLength = length;

    QCOMPARE(actualLength, expectedLength);

    const IDList actualNames = collection.getNameList();
    const IDList expectedNames = nameList;

    QCOMPARE(actualNames, expectedNames);
}
