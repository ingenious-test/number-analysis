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
    QList<Point> sortedList = values.clonePoints();
    qSort(sortedList);

    if(sortedList.isEmpty())
    {
        return 0.0;
    }

    if(sortedList.count() == 1)
    {
        return sortedList.first();
    }

    const bool even = (sortedList.count() % 2 == 0);

    if(even)
    {
        const int index = sortedList.count() / 2;
        return (sortedList.at(index) + sortedList.at(index-1)) / 2.0;
    }
    else
    {
        const int index = sortedList.count() / 2;
        return sortedList.at(index);
    }
}

MedianAnalysis *MedianAnalysis::clone()
{
    return new MedianAnalysis(*this);
}
