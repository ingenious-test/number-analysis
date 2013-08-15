#include "TestingUtilities.h"

QString sequencePointListToString(const SequencePointList &spl)
{
    QString stringRepresentation;

    foreach(const PointList &pl, spl)
    {
        stringRepresentation += "(" + pointListToString(pl) + ")\n";
    }

    return stringRepresentation;
}

QString pointListToString(const PointList &pl)
{
    QStringList pointsRepresentation;
    foreach(const Point &p, pl)
    {
        pointsRepresentation << QString::number(p);
    }
    return pointsRepresentation.join(",");
}

bool pointListFuzzyCompare(const PointList& actual, const PointList& expected)
{
    const int sizeActual = actual.size();
    const int sizeExpected = expected.size();

    if(sizeActual != sizeExpected)
    {
        return false;
    }

    for(int i = 0; i < actual.size(); i++)
    {
        bool isCompare = fuzzyCompare(actual[i],expected[i]);
        if(!isCompare)
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

QString analysisResultsToString(const AnalysisResults analysisResults)
{
    QString stringRepresentation;

    QHashIterator<ID, AnalysisResult> analysisResult(analysisResults);
    while (analysisResult.hasNext())
    {
        analysisResult.next();
        stringRepresentation += analysisResult.key() + ":\n"
                + analysisResultToString(analysisResult.value()) + "\n\n";
    }

    return stringRepresentation;
}

QString analysisResultToString(const AnalysisResult analysisResult)
{
    QStringList resultRepresentation;

    QHashIterator<IDAnalysis, double> result(analysisResult);
    while (result.hasNext())
    {
        result.next();
        resultRepresentation << result.key() + ": " + QString::number(result.value());
    }
    return resultRepresentation.join("\n");
}

bool analysisResultFuzzyCompare(const AnalysisResult& actual, const AnalysisResult& expected)
{
    const QList<IDAnalysis> keysActual = actual.keys();
    const QList<IDAnalysis> keysExpected = expected.keys();

    if(keysActual != keysExpected)
    {
        return false;
    }

   QHashIterator<IDAnalysis, double> result(actual);
    while (result.hasNext())
    {
        result.next();

        const double actualResult = result.value();
        const double expectedResult = expected.value(result.key());

        bool isCompare = fuzzyCompare(actualResult, expectedResult);

        if(!isCompare)
        {
            return false;
        }
    }

    return true;
}

bool analysisResultsFuzzyCompare(const AnalysisResults& actual, const AnalysisResults& expected)
{
    const QList<ID> keysActual = actual.keys();
    const QList<ID> keysExpected = expected.keys();

     if(keysActual != keysExpected)
    {
        return false;
    }

     QHashIterator<ID, AnalysisResult> analysisResult(actual);
     while (analysisResult.hasNext())
     {
         analysisResult.next();
         bool isCompare = analysisResultFuzzyCompare(analysisResult.value(),
                                                     expected.value(analysisResult.key()));
         if(!isCompare)
         {
             return false;
         }
     }


    return true;
}

 bool fuzzyCompare(const double actual, const double expected)
{
    const double eps = 0.0001;
    const bool result = (qAbs(actual - expected)  <= eps);
    return result;
}
