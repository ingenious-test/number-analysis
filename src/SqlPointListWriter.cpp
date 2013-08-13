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
            error(QString("can't open database " + dataBaseName_));
            return;
        }
        QSqlQuery query(dataBase);
        bool querySuccess = false;

        querySuccess = query.prepare("CREATE TABLE tableName (id, num, value)");

        if(!querySuccess)
        {
            qWarning() ;
            error(QString("prepare create table " + query.lastError().text()));
            return;
        }

        querySuccess = query.exec();

        if(!querySuccess)
        {
            error(QString("exec create table " + query.lastError().text()));
            return;
        }

        querySuccess = query.prepare("INSERT INTO tableName VALUES(:id, :num, :value)");

        if(!querySuccess)
        {
            error(QString("prepare insert" + query.lastError().text()));
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
                error(QString("exec insert table" + query.lastError().text()));
                return;
            }
        }
    }

    QSqlDatabase::removeDatabase("connection");
}

void SqlPointListWriter::error(const QString &errorString)
{
    qWarning() << errorString;
}
