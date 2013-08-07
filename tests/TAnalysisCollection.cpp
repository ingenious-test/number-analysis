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
                                                                      << new StupidAnalysis())
                                                << (PointList() << 1.0)
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

void TAnalysisCollection::TestAnalyzeAnalysisAddRemove_data()
{
    QTest::addColumn<AnalysisCollection>("collection");
    QTest::addColumn<int>("length");
    QTest::addColumn<QStringList>("nameList");


    QTest::newRow("empty-collection") << AnalysisCollection() << 0 << QStringList();

    AnalysisCollection test1;

    for(int i = 0; i < 10; i++)
    {
        StupidAnalysis* stupidAnalysis = new StupidAnalysis;
        test1.addAnalysis(static_cast<AbstractAnalysis*>(stupidAnalysis));

        QTest::newRow(QString("stupid-analysis-collection-added-" + QString::number(i)).toStdString().c_str())
                << test1
                << 1
                << (QStringList() << "stupid");

        if(i != 9)
        {
            test1.removeAll();

            QTest::newRow(QString("stupid-analysis-collection-removed-" + QString::number(i)).toStdString().c_str())
                    << test1
                    << 0
                    << QStringList();
        }

        delete stupidAnalysis;
    }



    AnalysisCollection test2;
    for(int i = 0; i < 10; i++)
    {
        StupidAnalysis* stupidAnalysis = new StupidAnalysis;
        AverageAnalysis* averageAnalysis = new AverageAnalysis;

        test2.addAnalysis(static_cast<AbstractAnalysis*>(stupidAnalysis));
        test2.addAnalysis(static_cast<AbstractAnalysis*>(averageAnalysis));


        QTest::newRow(QString("stupid-avarage-analysis-collection-added-" + QString::number(i)).toStdString().c_str())
                << test2
                << 2
                << (QStringList() << "stupid" << "average");

        if(i != 9)
        {
            test2.removeAll();

            QTest::newRow(QString("stupid-avarage-analysis-collection-removed-" + QString::number(i)).toStdString().c_str())
                    << test2
                    << 0
                    << QStringList();
        }

        delete stupidAnalysis;
        delete averageAnalysis;
    }

}

void TAnalysisCollection::TestAnalyzeAnalysisAddRemove()
{
    QFETCH(AnalysisCollection, collection);
    QFETCH(int, length);
    QFETCH(QStringList, nameList);

    const int actualLength = collection.length();
    const int expectedLength = length;

    QCOMPARE(actualLength, expectedLength);

    const QStringList actualNames = collection.getNameList();
    const QStringList expectedNames = nameList;

    QCOMPARE(actualNames, expectedNames);
}
