#include "SqlPointListWriter.h"

SqlPointListWriter::SqlPointListWriter(const QString &dataBaseName, const QString &tableName) :
    SqlPointListInterface(dataBaseName, tableName)
{   
}

void SqlPointListWriter::write(const ID &item, const PointList &points) const
{
    QSqlQuery query(dataBase());
    bool querySuccess = false;

    querySuccess = query.prepare("INSERT OR ABORT INTO " + tableName() + " VALUES(:id, :num, :value)");

    if(!querySuccess)
    {
        return;
    }

    dataBase().transaction();
    for(int num = 0; num < points.length(); ++num)
    {
        query.bindValue(":id", item);
        query.bindValue(":num", num);
        query.bindValue(":value", points.at(num));

        querySuccess = query.exec();

        if(!querySuccess)
        {
            qWarning() << "exec insert table" << query.lastError().text();
            dataBase().commit();
            return;
        }
    }
     dataBase().commit();
     query.finish();
}
