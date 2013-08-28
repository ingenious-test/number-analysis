#ifndef ANALYSISTABLEMODEL_H

#define ANALYSISTABLEMODEL_H

#include <QAbstractItemModel>

#include "../mocs/MocPointListReader.h"

#include "AnalysisCollection.h"


class AnalysisTableModel : public QAbstractItemModel
{
    Q_OBJECT

    friend class TAnalysisTableModel;
    friend class AnalysisWindow;

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

    void sort(int column, Qt::SortOrder order = Qt::AscendingOrder);

    IDAnalysisList getHeaders() const;
    const IDList& getPointsIDs() const;

    const AnalysisResults& Results() const;
    void  setResults(const AnalysisResults& results);

    void addAnalysis(AbstractAnalysis *analysis);
    void removeAnalysis(const QString &id);

    void appendPointList(const ID& id);
    void appendPointList(const IDList& items);
    bool containsPointList(const ID& id) const;

    const int seqCount() const { return items_.count();}

    void setItemsCountOnPage(const int count);
    int pagesCount() const;
    const int currentPage() const;
    void setCurrentPage(const int page);


    static bool columnIDLessThan(const ID &s1, const ID &s2);
    static bool columnIDMoreThan(const ID &s1, const ID &s2);

protected slots:
    void analyzeAll();
    void analyze(const ID& item);

    static bool sortByAnalysisLessThan(const QPair<ID, double> &pair1,
                                const QPair<ID, double> &pair2);
    static bool sortByAnalysisMoreThan(const QPair<ID, double> &pair1,
                                       const QPair<ID, double> &pair2);

private:
    AnalysisResults results_;
    AnalysisCollection collection_;
    IDList items_;
    AbstractPointListReader *reader_;

    int currentPage_;
    int itemsCountOnPage_;

    void appendPointList_(const ID& id);

signals:
    void currentPageChanged();
    void itemsCountOnPageChanged();
    void dataChanged();
};

#endif // ANALYSISTABLEMODEL_H
