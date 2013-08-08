#ifndef ANALYSISCOLLECTION_H

#define ANALYSISCOLLECTION_H

#include "AbstractAnalysis.h"

class AnalysisResult : public QHash<QString, double>
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
};
Q_DECLARE_METATYPE(AnalysisResult)


class AnalysisList : public QHash<QString, AbstractAnalysis*>
{
public:
    AnalysisList& insertInc(AbstractAnalysis* value)
    {
        QString name = value->name();

        if(contains(name))
        {
            delete this->value(name);
            remove(name);
        }

        insert(name, value);
        return *this;
    }
};
Q_DECLARE_METATYPE(AnalysisList)

class AnalysisCollection
{
    friend class AnalysisTableModel;

public:
    AnalysisCollection();
    AnalysisCollection(AnalysisList analyzes);

    ~AnalysisCollection();

    AnalysisResult analyze(const PointList &list) const;

    AnalysisCollection& addAnalysis(AbstractAnalysis *analysis);

    void removeAnalysis(const QString &name);
    void removeAll();

    const IDList getNameList() const;

    const int size() const;

    AnalysisCollection* clone();


private:
    AnalysisCollection(const AnalysisCollection& collection);
    AnalysisList analysisTable_;


};

#endif // ANALYSISCOLLECTION_H
