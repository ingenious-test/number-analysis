#include "SqlPointListReader.h"

SqlPointListReader::SqlPointListReader(const QString &dataBaseName, const QString& tableName) :
    SqlPointListInterface(dataBaseName, tableName)
{
}

PointList SqlPointListReader::read(const ID &item)
{
    PointList points;


    QSqlQuery query(dataBase());

    query.prepare("SELECT value FROM " + tableName() + " WHERE id = :id");
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

    query.finish();
    query.clear();

    return points;
}

IDList SqlPointListReader::readAllItems()
{
    IDList allItems;

    QSqlQuery query(dataBase());
    bool querySuccess = false;

    querySuccess = execQuery(query, "SELECT DISTINCT id FROM " + tableName() + "");

    if(!querySuccess)
    {
        return IDList();;
    }

    while(query.next())
    {
        const ID item(query.value(0).toString());

        allItems << item;
    }

    query.finish();
    query.clear();

    return allItems;
}
