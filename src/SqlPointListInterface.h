#ifndef SQLPOINTLISTINTERFACE_H

#define SQLPOINTLISTINTERFACE_H

#include <QSqlQuery>
#include <QSqlError>

#include <QDebug>

class SqlPointListInterface
{
    friend class AnalysisWindow;
    friend class BSqlPointListInterface;
public:
    SqlPointListInterface(const QString &dataBaseName, const QString &tableName);

    virtual ~SqlPointListInterface();

    QString dataBaseName() const;
    QSqlDatabase dataBase() const;
    QString tableName() const;

protected:
    bool execQuery(QSqlQuery &query, const QString& queryStr);
    static void removeConnection();

private:
    QSqlDatabase dataBase_;
    const QString dataBaseName_;

    const QString tableName_;

    static const QString connectionName;

};

#endif // SQLPOINTLISTINTERFACE_H
