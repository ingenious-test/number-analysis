#ifndef POINTLISTGENERATOR_H

#define POINTLISTGENERATOR_H

#include "AbstractAnalysis.h"

class PointListGenerator
{
public:
    PointListGenerator();
    PointList generateByLenghtConst(int lenght);
    PointList generateByLenghtValue(const int lenght, const Point value);
    PointList generateStartEnd(const int start, const int end);
};

#endif // POINTLISTGENERATOR_H
