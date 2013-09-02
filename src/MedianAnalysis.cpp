#include "MedianAnalysis.h"

MedianAnalysis::MedianAnalysis():
    AbstractAnalysis("median")
{

}

MedianAnalysis::MedianAnalysis(const MedianAnalysis &a):
    AbstractAnalysis("median")
{
}

double MedianAnalysis::analyze(const PointList &values) const
{
    QList<Point> sortedList = values.points();
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

    if(even)
    {
        return (sortedList.at(index) + sortedList.at(index-1)) / 2.0;
    }
    else
    {
        return sortedList.at(index);
    }
}

MedianAnalysis *MedianAnalysis::clone()
{
    return new MedianAnalysis(*this);
}
