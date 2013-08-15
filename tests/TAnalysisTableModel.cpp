#include "TAnalysisTableModel.h"

TAnalysisTableModel::TAnalysisTableModel()
{

}

void TAnalysisTableModel::TestAddRemoveMoc_data()
{
    QTest::addColumn<AnalysisList>("analyzes");
    QTest::addColumn<IDList>("pointsIDs");
    QTest::addColumn<IDList>("resultPointsIDs");
    QTest::addColumn<IDAnalysisList>("analyzesID");
    QTest::addColumn<AnalysisResults>("analyzesResult");


    QTest::newRow("empty") << AnalysisList() << IDList() << IDList()  << IDAnalysisList() << AnalysisResults();

    QTest::newRow("one") << (AnalysisList()
                             << new StupidAnalysis(1.0)
                             << new AverageAnalysis())
                         << (IDList() << "First")
                         << (IDList() << "First")
                         << (IDAnalysisList() <<StupidAnalysis().id() << AverageAnalysis().id())
                         << AnalysisResults().insertInc("First",
                                                        AnalysisResult().insertInc(StupidAnalysis().id(), 1.0)
                                                        .insertInc(AverageAnalysis().id(), 0.0));

    QTest::newRow("two") << (AnalysisList()
                             << new StupidAnalysis(1.0)
                             << new AverageAnalysis())
                         << (IDList() << "First" << "Second")
                         << (IDList() << "First" << "Second")
                         << (IDAnalysisList() <<StupidAnalysis().id() << AverageAnalysis().id())
                         << AnalysisResults().insertInc("First",
                                                        AnalysisResult().insertInc(StupidAnalysis().id(), 1.0)
                                                        .insertInc(AverageAnalysis().id(), 0.0))
                            .insertInc("Second",
                                       AnalysisResult().insertInc(StupidAnalysis().id(), 1.0)
                                       .insertInc(AverageAnalysis().id(), 0.0));

    QTest::newRow("three") << (AnalysisList()
                               << new StupidAnalysis(1.0)
                               << new AverageAnalysis())
                           << (IDList() << "First" << "Second" << "Third")
                           << (IDList() << "First" << "Second" << "Third")
                           << (IDAnalysisList() << StupidAnalysis().id() << AverageAnalysis().id())
                           <<  AnalysisResults()
                               .insertInc("First",
                                          AnalysisResult().insertInc(StupidAnalysis().id(), 1.0)
                                          .insertInc(AverageAnalysis().id(), 0.0))
                               .insertInc("Second",
                                          AnalysisResult().insertInc(StupidAnalysis().id(), 1.0)
                                          .insertInc(AverageAnalysis().id(), 0.0))
                               .insertInc("Third",
                                          AnalysisResult().insertInc(StupidAnalysis().id(), 1.0)
                                          .insertInc(AverageAnalysis().id(), 0.0));

    QTest::newRow("four-with-empty") << (AnalysisList()
                                         << new StupidAnalysis(1.0)
                                         << new AverageAnalysis())
                                     << (IDList() << "First" << "" << "Second" << "Third")
                                     << (IDList() << "First" << "Second" << "Third")
                                     << (IDAnalysisList() << StupidAnalysis().id() << AverageAnalysis().id())
                                     <<  AnalysisResults()
                                         .insertInc("First",
                                                    AnalysisResult().insertInc(StupidAnalysis().id(), 1.0)
                                                    .insertInc(AverageAnalysis().id(), 0.0))
                                         .insertInc("Second",
                                                    AnalysisResult().insertInc(StupidAnalysis().id(), 1.0)
                                                    .insertInc(AverageAnalysis().id(), 0.0))
                                         .insertInc("Third",
                                                    AnalysisResult().insertInc(StupidAnalysis().id(), 1.0)
                                                    .insertInc(AverageAnalysis().id(), 0.0)); ;

    QTest::newRow("four-with-repeat") << (AnalysisList()
                                          << new StupidAnalysis(1.0)
                                          << new AverageAnalysis())
                                      << (IDList() << "First" << "First" << "Second" << "Third")
                                      << (IDList() << "First" << "Second" << "Third")
                                      << (IDAnalysisList() << StupidAnalysis().id() << AverageAnalysis().id())
                                      <<  AnalysisResults()
                                          .insertInc("First",
                                                     AnalysisResult().insertInc(StupidAnalysis().id(), 1.0)
                                                     .insertInc(AverageAnalysis().id(), 0.0))
                                          .insertInc("Second",
                                                     AnalysisResult().insertInc(StupidAnalysis().id(), 1.0)
                                                     .insertInc(AverageAnalysis().id(), 0.0))
                                          .insertInc("Third",
                                                     AnalysisResult().insertInc(StupidAnalysis().id(), 1.0)
                                                     .insertInc(AverageAnalysis().id(), 0.0)); ;

}

void TAnalysisTableModel::TestAddRemoveMoc()
{
    QFETCH(AnalysisList, analyzes);
    QFETCH(IDList, pointsIDs);
    QFETCH(IDList, resultPointsIDs);
    QFETCH(IDAnalysisList, analyzesID);
    QFETCH(AnalysisResults, analyzesResult);

    MocPointListReader reader(pointsIDs);

    AnalysisTableModel model(&reader);
    model.appendPointList(pointsIDs);


    foreach(AbstractAnalysis* analysis, analyzes)
    {
        model.addAnalysis(analysis);
        delete analysis;
    }

    model.analyzeAll();

    analyzes.clear();

    IDList idsFromModel;
    for(int i = 0; i < model.rowCount(); i++)
    {
        idsFromModel.append(model.index(i, 0).data().toString());
    }

    const IDList actualPointsID = idsFromModel;
    const IDList expectedPointsID = resultPointsIDs;

    QCOMPARE(actualPointsID, expectedPointsID);

    IDAnalysisList analyzesIDsFromModel;
    for(int i = 1; i < model.columnCount(); i++)
    {
        analyzesIDsFromModel.append(model.headerData(i).toString());
    }

    const IDAnalysisList actualAnalyzes = analyzesIDsFromModel;
    const IDAnalysisList expectedAnalyzes= analyzesID;

    QCOMPARE(actualAnalyzes, expectedAnalyzes);

    const AnalysisResults actualAnalysisResults = model.Results();
    const AnalysisResults expectedAnalysisResults= analyzesResult;

    QCOMPARE(actualAnalysisResults, expectedAnalysisResults);
}
