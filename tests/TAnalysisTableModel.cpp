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
    QTest::addColumn< QList<AnalysisResult> >("results");

    QTest::newRow("null") << AnalysisTableModel() << 0 << 0 << IDList() << QList<AnalysisResult>();

    QTest::newRow("stupid-collection") << AnalysisTableModel(
                                              AnalysisCollection(AnalysisList() << new StupidAnalysis(1.0)),
                                              (QList<PointList>())
                                              << (PointList() << 2.0 << 3.0) << (PointList() << 1.0 << 2.0 << 4.0))
                                       << 2
                                       << 1
                                       << (IDList() << "stupid")
                                       << (QList<AnalysisResult>()
                                           << (AnalysisResult().insertInc(StupidAnalysis().name(), 1.0))
                                           << (AnalysisResult().insertInc(StupidAnalysis().name(), 1.0)));

    QTest::newRow("stupid-average-analysis-collection") << AnalysisTableModel(AnalysisList()
                                                                              << new StupidAnalysis(1.0) << new AverageAnalysis(),
                                                                              (QList<PointList>() << (PointList() << 2.0 << 3.0) << (PointList() << 1.0 << 2.0 << 4.0)))
                                                        << 2
                                                        << 2
                                                        << (IDList() << "stupid" << "average")
                                                        << (QList<AnalysisResult>()
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
    QFETCH(QList<AnalysisResult>, results);


    const int actualPontListCount = model.rowCount();
    const int expectedPontListCount = pontlistCount;

    QCOMPARE(actualPontListCount, expectedPontListCount);

    const int actualAnalyzesCount = model.columnCount();
    const int expectedAnalyzesCount = analyzesCount;

    QCOMPARE(actualAnalyzesCount, expectedAnalyzesCount);

    const IDList actualNames = model.getHeaders();
    const IDList expectedNames = nameList;

    QCOMPARE(actualNames, expectedNames);

    const QList<AnalysisResult> actualResult = model.analyze();
    const QList<AnalysisResult> expectedResult = results;

    QCOMPARE(actualResult, expectedResult);
}
