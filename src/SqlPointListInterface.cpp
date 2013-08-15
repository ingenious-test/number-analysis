#include "SqlPointListInterface.h"

const QString SqlPointListInterface::connectionName_("connection");
const ColumnsName SqlPointListInterface::columnID_("id");
const ColumnsName SqlPointListInterface::columnNUM_("num");
const ColumnsName SqlPointListInterface::columnVALUE_("value");

SqlPointListInterface::SqlPointListInterface(const QString &dataBaseName, const QString& tableName) :
    dataBaseName_(dataBaseName),
    tableName_(tableName),
    open_(false)
{

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

bool SqlPointListInterface::createTable(QSqlQuery &query)
{
    QString queryStr = "CREATE TABLE IF NOT EXISTS "
            + tableName_ +
            " (" + columnID() + ", " + columnNUM() + ", " + columnVALUE()
            + ", PRIMARY KEY(" + columnID() + ", " + columnNUM() + "))";



    bool result = execQuery(query, queryStr);
    return result;
}

void SqlPointListInterface::removeConnection()
{
    if(QSqlDatabase::contains(connectionName_))
    {

        QSqlDatabase::removeDatabase(connectionName_);
    }
}

bool SqlPointListInterface::open()
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
        open_ = false;
        return false;
    }

    QSqlQuery query(dataBase_);

    const bool createTableSuccess = createTable(query);
    if(!createTableSuccess)
    {
        open_ = false;
        return false;
    }


    if(prepareQueries())
    {
        open_ = true;
        return true;
    }

    open_ = false;
    return false;
}

bool SqlPointListInterface::isOpen() const
{
    return open_;
}

const ColumnsName &SqlPointListInterface::columnID()
{
    return columnID_;
}

const ColumnsName &SqlPointListInterface::columnNUM()
{
    return columnNUM_;
}

const ColumnsName &SqlPointListInterface::columnVALUE()
{
    return columnVALUE_;
}
