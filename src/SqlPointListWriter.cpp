#include "SqlPointListWriter.h"

SqlPointListWriter::SqlPointListWriter(const QString &dataBaseName, const QString &tableName) :
    SqlPointListInterface(dataBaseName, tableName)
{

}

void SqlPointListWriter::write(const ID &item, const PointList &points)
{
    if(isOpen())
    {
        dataBase().transaction();
        for(int num = 0; num < points.length(); ++num)
        {
            writePointsByID_.bindValue(":id", item);
            writePointsByID_.bindValue(":num", num);
            writePointsByID_.bindValue(":value", points.at(num));

            const bool querySuccess = writePointsByID_.exec();

            if(!querySuccess)
            {
                qWarning() << "exec insert table" << writePointsByID_.lastError().text();
                return;
            }
        }
        dataBase().commit();
        writePointsByID_.finish();
    }
    else
    {
        qWarning() << "database not open";
    }
}

void SqlPointListWriter::write(const IDList &items, const SequencePointList &seqPoints)
{
    if(items.size() != seqPoints.size())
    {
        qWarning() << "not equal sizes";
        return;
    }

    if(isOpen())
    {
        dataBase().transaction();
        for(int i = 0; i < items.size(); i++){
            for(int num = 0; num < seqPoints.at(i).length(); ++num)
            {
                writePointsByID_.bindValue(":id", items.at(i));
                writePointsByID_.bindValue(":num", num);
                writePointsByID_.bindValue(":value", seqPoints.at(i).at(num));

                const bool querySuccess = writePointsByID_.exec();

                if(!querySuccess)
                {
                    qWarning() << "exec insert table" << writePointsByID_.lastError().text();
                    return;
                }
            }
        }
        dataBase().commit();
        writePointsByID_.finish();
    }
    else
    {
        qWarning() << "database not open";
    }
}

bool SqlPointListWriter::prepareQueries()
{
    writePointsByID_ = QSqlQuery(dataBase());

    writePointsByID_.prepare("INSERT OR ABORT INTO " + tableName() + " VALUES(:id, :num, :value)");
    if(writePointsByID_.lastError().text() != " ")
    {
        qWarning() << "prepare insert points" << writePointsByID_.lastError().text();
        return false;
    }


    return true;
}
