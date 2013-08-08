#include "TAnalysisTableModel.h"

TAnalysisTableModel::TAnalysisTableModel()
{

}

void TAnalysisTableModel::TestAddRemove_data()
{
    QTest::addColumn<AnalysisList>("analyzes");
    QTest::addColumn<SequencePointList>("list");
    QTest::addColumn<IDList>("nameList");
    QTest::addColumn< AnalysisResults >("results");

    QTest::newRow("null")
            << AnalysisList()
            << SequencePointList()
            << IDList()
            << AnalysisResults();


    QTest::newRow("stupid-collection") << AnalysisList()
                                          .insertInc(new StupidAnalysis(1.0))
                                       << (SequencePointList()
                                           << (PointList() << 2.0 << 3.0) << (PointList() << 1.0 << 2.0 << 4.0))
                                       << (IDList() << "stupid")
                                       << (AnalysisResults()
                                           << (AnalysisResult().insertInc(StupidAnalysis().name(), 1.0))
                                           << (AnalysisResult().insertInc(StupidAnalysis().name(), 1.0)));

    QTest::newRow("stupid-average-analysis-collection") << AnalysisList()
                                                           .insertInc(new StupidAnalysis(1.0))
                                                           .insertInc(new AverageAnalysis())
                                                        << (SequencePointList()
                                                            << (PointList() << 2.0 << 3.0) << (PointList() << 1.0 << 2.0 << 4.0))
                                                        << (IDList() << "stupid" << "average")
                                                        << (AnalysisResults()
                                                            << (AnalysisResult().insertInc(StupidAnalysis().name(), 1.0)
                                                                .insertInc(AverageAnalysis().name(), (2.0 + 3.0) / 2.0))
                                                            << (AnalysisResult().insertInc(StupidAnalysis().name(), 1.0))
                                                            .insertInc(AverageAnalysis().name(), (1.0 + 2.0 + 4.0) / 3.0));

}

void TAnalysisTableModel::TestAddRemove()
{
    QFETCH(AnalysisList, analyzes);
    QFETCH(SequencePointList, list);
    QFETCH(IDList, nameList);
    QFETCH(AnalysisResults, results);


    AnalysisCollection collection(analyzes);

    foreach(AbstractAnalysis* item, analyzes.values())
    {
        delete item;
    }
    analyzes.clear();

    AnalysisTableModel model(collection, list);
    model.analyze();


    const int actualPontListCount = model.rowCount();
    const int expectedPontListCount = list.size();

    QCOMPARE(actualPontListCount, expectedPontListCount);

    const int actualAnalyzesCount = model.columnCount();
    const int expectedAnalyzesCount = collection.size();

    QCOMPARE(actualAnalyzesCount, expectedAnalyzesCount);

    const IDList actualNames = model.getHeaders();
    const IDList expectedNames = nameList;

    QCOMPARE(actualNames, expectedNames);


    const AnalysisResults actualResult = model.Results();
    const AnalysisResults expectedResult = results;

    QCOMPARE(actualResult, expectedResult);

    AnalysisResults resultModel;
    for(int i = 0; i < model.rowCount(); i++)
    {
        AnalysisResult result;
        for(int j = 0; j < model.columnCount(); j++)
        {
            result.insert(model.headerData(j).toString(), model.data(model.index(i, j)).toDouble());
        }

        if(!result.isEmpty())
        {
            resultModel.append(result);
        }
    }
    const AnalysisResults actualResultData = resultModel;
    const AnalysisResults expectedResultData = results;

    QCOMPARE(actualResultData, expectedResultData);
}
