#include "SqlPointListReader.h"

SqlPointListReader::SqlPointListReader(const QString &dataBaseName, const QString& tableName) :
    SqlPointListInterface(dataBaseName, tableName)
{

}

SqlPointListReader::~SqlPointListReader()
{
    foreach(AbstractStatictics *s, statisticsCollection)
    {
        delete s;
    }
}

bool SqlPointListReader::prepareQueries()
{
    readPointsByID_ = QSqlQuery(dataBase());
    readPointsByID_.setForwardOnly(true);
    readPointsByID_.prepare("SELECT " + columnVALUE() + " FROM " + tableName() + " WHERE " + columnID() + " = :id");
    if(readPointsByID_.lastError().text() != " ")
    {
        qWarning() << "prepare select points" << readPointsByID_.lastError().text();
        return false;
    }

    readAllPointsIDs_ = QSqlQuery(dataBase());
    readAllPointsIDs_.setForwardOnly(true);
    readAllPointsIDs_.prepare("SELECT DISTINCT " + columnID() + " FROM " + tableName());
    if(readAllPointsIDs_.lastError().text() != " ")
    {
        qWarning() << "prepare select points ids" << readAllPointsIDs_.lastError().text();
        return false;
    }

    return true;
}

PointList SqlPointListReader::read(const ID &item)
{
    if(isOpen())
    {
        PointList points(item);

        readPointsByID_.bindValue(":id", item);

        readPointsByID_.exec();
        if(readPointsByID_.lastError().text() != " ")
        {
            qWarning() << "exec select point" << readPointsByID_.lastError().text();
            return PointList();
        }

        while(readPointsByID_.next())
        {
            const Point point(readPointsByID_.value(0).toDouble());
            points << point;
        }

        readPointsByID_.finish();

        return points;
    }
    else
    {
        qWarning() << "database not open";
    }

    return PointList();
}

IDList SqlPointListReader::readAllItems()
{
    if(isOpen())
    {
        IDList allItems;

        const bool querySuccess = readAllPointsIDs_.exec();

        if(!querySuccess)
        {
            qWarning() << "exec select point ids" << readAllPointsIDs_.lastError().text();
            return IDList();
        }


        while(readAllPointsIDs_.next())
        {
            const ID item(readAllPointsIDs_.value(0).toString());

            allItems << item;
        }

        readAllPointsIDs_.finish();

        return allItems;
    }
    else
    {
        qWarning() << "database not open";
    }
    return IDList();
}

void SqlPointListReader::appendStatistics(AbstractStatictics *statistics)
{
    statisticsCollection.append(statistics);
}

void SqlPointListReader::appendStatistics(const StatisticsList &statisticsList)
{
    statisticsCollection.append(statisticsList);
}

PointListStorageStatistics SqlPointListReader::statistics()
{
    PointListStorageStatistics storageStatistics;

    foreach(AbstractStatictics *s, statisticsCollection)
    {
        s->open(dataBaseName(), tableName());
        storageStatistics << PointListStatistics(s->name(), s->exec());
    }

    return storageStatistics;
}
