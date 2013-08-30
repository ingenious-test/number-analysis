#include "AnalysisTableModel.h"



AnalysisTableModel::AnalysisTableModel(AbstractPointListReader *reader, QObject *parent):
    QAbstractItemModel(parent),
    reader_(reader)
{

}

AnalysisTableModel::~AnalysisTableModel()
{

}

QModelIndex AnalysisTableModel::index(int row, int column, const QModelIndex &parent) const
{
    return createIndex(row,column);
}

QModelIndex AnalysisTableModel::parent(const QModelIndex &child) const
{
    return QModelIndex();
}

int AnalysisTableModel::rowCount(const QModelIndex &parent) const
{
    return items_.count();
}

int AnalysisTableModel::columnCount(const QModelIndex &parent) const
{
    return collection_.size() + 1;
}

QVariant AnalysisTableModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
    {
        return QVariant();
    }

    IDAnalysisList listAnalysis = collection_.getIDList();

    if (role == Qt::DisplayRole)
    {
        if(index.column() == 0)
        {
            return items_.at(index.row());
        }
        else
        {
            if(results_.isEmpty())
            {
                return 0;
            }
            return results_.value(items_.at(index.row())).value(listAnalysis.at(index.column() - 1));
        }
    }
    else
    {
        return QVariant();
    }

    return QVariant();
}

QVariant AnalysisTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
    {
        return QVariant();
    }

    QStringList list = collection_.getIDList();

    if (orientation == Qt::Horizontal)
    {
        if(section == 0)
        {
            return QString("Идентификатор результата");
        }
        else
        {
            return list.at(section-1);
        }
    }

    if (orientation == Qt::Vertical)
    {
        return QString::number(section+1);
    }

    return QVariant();
}

bool AnalysisTableModel::columnIDLessThan(const ID &s1, const ID &s2)
{
    return s1 < s2;
}

bool AnalysisTableModel::columnIDMoreThan(const ID &s1, const ID &s2)
{
    return s1 > s2;
}

void AnalysisTableModel::sort(int column, Qt::SortOrder order)
{
    if(column == 0)
    {
        switch(order)
        {
        case Qt::AscendingOrder: qSort(items_.begin(), items_.end(), columnIDLessThan); break;
        case Qt::DescendingOrder: qSort(items_.begin(), items_.end(), columnIDMoreThan); break;
        }
    }
    else
    {
        const QString  sortingAnalysis = collection_.getIDAt(column - 1);

        QList< QPair<ID, double> > resultPairs;

        foreach(const ID& item, items_)
        {
            double result = 0.0;
            if(results_.contains(item))
            {
                if(results_.value(item).contains(sortingAnalysis))
                {
                    result = results_.value(item).value(sortingAnalysis);
                }
            }
            resultPairs.append(QPair<ID, double>(item, result));
        }

        switch(order)
        {
        case Qt::AscendingOrder: qSort(resultPairs.begin(), resultPairs.end(), sortByAnalysisLessThan); break;
        case Qt::DescendingOrder: qSort(resultPairs.begin(), resultPairs.end(), sortByAnalysisMoreThan); break;
        }

        IDList sortedItems;

        for(int i = 0; i < resultPairs.size(); ++i)
        {
            const QPair<ID, double> &pair = resultPairs.at(i);
            sortedItems << pair.first;
        }

        items_ = sortedItems;
    }

    reset();
}

IDAnalysisList AnalysisTableModel::getHeaders() const
{
    return collection_.getIDList();
}

const IDList &AnalysisTableModel::getPointsIDs() const
{
    return items_;
}

const AnalysisResults &AnalysisTableModel::Results() const
{
    return results_;
}

void AnalysisTableModel::setResults(const AnalysisResults &results)
{
    results_ = AnalysisResults(results);
}

void AnalysisTableModel::addAnalysis(AbstractAnalysis *analysis)
{
    collection_.addAnalysis(analysis);
    reset();
}

void AnalysisTableModel::removeAnalysis(const QString &id)
{
    removeAnalysis(id);
    reset();
}

void AnalysisTableModel::appendPointList(const ID &id)
{
    appendPointList_(id);
}

void AnalysisTableModel::appendPointList(const IDList &items)
{
    foreach(ID id, items)
    {
        appendPointList_(id);
    }
}

bool AnalysisTableModel::containsPointList(const ID &id) const
{
    return items_.contains(id);
}

void AnalysisTableModel::analyzeAll()
{
    results_.clear();

    foreach(const ID& item, items_)
    {
        analyze(item);
    }
}

void AnalysisTableModel::analyze(const ID &item)
{
    PointList pointList = reader_->read(item);
    AnalysisResult result = collection_.analyze(pointList);
    results_.insertInc(item, result);
    reset();
}

bool AnalysisTableModel::sortByAnalysisLessThan(const QPair<ID, double> &pair1,
                                                const QPair<ID, double> &pair2)
{
    return pair1.second < pair2.second;
}

bool AnalysisTableModel::sortByAnalysisMoreThan(const QPair<ID, double> &pair1,
                                                const QPair<ID, double> &pair2)
{
    return sortByAnalysisLessThan(pair2, pair1);
}

void AnalysisTableModel::appendPointList_(const ID &id)
{
    if(id.isEmpty())
    {
        qWarning() << "ID not set";
        return;
    }

    if(!items_.contains(id))
    {
        items_.append(id);
        reset();
    }
    else
    {
        qWarning() << QString("AnalysisTableModel contains ID: %1").arg(id);
    }
}

