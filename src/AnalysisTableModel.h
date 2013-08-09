#ifndef ANALYSISTABLEMODEL_H

#define ANALYSISTABLEMODEL_H

#include <QAbstractItemModel>

#include "AnalysisCollection.h"


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
};
Q_DECLARE_METATYPE(AnalysisResults)

class AnalysisTableModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    AnalysisTableModel(QObject *parent = 0);
    AnalysisTableModel(const AnalysisCollection &colletions,
                       const SequencePointList &seq = SequencePointList(),
                       QObject *parent = 0);

    ~AnalysisTableModel();

    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const;
    QModelIndex parent(const QModelIndex &child) const;

    int rowCount(const QModelIndex &parent  = QModelIndex()) const;
    int columnCount(const QModelIndex &parent  = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    QVariant headerData(int section, Qt::Orientation orientation = Qt::Horizontal, int role = Qt::DisplayRole) const;

    IDAnalysisList getHeaders();
    void analyze();

    const AnalysisResults& Results();

    const AnalysisCollection& analysisCollection();
    AnalysisCollection& addAnalysis(AbstractAnalysis *analysis);
    void removeAnalysis(const QString &name);


private:
    AnalysisResults results_;
    AnalysisCollection collection_;
    SequencePointList seqPointList_;



};

#endif // ANALYSISTABLEMODEL_H
