#include "TAnalysisTableModel.h"

TAnalysisTableModel::TAnalysisTableModel()
{

}

void TAnalysisTableModel::TestAddRemove_data()
{
    QTest::addColumn<AnalysisList>("analyzes");
    QTest::addColumn<IDList>("pointList");
    QTest::addColumn<IDList>("resultPointList");
    QTest::addColumn<IDAnalysisList>("analyzesList");

    QTest::newRow("empty") << AnalysisList() << IDList() << IDList()  << IDAnalysisList();

    QTest::newRow("one") << (AnalysisList()
                             << new StupidAnalysis(1.0)
                             << new AverageAnalysis())
                         << (IDList() << "First")
                         << (IDList() << "First")
                         << (IDAnalysisList() <<StupidAnalysis().id() << AverageAnalysis().id());

    QTest::newRow("two") << (AnalysisList()
                             << new StupidAnalysis(1.0)
                             << new AverageAnalysis())
                         << (IDList() << "First" << "Second")
                         << (IDList() << "First" << "Second")
                         << (IDAnalysisList() <<StupidAnalysis().id() << AverageAnalysis().id());

    QTest::newRow("three") << (AnalysisList()
                               << new StupidAnalysis(1.0)
                               << new AverageAnalysis())
                           << (IDList() << "First" << "Second" << "Third")
                           << (IDList() << "First" << "Second" << "Third")
                           << (IDAnalysisList() << StupidAnalysis().id() << AverageAnalysis().id());

    QTest::newRow("four-with-empty") << (AnalysisList()
                                         << new StupidAnalysis(1.0)
                                         << new AverageAnalysis())
                                     << (IDList() << "First" << "" << "Second" << "Third")
                                     << (IDList() << "First" << "Second" << "Third")
                                     << (IDAnalysisList() << StupidAnalysis().id() << AverageAnalysis().id());

    QTest::newRow("four-with-repeat") << (AnalysisList()
                                          << new StupidAnalysis(1.0)
                                          << new AverageAnalysis())
                                      << (IDList() << "First" << "First" << "Second" << "Third")
                                      << (IDList() << "First" << "Second" << "Third")
                                      << (IDAnalysisList() << StupidAnalysis().id() << AverageAnalysis().id());

}

void TAnalysisTableModel::TestAddRemove()
{
    QFETCH(AnalysisList, analyzes);
    QFETCH(IDList, pointList);
    QFETCH(IDList, resultPointList);
    QFETCH(IDAnalysisList, analyzesList);

    AnalysisTableModel model;
    model.appendPointList(pointList);

    foreach(AbstractAnalysis* analysis, analyzes)
    {
        model.addAnalysis(analysis);
        delete analysis;
    }

    analyzes.clear();

    IDList idFromModel;
    for(int i = 0; i < model.rowCount(); i++)
    {
        idFromModel.append(model.index(i, 0).data().toString());
    }

    const IDList actualPointSet = idFromModel;
    const IDList expectedPointSet = resultPointList;

    QCOMPARE(actualPointSet, expectedPointSet);

    IDAnalysisList analyzesFromModel;
    for(int i = 1; i < model.columnCount(); i++)
    {
        analyzesFromModel.append(model.headerData(i).toString());
    }


    const IDAnalysisList actualAnalysisList = analyzesFromModel;
    const IDAnalysisList expectedAnalysisList = analyzesList;

    QCOMPARE(actualAnalysisList, expectedAnalysisList);
}
