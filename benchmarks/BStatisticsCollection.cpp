#include "BStatisticsCollection.h"

BStatisticsCollection::BStatisticsCollection() :
    dataBaseName_("benchmarkCollectionStatistics.db"),
    tableName_("test")
{

}

BStatisticsCollection::~BStatisticsCollection()
{

}

void BStatisticsCollection::generateDatabase(const int seqCount, const int pointsCount)
{
    if(QFile::exists(dataBaseName_))
    {
        if(!QFile::remove(dataBaseName_))
        {
            qWarning() << "cannot remove database";
        }
    }

    SqlPointListWriter writer(dataBaseName_, tableName_);
    writer.open();
    SequencePointList seqPoints;
    IDList items;
    for(int i = 0; i < seqCount; i++)
    {
        PointList pointList;
        for(int j = 0; j < pointsCount; j++)
        {
            pointList << Point(j);
        }
        items << QString("id%1").arg(i);
        seqPoints << pointList;
        qDebug() << i << " / " << seqCount;
    }


    qWarning() << "----Start Write to DataBase----";
    QTime time(QTime::currentTime());
    writer.write(items, seqPoints);
    const int timeElapsed = time.secsTo(QTime::currentTime());
    qWarning() << "----End Write to DataBase----";

    qWarning() << "Database writen " << seqCount << " sequence with " << pointsCount << " points";
    qWarning() << "Database write time: " << timeElapsed << " s";
    QFileInfo info(dataBaseName_);
    qWarning() << "Database size: " << info.size() / 1024 << " kb";
}

void BStatisticsCollection::statistics()
{
    IncSequenceCountStatistics statistics;
    statistics.open(dataBaseName_, tableName_);

    QTime time(QTime::currentTime());
    statistics.exec();
    const int timeElapsed = time.secsTo(QTime::currentTime());
    qWarning() << "statistics exec time " << timeElapsed << " s";
}
