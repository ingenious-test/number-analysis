#ifndef ANALYSISTABLEMODEL_H

#define ANALYSISTABLEMODEL_H

#include <QAbstractItemModel>

#include "../mocs/MocPointListReader.h"

#include "AnalysisCollection.h"


class AnalysisTableModel : public QAbstractItemModel
{
    Q_OBJECT

    friend class TAnalysisTableModel;

public:
    AnalysisTableModel(AbstractPointListReader *reader,
                       QObject *parent = 0);

    ~AnalysisTableModel();

    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const;
    QModelIndex parent(const QModelIndex &child) const;

    int rowCount(const QModelIndex &parent  = QModelIndex()) const;
    int columnCount(const QModelIndex &parent  = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    QVariant headerData(int section, Qt::Orientation orientation = Qt::Horizontal, int role = Qt::DisplayRole) const;

    IDAnalysisList getHeaders() const;

    const AnalysisResults& Results() const;

    void addAnalysis(AbstractAnalysis *analysis);
    void removeAnalysis(const QString &id);

    void appendPointList(const ID& id);
    void appendPointList(const IDList& items);
    bool containsPointList(const ID& id) const;

protected slots:
    void analyzeAll();
    void analyze(const ID& item);

private:
    AnalysisResults results_;
    AnalysisCollection collection_;
    IDList items_;
    AbstractPointListReader *reader_;
};

#endif // ANALYSISTABLEMODEL_H
