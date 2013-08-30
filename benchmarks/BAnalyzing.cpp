#include "BAnalyzing.h"

BAnalyzing::BAnalyzing(const int pointsCount) :
    pointsCount_(pointsCount)
{

}

void BAnalyzing::run()
{
    QString dataBaseName = "analysingbenchmark.db";
    QString tableName = "testtable";

    if(QFile::exists(dataBaseName))
    {
        if(!QFile::remove(dataBaseName))
        {
            qWarning() << "can't remove testing database";
        }
    }

    SqlPointListWriter* writer = new SqlPointListWriter(dataBaseName, tableName);
    if(!writer->open())
    {
        qWarning() << "can't open writer";
    }

    SequencePointList seqPoints;
    qsrand(QTime(0,0).secsTo(QTime::currentTime()));
    for(int j = 0; j < pointsCount_; j++)
    {
        PointList points(QString("id%1").arg(j));
        for(int pointNum = 0; pointNum < 100; pointNum++)
        {
            points << pointNum;
        }

        seqPoints.append(points);
    }

    QTime timer;
    timer.start();
    writer->write(seqPoints);
    qWarning() << "write "
               << seqPoints.count()
               << " pointslist "
               << timer.elapsed() / 1000.0
               << "seconds";

    seqPoints.clear();
    delete writer;

    SqlPointListReader* reader = new SqlPointListReader(dataBaseName, tableName);
    if(!reader->open())
    {
        qWarning() << "sqlreader not open";
        return;
    }

    AnalysisList analysisList;
    analysisList
            << new StupidAnalysis
            << new AverageAnalysis
            << new AverageIgnoreNullAnalysis
            << new StandardDeviationAnalysis
            << new MedianAnalysis
            << new FirstQuartileAnalysis
            << new ThirdQuartileAnalysis;

    timer.start();
    const IDList idList = reader->readAllItems();
    qWarning() << "Read time" <<timer.elapsed() / 1000.0;

    AnalysisTableModel* analysisModel = new AnalysisTableModel(reader);


    foreach(AbstractAnalysis* analysis, analysisList)
    {
        analysisModel->addAnalysis(analysis);
        delete analysis;
    }

    timer.start();
    analysisModel->appendPointList(idList);
    qWarning() << "Add to analyzing time" <<timer.elapsed() / 1000.0;

    timer.start();
    analysisModel->analyzeAll();

    qWarning() << "Analyzing time" <<timer.elapsed() / 1000.0;

    analysisList.clear();
    delete analysisModel;
    delete reader;

    SqlPointListInterface::removeConnection();
}
