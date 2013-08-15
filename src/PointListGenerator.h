#ifndef POINTLISTGENERATOR_H

#define POINTLISTGENERATOR_H

#include "AbstractAnalysis.h"

class PointListGenerator
{
public:
    PointListGenerator();
    PointList generateConst(int lenght);
    PointList generateConst(const int lenght, const Point value);
    PointList generateConst(const int start, const int end);
};

#endif // POINTLISTGENERATOR_H
