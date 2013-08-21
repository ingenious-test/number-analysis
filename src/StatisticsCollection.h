#ifndef STATISTICSCOLLECTION_H

#define STATISTICSCOLLECTION_H

#include "SqlPointListInterface.h"

class AbstractStatictics : public SqlPointListInterface
{
public:
    AbstractStatictics(const QString &dataBaseName,
                       const QString &tableName,
                       const QString &name,
                       const QString &warningMessage) :
        SqlPointListInterface(dataBaseName, tableName),
        name_(name),
        warningMessage_(warningMessage)
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
            qWarning() << warningMessage_ << query_.lastError().text();
            qWarning() << query_.lastQuery();
            return false;
        }
    }

    QVariant exec()
    {
        if(query_.exec())
        {
            if(query_.first())
            {

                return query_.value(0);
            }
        }

        return QVariant();
    }

protected:
    virtual QString queryCode() const = 0;

private:
    QSqlQuery query_;
    QString name_;
    QString warningMessage_;
};

class AverageSequenceLengthStatistics : public AbstractStatictics
{
public:
    AverageSequenceLengthStatistics(const QString &dataBaseName,
                                    const QString &tableName) :
        AbstractStatictics(dataBaseName,
                           tableName,
                           "average-sequence-length",
                           "prepare select average sequence length")
    {
        open();
    }

protected:
    QString queryCode() const
    {
        return "select AVG(c) from (select "
                + columnID() + ", count(*) as c from "
                + tableName() + " group by id)";
    }
};

class StatisticsCollection
{
public:
    StatisticsCollection();
};

#endif // STATISTICSCOLLECTION_H
