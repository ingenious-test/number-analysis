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

    bool isCompare = analysisResultsFuzzyCompare(actualAnalysisResults,expectedAnalysisResults);
    if(!isCompare)
    {
        QFAIL(QString("Compare values are not the same. \nActual:\n"
                      + analysisResultsToString(actualAnalysisResults)
                      + "\nExpected:\n"
                      + analysisResultsToString(expectedAnalysisResults)).toStdString().c_str());
    }
}

void TAnalysisTableModel::TestAddRemoveSql_data()
{
    QTest::addColumn<AnalysisList>("analyzes");
    QTest::addColumn<IDList>("pointsIDs");
    QTest::addColumn<SequencePointList>("points");
    QTest::addColumn<IDList>("resultPointsIDs");
    QTest::addColumn<IDAnalysisList>("analyzesID");
    QTest::addColumn<AnalysisResults>("analyzesResult");


    QTest::newRow("empty") << AnalysisList() << IDList() << SequencePointList() << IDList()  << IDAnalysisList() << AnalysisResults();

    QTest::newRow("one") << (AnalysisList()
                             << new StupidAnalysis(1.0)
                             << new AverageAnalysis())
                         << (IDList() << "First")
                         << (SequencePointList()
                             << (PointList() << Point(1.0) << Point(2.0) << Point(3.0)))
                         << (IDList() << "First")
                         << (IDAnalysisList() <<StupidAnalysis().id() << AverageAnalysis().id())
                         << AnalysisResults().insertInc("First",
                                                        AnalysisResult().insertInc(StupidAnalysis().id(), 1.0)
                                                        .insertInc(AverageAnalysis().id(), (1.0 + 2.0 + 3.0) / 3.0));

    QTest::newRow("two") << (AnalysisList()
                             << new StupidAnalysis(1.0)
                             << new AverageAnalysis())
                         << (IDList() << "First" << "Second")
                         << (SequencePointList()
                             << (PointList() << Point(11.0) << Point(2.3) << Point(3.4))
                             << (PointList() << Point(10.0) << Point(13.0)))
                         << (IDList() << "First" << "Second")
                         << (IDAnalysisList() <<StupidAnalysis().id() << AverageAnalysis().id())
                         << AnalysisResults().insertInc("First",
                                                        AnalysisResult().insertInc(StupidAnalysis().id(), 1.0)
                                                        .insertInc(AverageAnalysis().id(), (11.0 + 2.3 + 3.4) / 3.0))
                            .insertInc("Second",
                                       AnalysisResult().insertInc(StupidAnalysis().id(), 1.0)
                                       .insertInc(AverageAnalysis().id(), (10.0 + 13.0) / 2.0));

    QTest::newRow("three") << (AnalysisList()
                               << new StupidAnalysis(1.0)
                               << new AverageAnalysis())
                           << (IDList() << "First" << "Second" << "Third")
                           << (SequencePointList()
                               << (PointList() << Point(11.1) << Point(2.3))
                               << (PointList() << Point(12.0) << Point(13.0))
                               << (PointList() << Point(13.4) << Point(12.0)))
                           << (IDList() << "First" << "Second" << "Third")
                           << (IDAnalysisList() << StupidAnalysis().id() << AverageAnalysis().id())
                           <<  AnalysisResults()
                               .insertInc("First",
                                          AnalysisResult().insertInc(StupidAnalysis().id(), 1.0)
                                          .insertInc(AverageAnalysis().id(), (11.1 + 2.3) / 2.0))
                               .insertInc("Second",
                                          AnalysisResult().insertInc(StupidAnalysis().id(), 1.0)
                                          .insertInc(AverageAnalysis().id(), (12.0 + 13.0) / 2.0))
                               .insertInc("Third",
                                          AnalysisResult().insertInc(StupidAnalysis().id(), 1.0)
                                          .insertInc(AverageAnalysis().id(), (13.4 + 12.0) / 2.0));
}

void TAnalysisTableModel::TestAddRemoveSql()
{
    QFETCH(AnalysisList, analyzes);
    QFETCH(IDList, pointsIDs);
    QFETCH(SequencePointList, points);
    QFETCH(IDList, resultPointsIDs);
    QFETCH(IDAnalysisList, analyzesID);
    QFETCH(AnalysisResults, analyzesResult);

    const QString dataBaseName = QString(QTest::currentTestFunction()) + QString(QTest::currentDataTag()) + "TestAddRemoveSql.db";
    const QString tableName = "Points";

    if(QFile::exists(dataBaseName))
    {
        if(!QFile::remove(dataBaseName))
        {
            QFAIL("can't remove testing database");
        }
    }

    SqlPointListWriter writer(dataBaseName, tableName);
    {
        for(int i = 0; i < pointsIDs.size(); i++)
        {
            writer.write(pointsIDs.at(i), points.at(i));
        }
    }

    SqlPointListReader reader(dataBaseName, tableName);

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

    bool isCompare = analysisResultsFuzzyCompare(actualAnalysisResults,expectedAnalysisResults);
    if(!isCompare)
    {
        QFAIL(QString("Compare values are not the same. \nActual:\n"
                      + analysisResultsToString(actualAnalysisResults)
                      + "\nExpected:\n"
                      + analysisResultsToString(expectedAnalysisResults)).toStdString().c_str());
    }
}

void TAnalysisTableModel::TestSorting_data()
{
    QTest::addColumn<AnalysisResults>("inputResult");
    QTest::addColumn<AnalysisList>("analyzes");
    QTest::addColumn<IDList>("pointsIDs");
    QTest::addColumn<IDList>("resultPointsIDs");
    QTest::addColumn<int>("column");
    QTest::addColumn<int>("sortType");

    QTest::newRow("one") << AnalysisResults().insertInc("First",
                                                        AnalysisResult().insertInc(StupidAnalysis().id(), 1.0)
                                                        .insertInc(AverageAnalysis().id(), 2.0))
                         << (AnalysisList()
                             << new StupidAnalysis(1.0)
                             << new AverageAnalysis())
                         << (IDList() << ID("First"))
                         << (IDList() << ID("First"))
                         << 0
                         << 0;

    QTest::newRow("two") << AnalysisResults()
                            .insertInc("First",
                                       AnalysisResult()
                                       .insertInc(StupidAnalysis().id(), 1.0)
                                       .insertInc(AverageAnalysis().id(), 2.0))
                            .insertInc("Second",
                                       AnalysisResult()
                                       .insertInc(StupidAnalysis().id(), 2.0)
                                       .insertInc(AverageAnalysis().id(), 3.0))
                         << (AnalysisList()
                             << new StupidAnalysis(1.0)
                             << new AverageAnalysis())
                         << (IDList() << ID("Second") << ID("First"))
                         << (IDList() << ID("First") << ID("Second"))
                         << 0
                         << 0;

}

void TAnalysisTableModel::TestSorting()
{
    QFETCH(AnalysisResults, inputResult);
    QFETCH(AnalysisList, analyzes);
    QFETCH(IDList, pointsIDs);
    QFETCH(IDList, resultPointsIDs);
    QFETCH(int, column);
    QFETCH(int, sortType);


    AnalysisTableModel model(0);

    model.appendPointList(pointsIDs);

    foreach(AbstractAnalysis* analysis, analyzes)
    {
        model.addAnalysis(analysis);
        delete analysis;
    }

    model.setResults(inputResult);

    model.sort(column, sortType == 0 ? Qt::AscendingOrder : Qt::DescendingOrder);

    const AnalysisResults actualAnalysisResults = model.Results();
    const AnalysisResults expectedAnalysisResults= inputResult;

    bool isCompare = analysisResultsFuzzyCompare(actualAnalysisResults,expectedAnalysisResults);
    if(!isCompare)
    {
        QFAIL(QString("Compare values are not the same. \nActual:\n"
                      + analysisResultsToString(actualAnalysisResults)
                      + "\nExpected:\n"
                      + analysisResultsToString(expectedAnalysisResults)).toStdString().c_str());
    }


    const IDList actualPointsID = model.getPointsIDs();
    const IDList expectedPointsID= resultPointsIDs;

    QCOMPARE(actualPointsID, expectedPointsID);
}
