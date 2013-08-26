#include "ThirdQuartileAnalysis.h"

ThirdQuartileAnalysis::ThirdQuartileAnalysis() :
    AbstractAnalysis("third-quartile")
{
}

ThirdQuartileAnalysis::ThirdQuartileAnalysis(const ThirdQuartileAnalysis &a):
    AbstractAnalysis("third-quartile")
{
}

double ThirdQuartileAnalysis::analyze(const PointList &values) const
{
    QList<Point> sortedList = values.clonePoints();
    qSort(sortedList);
    const int listCount = sortedList.count();

    if(sortedList.isEmpty())
    {
        return 0.0;
    }

    if(listCount == 1)
    {
        return sortedList.first();
    }

    const bool even = (listCount % 2 == 0);
    const int index = listCount / 2;

    PointList secondPart;

    if(even)
    {
        for(int i = index ; i < listCount; i++)
        {
            secondPart.append(sortedList.at(i));
        }
    }
    else
    {
        for(int i = index; i < listCount; i++)
        {
            secondPart.append(sortedList.at(i));
        }
    }

    MedianAnalysis median;

    return median.analyze(secondPart);
}

ThirdQuartileAnalysis *ThirdQuartileAnalysis::clone()
{
    return new ThirdQuartileAnalysis(*this);
}
