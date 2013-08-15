#include "PointListGenerator.h"

PointListGenerator::PointListGenerator()
{
}

PointList PointListGenerator::generateConst(const int lenght)
{
    PointList pointList;

    for(int i = 1; i <= lenght; i++)
    {
        pointList.append(static_cast<double>(i));
    }

    return pointList;
}

PointList PointListGenerator::generateConst(const int lenght, const Point value)
{
    PointList pointList;

    for(int i = 1; i <= lenght; i++)
    {
        pointList.append(value);
    }

    return pointList;
}

PointList PointListGenerator::generateConst(const int start, const int end)
{
    PointList pointList;

    for(int i = start; i <= end; i++)
    {
        pointList.append(i);
    }

    return pointList;
}
