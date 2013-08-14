#include "BSqlPointListInterface.h"

BSqlPointListInterface::BSqlPointListInterface(const int nRuns):
    nRuns_(nRuns)
{

}

void BSqlPointListInterface::run()
{
    for(int i = 0; i < nRuns_; ++i)
    {
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

        writer->write("id1", PointList() << Point(1.0));

        AbstractPointListReader* reader = new SqlPointListReader(dataBaseName, tableName);

        reader->read("id1");



        AnalysisTableModel* tableModel = new AnalysisTableModel(reader);
        ItemListModel* itemListModel = new ItemListModel(reader);


        delete tableModel;
        delete itemListModel;

        delete writer;
        delete reader;


        SqlPointListInterface::removeConnection();

        qDebug() << QString("iteration : " + QString::number(i));
    }
}
