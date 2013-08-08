#include "AnalysisTableModel.h"
#include "QStandardItemModel"


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
    return results_.length();
}

int AnalysisTableModel::columnCount(const QModelIndex &parent) const
{
    return collection_.size();
}

QVariant AnalysisTableModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
    {
        return QVariant();
    }

    IDList list = collection_.getNameList();

    bool isValidColumn = (index.column() > -1) && (index.column() < list.length());

    if(!isValidColumn)
    {
        return QVariant();
    }

    if (role == Qt::DisplayRole)
    {
        return results_.at(index.row()).value(list.at(index.column()),0);
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

    bool isValidSection = (section > -1) && (section < list.length());

    if(!isValidSection)
    {
        return QVariant();
    }

    if (orientation == Qt::Horizontal)
    {
        return list.at(section);
    }

    if (orientation == Qt::Vertical)
    {
        return QString::number(section+1);
    }

    return QVariant();
}

IDList AnalysisTableModel::getHeaders()
{
    return collection_.getNameList();
}

void AnalysisTableModel::analyze()
{
    if(collection_.size() > 0)
    {
        results_.clear();
        foreach(PointList item, seqPointList_)
        {
            results_.append(collection_.analyze(item));
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

void AnalysisTableModel::clearAnalyses()
{
    collection_.removeAll();
}

const SequencePointList &AnalysisTableModel::sequencePointList()
{
    return seqPointList_;
}

void AnalysisTableModel::addPointList(const PointList &pointList)
{
    seqPointList_.append(pointList);
}

void AnalysisTableModel::removePointList(const int index)
{
    bool isValidIndex = (index > -1) && (index < seqPointList_.length());

    if(isValidIndex)
    {
        seqPointList_.removeAt(index);
    }
}
