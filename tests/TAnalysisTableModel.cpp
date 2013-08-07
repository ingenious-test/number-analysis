#include "TAnalysisTableModel.h"

TAnalysisTableModel::TAnalysisTableModel()
{

}

void TAnalysisTableModel::TestAddRemove_data()
{
    QTest::addColumn<AnalysisTableModel>("model");
    QTest::addColumn<int>("pontlistCount");
    QTest::addColumn<int>("analyzesCount");
    QTest::addColumn<IDList>("nameList");
    QTest::addColumn< AnalysisResults >("results");

    QTest::newRow("null")
            << AnalysisTableModel()
            << 0 << 0
            << IDList()
            << AnalysisResults();

    QTest::newRow("stupid-collection") << AnalysisTableModel(
                                              new AnalysisCollection(AnalysisList() << new StupidAnalysis(1.0)),
                                              (SequencePointList())
                                              << (PointList() << 2.0 << 3.0) << (PointList() << 1.0 << 2.0 << 4.0))
                                       << 2
                                       << 1
                                       << (IDList() << "stupid")
                                       << (AnalysisResults()
                                           << (AnalysisResult().insertInc(StupidAnalysis().name(), 1.0))
                                           << (AnalysisResult().insertInc(StupidAnalysis().name(), 1.0)));

    QTest::newRow("stupid-average-analysis-collection") << AnalysisTableModel(
                                                               new AnalysisCollection(AnalysisList()
                                                                                      << new StupidAnalysis(1.0) << new AverageAnalysis()),
                                                                                      (SequencePointList() << (PointList() << 2.0 << 3.0) << (PointList() << 1.0 << 2.0 << 4.0)))
                                                        << 2
                                                        << 2
                                                        << (IDList() << "stupid" << "average")
                                                        << (AnalysisResults()
                                                            << (AnalysisResult().insertInc(StupidAnalysis().name(), 1.0)
                                                                .insertInc(AverageAnalysis().name(), (2.0 + 3.0) / 2.0))
                                                            << (AnalysisResult().insertInc(StupidAnalysis().name(), 1.0))
                                                            .insertInc(AverageAnalysis().name(), (1.0 + 2.0 + 4.0) / 3.0));
}

void TAnalysisTableModel::TestAddRemove()
{
    QFETCH(AnalysisTableModel, model);
    QFETCH(int, pontlistCount);
    QFETCH(int, analyzesCount);
    QFETCH(IDList, nameList);
    QFETCH(AnalysisResults, results);

    model.analyze();

    const int actualPontListCount = model.rowCount();
    const int expectedPontListCount = pontlistCount;

    QCOMPARE(actualPontListCount, expectedPontListCount);

    const int actualAnalyzesCount = model.columnCount();
    const int expectedAnalyzesCount = analyzesCount;

    QCOMPARE(actualAnalyzesCount, expectedAnalyzesCount);

    const IDList actualNames = model.getHeaders();
    const IDList expectedNames = nameList;

    QCOMPARE(actualNames, expectedNames);

    const AnalysisResults actualResult = model.Results();
    const AnalysisResults expectedResult = results;

    QCOMPARE(actualResult, expectedResult);
}
