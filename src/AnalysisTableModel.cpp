#include "AnalysisTableModel.h"

AnalysisTableModel::AnalysisTableModel(QObject *parent) :
    QAbstractItemModel(parent)
{

}

AnalysisTableModel::AnalysisTableModel(const AnalysisCollection& colletions, const SequencePointList &seq, QObject *parent):
    QAbstractItemModel(parent), collection_(colletions)
{

    seqPointList_ = seq;
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
    return seqPointList_.size();
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
        IDList listResults = seqPointList_.getIDs();
        if(index.column() == 0)
        {
            return listResults.at(index.row());
        }
        else
        {
            if(results_.isEmpty())
            {
                return 0;
            }
            return results_.value(listResults.at(index.row())).value(listAnalysis.at(index.column() - 1),0);
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

void AnalysisTableModel::analyze()
{
    if(collection_.size() > 0)
    {
        results_.clear();

        for(int i = 0; i < seqPointList_.size(); i++)
        {
            results_.insert(seqPointList_[i].id(), collection_.analyze(seqPointList_[i]));
        }

        reset();
    }
}

const AnalysisResults &AnalysisTableModel::Results()
{
    return results_;
}

const AnalysisCollection &AnalysisTableModel::analysisCollection()
{
    return collection_;
}

AnalysisTableModel &AnalysisTableModel::addAnalysis(AbstractAnalysis *analysis)
{
    collection_.addAnalysis(analysis);
    reset();
    return *this;
}

void AnalysisTableModel::removeAnalysis(const QString &name)
{
    removeAnalysis(name);
    reset();
}

void AnalysisTableModel::addPointList(const PointList &pointList)
{
    if(pointList.isSetID())
    {
        int index = containsPointList(pointList.id());
        if(index > -1)
        {
            removePointList(index);
            qWarning() << pointList.id() + " at " + QString::number(index) + " are replaced";
        }

        seqPointList_.append(pointList);
        idHash_.insert(pointList.id(), seqPointList_.size() - 1);

        reset();
    }
    else
    {
        qWarning() << "ID is not set";
    }
}

void AnalysisTableModel::removePointList(const ID &id)
{
    int index = containsPointList(id);
    if(index > -1)
    {
        removePointList(index);
    }
}

void AnalysisTableModel::removePointList(const int index)
{
    bool isValidIndex = (index > -1 && index) < (seqPointList_.size());
    if(isValidIndex)
    {
        idHash_.remove(seqPointList_[index].id());
        seqPointList_.removeAt(index);
        reset();
    }
}

int AnalysisTableModel::containsPointList(const ID& id)
{
    if(idHash_.contains(id))
    {
        return idHash_[id];
    }
    return -1;
}

int AnalysisTableModel::containsPointList(const PointList &pointList)
{
    return containsPointList(pointList.id());
}
