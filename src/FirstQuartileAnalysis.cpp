#include "FirstQuartileAnalysis.h"

FirstQuartileAnalysis::FirstQuartileAnalysis() :
    AbstractAnalysis("first-quartile")
{
}

FirstQuartileAnalysis::FirstQuartileAnalysis(const FirstQuartileAnalysis &a):
    AbstractAnalysis("first-quartile")
{
}

double FirstQuartileAnalysis::analyze(const PointList &values) const
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

    PointList firstPart;

    if(even)
    {
        for(int i = 0; i < index; i++)
        {
            firstPart.append(sortedList.at(i));
        }
    }
    else
    {
        for(int i = 0; i < (index + 1); i++)
        {
            firstPart.append(sortedList.at(i));
        }
    }

    MedianAnalysis median;

    return median.analyze(firstPart);
}

FirstQuartileAnalysis *FirstQuartileAnalysis::clone()
{
    return new FirstQuartileAnalysis(*this);
}
