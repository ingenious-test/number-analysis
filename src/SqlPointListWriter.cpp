#include "SqlPointListWriter.h"

SqlPointListWriter::SqlPointListWriter(const QString &dataBaseName) :
    dataBaseName_(dataBaseName)
{
}

void SqlPointListWriter::write(const ID &item, const PointList &points)
{
    {
        QSqlDatabase dataBase = QSqlDatabase::addDatabase("QSQLITE", "connection");
        dataBase.setDatabaseName(dataBaseName_);
        if (!dataBase.open())
        {
            qWarning() << "can't open database " << dataBaseName_;
            return;
        }
        QSqlQuery query(dataBase);

        query.prepare("CREATE TABLE tableName (id, num, value)");

        if(query.lastError().text() != " ")
        {
            qWarning() << "prepare create table" << query.lastError().text();
            return;
        }

        query.exec();

        if(query.lastError().text() != " ")
        {
            qWarning() << "exec create table" << query.lastError().text();
            return;
        }

        query.prepare("INSERT INTO tableName VALUES(:id, :num, :value)");

        if(query.lastError().text() != " ")
        {
            qWarning() << "prepare insert" << query.lastError().text();
            return;
        }

        for(int num = 0; num < points.length(); ++num)
        {
            query.bindValue(":id", item);
            query.bindValue(":num", num);
            query.bindValue(":value", points.at(num));

            query.exec();

            if(query.lastError().text() != " ")
            {
                qWarning() << "exec insert table" << query.lastError().text();
                return;
            }
        }
    }

    QSqlDatabase::removeDatabase("connection");
}
