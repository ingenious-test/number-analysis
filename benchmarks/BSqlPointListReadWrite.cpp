#include "BSqlPointListReadWrite.h"

BSqlPointListReadWrite::BSqlPointListReadWrite(const int pointsCount):
    pointsCount_(pointsCount)
{
}

void BSqlPointListReadWrite::runRead()
{

        qWarning() << "Read";
        QString dataBaseName = "test.db";
        QString tableName = "testtable";

        if(!QFile::exists(dataBaseName))
        {

                qWarning() << "can't find " << dataBaseName << ". first need runWrite()";
                return;
        }

        SqlPointListReader* reader = new SqlPointListReader(dataBaseName, tableName);
        reader->open();

        SequencePointList seqList;
        for(int j = 0; j < pointsCount_; j++)
        {
            PointList points;

            QTime readTime;
            readTime.start();
            points = reader->read(QString("id%1").arg(j));
            qWarning() << "read pointlist"
                     << QString("id%1").arg(j)
                     << " with "
                     << points.count()
                     << " points "
                     << readTime.elapsed() / 1000.0
                     << "seconds";

            seqList.append(points);
        }

        delete reader;


        SqlPointListInterface::removeConnection();
}

void BSqlPointListReadWrite::runWrite()
{

        qDebug() << "Write";
        QString dataBaseName = "test.db";
        QString tableName = "testtable";

        if(QFile::exists(dataBaseName))
        {
            if(!QFile::remove(dataBaseName))
            {
                qWarning() << "can't remove testing database";
            }
        }


        SqlPointListWriter* writer = new SqlPointListWriter(dataBaseName, tableName);
        writer->open();

        qsrand(QTime(0,0).secsTo(QTime::currentTime()));
        for(int j = 0; j < pointsCount_; j++)
        {
            const int pointsCount = (qrand() % (500) + 1);
            PointList points(QString("id%1").arg(j));
            for(int pointNum = 0; pointNum < pointsCount; pointNum++)
            {
                points << pointNum;
            }


            QTime writeTime;
            writeTime.start();
            writer->write(points);
            qWarning() << "write pointlist"
                     << points.id()
                     << " with "
                     << pointsCount
                     << " points "
                     << writeTime.elapsed() / 1000.0
                     << "seconds";
        }

        delete writer;

        SqlPointListInterface::removeConnection();
}
