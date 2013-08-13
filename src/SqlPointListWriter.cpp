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
        bool querySuccess = false;

        querySuccess = execQuery(query,"CREATE TABLE tableName (id, num, value)");

        if(!querySuccess)
        {
            return;
        }

        querySuccess = query.prepare("INSERT INTO tableName VALUES(:id, :num, :value)");

        if(!querySuccess)
        {
            return;
        }

        for(int num = 0; num < points.length(); ++num)
        {
            query.bindValue(":id", item);
            query.bindValue(":num", num);
            query.bindValue(":value", points.at(num));

            querySuccess = query.exec();

            if(!querySuccess)
            {
                qWarning() << "exec insert table" << query.lastError().text();
                return;
            }
        }
    }

    QSqlDatabase::removeDatabase("connection");
}

bool SqlPointListWriter::execQuery(QSqlQuery &query, const QString& queryStr)
{
    QString errorStr;
    bool preraredSuccess = query.prepare(queryStr);
    if(preraredSuccess)
    {
        bool execSuccess = query.exec();
        if(execSuccess)
        {
            return true;
        }
        else{
            errorStr = "exec";
        }

    }
    else
    {
        errorStr = "prepared";
    }

    qWarning() << errorStr << queryStr << query.lastError().text();
    return false;
}
