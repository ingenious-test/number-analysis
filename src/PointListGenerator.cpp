#include "PointListGenerator.h"

PointListGenerator::PointListGenerator()
{
}

PointList PointListGenerator::generateByLenghtConst(const int lenght)
{
    PointList pointList;

    for(int i = 1; i <= lenght; i++)
    {
        pointList.append(static_cast<double>(i));
    }

    return pointList;
}

PointList PointListGenerator::generateByLenghtValue(const int lenght, const Point value)
{
    PointList pointList;

    for(int i = 1; i <= lenght; i++)
    {
        pointList.append(value);
    }

    return pointList;
}

PointList PointListGenerator::generateStartEnd(const int start, const int end)
{
    PointList pointList;

    if(start > end)
    {
        return pointList;
    }

    for(int i = start; i <= end; i++)
    {
        pointList.append(static_cast<Point>(i));
    }

    return pointList;
}
