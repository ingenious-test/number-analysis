#ifndef STATISTICSCOLLECTION_H

#define STATISTICSCOLLECTION_H

#include "SqlPointListInterface.h"

class AbstractStatictics : public SqlPointListInterface
{
public:
    AbstractStatictics(
            const QString &name,
            const QString &dataBaseName = QString(),
            const QString &tableName = QString()) :
        SqlPointListInterface(dataBaseName, tableName),
        name_(name)
    {

    }

    QString name() const
    {
        return name_;
    }

    bool prepareQueries()
    {
        query_ = QSqlQuery(dataBase());
        query_.prepare(queryCode());

        if(query_.lastError().text() != " ")
        {
            qWarning() << prepareWarnings() << query_.lastError().text();
            qWarning() << query_.lastQuery();
            return false;
        }

        return true;
    }

    QVariant exec()
    {
        if(isOpen())
        {
            if(query_.exec())
            {
                QVariantList resultList;
                while(query_.next())
                {
                    resultList << query_.value(0);
                }

                if(resultList.size() == 1)
                {
                    return resultList.at(0);
                }
                else
                {
                    return QVariant(resultList);
                }
            }
        }

        return QVariant();
    }

protected:
    virtual QString prepareWarnings() = 0;
    virtual QString queryCode() const = 0;

private:
    QSqlQuery query_;
    QString name_;
};

typedef QList<AbstractStatictics*> StatisticsList;

class MaxSequenceLengthIdStatistics : public AbstractStatictics
{
public:
    MaxSequenceLengthIdStatistics() :
        AbstractStatictics("max-sequence-length-id")
    {

    }

protected:
    QString queryCode() const
    {
        return "SELECT " + columnID() + ", count("
                + columnVALUE() + ") FROM "
                + tableName() + " GROUP BY "
                + columnID() + " ORDER BY count("
                + columnVALUE() + ") DESC LIMIT 1;";
    }

    QString prepareWarnings()
    {
        return "prepare select max sequence id length";
    }
};

class MaxSequenceLengthStatistics : public AbstractStatictics
{
public:
    MaxSequenceLengthStatistics() :
        AbstractStatictics("max-sequence-length")
    {

    }

protected:
    QString queryCode() const
    {
        return "SELECT count("
                + columnVALUE() + ") FROM "
                + tableName() + " GROUP BY "
                + columnID() + " ORDER BY count("
                + columnVALUE() + ") DESC LIMIT 1;";
    }

    QString prepareWarnings()
    {
        return "prepare select max sequence length";
    }
};

class FiveTopSequenceLengthStatistics : public AbstractStatictics
{
public:
    FiveTopSequenceLengthStatistics() :
        AbstractStatictics("five-top-sequence-length")
    {

    }

protected:
    QString queryCode() const
    {
        return "SELECT " + columnID() + ", count("
                + columnVALUE() + ") FROM "
                + tableName() + " GROUP BY "
                + columnID() + " ORDER BY count("
                + columnVALUE() + ") DESC LIMIT 5;";
    }

    QString prepareWarnings()
    {
        return "prepare select five top sequence length";
    }
};

class MinSequenceLengthIdStatistics : public AbstractStatictics
{
public:
    MinSequenceLengthIdStatistics() :
        AbstractStatictics("min-sequence-length-id")
    {

    }

protected:
    QString queryCode() const
    {
        return "SELECT " + columnID() + ", count("
                + columnVALUE() + ") FROM "
                + tableName() + " GROUP BY "
                + columnID() + " ORDER BY count("
                + columnVALUE() + ") ASC LIMIT 1;";
    }

    QString prepareWarnings()
    {
        return "prepare select min sequence id length";
    }
};

class MinSequenceLengthStatistics : public AbstractStatictics
{
public:
    MinSequenceLengthStatistics() :
        AbstractStatictics("min-sequence-length")
    {

    }

protected:
    QString queryCode() const
    {
        return "SELECT count("
                + columnVALUE() + ") FROM "
                + tableName() + " GROUP BY "
                + columnID() + " ORDER BY count("
                + columnVALUE() + ") ASC LIMIT 1;";
    }

    QString prepareWarnings()
    {
        return "prepare select min sequence length";
    }
};

class AverageSequenceLengthStatistics : public AbstractStatictics
{
public:
    AverageSequenceLengthStatistics() :
        AbstractStatictics("average-sequence-length")
    {

    }

protected:
    QString queryCode() const
    {
        return "select AVG(c) from (select "
                + columnID() + ", count(*) as c from "
                + tableName() + " group by id)";
    }

    QString prepareWarnings()
    {
        return "prepare select average sequence length";
    }
};

class AverageNullCountPointsStatistics : public AbstractStatictics
{
public:
    AverageNullCountPointsStatistics() :
        AbstractStatictics("average-null-count-points")
    {

    }

protected:
    QString queryCode() const
    {
        return "select (select count(*) from "
                + tableName() +
                " where " + columnVALUE() +
                " = 0) / (select cast(count(*) as float) from (select distinct "
                + columnID() + " from "
                + tableName() + "))";
    }

    QString prepareWarnings()
    {
        return "prepare select average null count points";
    }
};

class AverageNoneNullCountPointsStatistics : public AbstractStatictics
{
public:
    AverageNoneNullCountPointsStatistics() :
        AbstractStatictics("average-none-null-count-points")
    {

    }

protected:
    QString queryCode() const
    {
        return "select (select count(*) from "
                + tableName() +
                " where " + columnVALUE() +
                " <> 0) / (select cast(count(*) as float) from (select distinct "
                + columnID() + " from "
                + tableName() + "))";
    }

    QString prepareWarnings()
    {
        return "prepare select average none null count points";
    }
};

class PercentNullCountPointsStatistics : public AbstractStatictics
{
public:
    PercentNullCountPointsStatistics() :
        AbstractStatictics("percent-null-count-points")
    {

    }

protected:
    QString queryCode() const
    {
        return "select (select count(*) from "
                + tableName() +
                " where " + columnVALUE() +
                " = 0) / (select cast(count(*) as float) from "
                + tableName() + ") * 100";
    }

    QString prepareWarnings()
    {
        return "prepare select null percent points";
    }
};

class PercentNoneNullCountPointsStatistics : public AbstractStatictics
{
public:
    PercentNoneNullCountPointsStatistics() :
        AbstractStatictics("percent-none-null-count-points")
    {

    }

protected:
    QString queryCode() const
    {
        return "select (select count(*) from "
                + tableName() +
                " where " + columnVALUE() +
                " <> 0) / (select cast(count(*) as float) from "
                + tableName() + ") * 100";
    }

    QString prepareWarnings()
    {
        return "prepare select none null percent points";
    }
};

class MaxPointStatistics : public AbstractStatictics
{
public:
    MaxPointStatistics() :
        AbstractStatictics("max-point")
    {

    }

protected:
    QString queryCode() const
    {
        return "select MAX("
                + columnVALUE()
                + ") FROM "
                + tableName();
    }

    QString prepareWarnings()
    {
        return "prepare select max point";
    }
};

class MinPointStatistics : public AbstractStatictics
{
public:
    MinPointStatistics() :
        AbstractStatictics("min-point")
    {

    }

protected:
    QString queryCode() const
    {
        return "select MIN("
                + columnVALUE()
                + ") FROM "
                + tableName();
    }

    QString prepareWarnings()
    {
        return "prepare select min point";
    }
};

class FiveTopPointsValueStatistics : public AbstractStatictics
{
public:
    FiveTopPointsValueStatistics() :
        AbstractStatictics("five-top-points-value")
    {

    }

protected:
    QString queryCode() const
    {
        return "SELECT value, count(" + columnVALUE()
                + ") FROM " + tableName() + " GROUP BY "
                + columnVALUE() + " ORDER BY count("
                + columnVALUE() + ") DESC LIMIT 5";
    }

    QString prepareWarnings()
    {
        return "prepare select five top points value";
    }
};

class SequenceWithRepeatCountStatistics : public AbstractStatictics
{
public:
    SequenceWithRepeatCountStatistics() :
        AbstractStatictics("sequence-with-repeat-count")
    {

    }

protected:
    QString queryCode() const
    {
        return "select count(*) from (select distinct ps1.id from "
                + tableName() + " as ps1 inner join "
                + tableName() + " as ps2 on ps1."
                + columnID() + " = ps2."
                + columnID() + " and ps1."
                + columnNUM() + " = ps2."
                + columnNUM() + " + 1 and ps1."
                + columnVALUE() + " = ps2."
                +columnVALUE() + ");";
    }

    QString prepareWarnings()
    {
        return "prepare select sequence with repeat count";
    }
};

class IncSequenceCountStatistics : public AbstractStatictics
{
public:
    IncSequenceCountStatistics() :
        AbstractStatictics("inc-sequences-count")
    {

    }

protected:
    QString queryCode() const
    {
        return "SELECT count( * ) FROM ( SELECT table1."
                + columnID() + ", table1.count, table2.count FROM ( SELECT ps1."
                + columnID() + " AS id, count( * ) AS count  FROM "
                + tableName() + " AS ps1 INNER JOIN "
                + tableName() + " AS ps2 ON ps1."
                + columnID() + " = ps2."
                + columnID() + " AND ps1."
                + columnNUM() + " = ps2."
                + columnNUM() + " + 1 WHERE ps1."
                + columnVALUE() + " - ps2."
                +columnVALUE() + " > 0 GROUP BY ps1."
                + columnID() + ") AS table1 INNER JOIN (SELECT "
                + columnID() + ", count( * ) - 1 AS count FROM "
                + tableName() + " GROUP BY "
                + columnID() + ") AS table2 ON table1.id = table2.id AND table1.count = table2.count);";
    }

    QString prepareWarnings()
    {
        return "prepare select increasing sequence count";
    }
};


class DecSequenceCountStatistics : public AbstractStatictics
{
public:
    DecSequenceCountStatistics() :
        AbstractStatictics("dec-sequences-count")
    {

    }

protected:
    QString queryCode() const
    {
        return "SELECT count( * ) FROM ( SELECT table1."
                + columnID() + ", table1.count, table2.count FROM ( SELECT ps1."
                + columnID() + " AS id, count( * ) AS count  FROM "
                + tableName() + " AS ps1 INNER JOIN "
                + tableName() + " AS ps2 ON ps1."
                + columnID() + " = ps2."
                + columnID() + " AND ps1."
                + columnNUM() + " = ps2."
                + columnNUM() + " + 1 WHERE ps1."
                + columnVALUE() + " - ps2."
                +columnVALUE() + " < 0 GROUP BY ps1."
                + columnID() + ") AS table1 INNER JOIN (SELECT "
                + columnID() + ", count( * ) - 1 AS count FROM "
                + tableName() + " GROUP BY "
                + columnID() + ") AS table2 ON table1.id = table2.id AND table1.count = table2.count);";
    }

    QString prepareWarnings()
    {
        return "prepare select decreasing sequence count";
    }
};



#endif // STATISTICSCOLLECTION_H
