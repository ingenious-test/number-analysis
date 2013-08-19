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

    if(writer.isOpen())
    {
        pointList = pointListGenerator.generateByLenghtValue(20, Point(0.0));
        writer.write(ID("twenty-zeros"), pointList);

        pointList = pointListGenerator.generateByLenghtValue(20, Point(3.0));
        writer.write(ID("twenty-triples"), pointList);

        pointList = pointListGenerator.generateByLenghtConst(20);
        writer.write(ID("from-one-to-twenty"), pointList);


        pointList = pointListGenerator.generateByLenghtConst(10);
        writer.write(ID("from-one-to-ten"), pointList);

        pointList = pointListGenerator.generateStartEnd(10, 20);
        writer.write(ID("from-ten-to-twenty"), pointList);

        pointList = pointListGenerator.generateByLenghtValue(40, Point(3.0));
        writer.write(ID("forty-triples"), pointList);

        pointList = pointListGenerator.generateByLenghtValue(30, Point(1.0));
        writer.write(ID("thirty-one"), pointList);

        pointList = pointListGenerator.generateStartEnd(20, 30);
        writer.write(ID("from-twenty-to-thirty"), pointList);

        pointList = pointListGenerator.generateStartEnd(12, 20);
        writer.write(ID("from-twelve-to-twenty"), pointList);

        pointList = pointListGenerator.generateStartEnd(2, 8);
        writer.write(ID("from-two-to-eight"), pointList);
    }



}
