#include "SqlPointListReader.h"

SqlPointListReader::SqlPointListReader(const QString &dataBaseName, const QString& tableName) :
    SqlPointListInterface(dataBaseName, tableName)
{
    if(!open())
    {
        qWarning() << "SqlPointListReader not open";
    }
}

bool SqlPointListReader::prepareQueries()
{
    readPointsByID_ = QSqlQuery(dataBase());


    readPointsByID_.prepare("SELECT " + columnVALUE() + " FROM " + tableName() + " WHERE " + columnID() + " = :id");
    if(readPointsByID_.lastError().text() != " ")
    {
        qWarning() << "prepare select points" << readPointsByID_.lastError().text();
        return false;
    }

    readAllPointsIDs_ = QSqlQuery(dataBase());
    readAllPointsIDs_.prepare("SELECT DISTINCT " + columnID() + " FROM " + tableName() + "");
    if(readAllPointsIDs_.lastError().text() != " ")
    {
        qWarning() << "prepare select points ids" << readAllPointsIDs_.lastError().text();
        return false;
    }

    statisticsMaxSequenceLengthId = QSqlQuery(dataBase());
    statisticsMaxSequenceLengthId.prepare("select id, c from (select "
                                          + columnID() + " as id, count(*) as c from "
                                          + tableName() + " group by id order by c desc);");
    if(statisticsMaxSequenceLengthId.lastError().text() != " ")
    {
        qWarning() << "prepare select max sequence length" << statisticsMaxSequenceLengthId.lastError().text();
        qWarning() << statisticsMaxSequenceLengthId.lastQuery();
        return false;
    }

    statisticsMinSequenceLengthId = QSqlQuery(dataBase());
    statisticsMinSequenceLengthId.prepare("select id, c from (select "
                                          + columnID() + " as id, count(*) as c from "
                                          + tableName() + " group by id order by c asc) limit 1;");
    if(statisticsMinSequenceLengthId.lastError().text() != " ")
    {
        qWarning() << "prepare select min sequence length" << statisticsMinSequenceLengthId.lastError().text();
        qWarning() << statisticsMinSequenceLengthId.lastQuery();
        return false;
    }

    statisticsAverageSequenceLength = QSqlQuery(dataBase());
    statisticsAverageSequenceLength.prepare("select AVG(c) from (select "
                                            + columnID() + ", count(*) as c from "
                                            + tableName() + " group by id)");
    if(statisticsAverageSequenceLength.lastError().text() != " ")
    {
        qWarning() << "prepare select average sequence length" << statisticsAverageSequenceLength.lastError().text();
        qWarning() << statisticsAverageSequenceLength.lastQuery();
        return false;
    }

    statisticsAverageNullCountPoints = QSqlQuery(dataBase());
    statisticsAverageNullCountPoints.prepare("select (select count(*) from "
                                             + tableName() +
                                             " where " + columnVALUE() +
                                             " = 0) / (select cast(count(*) as float) from (select distinct "
                                             + columnID() + " from "
                                             + tableName() + "))");
    if(statisticsAverageNullCountPoints.lastError().text() != " ")
    {
        qWarning() << "prepare select average null count points" << statisticsAverageNullCountPoints.lastError().text();
        qWarning() << statisticsAverageNullCountPoints.lastQuery();
        return false;
    }

    statisticsAverageNoneNullCountPoints = QSqlQuery(dataBase());
    statisticsAverageNoneNullCountPoints.prepare("select (select count(*) from "
                                                 + tableName() +
                                                 " where " + columnVALUE() +
                                                 " <> 0) / (select cast(count(*) as float) from (select distinct "
                                                 + columnID() + " from "
                                                 + tableName() + "))");
    if(statisticsAverageNoneNullCountPoints.lastError().text() != " ")
    {
        qWarning() << "prepare select average none null count points" << statisticsAverageNoneNullCountPoints.lastError().text();
        qWarning() << statisticsAverageNoneNullCountPoints.lastQuery();
        return false;
    }

    statisticsPercentNullCountPoints = QSqlQuery(dataBase());
    statisticsPercentNullCountPoints.prepare("select (select count(*) from "
                                             + tableName() +
                                             " where " + columnVALUE() +
                                             " = 0) / (select cast(count(*) as float) from "
                                             + tableName() + ") * 100");
    if(statisticsPercentNullCountPoints.lastError().text() != " ")
    {
        qWarning() << "prepare select average null percent points" << statisticsPercentNullCountPoints.lastError().text();
        qWarning() << statisticsPercentNullCountPoints.lastQuery();
        return false;
    }

    statisticsPercentNoneNullCountPoints = QSqlQuery(dataBase());
    statisticsPercentNoneNullCountPoints.prepare("select (select count(*) from "
                                                 + tableName() +
                                                 " where " + columnVALUE() +
                                                 " <> 0) / (select cast(count(*) as float) from "
                                                 + tableName() + ") * 100");
    if(statisticsPercentNoneNullCountPoints.lastError().text() != " ")
    {
        qWarning() << "prepare select average null percent points" << statisticsPercentNoneNullCountPoints.lastError().text();
        qWarning() << statisticsPercentNoneNullCountPoints.lastQuery();
        return false;
    }

    statisticsMaxPoint = QSqlQuery(dataBase());
    statisticsMaxPoint.prepare("select MAX(" + columnVALUE() + ") FROM " + tableName());
    if(statisticsMaxPoint.lastError().text() != " ")
    {
        qWarning() << "prepare select max point" << statisticsMaxPoint.lastError().text();
        qWarning() << statisticsMaxPoint.lastQuery();
        return false;
    }

    statisticsMinPoint = QSqlQuery(dataBase());
    statisticsMinPoint.prepare("select MIN(" + columnVALUE() + ") FROM " + tableName());
    if(statisticsMinPoint.lastError().text() != " ")
    {
        qWarning() << "prepare select min point" << statisticsMinPoint.lastError().text();
        qWarning() << statisticsMinPoint.lastQuery();
        return false;
    }


    statisticsFiveTopPointsValue = QSqlQuery(dataBase());
    statisticsFiveTopPointsValue.prepare("SELECT value, count(" + columnVALUE()
                                         + ") FROM " + tableName() + " GROUP BY "
                                         + columnVALUE() + " ORDER BY count("
                                         + columnVALUE() + ") DESC LIMIT 5");
    if(statisticsFiveTopPointsValue.lastError().text() != " ")
    {
        qWarning() << "prepare select five top points value" << statisticsFiveTopPointsValue.lastError().text();
        qWarning() << statisticsFiveTopPointsValue.lastQuery();
        return false;
    }


    statisticsSequenceWithRepeatCount = QSqlQuery(dataBase());
    statisticsSequenceWithRepeatCount.prepare("select count(*) from (select distinct ps1.id from "
                                              + tableName() + " as ps1 inner join "
                                              + tableName() + " as ps2 on ps1."
                                              + columnID() + " = ps2."
                                              + columnID() + " and ps1."
                                              + columnNUM() + " = ps2."
                                              + columnNUM() + " + 1 and ps1."
                                              + columnVALUE() + " = ps2."
                                              +columnVALUE() + ");");
    if(statisticsSequenceWithRepeatCount.lastError().text() != " ")
    {
        qWarning() << "prepare select sequence with repeat count" << statisticsSequenceWithRepeatCount.lastError().text();
        qWarning() << statisticsSequenceWithRepeatCount.lastQuery();
        return false;
    }

    return true;
}

PointList SqlPointListReader::read(const ID &item)
{
    if(isOpen())
    {
        PointList points;

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
    return IDList();
}

PointListStorageStatistics SqlPointListReader::statistics()
{
    PointListStorageStatistics storageStatistics;


    if(statisticsMaxSequenceLengthId.exec())
    {
        if(statisticsMaxSequenceLengthId.first())
        {

            storageStatistics << PointListStatistics("max-sequence-length-id", statisticsMaxSequenceLengthId.value(0));
            storageStatistics << PointListStatistics("max-sequence-length", statisticsMaxSequenceLengthId.value(1));

            QStringList fiveTopSequenceIds;
            for(int i = 0; i < 5; i++)
            {
                fiveTopSequenceIds << statisticsMaxSequenceLengthId.value(0).toString();
                if(!statisticsMaxSequenceLengthId.next())
                {
                    break;
                }
            }

            storageStatistics << PointListStatistics("five-top-sequence-length", fiveTopSequenceIds);

        }
    }

    if(statisticsMinSequenceLengthId.exec())
    {
        if(statisticsMinSequenceLengthId.first())
        {

            storageStatistics << PointListStatistics("min-sequence-length-id", statisticsMinSequenceLengthId.value(0));
            storageStatistics << PointListStatistics("min-sequence-length", statisticsMinSequenceLengthId.value(1));
        }
    }



    if(statisticsAverageSequenceLength.exec())
    {
        if(statisticsAverageSequenceLength.first())
        {

            storageStatistics << PointListStatistics("average-sequence-length", statisticsAverageSequenceLength.value(0));
        }
    }


    if(statisticsAverageNullCountPoints.exec())
    {
        if(statisticsAverageNullCountPoints.first())
        {

            storageStatistics << PointListStatistics("average-null-count-points", statisticsAverageNullCountPoints.value(0));
        }
    }


    if(statisticsAverageNoneNullCountPoints.exec())
    {
        if(statisticsAverageNoneNullCountPoints.first())
        {

            storageStatistics << PointListStatistics("average-none-null-count-points", statisticsAverageNoneNullCountPoints.value(0));
        }
    }

    if(statisticsPercentNullCountPoints.exec())
    {
        if(statisticsPercentNullCountPoints.first())
        {

            storageStatistics << PointListStatistics("percent-null-count-points", statisticsPercentNullCountPoints.value(0));
        }
    }


    if(statisticsPercentNoneNullCountPoints.exec())
    {
        if(statisticsPercentNoneNullCountPoints.first())
        {

            storageStatistics << PointListStatistics("percent-none-null-count-points", statisticsPercentNoneNullCountPoints.value(0));
        }
    }

    if(statisticsMaxPoint.exec())
    {
        if(statisticsMaxPoint.first())
        {

            storageStatistics << PointListStatistics("max-point", statisticsMaxPoint.value(0));
        }
    }

    if(statisticsMinPoint.exec())
    {
        if(statisticsMinPoint.first())
        {

            storageStatistics << PointListStatistics("min-point", statisticsMinPoint.value(0));
        }
    }



    if(statisticsFiveTopPointsValue.exec())
    {
        if(statisticsFiveTopPointsValue.first())
        {

            storageStatistics << PointListStatistics("min-point", statisticsFiveTopPointsValue.value(0));

            QStringList fiveTopPointsValue;
            for(int i = 0; i < 5; i++)
            {
                fiveTopPointsValue << statisticsFiveTopPointsValue.value(0).toString();
                if(!statisticsFiveTopPointsValue.next())
                {
                    break;
                }
            }

            storageStatistics << PointListStatistics("five-top-points-value", fiveTopPointsValue);
        }
    }

    if(statisticsSequenceWithRepeatCount.exec())
    {
        if(statisticsSequenceWithRepeatCount.first())
        {

            storageStatistics << PointListStatistics("sequence-with-repeat-count", statisticsSequenceWithRepeatCount.value(0));
        }
    }

    return storageStatistics;
}
