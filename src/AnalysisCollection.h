#ifndef ANALYSISCOLLECTION_H

#define ANALYSISCOLLECTION_H

#include "AbstractAnalysis.h"

class AnalysisResult : public QHash<IDAnalysis, double>
{
public:
    AnalysisResult& insertInc(const IDAnalysis &name, const double &value)
    {
        if(contains(name))
        {
            remove(name);
        }

        insert(name, value);
        return *this;
    }


    QString toString() const
    {
        QStringList resultRepresentation;

        QHashIterator<IDAnalysis, double> result(*this);
        while (result.hasNext())
        {
            result.next();
            resultRepresentation << result.key() + ": " + QString::number(result.value());
        }
        return resultRepresentation.join("\n");
    }

    static bool fuzzyCompare(const AnalysisResult& actual, const AnalysisResult& expected)
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

            bool isCompare = PointList::fuzzyComparePoints(actualResult, expectedResult);

            if(!isCompare)
            {
                return false;
            }
        }

        return true;
    }

};


class AnalysisResults : public QHash<ID, AnalysisResult>
{
public:
    AnalysisResults& insertInc(const ID &id, const AnalysisResult &analysisResult)
    {
        if(contains(id))
        {
            remove(id);
        }

        insert(id, analysisResult);
        return *this;
    }

    QString toString() const
    {
        QString stringRepresentation;

        QHashIterator<ID, AnalysisResult> analysisResult(*this);
        while (analysisResult.hasNext())
        {
            analysisResult.next();
            stringRepresentation += analysisResult.key() + ":\n"
                    + analysisResult.value().toString() + "\n\n";
        }

        return stringRepresentation;
    }

    static bool fuzzyCompare(const AnalysisResults& actual, const AnalysisResults& expected)
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
             bool isCompare = AnalysisResult::fuzzyCompare(analysisResult.value(),
                                                         expected.value(analysisResult.key()));
             if(!isCompare)
             {
                 return false;
             }
         }


        return true;
    }

};



typedef QList<AbstractAnalysis*> AnalysisList;


class AnalysisCollection
{
    friend class AnalysisTableModel;

public:
    AnalysisCollection();
    AnalysisCollection(AnalysisList analyzes);

    ~AnalysisCollection();

    AnalysisResult analyze(const PointList &list) const;

    void addAnalysis(AbstractAnalysis *analysis);
    int indexOfAnalysis(const IDAnalysis& idAnalysis);
    void removeAnalysis(const int index);
    void removeAllAnalysis();

    const IDAnalysisList getIDList() const;
    const IDAnalysis getIDAt(const int index) const;

    int size() const;

    AnalysisCollection* clone();

private:
    AnalysisCollection(const AnalysisCollection& collection);
    AnalysisList analysisTable_;


};

#endif // ANALYSISCOLLECTION_H
