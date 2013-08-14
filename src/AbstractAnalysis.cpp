#include "AbstractAnalysis.h"

QString sequencePointListToString(const SequencePointList &spl)
{
    QString stringRepresentation;

    foreach(const PointList &pl, spl)
    {
        QStringList pointsRepresentation;
        foreach(const Point &p, pl)
        {
            pointsRepresentation << QString::number(p);
        }

        stringRepresentation += "(" + pointsRepresentation.join(",") + ")\n";
    }

    return stringRepresentation;
}

AbstractAnalysis::AbstractAnalysis(const IDAnalysis &id) :
    id_(id)
{

}

double AbstractAnalysis::listSum(const PointList &list)
{
    double sum = 0.0;
    foreach(const Point e, list)
    {
        sum += e;
    }
    return sum;
}

bool AbstractAnalysis::isValid()
{
    return !id_.isEmpty();
}


IDAnalysis AbstractAnalysis::id()
{
    return id_;
}
