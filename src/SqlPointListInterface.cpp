#include "SqlPointListInterface.h"

const QString SqlPointListInterface::connectionName("connection");

SqlPointListInterface::SqlPointListInterface(const QString &dataBaseName, const QString& tableName) :
    dataBaseName_(dataBaseName),
    tableName_(tableName)
{
    if(QSqlDatabase::contains(connectionName))
    {
        dataBase_ = QSqlDatabase::database(connectionName);
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

    querySuccess = execQuery(query, "CREATE TABLE IF NOT EXISTS "
                             + tableName_ +
                             " (id, num, value, PRIMARY KEY(id, num))");
    query.finish();
}

SqlPointListInterface::~SqlPointListInterface()
{

}

QString SqlPointListInterface::dataBaseName() const
{
    return dataBaseName_;
}

QSqlDatabase SqlPointListInterface::dataBase() const
{
    return dataBase_;
}

QString SqlPointListInterface::tableName() const
{
    return tableName_;
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

void SqlPointListInterface::removeConnection()
{
    if(QSqlDatabase::contains(connectionName))
    {

        QSqlDatabase::removeDatabase(connectionName);
    }
}
