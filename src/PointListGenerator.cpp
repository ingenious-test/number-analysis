#include "PointListGenerator.h"

PointListGenerator::PointListGenerator()
{
}

PointList PointListGenerator::generateConst(int lenght)
{
    PointList pointList;

    for(int i = 1; i <= lenght; i++)
    {
        pointList.append(i);
    }

    return pointList;
}
