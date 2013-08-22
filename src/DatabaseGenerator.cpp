#include "DatabaseGenerator.h"

DatabaseGenerator::DatabaseGenerator()
{
}

void DatabaseGenerator::generateDataBase(const QString &dataBaseName, const QString& tableName)
{
    PointListGenerator pointListGenerator;
    PointList pointList;

    if(QFile::exists(dataBaseName))
    {
        if(!QFile::remove(dataBaseName))
        {
            qWarning() << "can't remove testing database";
            return;
        }
    }

    SqlPointListWriter writer(dataBaseName, tableName);
    writer.open();

    if(writer.isOpen())
    {
        pointList = pointListGenerator.generateByLenghtValue(20, Point(0.0));
        pointList.setID(ID("twenty-zeros"));
        writer.write(pointList);

        pointList = pointListGenerator.generateByLenghtValue(20, Point(3.0));
        pointList.setID(ID("twenty-triples"));
        writer.write(pointList);

        pointList = pointListGenerator.generateByLenghtConst(20);
        pointList.setID(ID("from-one-to-twenty"));
        writer.write(pointList);


        pointList = pointListGenerator.generateByLenghtConst(10);
        pointList.setID(ID("from-one-to-ten"));
        writer.write(pointList);

        pointList = pointListGenerator.generateStartEnd(10, 20);
        pointList.setID(ID("from-ten-to-twenty"));
        writer.write(pointList);

        pointList = pointListGenerator.generateByLenghtValue(40, Point(3.0));
        pointList.setID(ID("forty-triples"));
        writer.write(pointList);

        pointList = pointListGenerator.generateByLenghtValue(30, Point(1.0));
        pointList.setID(ID("thirty-one"));
        writer.write(pointList);

        pointList = pointListGenerator.generateStartEnd(20, 30);
        pointList.setID(ID("from-twenty-to-thirty"));
        writer.write(pointList);

        pointList = pointListGenerator.generateStartEnd(12, 20);
        pointList.setID(ID("from-twelve-to-twenty"));
        writer.write(pointList);

        pointList = pointListGenerator.generateStartEnd(2, 8);
        pointList.setID(ID("from-two-to-eight"));
        writer.write(pointList);
    }



}
