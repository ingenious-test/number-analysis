#include "AnalysisTableModel.h"



AnalysisTableModel::AnalysisTableModel(AbstractPointListReader *reader, const AnalysisCollection &colletions, QObject *parent):
    QAbstractItemModel(parent),
    collection_(colletions),
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
    return items_.size();
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

    IDAnalysisList listAnalysis = collection_.getNameList();

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
            return results_.value(listAnalysis.at(index.row())).value(items_.at(index.column() - 1),0);
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

    QStringList list = collection_.getNameList();

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

IDAnalysisList AnalysisTableModel::getHeaders()
{
    return collection_.getNameList();
}

void AnalysisTableModel::analyze(const ID &id)
{
    MocPointListReader reader(IDList() << ID("2"));

    PointList points = reader.read(id);

    qWarning() << points;
}

const AnalysisResults &AnalysisTableModel::Results()
{
    return results_;
}

const AnalysisCollection &AnalysisTableModel::analysisCollection()
{
    return collection_;
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
    if(id.isEmpty())
    {
        qWarning() << "ID not set";
        return;
    }

    if(!items_.contains(id))
    {
        items_.append(id);
        analyze(id);
        reset();
    }
    else
    {
        qWarning() << QString("ItemListModel contains ID: %1").arg(id);
    }
}

void AnalysisTableModel::appendPointList(const IDList &items)
{
    foreach(ID id, items)
    {
        appendPointList(id);
    }
}

bool AnalysisTableModel::containsPointList(const ID &id)
{
    return items_.contains(id);
}
