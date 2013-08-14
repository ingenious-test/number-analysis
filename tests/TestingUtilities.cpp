#include "TestingUtilities.h"

bool pointListFuzzyCompare(const PointList& actual, const PointList& expected)
{
    const int eps = 0.0001;
    const int sizeActual = actual.size();
    const int sizeExpected = expected.size();

    if(sizeActual != sizeExpected)
    {
        return false;
    }

    for(int i = 0; i < actual.size(); i++)
    {
        if(qAbs(actual[i] - expected[i]) < eps)
        {
            return false;
        }
    }

    return true;
}

bool seqPointListFuzzyCompare(const SequencePointList& actual, const SequencePointList& expected)
{
    const int sizeActual = actual.size();
    const int sizeExpected = expected.size();

    if(sizeActual != sizeExpected)
    {

        return false;
    }

    for(int i = 0; i < actual.size(); i++)
    {
        bool isCompare = pointListFuzzyCompare(actual[i], expected[i]);
        if(!isCompare)
        {
            return false;
        }
    }

    return true;
}
