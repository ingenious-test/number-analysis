#ifndef ANALYSISTABLEMODEL_H

#define ANALYSISTABLEMODEL_H

#include <QAbstractItemModel>

#include "AnalysisCollection.h"

typedef QList<PointList> SequencePointList;
typedef QList<AnalysisResult> AnalysisResults;

class AnalysisTableModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    AnalysisTableModel(QObject *parent = 0);
    AnalysisTableModel(AnalysisCollection *colletions,
                       const SequencePointList &seq = SequencePointList(), QObject *parent = 0);
    AnalysisTableModel(const AnalysisTableModel& analysisTableModel);

    ~AnalysisTableModel();

    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const;
    QModelIndex parent(const QModelIndex &child) const;

    int rowCount(const QModelIndex &parent  = QModelIndex()) const;
    int columnCount(const QModelIndex &parent  = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;

    IDList getHeaders();
    void analyze();

    const AnalysisResults& Results();

    AnalysisCollection* analysisCollection();
    void setAnalysisCollection(AnalysisCollection* collection);

    const SequencePointList &sequencePointList();
    void addPointList(const PointList& pointList);
    void removePointList(const int index);

private:
    AnalysisResults results_;
    AnalysisCollection* collection_;
    SequencePointList seqPointList_;




};

Q_DECLARE_METATYPE(AnalysisTableModel)
Q_DECLARE_METATYPE(AnalysisResults)

#endif // ANALYSISTABLEMODEL_H
