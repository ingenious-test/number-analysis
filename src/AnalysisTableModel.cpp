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

AnalysisCollection &AnalysisTableModel::addAnalysis(AbstractAnalysis *analysis)
{
    return collection_.addAnalysis(analysis);
}

void AnalysisTableModel::removeAnalysis(const QString &name)
{
    removeAnalysis(name);
}
