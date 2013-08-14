#include "BSqlPointListReadWrite.h"

BSqlPointListReadWrite::BSqlPointListReadWrite(const int nRuns):
    nRuns_(nRuns)
{
}

void BSqlPointListReadWrite::run()
{
    for(int i = 0; i < nRuns_; ++i)
    {
        qDebug() << "iteration : " << i << " / " << nRuns_;
        QString dataBaseName = QString("test%1.db").arg(i);
        QString tableName = QString("table%1").arg(i);

        if(QFile::exists(dataBaseName))
        {
            if(!QFile::remove(dataBaseName))
            {
                qWarning() << "can't remove testing database";
            }
        }


        SqlPointListWriter* writer = new SqlPointListWriter(dataBaseName, tableName);

        qsrand(QTime(0,0).secsTo(QTime::currentTime()));
        for(int j = 0; j < 5; j++)
        {
            const int pointsCount = (qrand() % (500) + 1);
            PointList pointList;
            for(int pointNum = 0; pointNum < pointsCount; pointNum++)
            {
                pointList << pointNum;
            }


            QTime writeTime;
            writeTime.start();
            writer->write(QString("id%1").arg(j), pointList);
            qDebug() << "write pointlist"
                     << QString("id%1").arg(j)
                     << " with "
                     << pointsCount
                     << " points "
                     << writeTime.elapsed() / 1000.0
                     << "seconds";
        }

        AbstractPointListReader* reader = new SqlPointListReader(dataBaseName, tableName);

        SequencePointList seqList;
        for(int j = 0; j < 5; j++)
        {
            PointList pointList;

            qDebug() << "read "
                        + QString("id%1").arg(j)
                        + " with " + QString::number(seqList.last().size())
                        + " points";

            QTime readTime;
            readTime.start();
            pointList = reader->read(QString("id%1").arg(j));
            qDebug() << "read pointlist"
                     << QString("id%1").arg(j)
                     << " with "
                     << pointList.size()
                     << " points "
                     << readTime.elapsed() / 1000.0
                     << "seconds";

            seqList.append(pointList);
        }


        delete writer;
        delete reader;


        SqlPointListInterface::removeConnection();
    }
}
