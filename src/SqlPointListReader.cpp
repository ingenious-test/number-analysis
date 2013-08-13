#include "SqlPointListReader.h"

SqlPointListReader::SqlPointListReader(const QString &dataBaseName) :
    dataBaseName_(dataBaseName)
{
}

PointList SqlPointListReader::read(const ID &item)
{
    PointList points;

    {
        QSqlDatabase dataBase = QSqlDatabase::addDatabase("QSQLITE", "connection");
        dataBase.setDatabaseName(dataBaseName_);
        if (!dataBase.open())
        {
            qWarning() << "can't open database " << dataBaseName_;
            return PointList();
        }

        QSqlQuery query(dataBase);

        query.prepare("SELECT value FROM tableName WHERE id = :id");
        if(query.lastError().text() != " ")
        {
            qWarning() << "prepare select points" << query.lastError().text();
            return PointList();
        }

        query.bindValue(":id", item);

        query.exec();
        if(query.lastError().text() != " ")
        {
            qWarning() << "exec select point" << query.lastError().text();
            return PointList();
        }

        while(query.next())
        {
            const Point point(query.value(0).toDouble());
            points << point;
        }
    }

    QSqlDatabase::removeDatabase("connection");

    return points;
}

IDList SqlPointListReader::readAllItems()
{
    IDList allItems;

    {
        QSqlDatabase dataBase = QSqlDatabase::addDatabase("QSQLITE", "connection");
        dataBase.setDatabaseName(dataBaseName_);
        if (!dataBase.open())
        {
            error(QString("can't open database " + dataBaseName_));
            return IDList();
        }

        QSqlQuery query(dataBase);
        bool querySuccess = false;

        querySuccess = query.prepare("SELECT DISTINCT id FROM tableName");

        if(!querySuccess)
        {
            error(QString("prepare select id" + query.lastError().text()));
            return IDList();
        }

        querySuccess = query.exec();


        if(!querySuccess)
        {
            error(QString("exec select id" + query.lastError().text()));
            return IDList();
        }

        while(query.next())
        {
            const ID item(query.value(0).toString());

            allItems << item;
        }
    }

    QSqlDatabase::removeDatabase("connection");

    return allItems;
}

void SqlPointListReader::error(const QString &errorString)
{
    qWarning() << errorString;
}
