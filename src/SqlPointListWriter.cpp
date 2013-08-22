#include "SqlPointListWriter.h"

SqlPointListWriter::SqlPointListWriter(const QString &dataBaseName, const QString &tableName) :
    SqlPointListInterface(dataBaseName, tableName)
{

}

void SqlPointListWriter::write(const PointList &points)
{
    if(!points.isValid())
    {
        qWarning() << "Point list do not valid";
        return ;
    }

    if(isOpen())
    {
        dataBase().transaction();
        for(int num = 0; num < points.count(); ++num)
        {
            writePointsByID_.bindValue(":id", points.id());
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

void SqlPointListWriter::write(const SequencePointList &seqPoints)
{
    if(seqPoints.isEmpty())
    {
        qWarning() << "empty SequencePointList";
        return;
    }

    if(!seqPoints.isValid())
    {
        qWarning() << "not valid SequencePointList";
        return;
    }

    if(isOpen())
    {
        dataBase().transaction();
        for(int i = 0; i < seqPoints.count(); i++){
            for(int num = 0; num < seqPoints.at(i).count(); ++num)
            {
                writePointsByID_.bindValue(":id",  seqPoints.at(i).id());
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
