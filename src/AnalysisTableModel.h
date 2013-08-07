#ifndef ANALYSISTABLEMODEL_H

#define ANALYSISTABLEMODEL_H

#include <QAbstractItemModel>

#include "AnalysisCollection.h"

class AnalysisTableModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    AnalysisTableModel(QObject *parent = 0);
    AnalysisTableModel(const AnalysisCollection &colletions,
                       const QList<PointList> &seq = QList<PointList>(), QObject *parent = 0);
    AnalysisTableModel(const AnalysisTableModel& analysisTableModel);

    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const;
    QModelIndex parent(const QModelIndex &child  = QModelIndex()) const;
    int rowCount(const QModelIndex &parent  = QModelIndex()) const;
    int columnCount(const QModelIndex &parent  = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role) const;

    const IDList getHeaders();
    QList<AnalysisResult> analyze();




};

Q_DECLARE_METATYPE(AnalysisTableModel)
Q_DECLARE_METATYPE(QList<AnalysisResult>)

#endif // ANALYSISTABLEMODEL_H
