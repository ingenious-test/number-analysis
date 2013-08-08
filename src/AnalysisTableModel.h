#ifndef ANALYSISTABLEMODEL_H

#define ANALYSISTABLEMODEL_H

#include <QAbstractItemModel>

#include "AnalysisCollection.h"

typedef QList<PointList> SequencePointList;
Q_DECLARE_METATYPE(SequencePointList)

typedef QList<AnalysisResult> AnalysisResults;
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

    IDList getHeaders();
    void analyze();

    const AnalysisResults& Results();

    const AnalysisCollection& analysisCollection();
    AnalysisCollection& addAnalysis(AbstractAnalysis *analysis);
    void removeAnalysis(const QString &name);
    void clearAnalyses();


    const SequencePointList &sequencePointList();
    void addPointList(const PointList& pointList);
    void removePointList(const int index);

private:
    AnalysisResults results_;
    AnalysisCollection collection_;
    SequencePointList seqPointList_;



};

#endif // ANALYSISTABLEMODEL_H
