#ifndef SQLPOINTLISTINTERFACE_H

#define SQLPOINTLISTINTERFACE_H

#include <QSqlQuery>
#include <QSqlError>

#include <QDebug>

class SqlPointListInterface
{
public:
    SqlPointListInterface(const QString &dataBaseName, const QString &tableName);

    virtual ~SqlPointListInterface();

    QString dataBaseName() const;
    QSqlDatabase dataBase() const;
    QString tableName() const;

protected:
    bool execQuery(QSqlQuery &query, const QString& queryStr);


private:
    QSqlDatabase dataBase_;
    const QString dataBaseName_;

    const QString connectionName_;
    const QString tableName_;
};

#endif // SQLPOINTLISTINTERFACE_H
