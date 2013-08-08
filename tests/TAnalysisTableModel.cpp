#include "TAnalysisTableModel.h"

TAnalysisTableModel::TAnalysisTableModel()
{

}

void TAnalysisTableModel::TestAddRemove_data()
{
    QTest::addColumn<AnalysisList>("analyzes");
    QTest::addColumn<SequencePointList>("list");
    QTest::addColumn<IDSet>("idSet");
    QTest::addColumn<IDAnalysisList>("nameList");
    QTest::addColumn< AnalysisResults >("results");

    QTest::newRow("null")
            << AnalysisList()
            << SequencePointList()
            << IDSet()
            << IDAnalysisList()
            << AnalysisResults();


    QTest::newRow("stupid-collection") << AnalysisList()
                                          .insertInc(new StupidAnalysis(1.0))
                                       << (SequencePointList()
                                           << (PointList() << 2.0 << 3.0) << (PointList() << 1.0 << 2.0 << 4.0))
                                       << IDSet().insertInc("Первый").insertInc("Второй")
                                       << (IDAnalysisList() << "stupid")
                                       << AnalysisResults()
                                          .insertInc("Первый", AnalysisResult().insertInc(StupidAnalysis().name(), 1.0))
                                          .insertInc("Второй", AnalysisResult().insertInc(StupidAnalysis().name(), 1.0));

    QTest::newRow("stupid-average-analysis-collection") << AnalysisList()
                                                           .insertInc(new StupidAnalysis(1.0))
                                                           .insertInc(new AverageAnalysis())
                                                        << (SequencePointList()
                                                            << (PointList() << 2.0 << 3.0) << (PointList() << 1.0 << 2.0 << 4.0))
                                                        << IDSet().insertInc("Первый").insertInc("Второй")
                                                        << (IDAnalysisList() << "stupid" << "average")
                                                        << AnalysisResults()
                                                           .insertInc("Первый", AnalysisResult()
                                                                      .insertInc(StupidAnalysis().name(), 1.0)
                                                                      .insertInc(AverageAnalysis().name(), (2.0 + 3.0) / 2.0))
                                                           .insertInc("Второй", AnalysisResult()
                                                                      .insertInc(StupidAnalysis().name(), 1.0)
                                                                      .insertInc(AverageAnalysis().name(), (1.0 + 2.0 + 4.0) / 3.0));

}

void TAnalysisTableModel::TestAddRemove()
{
    QFETCH(AnalysisList, analyzes);
    QFETCH(SequencePointList, list);
    QFETCH(IDSet, idSet);
    QFETCH(IDAnalysisList, nameList);
    QFETCH(AnalysisResults, results);


    AnalysisCollection collection(analyzes);

    foreach(AbstractAnalysis* item, analyzes.values())
    {
        delete item;
    }
    analyzes.clear();

    AnalysisTableModel model(collection, list);
    model.insertID(idSet);
    model.analyze();


    const int actualPontListCount = model.rowCount();
    const int expectedPontListCount = list.size();

    QCOMPARE(actualPontListCount, expectedPontListCount);

    const int actualAnalyzesCount = model.columnCount();
    const int expectedAnalyzesCount = collection.size() + 1;

    QCOMPARE(actualAnalyzesCount, expectedAnalyzesCount);

    const IDAnalysisList actualNames = model.getHeaders();
    const IDAnalysisList expectedNames = nameList;

    QCOMPARE(actualNames, expectedNames);


    const AnalysisResults actualResult = model.Results();
    const AnalysisResults expectedResult = results;

    QCOMPARE(actualResult, expectedResult);

    AnalysisResults resultModel;
    QList<ID> idList = idSet.toList();

    for(int i = 0; i < model.rowCount(); i++)
    {
        AnalysisResult result;
        for(int j = 1; j < model.columnCount(); j++)
        {
            result.insert(model.headerData(j).toString(), model.data(model.index(i, j)).toDouble());
        }

        if(!result.isEmpty())
        {
            resultModel.insert(idList[i] , result);
        }
    }
    const AnalysisResults actualResultData = resultModel;
    const AnalysisResults expectedResultData = results;

    QCOMPARE(actualResultData, expectedResultData);
}
