#ifndef SQLPOINTLISTINTERFACE_H

#define SQLPOINTLISTINTERFACE_H

#include <QSqlQuery>
#include <QSqlError>

#include <QDebug>

class SqlPointListInterface
{
public:
    SqlPointListInterface(const QString &dataBaseName);

    virtual ~SqlPointListInterface();

    QString dataBaseName() const;
    QSqlDatabase dataBase() const;

    bool execQuery(QSqlQuery &query, const QString& queryStr);


private:
    QSqlDatabase dataBase_;
    const QString dataBaseName_;

    const QString connectionName_;
};

#endif // SQLPOINTLISTINTERFACE_H
