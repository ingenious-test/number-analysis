#include "SqlPointListInterface.h"

SqlPointListInterface::SqlPointListInterface(const QString &dataBaseName) :
    dataBaseName_(dataBaseName),
    connectionName_("connection")
{
    if(QSqlDatabase::contains(connectionName_))
    {
        dataBase_ = QSqlDatabase::database(connectionName_);
    }
    else
    {
        dataBase_ = QSqlDatabase::addDatabase("QSQLITE", "connection");
    }

    dataBase_.setDatabaseName(dataBaseName_);
    if (!dataBase_.open())
    {
        qWarning() << "can't open database " << dataBaseName_;
        return;
    }

    QSqlQuery query(dataBase_);
    bool querySuccess = false;

    querySuccess = execQuery(query, "CREATE TABLE IF NOT EXISTS tableName (id, num, value, PRIMARY KEY(id, num))");
}

SqlPointListInterface::~SqlPointListInterface()
{
    //  QSqlDatabase::removeDatabase("connection");
}

QString SqlPointListInterface::dataBaseName() const
{
    return dataBaseName_;
}

QSqlDatabase SqlPointListInterface::dataBase() const
{
    return dataBase_;
}

bool SqlPointListInterface::execQuery(QSqlQuery &query, const QString& queryStr)
{
    QString errorStr;
    const bool preraredSuccess = query.prepare(queryStr);
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
