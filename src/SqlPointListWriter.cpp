#include "SqlPointListWriter.h"

SqlPointListWriter::SqlPointListWriter(const QString &dataBaseName, const QString &tableName) :
    SqlPointListInterface(dataBaseName, tableName)
{   
    if(!open())
    {
        qWarning() << "SqlPointListWriter not open";
    }
}

void SqlPointListWriter::write(const ID &item, const PointList &points)
{
    dataBase().transaction();
    for(int num = 0; num < points.length(); ++num)
    {
        writePointsByID_.bindValue(":id", item);
        writePointsByID_.bindValue(":num", num);
        writePointsByID_.bindValue(":value", points.at(num));

        const bool querySuccess = writePointsByID_.exec();

        if(!querySuccess)
        {
            qWarning() << "exec insert table" << writePointsByID_.lastError().text();
            dataBase().commit();
            return;
        }
    }
     dataBase().commit();
     writePointsByID_.finish();
}

bool SqlPointListWriter::prepareQueries()
{
    writePointsByID_ = QSqlQuery(dataBase());

    writePointsByID_.prepare("INSERT OR ABORT INTO " + tableName() + " VALUES(:id, :num, :value)");
    if(writePointsByID_.lastError().text() != " ")
    {
        qWarning() << "prepare insert points" << writePointsByID_.lastError().text();
        return false;
    }


    return true;
}
