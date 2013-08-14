#include "BSqlPointListInterface.h"

BSqlPointListInterface::BSqlPointListInterface(const int nRuns):
    nRuns_(nRuns)
{

}

void BSqlPointListInterface::run()
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
        AbstractPointListReader* reader = new SqlPointListReader(dataBaseName, tableName);

        delete writer;
        delete reader;


        SqlPointListInterface::removeConnection();
    }
}
